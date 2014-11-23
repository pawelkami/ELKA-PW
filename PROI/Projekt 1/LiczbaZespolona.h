//Projekt 1 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, marzec 2014

#ifndef LICZBAZESPOLONA_H_INCLUDED
#define LICZBAZESPOLONA_H_INCLUDED

#include <iostream>
using namespace std;

class LiczbaZespolona
{
private:
	int licznik_re, licznik_im, mianownik_re, mianownik_im;
	
public:
	LiczbaZespolona(void);							//konstruktor bezargumentowy
	LiczbaZespolona(int,int,int,int);				//konstruktor dwuargumentowy
	~LiczbaZespolona(void);

	LiczbaZespolona operator+(const LiczbaZespolona&);									//dodawanie
	LiczbaZespolona operator+=(const LiczbaZespolona&);									//dodawanie
	LiczbaZespolona operator-(const LiczbaZespolona&);									//odejmowanie
	LiczbaZespolona operator-=(const LiczbaZespolona&);									//-=
	LiczbaZespolona operator*(const LiczbaZespolona&);									//mnozenie
	LiczbaZespolona operator*=(const LiczbaZespolona&);									//*=
	double modul(void);																	//modul liczby zespolonej
	friend ostream& operator<<(ostream&, const LiczbaZespolona&);						//drukowanie do strumienia

	void set(int licz_re, int mian_re, int licz_im, int mian_im) 
	{
		licznik_re = licz_re; 
		mianownik_re = mian_re; 
		licznik_im = licz_im; 
		mianownik_im = mian_im; 
	}            //ustawia wartosc prywatnych zmiennych licznikow i mianownikow
	static bool konstrdestr;					//ustawia czy ma wlaczyc czy wylaczyc pokazywanie konstruktorow i destruktorow
	void skracanie();
	int NWD(const int, const int);					//NWD dwoch liczb, algorytm Euklidesa
};

#endif //LICZBAZESPOLONA_H_INCLUDED
