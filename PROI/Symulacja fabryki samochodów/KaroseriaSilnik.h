//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef KAROSERIASILNIK_H_INCLUDED
#define KAROSERIASILNIK_H_INCLUDED

#include <iostream>
#include "dane.h"
#include "OponaKaroseria.h"
#include "Silnik.h"
#include <queue>
#include <Windows.h>

using namespace std;


class KaroseriaSilnik 				//6 na grafie - montuje silniki w pomalowanej karoserii z oponami
	: private Silnik, 
	  private Karoseria,
	  private Opona
{
private:
	OponaKaroseria opokar;
	Silnik sil;

public:
	queue<OponaKaroseria> kolejka_opokar;		//kolejka pomalowanych karoserii z oponami
	queue<Silnik> kolejka_silnik;				//kolejka silnikow

	virtual KaroseriaSilnik montaz()			//montuje silniki w karoserii z oponami
	{
		if(kolejka_opokar.empty() || kolejka_silnik.empty())			//jesli kolejka pusta rzuc wyjatek
			throw 0;
		
		if(!kolejka_opokar.empty())		//na wszelki wypadek
		{
			opokar = kolejka_opokar.front();	//wyciaga z kolejki
			kolejka_opokar.pop();		//usuwa element z kolejki
		}
		if(!kolejka_silnik.empty())		//na wszelki wypadek
		{
			sil = kolejka_silnik.front();		//wyciaga z kolejki
			kolejka_silnik.pop();		//usuwa element z kolejki
		}
		Sleep(1500);
		
		cout << "Zamontowano silnik " << sil << " w " << opokar << endl;
		fout << "Zamontowano silnik " << sil << " w " << opokar << endl;
		
		return *this;
	}

	friend ostream& operator<<(ostream& out, const KaroseriaSilnik& z)          //operator drukowania do strumienia
	{
		out << z.opokar << " z silnikiem " << z.sil;
		return out;							//zwraca co ma wypisac
	}

};

#endif