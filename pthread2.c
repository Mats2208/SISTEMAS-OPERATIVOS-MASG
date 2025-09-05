#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_HILOS 4
#define TAM_ARREGLO 16

int arreglo[TAM_ARREGLO];
int suma_parcial[NUM_HILOS];

void *sumar(void *arg){
    int id = *(int *) arg;
    int inicio = id * (TAM_ARREGLO / NUM_HILOS);
    int fin = inicio + (TAM_ARREGLO / NUM_HILOS);
    int suma = 0;

    for(int i = inicio; i < fin; i++){
        suma += arreglo[i];
    }

    suma_parcial[id] = suma;
    pthread_exit(NULL);
}

int main(){
    pthread_t hilos[NUM_HILOS];
    int suma_total = 0;

    for(int i = 0; i < TAM_ARREGLO; i++){
        arreglo[i] = i + 1; 
    }
    int ids[NUM_HILOS];
    for(int i = 0; i < NUM_HILOS; i++){
        ids[i] = i;
        if (pthread_create(&hilos[i], NULL, sumar, &ids[i]) != 0){
            perror("Error al crear el hilo");
            exit(1);
        }
    }

    for(int i = 0; i < NUM_HILOS; i++){
        pthread_join(hilos[i], NULL);
        suma_total += suma_parcial[i];
    }

    printf("La suma total del arreglo es: %d\n", suma_total);
    return 0;
}