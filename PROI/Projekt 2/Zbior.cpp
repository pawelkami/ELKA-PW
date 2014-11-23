//Projekt 2 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, kwiecien 2014

#include "Zbior.h"
#include <iostream>
#include <cstring>

int Zbior::licznik_statyczny = 0;

Zbior::Zbior(void)		//konstruktor domyslny
{
	tablica = new LiczbaZespolona<double>[1];		//stworzenie nowej tablicy o wymiarze 1
	wymiar = 1;
	elementow_w_zbiorze = 0;
	++licznik_statyczny;
}


Zbior::~Zbior(void)		//destruktor
{
	if(tablica)			//tablica != NULL
		delete[] tablica;			//zwalnianie pamieci zajetej przez tablice
	--licznik_statyczny;
}

void Zbior::dodaj(const LiczbaZespolona<double> &nowy)   //dodawanie elementu do zbioru
{
	if(elementow_w_zbiorze + 1 == wymiar)			//jesli doszlismy do konca wymiaru tablicy i trzeba ja powiekszyc
	{
		wymiar *= 2;		//zwiekszenie wymiaru tablicy dwukrotnie
		LiczbaZespolona<double>* temp = new LiczbaZespolona<double>[wymiar];	//tworzenie tymczasowej tablicy o nowym wymiarze
		
		memcpy(temp, tablica, wymiar*sizeof(LiczbaZespolona<double>));	//kopiowanie tablicy do tymczasowej	
		temp[elementow_w_zbiorze] = nowy;		//dodawanie nowego elementu do tablicy tymczasowej
		delete[] tablica;
		tablica = temp;		//przypisanie wskaznika na tablice tymczasowa do naszej glownej tablicy
	}
	else
	{
		tablica[elementow_w_zbiorze] = nowy;	//dodaje nowy element na koniec zbioru
	}
	elementow_w_zbiorze++;
}

ostream& operator<<(ostream& out, Zbior& zbior)			//wypisywanie zbioru
{
	out << "Liczba elementow w zbiorze: " << zbior.elementow_w_zbiorze << endl;
	for(int i = 0; i < zbior.elementow_w_zbiorze; i++)
	{
		out << zbior.tablica[i] << endl;
	}
		out << "\n";		//enter
	return out;
}

bool Zbior::operator==(Zbior &z)		//porownywanie zbiorow
{
	bool temp = false;				//pomocniczy bool
	if (elementow_w_zbiorze != z.elementow_w_zbiorze)		//jesli sa rozne liczby elementow to zbiory nie sa rowne
		return false;
	for(int i = 0; i < elementow_w_zbiorze; i++)			//poszukiwanie takich samych elementow w obu zbiorach
	{
		temp = false;
		for(int j = 0; j < elementow_w_zbiorze; j++)
		{
			if(tablica[i] == z.tablica[j])		//jesli znalezlismy taki sam element to przerywamy petle
			{
				temp = true;
				break;
			}
		}
		if(temp == false) return false;			//nie znaleziono takiego samego elementu w drugim zbiorze
	}
	return true;
}

bool Zbior::operator!=(Zbior& z)
{
	return !(*this == z);		//jesli nie sa rowne to zwroc true
}

Zbior Zbior::operator+(const Zbior &z)		//dodawanie zbiorow
{
	Zbior suma;

	for(int i = 0; i < elementow_w_zbiorze; i++)     //dodaje elementy z pierwszego zbioru
	{
		suma.dodaj(tablica[i]);
	}
	for(int j = 0; j < z.elementow_w_zbiorze; j++)		//dodaje elementy z drugiego zbioru
	{
		suma.dodaj(z.tablica[j]);
	}
	return suma;
}

Zbior Zbior::operator-(const Zbior &z)		//odejmuje zbiory
{
	Zbior roznica;
	bool temp = false;
	for(int i = 0; i < elementow_w_zbiorze; i++)  //szuka takich samych elementow w obu zbiorach
	{
		temp = false;
		for(int j = 0; j < z.elementow_w_zbiorze; j++)
		{
			if(tablica[i] == z.tablica[j])	//jesli znajdzie taki sam element w obu zbiorach to go nie dodaje do nowego zbioru
			{
				temp = true;
				break;
			}
		}
		if (!temp) roznica.dodaj(tablica[i]);  //jesli nie znajdzie w drugim zbiorze takiego elementu to go dodaje do nowego zbioru
	}
	return roznica;
}


Zbior& Zbior::operator=(const Zbior &z)			//operator przypisania poniewaz bywaly bledy przy przepisywaniu
{
	delete [] tablica;
	elementow_w_zbiorze = z.elementow_w_zbiorze;
    wymiar = z.wymiar;
    tablica = new LiczbaZespolona<double>[wymiar];
	memcpy(tablica, z.tablica, wymiar*sizeof(LiczbaZespolona<double>));  //przepisywanie tablicy z jednej do drugiej

    return *this;
}
