//Projekt 1 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, marzec 2014

#include "LiczbaZespolona.h"
#include <cmath>
#include <iostream>

using namespace std;

bool LiczbaZespolona::konstrdestr = false;  //true - wyswietla konstruktory i destruktory, false - wylacza wyswietlanie

LiczbaZespolona::LiczbaZespolona(void)			//konstruktor domyslny, ustawia liczbe na 0 + 0i
{
	licznik_re = 0;
	licznik_im = 0;
	mianownik_re = 1;
	mianownik_im = 1;
	if(konstrdestr == true) cout << "KONTRUKTOR NA RZECZ LICZBY ZESPOLONEJ " << *this << endl;

}


LiczbaZespolona::LiczbaZespolona(int licznikre, int mianownikre, int licznikim, int mianownikim)   //konstruktor dwuargumentowy
{
	licznik_re = licznikre;
	licznik_im = licznikim;
	mianownik_im = mianownikim;
	mianownik_re = mianownikre;
	if(konstrdestr == true) cout << "KONTRUKTOR NA RZECZ LICZBY ZESPOLONEJ " << *this << endl;
}


LiczbaZespolona::~LiczbaZespolona(void)			//destruktor
{
	if(konstrdestr == true) cout << "DESTRUKTOR NA RZECZ LICZBY ZESPOLONEJ " << *this  << endl;
}

LiczbaZespolona LiczbaZespolona::operator+(const LiczbaZespolona& a)      //operacja dodawania liczb zespolonych
{
	LiczbaZespolona suma;
	suma.licznik_re = this->licznik_re * a.mianownik_re + this->mianownik_re * a.licznik_re;	//obliczanie licznika re
	suma.mianownik_re = this->mianownik_re * a.mianownik_re;									//obliczanie mianownika re
	suma.licznik_im = this->licznik_im * a.mianownik_im + this->mianownik_im * a.licznik_im;	//obliczanie licznika im
	suma.mianownik_im = this->mianownik_im * a.mianownik_im;									//obliczanie mianownika im
	
	suma.skracanie();						//skracanie ulamkow
	return suma;
}

LiczbaZespolona LiczbaZespolona::operator+=(const LiczbaZespolona& a)			//operacja += liczb zespolonych
{
	this->licznik_re = this->licznik_re * a.mianownik_re + this->mianownik_re * a.licznik_re;	//obliczanie licznika re
	this->mianownik_re = this->mianownik_re * a.mianownik_re;									//obliczanie mianownika re
	this->licznik_im = this->licznik_im * a.mianownik_im + this->mianownik_im * a.licznik_im;	//obliczanie licznika im
	this->mianownik_im = this->mianownik_im * a.mianownik_im;									//obliczanie mianownika im
	
	this->skracanie();								//skracanie ulamkow
	return *this;
}

LiczbaZespolona LiczbaZespolona::operator-(const LiczbaZespolona& a)		//operacja odejmowania liczb zespolonych
{
	LiczbaZespolona roznica;
	roznica.licznik_re = this->licznik_re * a.mianownik_re - this->mianownik_re * a.licznik_re;	//obliczanie licznika re
	roznica.mianownik_re = this->mianownik_re * a.mianownik_re;									//obliczanie mianownika re
	roznica.licznik_im = this->licznik_im * a.mianownik_im - this->mianownik_im * a.licznik_im;	//obliczanie licznika im
	roznica.mianownik_im = this->mianownik_im * a.mianownik_im;									//obliczanie mianownika im
	
	roznica.skracanie();					//skracanie ulamkow
	return roznica;
}

LiczbaZespolona LiczbaZespolona::operator-=(const LiczbaZespolona& a)			//-= liczb zespolonych
{
	this->licznik_re = this->licznik_re * a.mianownik_re - this->mianownik_re * a.licznik_re;	//obliczanie licznika re
	this->mianownik_re = this->mianownik_re * a.mianownik_re;									//obliczanie mianownika re
	this->licznik_im = this->licznik_im * a.mianownik_im - this->mianownik_im * a.licznik_im;	//obliczanie licznika im
	this->mianownik_im = this->mianownik_im * a.mianownik_im;									//obliczanie mianownika im
	
	this->skracanie();					//skracanie ulamkow
	return *this;
}

