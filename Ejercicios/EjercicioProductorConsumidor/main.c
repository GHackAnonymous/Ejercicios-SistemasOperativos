#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int valor[2];

sem_t sMe,sC,sP;

void *rutinaProductor(void *arg)
{
    sem_wait(&sMe);
}
void *rutinaConsumidor(void *arg)
{
    for(int i = 0; i<30; i++)
    {
        printf("Hola %d del hilo%d\n",i, (int*) arg);
        sleep(1);
    }
    valor = 2;
}

int main()
{

    pthread_t hP1, hP2, hC1;

    int sem_init(&sMe, 0, 1);
    int sem_init(&sC, 0, 1);
    int sem_init(&sP, 0, 2);

    pthread_create(&hP1,NULL,rutina,(void*) "hiloProductor1");
    pthread_create(&hP2,NULL,rutina2,(void*) "hiloProductor2");
    pthread_create(&hC2,NULL,rutina2,(void*) "hiloConsumidor1");

    pthread_join(hP1, NULL);
    pthread_join(hP2, NULL);
    pthread_join(hC1, NULL);

    printf("Finalizacion del programas. Limpiando...");

    sem_destroy(&hP1);
    sem_destroy(&hP2);
    sem_destroy(&hC1);

}
