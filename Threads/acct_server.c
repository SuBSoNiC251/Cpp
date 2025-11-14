// acct_server.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#define SOCKET_PATH "/tmp/acct.sock"
#define BACKLOG 8

static int account_balance = 1000;
static pthread_mutex_t balance_mtx = PTHREAD_MUTEX_INITIALIZER;

void *handle_client(void *arg) {
    int client_fd = *(int*)arg;
    free(arg);

    // protocol: client sends int32_t amounts (network byte order)
    int32_t net_amount;
    ssize_t r = read(client_fd, &net_amount, sizeof(net_amount));
    if (r != sizeof(net_amount)) {
        close(client_fd);
        return NULL;
    }

    int32_t amount = (int32_t)ntohl(net_amount);

    pthread_mutex_lock(&balance_mtx);
    if (amount < 0) {
        int withdraw = -amount;
        if (account_balance >= withdraw) {
            account_balance -= withdraw;
            dprintf(client_fd, "OK Withdrawal:%d NewBalance:%d\n", withdraw, account_balance);
        } else {
            dprintf(client_fd, "ERR Insufficient funds for withdrawal:%d\n", withdraw);
        }
    } else {
        account_balance += amount;
        dprintf(client_fd, "OK Deposit:%d NewBalance:%d\n", amount, account_balance);
    }
    pthread_mutex_unlock(&balance_mtx);

    close(client_fd);
    return NULL;
}

int main(void) {
    int server_fd, rc;
    struct sockaddr_un addr;

    unlink(SOCKET_PATH);
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    rc = bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    if (rc < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    rc = listen(server_fd, BACKLOG);
    if (rc < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    printf("acct_server: listening on %s, initial balance: %d\n", SOCKET_PATH, account_balance);

    while (1) {
        int *client_fd = malloc(sizeof(int));
        if (!client_fd) break;
        *client_fd = accept(server_fd, NULL, NULL);
        if (*client_fd < 0) {
            free(client_fd);
            if (errno == EINTR) continue;
            perror("accept");
            break;
        }

        pthread_t t;
        pthread_create(&t, NULL, handle_client, client_fd);
        pthread_detach(t);
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    pthread_mutex_destroy(&balance_mtx);
    return 0;
}
