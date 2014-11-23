//Projekt 3 - maj 2014 - student: Pawe� Kami�ski - grupa 2I3 - prowadz�cy Piotr Wito�ski
//SYMULACJA FABRYKI SAMOCHOD�W
#ifndef SILNIK_H_INCLUDED
#define SILNIK_H_INCLUDED

#include <iostream>
#include "dane.h"
#include <Windows.h>

using namespace std;


class Silnik 				//5 na grafie - stanowisko produkuj�ce silniki
{
private:
	string silniczek;

public:
	Silnik produkcja()			//produkuje silnik
	{
		Sleep(2000);		//odczekuje pewien czas
		silniczek = silniki[rand() % 5];		//losuje jaki silnik
		cout << "Wykonano silnik " << silniczek << endl;
		fout << "Wykonano silnik " << silniczek << endl;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Silnik& z)          //operator drukowania do strumienia
	{
		out << z.silniczek;
		return out;							//zwraca co ma wypisac
	}
};

#endif