LiczbaZespolona LiczbaZespolona::operator*(const LiczbaZespolona& a)		//mnozenie liczb zespolonych
{
	LiczbaZespolona iloczyn;
	iloczyn.licznik_re = a.licznik_re * this->licznik_re * a.mianownik_im * this->mianownik_im - a.mianownik_re * a.licznik_im * this->licznik_im * this->mianownik_re;		//iloczyn licznika czesci rzeczywistej
	iloczyn.licznik_im = a.mianownik_re * a.licznik_im * this->licznik_re * this->mianownik_im + a.licznik_re * a.mianownik_im * this->licznik_im * this->mianownik_re;        //iloczyn licznika czesci urojonej
	iloczyn.mianownik_re = a.mianownik_re * a.mianownik_im * this->mianownik_re * this->mianownik_im; //iloczyn mianownika czesci rzeczywistej
	iloczyn.mianownik_im = iloczyn.mianownik_re; //iloczyn mianownika czesci urojonej
	
	iloczyn.skracanie();				//skracanie ulamkow
	return iloczyn;
}

LiczbaZespolona LiczbaZespolona::operator*=(const LiczbaZespolona& a)			//*= liczb zespolonych
{
	LiczbaZespolona temp;								//tymczasowy obiekt zeby moc z niego potem przepisac wartosc do a
	temp.licznik_re = a.licznik_re * this->licznik_re * a.mianownik_im * this->mianownik_im - a.mianownik_re * a.licznik_im * this->licznik_im * this->mianownik_re;		//iloczyn licznika czesci rzeczywistej
	temp.licznik_im = a.mianownik_re * a.licznik_im * this->licznik_re * this->mianownik_im + a.licznik_re * a.mianownik_im * this->licznik_im * this->mianownik_re;        //iloczyn licznika czesci urojonej
	temp.mianownik_re = a.mianownik_re * a.mianownik_im * this->mianownik_re * this->mianownik_im; //iloczyn mianownika czesci rzeczywistej
	temp.mianownik_im = temp.mianownik_re; //iloczyn mianownika czesci urojonej
	
	temp.skracanie();             //skracanie ulamka
	*this = temp;				//przypisanie temu obiektowi wartosci iloczynu
	return *this;
}


ostream& operator<<(ostream& out, const LiczbaZespolona& z)          //operator drukowania do strumienia liczby zespolonej
{
	out << "(" << z.licznik_re << "/" << z.mianownik_re << " , " << z.licznik_im << "/" << z.mianownik_im << ")";
	return out;							//zwraca co ma wypisac
}

double LiczbaZespolona::modul()					//wyznaczanie modulu liczby zespolonej
{
	double ModulLiczby;
	ModulLiczby = (double(licznik_re)/double(mianownik_re))*(double(licznik_re)/double(mianownik_re)) + (double(licznik_im)/double(mianownik_im))*(double(licznik_im)/double(mianownik_im));
	ModulLiczby = sqrt(ModulLiczby);		//wzor na modul
	return ModulLiczby;
}

int LiczbaZespolona::NWD(const int a, const int b)        //algorytm Hornera na NWD
{
    int pom;
	int temp1 = a, temp2 = b;
 
    while(temp2!=0)
    {
		pom = temp2;
		temp2 = temp1 % temp2;
		temp1 = pom;  
    }
 
    return temp1;
}

void LiczbaZespolona::skracanie()				//skracanie ulamka do najprostszej postaci
{
	int najwiekszydzielnik_re, najwiekszydzielnik_im;
	najwiekszydzielnik_re = NWD(this->licznik_re, this->mianownik_re);		//najwiekszy wspolny dzielnik w czesci rzeczywistej
	najwiekszydzielnik_im = NWD(this->licznik_im, this->mianownik_im);		//najwiekszy wspolny dzielnik w czesci urojonej


	if((najwiekszydzielnik_re !=1) && (najwiekszydzielnik_re !=0))			//jesli rozne od jeden to znaczy ze mozna skrocic ulamek
	{
		this->licznik_re = this->licznik_re / najwiekszydzielnik_re;			//skracanie
		this->mianownik_re = this->mianownik_re / najwiekszydzielnik_re;		//skracanie
		if(this->mianownik_re < 0)							//ustawienie zeby pokazywalo minus przy liczniku w wypadku liczby ujemnej
		{
			this->licznik_re = -(this->licznik_re);
			this->mianownik_re = -(this->mianownik_re);
		}
	}

	if((najwiekszydzielnik_im !=1) && (najwiekszydzielnik_im !=0))			//jesli rozne od jeden to znaczy ze mozna skrocic ulamek
	{
		this->licznik_im = this->licznik_im / najwiekszydzielnik_im;			//skracanie
		this->mianownik_im = this->mianownik_im / najwiekszydzielnik_im;		//skracanie
		if(this->mianownik_im < 0)						//ustawienie zeby pokazywalo minus przy liczniku w wypadku liczby ujemnej
		{
			this->licznik_im = -(this->licznik_im);
			this->mianownik_im = -(this->mianownik_im);
		}
	}
}