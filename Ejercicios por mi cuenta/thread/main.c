#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hilo1(void *arg){
    printf("hola");
}
void *hilo2(void *arg){
    printf("Hola2");
}

int main(void){

   pthread_t h1, h2;

    pthread_create(&h1, NULL, hilo1, NULL);
    pthread_create(&h2, NULL, hilo2, NULL);

    pthread_join(h1,NULL);
    pthread_join(h2,NULL);

    return 0;
}
