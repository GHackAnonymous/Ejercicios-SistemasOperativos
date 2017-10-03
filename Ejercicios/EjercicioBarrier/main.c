#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
//#include <signal.h>

int tareaEnBarrera = 0;

sem_t sVacio, sMutex, sExit;

int N = 3;
int x = 0;

void *rutinaEnBarrier(void *arg){
		
	sem_wait(&sVacio);
    sem_wait(&sMutex);
    
    printf("Semaforo sVacio y SMutex en rojo\n");
    
	//seccion critica

	printf("Valor de tarea en Barrier: %d\n",tareaEnBarrera);
	printf("Valor de x: %d\n",x);

	x = ++tareaEnBarrera;
	
	printf("Valor de x: %d\n",x);
	
	sem_post(&sMutex);

    if(x < N){
    	printf("El hilo %d espera en la barrera\n",arg);
		sem_wait(&sExit);
	}else{
		printf("Se abre la barrera\n");
		printf("Semaforo sVacio y SMutex en verde\n");
		
		//sem_post(&sExit, N-1);
		//signal(&sExit,N-1);
		
		int cnt = 0;
		for(cnt = 0; cnt < 3; cnt++){
			sem_post(&sExit);
		}
		//sem_post(&sExit);
		//sem_post(&sExit);
		//sem_post(&sExit);
		
	}
	
	printf("El hilo %d pasa la barrera\n",arg);
	
	sem_wait(&sMutex);
	
	x = --tareaEnBarrera;
	
	sem_post(&sMutex);
	
	if(x == 0){
		sem_post(&sVacio);
	}
}

int main()
{

    pthread_t h1, h2, h3;


    sem_init(&sVacio, 0, N);
    sem_init(&sMutex, 0, 1);
    sem_init(&sExit, 0, 0);

    pthread_create(&h1,NULL,rutinaEnBarrier,(void*) 1);
    pthread_create(&h2,NULL,rutinaEnBarrier,(void*) 2);
    pthread_create(&h3,NULL,rutinaEnBarrier,(void*) 3);

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);
    pthread_join(h3, NULL);

    printf("Finalizacion del programas. Limpiando...");

    sem_destroy(&h1);
  	sem_destroy(&h2);
   	sem_destroy(&h3);
   	
   	sleep(3);

}

/*

https://stackoverflow.com/questions/5282099/signal-handling-in-pthreads

*/
