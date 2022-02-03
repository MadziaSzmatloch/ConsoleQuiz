#pragma once
#include <iostream>
#include <locale.h>
#include <Windows.h>
#include <SFML/Audio.hpp>
using namespace std;


void pomoc(string poprawna, string a, string b, string c, string d);  // funkcja odpowiedzialna za ko≥a ratunkowe
class Pytanie                     // deklaracja klasy
{
public:
	string tresc;
	string a, b, c, d;
	int nr_pyt;
	string poprawna;
	string odpowiedz;
	int punkt;
	int minusowe = 0;

	void wczytaj(string temat);               // wczytuje dane z pliku
	void zadaj(string temat);                 // zadaje pytanie
	void sprawdz(int* w_strike);			 // sprawdza podanπ odpowiedü
	
};
