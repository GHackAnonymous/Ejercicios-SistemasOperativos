#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


sem_t theSemaphore;

void* threadMainFunction(void*);

int main()
{
  int i;
  pthread_t idT1, idT2, idT3;
  
  
  sem_init(&theSemaphore, 0, 1);
  pthread_create(&idT1, NULL, threadMainFunction, (void*) NULL);
  pthread_create(&idT2, NULL, threadMainFunction, (void*) NULL);
  pthread_create(&idT3, NULL, threadMainFunction, (void*) NULL);
  
  pthread_join (idT1, NULL);
  pthread_join (idT2, NULL);
  pthread_join (idT3, NULL);
  printf("Threads finished. Main going to finish \n");
  sem_destroy(&theSemaphore);
  return 0;
}

void *threadMainFunction(void *arg)
{
  int i;
  
  for (i=0;i<10;i++)
  {
    sem_wait(&theSemaphore);
    printf("thread in Critical Section\n");
    printf("thread going out from Critical Section\n");
    sleep(1);
    sem_post(&theSemaphore);
    
  }
  return NULL;
}
