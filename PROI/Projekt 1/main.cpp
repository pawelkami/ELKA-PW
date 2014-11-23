//Projekt 1 - student Pawe³ Kamiñski - 2I3 - prowadzacy laboratorium Piotr Witonski - Politechnika Warszawska, marzec 2014

#define _CRT_SECURE_NO_DEPRECATE  //bo Visual Studio nie lubi scanfa

#include <iostream>
#include <cstdio>
#include "LiczbaZespolona.h"

using namespace std;

void wyswietlmenu()
{
	cout << "\nCmplx Numbers 1.0 - author Pawel Kaminski, Politechnika Warszawska 2014\n"
		 << "1. Dodaj do siebie liczby zespolone(+)\n"
		 << "2. Dodaj jedna do drugiej (+=)\n"
		 << "3. Odejmij od siebie liczby zespolone (-)\n"
		 << "4. Odejmij jedna od drugiej (-=)\n"
		 << "5. Pomnoz dwie liczby zespolone (*)\n"
		 << "6. Pomnoz jedna liczbe zespolona przez druga (*=)\n"
		 << "7. Wyznacz modul liczby zespolonej\n"
		 << "8. Wprowadz nowe liczby zespolone\n"
		 << "9. Wlacz/wylacz pokazywanie konstruktorow i destruktorow\n"
		 << "10. Pokaz aktualne liczby\n"
		 << "0. Wyjdz z programu\n" << endl;	
}

int main()
{
	LiczbaZespolona z1,z2,z3;
	LiczbaZespolona::konstrdestr = false;    //false - wylaczone pokazywanie konstruktorow i destruktorow
	bool menu = true;
	int licznik_rzecz, licznik_uroj, mianownik_rzecz, mianownik_uroj;		//potrzebne przy wprowadzaniu liczb zespolonych

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
		case 1:                                     //dodawanie
			z3 = z1 + z2;
			cout << "Wynik to " << z3 << endl;
			break;

		case 2:										//dodawanie +=
			z1+=z2;
			cout << "Wynik to " << z1 << endl;
			break;

		case 3:										//odejmowanie
			z3 = z1 - z2;
			cout << "Wynik to " << z3 << endl;
			break;

		case 4:										//odejmowanie -=
			z1-=z2;
			cout << "Wynik to " << z1 << endl;
			break;

		case 5:
			z3 = z1 * z2;							//mnozenie *
			cout << "Wynik to " << z3 << endl;
			break;

		case 6:
			z1*=z2;									//mnozenie *=
			cout << "Wynik to " << z1 << endl;
			break;

		case 7:
			cout << "Modul liczby " << z1 << ":\t" << z1.modul() << endl;
			cout << "Modul liczby " << z2 << ":\t" << z2.modul() << endl;
			cout << "Modul liczby " << z3 << ":\t" << z3.modul() << endl;
			break;

		case 8:
			cout << "\nWprowadzanie nowych liczb zespolonych: " << endl;
			cout << "Wprowadz pierwsza liczbe\n"
				 << "Licznik czesci rzeczywistej: ";
				while(true)
				{
					if(scanf("%d", &licznik_rzecz) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
					{
						cout << "Bledne dane, wprowadz licznik czesci rzeczywistej jeszcze raz: ";
						while(getchar() != '\n'); //wyciaga znaki z bufora
					}
					else
						break;
				}
						
				cout << "Mianownik czesci rzeczywistej: ";
				while(true)
				{
					if(scanf("%d", &mianownik_rzecz) != 1 || (mianownik_rzecz == 0))   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
					{
						cout << "Bledne dane, wprowadz mianownik czesci rzeczywistej jeszcze raz: ";
						while(getchar() != '\n'); //wyciaga znaki z bufora
					}
					else
						break;
				}
			cout << "Licznik czesci urojonej: ";
			while(true)
			{
				if(scanf("%d", &licznik_uroj) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz licznik czesci urojonej jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
			}

			cout << "Mianownik czesci urojonej: ";
			while(true)
			{
				if(scanf("%d", &mianownik_uroj) != 1 || (mianownik_uroj == 0))   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz mianownik czesci urojonej jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
			}
			z1.set(licznik_rzecz, mianownik_rzecz, licznik_uroj, mianownik_uroj);				//ustawia wartosc z1
			z1.skracanie();							//skraca ulamki


			cout << "Wprowadz druga liczbe\n"
				 << "Czesc rzeczywista: ";
			while(true)
			{
				if(scanf("%d", &licznik_rzecz) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz licznik czesci rzeczywistej jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
			}
						
			cout << "Mianownik czesci rzeczywistej: ";
			while(true)
				{
					if(scanf("%d", &mianownik_rzecz) != 1 || (mianownik_rzecz == 0))   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
					{
						cout << "Bledne dane, wprowadz mianownik czesci rzeczywistej jeszcze raz: ";
						while(getchar() != '\n'); //wyciaga znaki z bufora
					}
					else
						break;
				}
			cout << "Licznik czesci urojonej: ";
			while(true)
			{
				if(scanf("%d", &licznik_uroj) != 1)   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz licznik czesci urojonej jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
			}

			cout << "Mianownik czesci urojonej: ";
			while(true)
			{
				if(scanf("%d", &mianownik_uroj) != 1 || (mianownik_uroj == 0))   //jesli nie udalo sie wczytac to wchodzi do if i wprowadza sie ponownie dane
				{
					cout << "Bledne dane, wprowadz mianownik czesci urojonej jeszcze raz: ";
					while(getchar() != '\n'); //wyciaga znaki z bufora
				}
				else
					break;
			}

			z2.set(licznik_rzecz, mianownik_rzecz, licznik_uroj, mianownik_uroj);             //ustawia wartosc z2
			z2.skracanie();
			break;

		case 9:
			if(LiczbaZespolona::konstrdestr == true) LiczbaZespolona::konstrdestr = false;        // ustawia zmienna czy ma wyswietlac konstruktory i destruktory
			else LiczbaZespolona::konstrdestr = true;
			break;

		case 10:
			cout << "z1: " << z1 << endl;						//wypisuje liczby zespolone
			cout << "z2: " << z2 << endl;
			cout << "z3: " << z3 << endl;
			break;

		case 0:
			menu = false;							//wylacza menu
			cout << "Dziekuje za skorzystanie z programu!\nDo zobaczenia! :)" << endl;
			break;
		}
	} while(menu == true);             //wyswietla dopoki menu jest true
	
	return 0;
}