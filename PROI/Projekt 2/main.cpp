//Projekt 2 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, kwiecien 2014

#include <iostream>
#include "LiczbaZespolona.h"
#include "Zbior.h"
#include <cstdio>

#define _CRT_SECURE_NO_DEPRECATE  //bo Visual Studio nie lubi scanfa


using namespace std;

void wyswietlmenu()
{
	cout << "MultiCmplxZbior v1.2 - Pawel Kaminski, Politechnika Warszawska 2014\n"
		 << "1. Dodaj dwa zbiory\n"
		 << "2. Odejmij dwa zbiory\n"
		 << "3. Porownaj zbiory (==)\n"
		 << "4. Porownaj zbiory (!=)\n"
		 << "5. Dodaj element do pierwszego zbioru\n"
		 << "6. Dodaj element do drugiego zbioru\n"
		 << "7. Wypisz zbiory\n"
		 << "8. Wlacz pokazywanie konstruktorow i destruktorow liczb zespolonych\n"
		 << "0. Wyjdz z programu\n" << endl;
	cout << "Liczba utworzonych obiektow: " << Zbior::licznik_statyczny << endl;
}
template<class T>
bool LiczbaZespolona<T>::konstrdestr = false;

int main()
{
	LiczbaZespolona<double> z1;
	Zbior zbiorek1, zbiorek2, zbiorek3;
	double rzecz, uroj;
	bool menu = true;

	do{
		wyswietlmenu();
		int wybor;
		while(true)
		{
			if(scanf("%d", &wybor) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
			{
				while(getchar() != '\n'); //wyciaga znaki z bufora
			}
			else
				break;
		}

		switch(wybor)
		{
			case 1:
				zbiorek3 = zbiorek1 + zbiorek2;
				cout << "Zbiory zostaly dodane\n\n";
				break;

			case 2:
				zbiorek3 = zbiorek1 - zbiorek2;
				cout << "Zbiory zostaly odjete\n\n";
				break;

			case 3:
				if(zbiorek1 == zbiorek2)
				{
					cout << "Zbiory sa rowne\n\n";
				}
				else
				{
					cout << "Zbiory nie sa rowne\n\n";
				}
				break;

			case 4:
				if(zbiorek1 != zbiorek2)
				{
					cout << "Zbiory nie sa rowne\n\n";
				}
				else
				{
					cout << "Zbiory sa rowne\n\n";
				}
				break;

			case 5:
				cout << "Podaj czesc rzeczywista liczby: ";
				while(true)
				{
					if(scanf("%lf", &rzecz) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
					{
						cout << "Bledne dane, wprowadz czesc rzeczywista jeszcze raz: ";
						while(getchar() != '\n'); //wyciaga znaki z bufora
					}
					else
						break;
				}
				cout << "Podaj czesc urojona liczby: ";
				while(true)
				{
				if(scanf("%lf", &uroj) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz czesc urojona jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
				}
				z1.set(rzecz, uroj);
				zbiorek1.dodaj(z1);
				break;

			case 6:
				cout << "Podaj czesc rzeczywista liczby: ";
				while(true)
				{
					if(scanf("%lf", &rzecz) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
					{
						cout << "Bledne dane, wprowadz czesc rzeczywista jeszcze raz: ";
						while(getchar() != '\n'); //wyciaga znaki z bufora
					}
					else
						break;
				}
				cout << "Podaj czesc urojona liczby: ";
				while(true)
				{
				if(scanf("%lf", &uroj) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz czesc urojona jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
				}
				z1.set(rzecz, uroj);
				zbiorek2.dodaj(z1);
				break;

			case 7:
				cout << "Pierwszy zbior:\n" << zbiorek1;
				cout << "Drugi zbior:\n" << zbiorek2;
				cout << "Trzeci zbior:\n" << zbiorek3;
				break;

			case 8:
				if(LiczbaZespolona<double>::konstrdestr == true) LiczbaZespolona<double>::konstrdestr = false;        // ustawia zmienna czy ma wyswietlac konstruktory i destruktory
				else LiczbaZespolona<double>::konstrdestr = true;
				break;

			case 0:
				menu = false;
				break;
		}

	}while(menu);

	return 0;
}
