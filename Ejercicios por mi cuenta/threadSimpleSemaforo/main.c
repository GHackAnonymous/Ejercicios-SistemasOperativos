#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int valor = 0;

void *rutina(void *arg){
    for(int i = 0; i<10; i++){
        printf("               Hola %d del hilo%d\n",i, (int*) arg);
        sleep((i+1)/2);
    }
	valor = 1;
}
void *rutina2(void *arg){
    for(int i = 0; i<30; i++){
        printf("Hola %d del hilo%d\n",i, (int*) arg);
        sleep(1);
    }
	valor = 2;
}

int main(){
    
    pthread_t h1, h2;
    
    pthread_create(&h1,NULL,rutina,(void*) 1);
    pthread_create(&h2,NULL,rutina2,(void*) 2);
    
    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    
}
