//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef WATKI_H_INCLUDED
#define WATKI_H_INCLUDED


#include <iostream>
#include "Samochod.h"
#include <process.h>
#include <cstdlib>
#include "Opona.h"
#include "Karoseria.h"
#include "PomalowanaKaroseria.h"
#include "OponaKaroseria.h"
#include "Silnik.h"
#include "KaroseriaSilnik.h"
#include <vector>

using namespace std;


Opona ogumienie[4];						//4 stanowiska produkujace opony
Silnik motorek[2];						//2 stanowiska produkujace silnik
Karoseria karo[2];						//2 stanowiska produkujace karoseria
PomalowanaKaroseria kolorkar[2];		//2 stanowiska malujace karoserie
OponaKaroseria oponakaroseria[2];		//2 stanowiska montujace opony w karoserii
KaroseriaSilnik karoseriasilnik[2];		//2 stanowiska montujace silnik w karoserii
Samochod elektronika[2];				//2 stanowiska montujace elektronike - samochod ukonczony

vector<Samochod> wektor_utworzonych_samochodow;			//ida tam ukonczone samochody zeby mozna bylo je pozniej wypisac

int liczba_samochodow;					//liczba samochodow ktore bedzie trzeba stworzyc
int liczba_opon = 0;					//liczba wyprodukowanych kompletow opon
int liczba_silnikow = 0;				//liczba wyprodukowanych silnikow
int liczba_karoserii = 0;				//liczba wyprodukowanych karoserii
int liczba_pomalowanych_karoserii = 0;	//liczba pomalowanych karoserii
int liczba_karoserii_z_oponami = 0;		//liczba zmontowanych karoserii z oponami
int liczba_karoseriasilnik = 0;			//liczba karoserii z zamontowanym silnikiem
int liczba_elektronika = 0;				//liczba zmontowanych calkowicie samochodow

void __cdecl thread_produkcja_opon(void *Args)
{
	int *iptr = (int*)Args;		//argument podawany do funkcji, mowi ktore stanowisko uruchomic

	while(liczba_opon < liczba_samochodow)		//dopoki nie wykona wystarczajacej liczby opon
	{
		if ((oponakaroseria[0].kolejka_opony.size()) < 10 && (oponakaroseria[1].kolejka_opony.size() < 10))	//jesli kolejki w kolejnych stanowiskach sa wieksze od 10 to ma czekac
		{
			if (oponakaroseria[0].kolejka_opony.size() < oponakaroseria[1].kolejka_opony.size())
			{
				liczba_opon++;
				oponakaroseria[0].kolejka_opony.push(ogumienie[*iptr].produkcja());		//dodaje do kolejki pierwszego stanowiska
			}
			else
			{
				liczba_opon++;
				oponakaroseria[1].kolejka_opony.push(ogumienie[*iptr].produkcja());		//dodaje do kolejki drugiego stanowiska

			}
		}
		else Sleep(1500);			//jesli kolejki sa za dlugie to czeka przez jednostke czasu
		fout_kol << "Dlugosc kolejki opon w stanowisku nr 0 montujacym opony w karoserii: " << oponakaroseria[0].kolejka_opony.size() << endl;		//wrzuca do drugiego pliku dlugosc kolejki w stanowisku
		fout_kol << "Dlugosc kolejki opon w stanowisku nr 1 montujacym opony w karoserii: " << oponakaroseria[1].kolejka_opony.size() << endl;		//wrzuca do drugiego pliku dlugosc kolejki w stanowisku

	}
	
	_endthread();		//zakonczenie watku
}



