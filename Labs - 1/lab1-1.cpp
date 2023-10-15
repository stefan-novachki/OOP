// Lab 1 - 1

#include <stdio.h>

typedef struct Transaction {
    int id;
    int sum;
    int provizija;
    int kreditna;
} Transaction;

int main() {
    int n;
    int i;
    scanf("%d", &n);
    int flag = 0;

    Transaction t;
    Transaction transakcii[100];

    for (i = 0; i < n; i++) {
        scanf("%d %d %d %d", &t.id, &t.sum, &t.provizija, &t.kreditna);
        if (t.kreditna == 1) {
            transakcii[flag] = t;
            flag++;
        }
    }

    if (flag == 0) {
        printf("No credit card transaction");
    } else {
        for (i = 0; i < flag; i++) {
            printf("%d %d\n", transakcii[i].id, transakcii[i].sum + transakcii[i].provizija);
        }
    }

    return 0;
}