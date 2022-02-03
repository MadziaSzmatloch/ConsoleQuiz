#include <iostream>
#include "Nag³ówek.h"
#include <fstream>	// do plików tekstowych
#include <cstdlib>	// funkcja exit
#include <string>
#include <SFML/Audio.hpp>
#include<time.h>
#include<Windows.h>

using namespace std;

// Deklaracja metod
void Pytanie::wczytaj(string temat)		// metoda wczytaj z klasy Pytanie
{
	//otwarcie odpowiedniego pliku z pytaniami zale¿nie od wybranego tematu
	fstream plik;
	if (temat == "1")
		plik.open("pytania_programowanie.txt", ios::in);
	else if (temat == "2")
		plik.open("pytania_historia.txt", ios::in);
	else if (temat == "3")
		plik.open("pytania_seriale.txt", ios::in);
	else if (temat == "4")
		plik.open("pytania_matematyka.txt", ios::in);
	
	if (plik.good() == false)
	{
		cout << "Brak pliku z pytaniami";
		exit(0);
	}

	int nr_linii = (nr_pyt - 1) * 6 + 1;  //wzór na nr_linii
	int aktualny_numer = 1;
	string linia;	// do przechowania obecnej linii

	while (getline(plik, linia))   // zapisanie tresci pytania, odpowiedzi a,b,c,d i poprawnej odpowiedzi
	{
		if (aktualny_numer == nr_linii) tresc = linia;
		if (aktualny_numer == nr_linii + 1) a = linia;
		if (aktualny_numer == nr_linii + 2) b = linia;
		if (aktualny_numer == nr_linii + 3) c = linia;
		if (aktualny_numer == nr_linii + 4) d = linia;
		if (aktualny_numer == nr_linii + 5) poprawna = linia;
		aktualny_numer++;
	}
	plik.close();
}

void Pytanie::zadaj(string temat)
{
	srand(time(NULL));
	int kolor = rand() % 15 +1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, kolor);
	cout << tresc << endl;
	cout << "a)" << a << endl;
	cout << "b)" << b << endl;
	cout << "c)" << c << endl;
	cout << "d)" << d << endl;
	cin >> odpowiedz;
}

void Pytanie::sprawdz(int* w_strike)
{
	transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);  // zamiana wielkich liter na ma³e
	int n=0;
	if (odpowiedz == "pomoc")  // sprawdzenie czy u¿yta zosta³a komenda pomoc
	{
		minusowe -= 200;
		pomoc(poprawna, a, b, c, d); //wywo³anie funkcji pomoc
		getchar();
		cin >> odpowiedz;

		if (odpowiedz == poprawna)
		{
			(*w_strike)++;  //zwiêkszenie strike
			n++;
			punkt = (*w_strike) * 100; //przydzial odpowiedniej liczby punktów
			cout << "Zdoby³eœ " << punkt << " punktów!" << endl;
		}
		else
		{
			*w_strike = 0;  //wyzerowanie strike
			n = 1;
			punkt = 0;
			cout << "Zdoby³eœ " << punkt << " punktów!" << endl;
			cout << "Poprawna odpowiedŸ: " << poprawna << endl;
		}
	}
	else
	{
		int k = 0;
		if ((odpowiedz == "a") || (odpowiedz == "b") || (odpowiedz == "c") || (odpowiedz == "d"))  //sprawdzenie czy podana zosta³a odpowiednia litera
			k++;
		while (k==0)
		{
			cout << "Podaj litery a, b, c, d!" << endl;
			cin >> odpowiedz;
			transform(odpowiedz.begin(), odpowiedz.end(), odpowiedz.begin(), ::tolower);
			if ((odpowiedz == "a") || (odpowiedz == "b") || (odpowiedz == "c") || (odpowiedz == "d"))
				k++;
		}
		if (odpowiedz == poprawna)
		{
			(*w_strike)++;
			n++;
			punkt = (*w_strike) * 100;
			cout << "Zdoby³eœ " << punkt << " punktów!" << endl;
		}
		else
		{
			*w_strike = 0;
			n = 1;
			punkt = 0;
			cout << "Zdoby³eœ " << punkt << " punktów!" << endl;
			cout << "Poprawna odpowiedŸ: " << poprawna << endl;
		}
	}
}

void pomoc(string poprawna, string a, string b, string c, string d)
{
	int zmienna{}, odp1{}, odp2{};
	srand(time(NULL));
	//zapisanie jako int poprawnej odpowiedzi
	if (poprawna == "a")
		odp1 = 1;
	else if (poprawna == "b")
		odp1 = 2;
	else if (poprawna == "c")
		odp1 = 3;
	else if (poprawna == "d")
		odp1 = 4;

	int k = 1;
	odp2 = rand() % 4 + 1;  //losowanie b³êdnej odpowiedzi, która siê wyœwietli
	while (k == 1)
	{
		if (odp1 != odp2)
		{
			k = 0;
		}
		else if(odp1==odp2)
		{
			odp2 = rand() % 4 + 1;
			k = 1;
		}
	}

	//wyœwietlenie odpowiedzi
	if ((odp1 == 1 && odp2 == 2) || (odp1 == 2 && odp2 == 1))
	{
		cout << "a)" << a << endl;
		cout << "b)" << b << endl;
	}
	else if ((odp1 == 1 && odp2 == 3) || (odp1 == 3 && odp2 == 1))
	{
		cout << "a)" << a << endl;
		cout << "c)" << c << endl;
	}
	else if ((odp1 == 1 && odp2 == 4) || (odp1 == 4 && odp2 == 1))
	{
		cout << "a)" << a << endl;
		cout << "d)" << d << endl;
	}
	else if ((odp1 == 2 && odp2 == 3) || (odp1 == 3 && odp2 == 2))
	{
		cout << "b)" << b << endl;
		cout << "c)" << c << endl;
	}
	else if ((odp1 == 2 && odp2 == 4) || (odp1 == 4 && odp2 == 2))
	{
		cout << "b)" << b << endl;
		cout << "d)" << d << endl;
	}
	else if ((odp1 == 3 && odp2 == 4) || (odp1 == 4 && odp2 == 3))
	{
		cout << "c)" << c << endl;
		cout << "d)" << d << endl;
	}
}

