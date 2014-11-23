//Projekt 2 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, kwiecien 2014

#ifndef ZBIOR_H_INCLUDED
#define ZBIOR_H_INCLUDED

#include "LiczbaZespolona.h"


class Zbior
{
private:
	LiczbaZespolona<double>* tablica;		//wskaznik na pierwszy element tablicy dynamicznej
public:
	Zbior(void);
	~Zbior(void);
	
	Zbior& operator=(const Zbior& z);	//operator przypisania, poniewaz od czasu do czasu pojawialy sie bledy przy przypisaniu

	void dodaj(const LiczbaZespolona<double> &nowy);	//dodawanie elementow do zbioru
	friend ostream& operator<<(ostream& out, Zbior& z);
	bool operator==(Zbior &z);	
	bool operator!=(Zbior &z);
	Zbior operator+(const Zbior &z);
	Zbior operator-(const Zbior &z);

	static int licznik_statyczny;
	
	int elementow_w_zbiorze;		//liczba elementow w zbiorze
	int wymiar;			//wymiar tablicy dynamicznej
};

#endif

