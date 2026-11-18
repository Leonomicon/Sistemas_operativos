#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FILOSOFOS 5

pthread_mutex_t tenedores[NUM_FILOSOFOS];

void* filosofo(void* arg) {
    int id = *((int*)arg);
    int izq = id;
    int der = (id + 1) % NUM_FILOSOFOS;

    for (int i = 0; i < 3; i++) {
        printf("Filosofo %d esta pensando\n", id);

        if (id % 2 == 0) {
            pthread_mutex_lock(&tenedores[izq]);
            pthread_mutex_lock(&tenedores[der]);
        } else {
            pthread_mutex_lock(&tenedores[der]);
            pthread_mutex_lock(&tenedores[izq]);
        }

        printf("Filosofo %d esta comiendo\n", id);

        pthread_mutex_unlock(&tenedores[izq]);
        pthread_mutex_unlock(&tenedores[der]);
    }

    return NULL;
}

int main() {
    pthread_t hilos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&tenedores[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_destroy(&tenedores[i]);
    }

    return 0;
}
