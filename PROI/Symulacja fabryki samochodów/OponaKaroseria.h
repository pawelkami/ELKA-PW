//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef OPONAKAROSERIA_H_INCLUDED
#define OPONAKAROSERIA_H_INCLUDED


#include <iostream>
#include <queue>
#include "Opona.h"
#include "PomalowanaKaroseria.h"
#include "dane.h"

using namespace std;


class OponaKaroseria 				//4 na grafie - stanowisko montuj¹ce opony w pomalowanej karoserii
	: private Opona, private Karoseria
{
private:
	PomalowanaKaroseria pomkar;				//pomalowana karoseria ktora montuje
	Opona opon;								//opony ktore montuje

public:
	queue<Opona> kolejka_opony;			//kolejka od stanowiska produkujacego opony
	queue<PomalowanaKaroseria> kolejka_pomkar;		//kolejka od stanowiska malujacego karoserie

	virtual OponaKaroseria montaz()			//montuje opony w karoserii
	{
		if(kolejka_opony.empty())			//jesli pusta kolejka to rzuc wyjatek
		{
			throw 0;
		}
		if(kolejka_pomkar.empty())
		{
			throw 0;
		}
		
		if(!kolejka_pomkar.empty())
		{					
			pomkar = kolejka_pomkar.front();	//wyciaga z kolejki pomalowana karoserie
			kolejka_pomkar.pop();		//usuwa z kolejki wyciagniety element
		}
		
		if(!kolejka_opony.empty())
		{
			opon = kolejka_opony.front();	//wyciaga z kolejki opony
			kolejka_opony.pop();		//usuwa z kolejki wyciagniete opony
		}
		Sleep(1000);		//odczekuje pewien czas
		cout << "Zamontowano opony " << opon << " do " << pomkar << endl;
		fout << "Zamontowano opony " << opon << " do " << pomkar << endl;

		return *this;
	}

	friend ostream& operator<<(ostream& out, const OponaKaroseria& z)          //operator drukowania do strumienia
	{
		out << z.pomkar << " z oponami " << z.opon << " ";
		return out;							//zwraca co ma wypisac
	}
};

#endif