//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef SAMOCHOD_H_INCLUDED
#define SAMOCHOD_H_INCLUDED

#include <iostream>
#include <queue>
#include "dane.h"
#include <string>
#include <windows.h>
#include <cstdlib>
#include "Opona.h"
#include "KaroseriaSilnik.h"


using namespace std;

class Samochod				//7 na grafie - stanowisko montuj¹ce elektronikê w pomalowanej karoserii z silnikiem i oponami
	: private Silnik,
	  private Karoseria,
	  private Opona		
{
private:
	KaroseriaSilnik karsil;

public:
	queue<KaroseriaSilnik> kolejka;
	Samochod montaz()
	{
		if(kolejka.empty())			//jesli kolejka pusta to wyrzuc wyjatek
			throw 0;
		
		if(!kolejka.empty())	//na wszelki wypadek
		{	
			karsil = kolejka.front();			//wyciaga z kolejki karoserie z silnikiem
			kolejka.pop();		//usuwa element ktory wczytalo z kolejki
		}
		Sleep(1500);
		    
		HANDLE hOut;
		hOut = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hOut, 6 );				//kolor zolty tekstu kiedy zakonczy sie robic samochod
		cout << "Zamontowano elektronike w " << karsil << ". Samochod ukonczony." << endl;
		SetConsoleTextAttribute(hOut, 7);		//powrot na biala czcionke
		fout << "Zamontowano elektronike w " << karsil << ". Samochod ukonczony." << endl;
		
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Samochod& z)          //operator drukowania do strumienia
	{
		out << "Samochod " << z.karsil;
		return out;							//zwraca co ma wypisac
	}
};

#endif