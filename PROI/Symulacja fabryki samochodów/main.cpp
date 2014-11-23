//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "watki.h"	
#include <process.h>			//_beginthread
#include <iomanip>			//setw
#include "Opona.h"
#include "Karoseria.h"
#include "PomalowanaKaroseria.h"
#include "OponaKaroseria.h"
#include "Silnik.h"
#include "KaroseriaSilnik.h"
#include <Windows.h>

#define _CRT_SECURE_NO_DEPRECATE

using namespace std;

void menu()
{
	cout << "Co chcesz teraz zrobic?" << endl;
	cout << "1. Wypisz stworzone samochody." << endl;
	cout << "2. Zakoncz program." << endl;
}


int main()
{
	cout << "Car Factory Simulation v1.1 - Pawel Kaminski, Politechnika Warszawska 2014" << endl;
	fout.open("output.txt");				//otwarcie pliku ktory zapisuje przebieg dzialania fabryki
	fout_kol.open("kolejki.txt");			//otwarcie pliku ktory zapisuje stan kolejek
	if(!fout.good() || !fout_kol.good())
	{
		cout << "Nie udalo sie otworzyc pliku!!!"<< endl;
		return 0;
	}

	srand( time( NULL ) );
	cout << "Podaj liczbe samochodow, ktore maja zostac utworzone: ";

	while(scanf_s("%d", &liczba_samochodow) != 1) //dopóki nie uda siê wczytaæ
	{
		//ew. komunikat b³êdu
		int c;
		while((c = getchar()) != '\n' && c != EOF); //pêtla wyci¹gaj¹ca znaki z bufora
	}

	int i0 = 0;			//do wywolywania _beginthread - lista argumentow
	int i1 = 1;			//
	int i2 = 2;			//
	int i3 = 3;			//


	//**********************WYWOLYWANIE WATKOW DO KAZDEGO STANOWISKA*********************
	_beginthread(thread_produkcja_opon,0, &i0);				//watki produkujace opony
	Sleep(130);												//Sleep zeby opoznic troche wywolanie watku, zeby sie na siebie
	_beginthread(thread_produkcja_opon,0, &i1);				//nie nakladaly poniewaz wtedy wystepuja bledy
	Sleep(140);												//(np. dwie funkcje w tej samej chwili oprozniaja ta sama kolejke
	_beginthread(thread_produkcja_opon,0, &i2);				//a jest w niej tylko jeden element - wyjatek nie zostaje zgloszony bo
	Sleep(120);												//dzieje sie to juz po sprawdzeniu czy kolejka jest pusta)
	_beginthread(thread_produkcja_opon,0, &i3);				//
	Sleep(100);												//
	_beginthread(thread_produkcja_karoserii,0, &i0);		//watki produkujace karoserie
	Sleep(110);												//
	_beginthread(thread_produkcja_karoserii,0, &i1);		//
	Sleep(220);												//
	_beginthread(thread_produkcja_silnika,0, &i0);			//watki produkujace silniki
	Sleep(100);												//
	_beginthread(thread_produkcja_silnika,0, &i1);			//
	Sleep(100);												//
	_beginthread(thread_malowanie_karoserii,0, &i0);		//watki malujace karoserie
	Sleep(100);												//
	_beginthread(thread_malowanie_karoserii,0, &i1);		//
	Sleep(100);												//
	_beginthread(thread_montowanie_opon_w_karoserii,0, &i0);//watki montujace opony w karoserii
	Sleep(150);												//
	_beginthread(thread_montowanie_opon_w_karoserii,0, &i1);//
	Sleep(200);												//
	_beginthread(thread_montowanie_silnika_w_karoserii,0, &i0);	//watki montujace silnik w karoserii
	Sleep(110);													//
	_beginthread(thread_montowanie_silnika_w_karoserii,0, &i1); //
	Sleep(120);													//
	
	HANDLE hThread[2];
	hThread[0] =( HANDLE ) _beginthread( thread_montowanie_elektroniki_w_karoserii, 0, &i0 );	//montowanie elektroniki w karoserii
	Sleep(110);																						//czyli ostatnie stanowisko
	hThread[1] =( HANDLE ) _beginthread( thread_montowanie_elektroniki_w_karoserii, 0, &i1 );	//
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);		//czeka az skoncza sie watki montowania elektroniki w samochodzie
	//*************************************************************************************************
	
	cout << "KONIEC SYMULACJI! WYKONANO WSZYSTKIE SAMOCHODY!" << endl;				//komunikat o koncu symulacji
	fout << "KONIEC SYMULACJI! WYKONANO WSZYSTKIE SAMOCHODY!" << endl;				//komunikat do pliku o koncu symulacji
	
	
	bool temp = true;		//mowi czy ma wlaczyc menu czy nie
	while(temp)
	{
		menu();			//wyswietla menu
		int wybor;
		while(scanf_s("%d", &wybor) != 1) //dopóki nie uda siê wczytaæ
		{
			//ew. komunikat b³êdu
			int c;
			while((c = getchar()) != '\n' && c != EOF); //pêtla wyci¹gaj¹ca znaki z bufora
		}
		
		switch(wybor)
		{
			case 1:
				cout << "Utworzono samochody:" << endl;
				for(int i =0; i < wektor_utworzonych_samochodow.size();i++)
				{
					cout << setw(3) << i+1 << ". " << wektor_utworzonych_samochodow[i] << endl;
					fout << setw(3) << i+1 << ". " << wektor_utworzonych_samochodow[i] << endl;
				}
				break;

			case 2:
				cout << "Koniec programu. Milego dnia :)" << endl;
				fout.close();
				fout_kol.close();
				temp = false;
				system("pause");
				return 0;
		}
	}

}