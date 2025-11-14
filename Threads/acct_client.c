// acct_client.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/acct.sock"

struct tx_args {
    int32_t amount;
};

void *perform_transaction(void *arg) {
    struct tx_args *t = (struct tx_args*)arg;

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return NULL;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(sock);
        return NULL;
    }

    int32_t net_amount = htonl(t->amount);
    if (write(sock, &net_amount, sizeof(net_amount)) != sizeof(net_amount)) {
        perror("write");
        close(sock);
        return NULL;
    }

    char buf[256];
    ssize_t n = read(sock, buf, sizeof(buf)-1);
    if (n > 0) {
        buf[n] = '\0';
        printf("Client tx %d -> Server: %s", t->amount, buf);
    } else {
        if (n == 0) printf("Client tx %d -> No reply\n", t->amount);
        else perror("read");
    }

    close(sock);
    return NULL;
}

int main(void) {
    pthread_t threads[6];
    struct tx_args txs[6] = { {200}, {-100}, {500}, {-300}, {150}, {-400} };

    for (int i = 0; i < 6; ++i) {
        pthread_create(&threads[i], NULL, perform_transaction, &txs[i]);
    }
    for (int i = 0; i < 6; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
