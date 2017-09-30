#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 5
#define MAX_PRODUCTS  10
#define N_PRODUCERS 2

typedef struct s_Buffer
{
  int head;
  int tail;
  int numElems;
  float buffer[MAX_BUFFER_SIZE];
}FIFO,*PFIFO;

FIFO fifo;
sem_t  sMe, sP, sC;

void* producersFunction(void*);
void* ConsumersFunction(void*);
void initFIFOandSems(void);
void cleanSems(void);

int main()
{
  pthread_t idProducer[N_PRODUCERS];
  pthread_t idConsumer;
  char str[128];
  int i;
  

  initFIFOandSems();
  for(i=0;i<N_PRODUCERS;i++) pthread_create(&idProducer[i],NULL,producersFunction,(void*)NULL);
  pthread_create(&idConsumer,NULL,ConsumersFunction,(void*)NULL);
  for(i=0;i<N_PRODUCERS;i++) pthread_join(idProducer[i],NULL);
  pthread_join(idConsumer,NULL);
  cleanSems();
  printf("type \"Return\" to finish\n");
  fgets(str,sizeof(str),stdin); 
  return 0;
}

void* producersFunction(void* arg)
{
  float f=1;;
  int i;

  for(i=0;i<MAX_PRODUCTS;i++)
  {
    //sleep(1);
    sem_wait(&sP);
    sem_wait(&sMe);
    fifo.buffer[fifo.head]=f;
    fifo.head=(fifo.head+1)%MAX_BUFFER_SIZE;
    fifo.numElems++;
    sem_post(&sMe);
    sem_post(&sC);
    f+=15;
  }
  return NULL;
}

void* ConsumersFunction(void* arg)
{
  float f;
  int i;
  
  for(i=0;i<N_PRODUCERS*MAX_PRODUCTS;i++)
  {                     
    sleep(1);
    sem_wait(&sC);
    sem_wait(&sMe);
    f=fifo.buffer[fifo.tail];
    fifo.tail=(fifo.tail+1)%MAX_BUFFER_SIZE;
    fifo.numElems--;
    sem_post(&sP);
    sem_post(&sMe);
    printf("Consuming %f\n",f);
  }
  return NULL;
}

void initFIFOandSems(void)
{
  fifo.head=fifo.tail=fifo.numElems=0;
  sem_init(&sMe, 0, 1);
  sem_init(&sP, 0, MAX_BUFFER_SIZE);
  sem_init(&sC, 0, 0);
}

void cleanSems(void)
{
  sem_destroy(&sMe);
  sem_destroy(&sP);
  sem_destroy(&sC);
}