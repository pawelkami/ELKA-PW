//Projekt 3 - maj 2014 - student: Pawe� Kami�ski - grupa 2I3 - prowadz�cy Piotr Wito�ski
//SYMULACJA FABRYKI SAMOCHOD�W
#ifndef POMALOWANAKAROSERIA_H_INCLUDED
#define POMALOWANAKAROSERIA_H_INCLUDED

#include <iostream>
#include "dane.h"
#include "Karoseria.h"
#include <queue>


using namespace std;


class PomalowanaKaroseria 			//3 - stanowisko malujace karoserie
	: private Karoseria
{
private:
	string kolorek;
	Karoseria kar;

public:
	queue<Karoseria> kolejka;		//kolejka oczekujacych Karoserii
	virtual PomalowanaKaroseria malowanie(void)			//
	{
		kolorek = kolory[rand() % 9];
		if(kolejka.empty())
		{
			throw 0;
		}
		if(!kolejka.empty())
		{
			kar = kolejka.front();
			kolejka.pop();
		}
		Sleep(1500);
		cout << "Pomalowano " << kar << " na kolor " << kolorek << endl;
		fout << "Pomalowano " << kar << " na kolor " << kolorek << endl;			//wypisuje do pliku

		return *this;
	}

	friend ostream& operator<<(ostream& out, const PomalowanaKaroseria& z)          //operator drukowania do strumienia 
	{
		out << "karoseria " << z.kar << " kolor " << z.kolorek;
		return out;							//zwraca co ma wypisac
	}
};

#endif