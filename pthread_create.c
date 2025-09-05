#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_DE_HILOS 5

void* imprimir_hola_mundo(void *arg){
    int id = *(int *)arg;
    printf("Hola mundo, Soy el hilo %d\n", id);
    return NULL;
}

int main(){
    pthread_t hilos[NUMERO_DE_HILOS];
    int ids[NUMERO_DE_HILOS];

    for(int i = 0; i < NUMERO_DE_HILOS; i++){
        ids[i] = 1;
        printf("Main creando el hilo %d\n", i);
        if(pthread_create(&hilos[i], NULL, imprimir_hola_mundo, &ids[i]) != 0){
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    for(int i = 0; i < NUMERO_DE_HILOS; i++){
        pthread_join(hilos[i], NULL);
    }


    printf("Main: Todos los hilos han terminado\n");
    return 0;
}