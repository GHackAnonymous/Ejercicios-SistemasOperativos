#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int valor[2];
int cnt;

sem_t sMe,sC,sP;

void *rutinaProductor(void *arg)
{
    //while(1)
    for(int i = 0; i<10;i++)
    {
        sem_wait(&sP);
        sem_wait(&sMe);
        //seccion critica


        if(cnt < 2 ){

            valor[cnt] = rand();

            printf("El hilo %d a metido el numero es: %d\n",(int)arg,valor[cnt]);
            printf("CNT: %d\n",cnt);

            cnt++;
            printf("CNT: %d\n",cnt);
        }
        sem_post(&sMe);
        sem_post(&sC);
    }
    printf("Salgo rutina hilo %d\n",(int)arg);
}
void *rutinaConsumidor(void *arg)
{
    //while(1)
    for(int i = 0; i<20;i++)
    {

        printf("Valor de i: %d\n",i);

        sem_wait(&sC);
        sem_wait(&sMe);
        //seccion critica


        if(cnt <= 2 ){
            cnt--;
            printf("                         El hilo %d a sacado el numero es: %d\n",(int)arg,valor[cnt]);
            printf("                         CNT: %d\n",cnt);


            printf("                         CNT: %d\n",cnt);
       }
        sem_post(&sMe);
        sem_post(&sP);
    }
    printf("                                 Salgo rutina hilo %d\n",(int)arg);
}

int main()
{

    pthread_t hP1, hP2, hC1;

    srand(10);

    sem_init(&sMe, 0, 1);
    sem_init(&sC, 0, 0);
    sem_init(&sP, 0, 2);

    pthread_create(&hP1,NULL,rutinaProductor,(void*) 1);
    pthread_create(&hP2,NULL,rutinaProductor,(void*) 2);
    pthread_create(&hC1,NULL,rutinaConsumidor,(void*) 3);

    pthread_join(hP1, NULL);
    pthread_join(hP2, NULL);
    pthread_join(hC1, NULL);

    printf("Finalizacion del programas. Limpiando...");

    sem_destroy(&hP1);
    sem_destroy(&hP2);
    sem_destroy(&hC1);

}
