//Projekt 3 - maj 2014 - student: Pawe³ Kamiñski - grupa 2I3 - prowadz¹cy Piotr Witoñski
//SYMULACJA FABRYKI SAMOCHODÓW
#ifndef DANE_H_INCLUDED
#define DANE_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ofstream fout;			//wypisywanie do pliku przebiegu dzialania fabryki
ofstream fout_kol;		//wypisywanie do pliku wielkosci kolejki

string oponki[9] = {"Bridgestone", "Continental", "Michelin", "Dunlop", "Debica", "Pirelli", "Goodyear", "Fulda", "Toyo"};

string kolory[9] = {"czerwony", "zielony", "niebieski", "turkusowy", "czarny", "bialy", "srebrny", "rozowy", "granatowy"};

string karoserie[9] = {"hatchback", "sedan", "coupe", "cabrio", "SUV", "terenowy", "ciezarowy", "dostawczy", "TIR"};

string silniki[5] = {"diesel", "benzyna", "elektryczny", "hybrydowy", "LPG"};


#endif