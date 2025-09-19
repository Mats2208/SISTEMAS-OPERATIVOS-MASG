#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 5

int bufer [ N ];
int count = 0;
int in = 0, out = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *productor(void *arg) {
    int item;
    while (1) {
        item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        bufer[in] = item;
        in = (in + 1) % N;
        count++;
        printf("Productor produjo: %d, Elementos en buffer: %d\n", item, count);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1); 
    }
}

void *consumidor(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        item = bufer[out];
        out = (out + 1) % N;
        count--;
        printf("Consumidor consumió: %d, Elementos en buffer: %d\n", item, count);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}

    int main(){
        pthread_t prod, cons;
        sem_init(&empty, 0, N);
        sem_init(&full, 0, 0);
        pthread_mutex_init(&mutex, NULL);
        
        pthread_create(&prod, NULL, productor, NULL);
        pthread_create(&cons, NULL, consumidor, NULL);
        
        pthread_join(prod, NULL);
        pthread_join(cons, NULL);
        
        sem_destroy(&empty);
        sem_destroy(&full);
        pthread_mutex_destroy(&mutex);
        
        return 0;
    }
