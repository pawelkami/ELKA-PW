//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef KAROSERIA_H_INCLUDED
#define KAROSERIA_H_INCLUDED

#include <iostream>
#include "dane.h"


using namespace std;

class Karoseria 				//2 na grafie - stanowisko produkujace karoserie
{
private:
	string karoseria;
public:
	virtual Karoseria produkcja()		//funkcja produkuj¹ca karoserie
	{
		Sleep(2000);		//odczekuje pewien czas
		karoseria = karoserie[rand() % 9];	//losuje jakas karoserie
		cout << "Wykonano karoserie dla samochodu typu " << karoseria << endl;
		fout << "Wykonano karoserie dla samochodu typu " << karoseria << endl;		//zapisuje do pliku
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Karoseria& k)          //operator drukowania do strumienia
	{
		out << k.karoseria;
		return out;							//zwraca co ma wypisac
	}
};

#endif