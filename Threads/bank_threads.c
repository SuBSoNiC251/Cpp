#include <stdio.h>
#include <pthread.h>

#define N 6  // Use #define instead of const int

int account_balance = 1000;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* perform_transaction(void* arg) {
    int amount = *(int*)arg;
    pthread_mutex_lock(&mtx);
    if (amount < 0) {
        int w = -amount;
        if (account_balance >= w)
            account_balance -= w, printf("Withdrawal: %d | New Balance: %d\n", w, account_balance);
        else
            printf("Withdrawal: %d | Insufficient funds.\n", w);
    } else {
        account_balance += amount;
        printf("Deposit: %d | New Balance: %d\n", amount, account_balance);
    }
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(void) {
    pthread_t th[N];
    int txns[N] = {200, -100, 500, -300, 150, -400};

    for (int i = 0; i < N; ++i)
        pthread_create(&th[i], NULL, perform_transaction, &txns[i]);

    for (int i = 0; i < N; ++i)
        pthread_join(th[i], NULL);

    printf("Final Account Balance: %d\n", account_balance);
    pthread_mutex_destroy(&mtx);
    return 0;
}