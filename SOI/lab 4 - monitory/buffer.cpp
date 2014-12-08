#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/shm.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>

void Buffer::push_buffer(char c)
{
	this->letter = c;
    this->size++;
}

bool Buffer::empty_buffer()
{
	if(this->size)
		return false;

	return true;
}


void Buffer::Producent(char ktory)
{
	enter();
	printf("\nProducent %c ---------WCHODZI-------- SEKCJA KRYTYCZNA============BEGIN PROD\n", ktory);
	if(empty_buffer())
	{
		push_buffer(rand()%26 + 65);	//losujemy literke
		printf("\nPRODUCENT %c WRZUCA LITERE ---------- %c\n",ktory, this->letter);
	}
	else
	{
		printf("\nPROUCENT %c - BUFOR PELNY - NIC NIE WRZUCAM\n", ktory);
	}

	printf("\nProducent %c ---------WYCHODZI------- SEKCJA KRYTYCZNA==============END PROD\n", ktory);
	leave();
}

void Buffer::Konsument(char ktory)
{
	MoznaCzytac.enter();
	ilosc_czytelnikow++;

	if(ilosc_czytelnikow == 1) enter();		//jesli to pierwszy czytelnik
	MoznaCzytac.leave();
	printf("\nILOSC CZYTELNIKOW: %d\n", ilosc_czytelnikow);
	printf("\nKonsument %c -------WEJSCIE---------- SEKCJA KRYTYCZNA\n", ktory);
	if(!empty_buffer())
	{
		printf("\nKONSUMENT %c ODCZYTAL LITERE -------- %c\n", ktory, letter);
	}
	else
	{
		printf("\nKONSUMENT %c - BUFOR PUSTY - NIC NIE WCZYTALEM\n", ktory);
	}
	MoznaCzytac.enter();
	ilosc_czytelnikow--;
	printf("\nILOSC CZYTELNIKOW: %d\n",ilosc_czytelnikow);
	if(ilosc_czytelnikow == 0)
	{
		this->letter = '\0';
		this->size = 0;
		leave();
	}
	MoznaCzytac.leave();
	printf("\nKonsument %c -------WYCHODZI--------- SEKCJA KRYTYCZNA\n", ktory);
}