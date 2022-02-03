#include <SFML/Audio.hpp>
#include <iostream>
#include "Nag³ówek.h"


using namespace std;

int piosenek = 0;
string temat;

int main()
{
	// funkcje potrzebne do poprawnego dzia³ania dŸwiêkow
	sf::SoundBuffer poprawnaBuffer;
	poprawnaBuffer.loadFromFile("Poprawna-odpowiedz.wav");
	sf::Sound soundPoprawna;
	soundPoprawna.setBuffer(poprawnaBuffer);

	sf::SoundBuffer blednaBuffer;
	blednaBuffer.loadFromFile("Bledna-odpowiedz.wav");
	sf::Sound soundBledna;
	soundBledna.setBuffer(blednaBuffer);

	sf::SoundBuffer victoryBuffer;
	victoryBuffer.loadFromFile("Victory-sound.wav");
	sf::Sound soundVictory;
	soundVictory.setBuffer(victoryBuffer);

	setlocale(LC_CTYPE, "Polish");  // funkcje potrzebnaa do poprawnego dzia³ania polskich znaków
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // funkcje potrzebnaa do poprawnego dzia³ania kolorów
	SetConsoleTextAttribute(hConsole, 11);
	cout << "   ______                       __     ____        _    " << endl;
	cout << "  / ____/___  ____  _________  / /__  / __ \\__  __(_)___" << endl;
	cout << " / /   / __ \\/ __ \\/ ___/ __ \\/ / _ \\/ / / / / / / /_  /" << endl;
	cout << "/ /___/ /_/ / / / (__  ) /_/ / /  __/ /_/ / /_/ / / / /_" << endl;
	cout << "\\____/\\____/_/ /_/____/\\____/_/\\___/\\___\\_\\__,_/_/ /___/" << endl;
	cout << "                                                        " << endl;

	cout << "Witaj w ConsoleQuiz! Za chwilê bedziêsz móg³ wybraæ jeden z 4 tematów quizu. " << endl;
	cout << "Nastêpnie bêdziesz musia³ odpowiedzieæ na 10 pytañ z danej dziedziny." << endl;
	cout << "Za ka¿d¹ dobr¹ odpowiedŸ bêdziesz dostawa³ coraz wiêksz¹ iloœæ punktów." << endl;
	cout << "Jeœli odpowiesz Ÿle, twój strike wróci do zera, a za nastêpne dobre odpowiedzi" << endl;
	cout << "bêdziesz dostawa³ znów stosunkowo zwiêkszaj¹c¹ siê iloœæ punktów. Na pytania odpowiadaj" << endl;
	cout << "wpisuj¹c litery a,b,c,d. Aby u¿yæ ko³a ratunkowego w miejsce odpowiedzi wpisz komendê pomoc." << endl;
	cout << "Po zatwierdzeniu jej enterem z 4 odpowiedzi zostan¹ 2. Ka¿de ko³o ratunkowe kosztuje Ciê 200 punktów" << endl;
	cout << "Celem gry jest uzyskanie 5500 punktów!" << endl;
	system("pause");
	system("cls");


	// wybór tematu
	int a = 0;
	while (a == 0)
	{
		cout << "WYBIERZ TEMAT" << endl;
		SetConsoleTextAttribute(hConsole, 13);
		cout << "1. Komputery" << endl;
		cout << "2. Historia" << endl;
		cout << "3. Seriale" << endl;
		cout << "4. Matematyka" << endl;
		SetConsoleTextAttribute(hConsole, 14);
		cout << "Podaj liczbê 1, 2, 3 lub 4" << endl;
		cin >> temat;
		if ((temat == "1") || (temat == "2") || (temat == "3") || (temat == "4"))
		{
			a++;
			system("cls");
		}
		else
		{
			cout << "Nie poda³eœ liczby 1, 2, 3, lub 4!" << endl;
			Sleep(1000);
			system("cls");
			a = 0;
		}
	}

	Pytanie p[10];  // stworzenie 10 obiektów pytañ
	int suma = 0, strike = 0;
	int* w_strike = &strike;
	// losowanie dwóch zmiennych potrzebnych do pseudolosowoœci pytañ
	int x, q;
	srand(time(NULL));
	x = rand() % 10 + 1;
	q = rand() % 5 + 1;
	for (int i = 0; i <= 9; i++)
	{
		if (i == 0)
		{
			p[i].nr_pyt = x;
		}
		else
		{
			p[i].nr_pyt = x + (i*q);  
		}
		p[i].wczytaj(temat);
		p[i].zadaj(temat);
		p[i].sprawdz(w_strike);
		if(p[i].punkt !=0)
		{
			soundPoprawna.play();  // wywo³anie dŸwiêku
			
		}
		else if (p[i].punkt == 0)
		{
			soundBledna.play(); // wywo³anie dŸwiêku
		}
		
		// dodanie do smu punktów zdobytych punktów i odjêcie punktów za u¿ycie pomocy
		suma += p[i].minusowe;
		suma += p[i].punkt;

		cout << "Twoja obecna iloœæ punktów: " << suma << endl;
		cout << endl;
		cout << "Kliknij enter, aby przejœæ dalej" << endl;
		system("pause");
		system("cls");
	}
	cout << "Zdobyte punkty: " << suma << endl;
	if (suma == 5500)
	{
		cout << "Zdoby³eœ wszystkie mo¿liwe punkty!!!" << endl;
		soundVictory.play();
		system("pause");
	}
}
