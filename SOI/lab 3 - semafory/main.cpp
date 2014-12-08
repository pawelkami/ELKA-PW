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

//pamiec wspoldzielona
Semaphore sem_wylaczny_dostep(1);		//mowi ze producent moze wejsc
Semaphore sem_mutex(1);				

Buffer buf1;
Buffer *buf = &buf1;

int ilosc_czytelnikow = 0;


void* producer_A(void* ptr)
{
      while(1)
      {
        sem_wylaczny_dostep.p();  			//uzyskuje wylaczny dostep
	printf("\nProducent A ---------WCHODZI-------- SEKCJA KRYTYCZNA============BEGIN PROD\n");	
	if(empty_buffer(buf))
	{
		push_buffer(buf, rand()%26 + 65);	//losujemy literke	
		printf("\nPRODUCENT A WRZUCA LITERE ---------- %c\n", buf->letter);
	}
	else
	{
		printf("\nPROUCENT A - BUFOR PELNY - NIC NIE WRZUCAM\n");
	}

	printf("\nProducent A ---------WYCHODZI------- SEKCJA KRYTYCZNA==============END PROD\n");        
	sem_wylaczny_dostep.v();        		//oddaje wylaczny dostep

        /* spanie */      
        sleep(rand()%5);

      }   
        
      pthread_exit(NULL);     
}

void* producer_B(void* ptr)
{
      while(1)
      {      
	sem_wylaczny_dostep.p();			//uzyskuje wylaczny dostep  
	printf("\nProducent B ---------WCHODZI-------- SEKCJA KRYTYCZNA===========BEGIN PROD\n");	
	
	if(empty_buffer(buf))
	{
		push_buffer(buf, rand()%26 + 65);	//losujemy literke
		printf("\nPRODUCENT B WRZUCA LITERE ---------- %c", buf->letter);
	}
	else
	{
		printf("\nPRODUCENT B - BUFOR PELNY - PRODUCENT NIC NIE WRZUCA\n");
	}
	
	printf("\nProducent B ---------WYCHODZI------- SEKCJA KRYTYCZNA============END PROD\n");        
	sem_wylaczny_dostep.v();        		//oddaje wylaczny dostep
        /* spanie */      
        sleep(rand()%5);

      }   
        
      pthread_exit(NULL);     
}

void* consumer_1(void* ptr)
{
      while(1) 
      {  
        sem_mutex.p();
	ilosc_czytelnikow++; 

	if(ilosc_czytelnikow == 1) sem_wylaczny_dostep.p();		//jesli to pierwszy czytelnik
        sem_mutex.v();
	printf("\nILOSC CZYTELNIKOW: %d\n", ilosc_czytelnikow);          
	printf("\nKonsument A -------WEJSCIE---------- SEKCJA KRYTYCZNA\n");
	if(!empty_buffer(buf))
	{
		printf("\nKONSUMENT A ODCZYTAL LITERE -------- %c\n", buf->letter);	
	}
	else
	{
		printf("\nKONSUMENT A - BUFOR PUSTY - NIC NIE WCZYTALEM\n");                          
        }
	sem_mutex.p();
	ilosc_czytelnikow--;
	printf("\nILOSC CZYTELNIKOW: %d\n", ilosc_czytelnikow);
	if(ilosc_czytelnikow == 0) 
	{
		buf->letter = '\0';
		buf->size = 0;
		sem_wylaczny_dostep.v();
	}
	sem_mutex.v();
	printf("\nKonsument A -------WYCHODZI--------- SEKCJA KRYTYCZNA\n");
        /* spanie */          
        sleep(rand()%5);
      } 
        
      pthread_exit(NULL);        
}

void* consumer_2(void* ptr)
{
      while(1) 
      {  
        sem_mutex.p();							//uzyskanie wylacznego dostepu do zmiennej ilosc_czytelnikow
	ilosc_czytelnikow++;						//o jednego czytelnika wiecej 
	if(ilosc_czytelnikow == 1) sem_wylaczny_dostep.p();		//jesli to pierwszy czytelnik
	sem_mutex.v();
	printf("\nILOSC CZYTELNIKOW: %d\n", ilosc_czytelnikow);        	//oddaje wylaczny dostep do "ilosc_czytelnikow"
	printf("\nKonsument B -------WEJSCIE---------- SEKCJA KRYTYCZNA\n");
	if(!empty_buffer(buf))
	{
		printf("\nKONSUMENT B ODCZYTAL LITERE -------- %c\n", buf->letter);   //dostep do danych
        }
	else
	{
		printf("\nKONSUMENT B - BUFOR PUSTY - NIC NIE ODCZYTAL\n");
	}
	sem_mutex.p();

	ilosc_czytelnikow--;						//jeden czytelnik mniej
	printf("\nILOSC CZYTELNIKOW: %d\n", ilosc_czytelnikow);
	if(ilosc_czytelnikow == 0) 
	{
		buf->letter = '\0';
		buf->size = 0;
		sem_wylaczny_dostep.v();		//jesli ostatni czytelnik to wychodzi
	}
	sem_mutex.v();
	printf("\nKonsument B -------WYCHODZI--------- SEKCJA KRYTYCZNA\n");
        
	/* spanie */      
	sleep(rand()%5);
	}

	pthread_exit(NULL);
} 

int main()
{
    pthread_t threadA, threadB, thread1, thread2;
    srand(time(NULL));
   
    init_buffer(buf);       
    
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
