#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t sem_empty;
sem_t sem_full;
pthread_mutex_t mutex;

void* productor(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = (id * 100) + i;

        sem_wait(&sem_empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Productor %d produjo el elemento %d en el indice %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_full);
    }
    return NULL;
}

void* consumidor(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&sem_full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumidor %d consumio el elemento %d del indice %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_empty);
    }
    return NULL;
}

int main() {
    pthread_t productores[2];
    pthread_t consumidores[2];
    int id_productores[2] = {1, 2};
    int id_consumidores[2] = {1, 2};

    sem_init(&sem_empty, 0, BUFFER_SIZE);
    sem_init(&sem_full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_create(&productores[i], NULL, productor, &id_productores[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_create(&consumidores[i], NULL, consumidor, &id_consumidores[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(productores[i], NULL);
        pthread_join(consumidores[i], NULL);
    }

    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
