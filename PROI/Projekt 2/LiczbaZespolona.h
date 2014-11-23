//Projekt 2 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, kwiecien 2014

#ifndef LICZBAZESPOLONA_H_INCLUDED
#define LICZBAZESPOLONA_H_INCLUDED

#include <iostream>
using namespace std;

template <class T>
class LiczbaZespolona
{
private:
	T re, im;

public:
	static bool konstrdestr;					//ustawia czy ma wlaczyc czy wylaczyc pokazywanie konstruktorow i destruktorow

	
	LiczbaZespolona(void) : re(0.0), im(0.0)				//konstruktor bezargumentowy
	{
		if(konstrdestr == true) cout << "KONTRUKTOR NA RZECZ LICZBY ZESPOLONEJ " << *this << endl;
	}

	LiczbaZespolona(T rzecz, T uroj)   //konstruktor dwuargumentowy
	{
		re = rzecz;
		im = uroj;
		if(konstrdestr == true) cout << "KONTRUKTOR NA RZECZ LICZBY ZESPOLONEJ " << *this << endl;
	}

	~LiczbaZespolona(void)			//destruktor
	{
		if(konstrdestr == true) cout << "DESTRUKTOR NA RZECZ LICZBY ZESPOLONEJ " << *this  << endl;
	}

	LiczbaZespolona<T> operator+(const LiczbaZespolona<T>& a)      //operacja dodawania liczb zespolonych
	{
		LiczbaZespolona<T> suma;
		suma.re = this->re + a.re;
		suma.im = this->im + a.im;
		return suma;
	}

	LiczbaZespolona<T> operator+=(const LiczbaZespolona<T>& a)			//operacja += liczb zespolonych
	{
		this->re = this->re + a.re;
		this->im = this->im + a.im;
		return *this;
	}

	LiczbaZespolona<T> operator-(const LiczbaZespolona<T>& a)		//operacja odejmowania liczb zespolonych
	{
		LiczbaZespolona<T> roznica;
		roznica.re = this->re - a.re;
		roznica.im = this->im - a.im;
		return roznica;
	}


	LiczbaZespolona<T> operator-=(const LiczbaZespolona<T>& a)			//-= liczb zespolonych
	{
		this->re = this->re - a.re;
		this->im = this->im - a.im;
		return *this;
	}
	LiczbaZespolona<T> operator*(const LiczbaZespolona<T>& a)		//mnozenie liczb zespolonych
	{
		LiczbaZespolona<T> iloczyn;
		iloczyn.re = this->re * a.re - this->im * a.im;
		iloczyn.im = this->re * a.im + a.re * this->im;
		return iloczyn;
	}

	LiczbaZespolona<T> operator*=(const LiczbaZespolona<T>& a)			//*= liczb zespolonych
	{
		LiczbaZespolona<T> temp;								//tymczasowy obiekt zeby moc z niego potem przepisac wartosc do a
		temp.re = this->re * a.re - this->im * a.im;
		temp.im = this->re * a.im + a.re * this->im;

		*this = temp;				//przypisanie temu obiektowi wartosci iloczynu
		return *this;
	}

	bool operator==(LiczbaZespolona<T>& a)
	{
		if(re == a.re && im == a.im)
		{
			return true;
		}
		else
			return false;
	}

	T modul()					//wyznaczanie modulu liczby zespolonej
	{
		T ModulLiczby;
		ModulLiczby = this->re * this->re + this->im *this->im;
		ModulLiczby = sqrt(ModulLiczby);		//wzor na modul
		return ModulLiczby;
	}

	friend ostream& operator<<(ostream& out, const LiczbaZespolona<T>& z)          //operator drukowania do strumienia liczby zespolonej
	{
		out << "(" << z.re << " , " << z.im << ")";
		return out;							//zwraca co ma wypisac
	}

	void set(T rzecz, T uroj) //ustawia wartosc prywatnych zmiennych licznikow i mianownikow
	{
		re = rzecz;
		im = uroj;
	}            

};

#endif //LICZBAZESPOLONA_H_INCLUDED
