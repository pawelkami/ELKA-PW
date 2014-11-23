//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef OPONA_H_INCLUDED
#define OPONA_H_INCLUDED

#include <iostream>
#include "dane.h"


using namespace std;

class Opona 				//1
{
private:
	string opony;

public:
	virtual Opona produkcja(void)			//produkuje opony
	{
		Sleep(2000);				//odczekuje jakis czas i po nim opony sa stworzone
		opony = oponki[rand() % 9];
		cout << "Wykonano opony " << opony << endl;
		fout << "Wykonano opony " << opony << endl;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Opona& o)          //operator drukowania do strumienia
	{
		out << o.opony;
		return out;							//zwraca co ma wypisac
	}
};

#endif