void __cdecl thread_produkcja_karoserii(void *Args)	
{
	int *iptr = (int*)Args;				//argument podawany do funkcji mowiacy ktore stanowisko wlaczyc

	while(liczba_karoserii < liczba_samochodow)		//dopoki nie wyprodukuje sie wystarczajacej ilosci
	{
		if(kolorkar[0].kolejka.size() < 10 && kolorkar[1].kolejka.size() < 10)		//jesli obie kolejki sa wieksze od 10 to czekaj
		{
			if(kolorkar[0].kolejka.size() < kolorkar[1].kolejka.size())		//idz do tego w ktorym jest mniejsza kolejka
			{
				liczba_karoserii++;
				kolorkar[0].kolejka.push(karo[*iptr].produkcja());			//wrzuca karoserie do kolejki stanowiska w ktorym beda ja malowac
			}
			else
			{
				liczba_karoserii++;
				kolorkar[1].kolejka.push(karo[*iptr].produkcja());
			}

		}
		else Sleep(1000);			//jesli sa za dlugie kolejki to czekaj przez jednostke czasu
		fout_kol << "Dlugosc kolejki w stanowisku malujacym karoserie nr 0 wynosi: " << kolorkar[0].kolejka.size() << endl;	//dlugosc kolejki wypisana do pliku
		fout_kol << "Dlugosc kolejki w stanowisku malujacym karoserie nr 1 wynosi: " << kolorkar[1].kolejka.size() << endl;	//dlugosc kolejki wypisana do pliku

	}

	_endthread();				//koniec watku
}


void __cdecl thread_malowanie_karoserii(void *Args)			//uruchomienie stanowiska malujacego karoserie
{
	int *iptr = (int*)Args;			//argument podawany do funkcji, mowi ktore stanowisko uruchomic
	
	while(liczba_pomalowanych_karoserii < liczba_samochodow)		//dopoki nie zostanie pomalowana wystarczajaca liczba karoserii dopoty ma pracowac
	{
		if(oponakaroseria[0].kolejka_pomkar.size() < 10 && oponakaroseria[1].kolejka_pomkar.size() < 10)	//jezeli z przodu sa za dlugie kolejki to czekaj
		{
			if(oponakaroseria[0].kolejka_pomkar.size() < oponakaroseria[1].kolejka_pomkar.size())
			{
				try		//jesli chce pobrac z pustej kolejki to wyrzuci wyjatek
				{
					liczba_pomalowanych_karoserii++;
					oponakaroseria[0].kolejka_pomkar.push(kolorkar[*iptr].malowanie());		//maluje karoserie i wrzuca ja do kolejki kolejnego stanowiska
				}
				catch(int)
				{
					liczba_pomalowanych_karoserii--;
					Sleep(1000);		//jesli zostal wyrzucony wyjatek to czeka przez chwile i proboje znowu zrobic ta operacje
				}
			}
			else
			{
				try		//jesli chce pobrac z pustej kolejki to wyrzuca wyjatek
				{
					liczba_pomalowanych_karoserii++;
					oponakaroseria[1].kolejka_pomkar.push(kolorkar[*iptr].malowanie());

				}
				catch(int)
				{
					liczba_pomalowanych_karoserii--;
					Sleep(1000);			//jesli wystapil wyjatek to "zamroz" stanowisko na pewien czas
				}
			}
		}
		else Sleep(1000);		//jesli za dlugie kolejki przed toba to czekaj
		fout_kol << "Dlugosc kolejki pomalowanych karoserii w stanowisku nr 0 montujacym opony w karoserii wynosi: " << oponakaroseria[0].kolejka_pomkar.size() << endl;
		fout_kol << "Dlugosc kolejki pomalowanych karoserii w stanowisku nr 1 montujacym opony w karoserii wynosi: " << oponakaroseria[1].kolejka_pomkar.size() << endl;

	}
	
	_endthread();		//konczy watek
}


