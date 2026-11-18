#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void* contar(void* arg) {
    int id = *((int*)arg);
    for (int i = 1; i <= 10000; i++) {
        if (i < 4000 || i > 6000) {
            sem_wait(&sem);
            printf("Hilo %d: %d\n", id, i);
            sem_post(&sem);
        } else {
            if (i == 4000) {
                sem_wait(&sem);
            }
            printf("Hilo %d: %d\n", id, i);
            if (i == 6000) {
                sem_post(&sem);
            }
        }
    }
    return NULL;
}

int main() {
    pthread_t hilo1, hilo2;
    int id1 = 1;
    int id2 = 2;

    sem_init(&sem, 0, 1);

    pthread_create(&hilo1, NULL, contar, &id1);
    pthread_create(&hilo2, NULL, contar, &id2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    sem_destroy(&sem);

    return 0;
}
