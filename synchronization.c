#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define N 5   // number of producers & consumers

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < 5; i++) {
        int item = rand() % 100;

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d produced: %d\n", id, item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(rand() % 3);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("\t\tConsumer %d consumed: %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    pthread_t prod[N], cons[N];
    int id[N];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&prod[i], NULL, producer, &id[i]);
        pthread_create(&cons[i], NULL, consumer, &id[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}