void __cdecl thread_montowanie_opon_w_karoserii(void *Args)			//watek odpowiadajacy za montowanie opon w karoserii
{
	int *iptr = (int*)Args;			//argumenty podawane do funckji mowiace ktore stanowisko uruchomic

	while (liczba_karoserii_z_oponami < liczba_samochodow)
	{
		if(karoseriasilnik[0].kolejka_opokar.size() < 10 && karoseriasilnik[1].kolejka_opokar.size() < 10)
		{
			if(karoseriasilnik[0].kolejka_opokar.size() < karoseriasilnik[1].kolejka_opokar.size())	//do mniejszej kolejki idzie
			{
				try			//jesli kolejka pusta to rzuc wyjatek
				{
					liczba_karoserii_z_oponami++;
					karoseriasilnik[0].kolejka_opokar.push(oponakaroseria[*iptr].montaz());
				}
				catch(int)
				{
					liczba_karoserii_z_oponami--;
					if(oponakaroseria[*iptr].kolejka_opony.size() == 0 && oponakaroseria[*iptr].kolejka_pomkar.size() > 0 && oponakaroseria[!(*iptr)].kolejka_opony.size() > 0)
					{
						oponakaroseria[*iptr].kolejka_opony.push(oponakaroseria[!(*iptr)].kolejka_opony.front());		//jesli ta kolejka nie ma opon do montazu a ma karoserie to zabiera z drugiego stanowiska
						oponakaroseria[!(*iptr)].kolejka_opony.pop();
					}
					Sleep(1000);		//"zamraza" stanowisko jesli zgloszony byl wyjatek
				}
			}
			else
			{
				try		//jesli pusta kolejka to rzuc wyjatek
				{
					liczba_karoserii_z_oponami++;
					karoseriasilnik[1].kolejka_opokar.push(oponakaroseria[*iptr].montaz());
				}
				catch(int)
				{
					liczba_karoserii_z_oponami--;
					if(oponakaroseria[*iptr].kolejka_opony.size() == 0 && oponakaroseria[*iptr].kolejka_pomkar.size() > 0 && oponakaroseria[!(*iptr)].kolejka_opony.size() > 0)
					{
						oponakaroseria[*iptr].kolejka_opony.push(oponakaroseria[!(*iptr)].kolejka_opony.front());		//jesli ta kolejka nie ma opon do montazu a ma karoserie to zabiera z drugiego stanowiska
						oponakaroseria[!(*iptr)].kolejka_opony.pop();
					}
					Sleep(1000);		//"zamraza" stanowisko jesli zgloszony byl wyjatek
				}
			}
		}
		else Sleep(1000);		//odczekuje pewien czas jesli z przodu sa za dlugie kolejki
		fout_kol << "Dlugosc kolejki karoserii z oponami w stanowisku nr 0 montujacym silniki do karoserii wynosi: " << karoseriasilnik[0].kolejka_opokar.size() << endl;
		fout_kol << "Dlugosc kolejki karoserii z oponami w stanowisku nr 1 montujacym silniki do karoserii wynosi: " << karoseriasilnik[1].kolejka_opokar.size() << endl;
	
	}
	_endthread();			//konczy watek
}

void __cdecl thread_produkcja_silnika(void *Args)		//produkuje silniki
{
	int *iptr = (int*)Args;			//argument podawany do funckji mowiacy ktore stanowisko uruchomic

	while(liczba_silnikow < liczba_samochodow)
	{
		if(karoseriasilnik[0].kolejka_silnik.size() < 10 && karoseriasilnik[0].kolejka_silnik.size() < 10)
		{	
			if(karoseriasilnik[0].kolejka_silnik.size() < karoseriasilnik[1].kolejka_silnik.size())
			{
				liczba_silnikow++;	
				karoseriasilnik[0].kolejka_silnik.push(motorek[*iptr].produkcja());		//idzie do mniejszej kolejki
			}
			else
			{
				liczba_silnikow++;	
				karoseriasilnik[1].kolejka_silnik.push(motorek[*iptr].produkcja());		//dodaje do krotszej kolejki
			}
		}
		else Sleep(1000);				//usypia jezeli z przodu sa dlugie kolejki
		fout_kol << "Dlugosc kolejki silnikow w stanowisku nr 0 montujacym silniki w karoserii wynosi: " << karoseriasilnik[0].kolejka_silnik.size() << endl;
		fout_kol << "Dlugosc kolejki silnikow w stanowisku nr 1 montujacym silniki w karoserii wynosi: " << karoseriasilnik[1].kolejka_silnik.size() << endl;

	}
	_endthread();			//koniec watku
}

