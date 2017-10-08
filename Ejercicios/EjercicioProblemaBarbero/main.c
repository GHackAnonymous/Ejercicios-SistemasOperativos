#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sSilla, sEntra, sAsientoBarbero, sBarbero, sBarberoTerminado;

void *rutinaClinete(void *arg){
	printf("Inicio rutina cliente %d en la puerta\n",(int)arg);
	sem_wait(&sEntra);
	printf("      El cliente %d entra\n",(int) arg);
    sem_wait(&sSilla);
	printf("      El cliente %d se sienta\n",(int) arg);
	sem_wait(&sAsientoBarbero);
    printf("      El cliente %d se sienta el la silla barbero\n",(int) arg);
	sem_post(&sSilla);
	
	//avisa al barbero
	printf("      El cliente %d Avisa al barbero\n",(int)arg);

	sem_post(&sBarbero);
	printf("toque al barbero\n");
	sem_wait(&sBarberoTerminado);
	printf("      El cliente %d paga y se va\n",(int) arg);
	sem_post(&sEntra);
    
}

void *tareaBarbero(void *arg){
	printf("                          Inicio rutina barbero\n");
	int i;
	for(i = 0; i<9;i++){
		sem_wait(&sBarbero);
	printf("               Barbero empieza ha cortar la barba\n");
	sleep(3);
	printf("               Barba cortada\n");
	sem_post(&sBarberoTerminado);
	sem_post(&sAsientoBarbero);
	}
	
	
	printf("                          Rutina barbero fin\n");
}

int main()
{

	printf("Creo hilos\n");

    pthread_t hC1, hC2, hC3, hC4, hC5, hC6, hC7, hC8, hC9;
	pthread_t hB;
	
	printf("Creo semaforos\n");

	sem_init(&sSilla, 0, 2);
	sem_init(&sEntra, 0, 6);
	sem_init(&sAsientoBarbero, 0, 1);
	sem_init(&sBarbero, 0, 0);
	sem_init(&sBarberoTerminado, 0, 0);

	printf("Asocio rutina a hilo\n");
	
    pthread_create(&hC1,NULL,rutinaClinete,(void*) 1);
    pthread_create(&hC2,NULL,rutinaClinete,(void*) 2);
    pthread_create(&hC3,NULL,rutinaClinete,(void*) 3);
	pthread_create(&hC4,NULL,rutinaClinete,(void*) 4);
    pthread_create(&hC5,NULL,rutinaClinete,(void*) 5);
    pthread_create(&hC6,NULL,rutinaClinete,(void*) 6);
	pthread_create(&hC7,NULL,rutinaClinete,(void*) 7);
    pthread_create(&hC8,NULL,rutinaClinete,(void*) 8);
    pthread_create(&hC9,NULL,rutinaClinete,(void*) 9);
	pthread_create(&hB,NULL,tareaBarbero,(void*) 0);
	
	printf("Pongo para ver la ejecucion de los hilos\n");

    pthread_join(hC1, NULL);
    pthread_join(hC2, NULL);
    pthread_join(hC3, NULL);
	pthread_join(hC4, NULL);
    pthread_join(hC5, NULL);
    pthread_join(hC6, NULL);
	pthread_join(hC7, NULL);
    pthread_join(hC8, NULL);
    pthread_join(hC9, NULL);
	pthread_join(hB, NULL);

    printf("Finalizacion del programas. Limpiando...\n");

    sem_destroy(&hC1);
  	sem_destroy(&hC2);
   	sem_destroy(&hC3);
	sem_destroy(&hC4);
  	sem_destroy(&hC5);
   	sem_destroy(&hC6);
	sem_destroy(&hC7);
  	sem_destroy(&hC8);
   	sem_destroy(&hC9);
	sem_destroy(&hB);
   	
   	sleep(3);

}