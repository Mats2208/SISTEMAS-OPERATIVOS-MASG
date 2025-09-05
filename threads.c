#include <pthread.h>
#include <stdio.h>

void* imprimir(void* arg){
    printf("Hola mundo desde el hilo\n");
    return NULL;
}

int main(){
    pthread_t hilo;
    pthread_create(&hilo, NULL, imprimir, NULL);
    pthread_join(hilo, NULL);
    return 0;
}