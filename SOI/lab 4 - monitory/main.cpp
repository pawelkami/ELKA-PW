#include <iostream>
#include "monitor.h"
#include "buffer.h"

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include <math.h>
#include <time.h>

Buffer *buf;


void* producer_A(void* ptr)
{
    while(1)
    {
        buf->Producent('A');
        /* spanie */
        sleep(rand()%5);

    }

    pthread_exit(NULL);
}

void* producer_B(void* ptr)
{
    while(1)
    {
        buf->Producent('B');
        /* spanie */
        sleep(rand()%5);
    }

    pthread_exit(NULL);
}

void* consumer_1(void* ptr)
{
    while(true)
    {
        buf->Konsument('A');
        /* spanie */
        sleep(rand() % 5);
    }


    pthread_exit(NULL);
}

void* consumer_2(void* ptr)
{
    while(1)
    {
        buf->Konsument('B');
        /* spanie */
        sleep(rand()%5);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threadA, threadB, thread1, thread2;
    srand(time(NULL));

    buf = new Buffer();

    pthread_create(&threadA, NULL, producer_A, NULL);
    pthread_create(&threadB, NULL, producer_B, NULL);
    pthread_create(&thread1, NULL, consumer_1, NULL);
    pthread_create(&thread2, NULL, consumer_2, NULL);

    pthread_join(threadA,(void**)NULL);
    pthread_join(threadB,(void**)NULL);
    pthread_join(thread1,(void**)NULL);
    pthread_join(thread2,(void**)NULL);

    return 0;
}