void __cdecl thread_montowanie_silnika_w_karoserii(void *Args)
{
	int *iptr = (int*)Args;				//argument podawany do funkcji mowiacy ktore stanowisko uruchomic
	while(liczba_karoseriasilnik < liczba_samochodow)		//dopoki nie wyprodukuje sie wystarczajacej liczby elementow
	{
		if(elektronika[0].kolejka.size() < 10 && elektronika[1].kolejka.size() < 10)
		{
			if(elektronika[0].kolejka.size() < elektronika[1].kolejka.size())
			{
				try			//jesli kolejka bedzie pusta to wyrzuci wyjatek
				{
					liczba_karoseriasilnik++;
					elektronika[0].kolejka.push(karoseriasilnik[*iptr].montaz());
				}
				catch(int)
				{
					liczba_karoseriasilnik--;
					if(karoseriasilnik[*iptr].kolejka_opokar.empty() && karoseriasilnik[*iptr].kolejka_silnik.size() > 0 && karoseriasilnik[!(*iptr)].kolejka_opokar.size() > 0)
					{
						karoseriasilnik[*iptr].kolejka_opokar.push(karoseriasilnik[!(*iptr)].kolejka_opokar.front());		//jezeli w tym stanowisku nie ma opon z karoseria a sa silniki a w drugim sa opony z karoseria to sa do niego transportowane opony z karoseria
						karoseriasilnik[!(*iptr)].kolejka_opokar.pop();		//wyrzucanie z kolejki wyciagnietego elementu
					}
					Sleep(1000);			//zatrzymuje proces na chwile
				}
			}
			else
			{
				try				//jesli kolejka z ktorej ma pobrac pusta to rzuca wyjatkiem
				{
					liczba_karoseriasilnik++;
					elektronika[1].kolejka.push(karoseriasilnik[*iptr].montaz());
				}
				catch(int)
				{
					liczba_karoseriasilnik--;
					if(karoseriasilnik[*iptr].kolejka_opokar.empty() && karoseriasilnik[*iptr].kolejka_silnik.size() > 0 && karoseriasilnik[!(*iptr)].kolejka_opokar.size() > 0)
					{
						karoseriasilnik[*iptr].kolejka_opokar.push(karoseriasilnik[!(*iptr)].kolejka_opokar.front());  //jezeli w tym stanowisku nie ma opon z karoseria a sa silniki a w drugim sa opony z karoseria to sa do niego transportowane opony z karoseria
						karoseriasilnik[!(*iptr)].kolejka_opokar.pop();
					}
					Sleep(1000);			//odczekuje pewien czas
				}
			}
		}
		else Sleep(1000);

		fout_kol << "Dlugosc kolejki karoserii z silnikiami w stanowisku nr 0 montujacym elektronike wynosi: " << elektronika[0].kolejka.size() << endl;		
		fout_kol << "Dlugosc kolejki karoserii z silnikiami w stanowisku nr 1 montujacym elektronike wynosi: " << elektronika[1].kolejka.size() << endl;

	}
	_endthread();
}

void __cdecl thread_montowanie_elektroniki_w_karoserii(void *Args)
{
	int *iptr = (int*)Args;				//mowi ktore stanowisko uruchomic
	while(liczba_elektronika < liczba_samochodow)
	{
		try		//jesli nie uda sie wyciagnac z kolejki to rzuca wyjatek
		{
			liczba_elektronika++;
			wektor_utworzonych_samochodow.push_back(elektronika[*iptr].montaz());			//montuje elektronike w samochodzie - samochod ukonczony
		}
		catch(int)
		{
			liczba_elektronika--;
			Sleep(1000);
		}
	}
	_endthread();			//konczy watek
}

#endif