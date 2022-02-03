#include <SFML/Audio.hpp>
#include <iostream>
#include "Nag��wek.h"


using namespace std;

int piosenek = 0;
string temat;

int main()
{
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

	setlocale(LC_CTYPE, "Polish");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	cout << "   ______                       __     ____        _    " << endl;
	cout << "  / ____/___  ____  _________  / /__  / __ \\__  __(_)___" << endl;
	cout << " / /   / __ \\/ __ \\/ ___/ __ \\/ / _ \\/ / / / / / / /_  /" << endl;
	cout << "/ /___/ /_/ / / / (__  ) /_/ / /  __/ /_/ / /_/ / / / /_" << endl;
	cout << "\\____/\\____/_/ /_/____/\\____/_/\\___/\\___\\_\\__,_/_/ /___/" << endl;
	cout << "                                                        " << endl;

	cout << "Witaj w ConsoleQuiz! Za chwil� bedzi�sz m�g� wybra� jeden z 4 temat�w quizu. " << endl;
	cout << "Nast�pnie b�dziesz musia� odpowiedzie� na 10 pyta� z danej dziedziny." << endl;
	cout << "Za ka�d� dobr� odpowied� b�dziesz dostawa� coraz wi�ksz� ilo�� punkt�w." << endl;
	cout << "Je�li odpowiesz �le, tw�j strike wr�ci do zera, a za nast�pne dobre odpowiedzi" << endl;
	cout << "b�dziesz dostawa� zn�w stosunkowo zwi�kszaj�c� si� ilo�� punkt�w. Na pytania odpowiadaj" << endl;
	cout << "wpisuj�c litery a,b,c,d. Aby u�y� ko�a ratunkowego w miejsce odpowiedzi wpisz komend� pomoc." << endl;
	cout << "Po zatwierdzeniu jej enterem z 4 odpowiedzi zostan� 2. Ka�de ko�o ratunkowe kosztuje Ci� 200 punkt�w" << endl;
	cout << "Celem gry jest uzyskanie 5500 punkt�w!" << endl;
	system("pause");
	system("cls");

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
		cout << "Podaj liczb� 1, 2, 3 lub 4" << endl;
		cin >> temat;
		if ((temat == "1") || (temat == "2") || (temat == "3") || (temat == "4"))
		{
			a++;
			system("cls");
		}
		else
		{
			cout << "Nie poda�e� liczby 1, 2, 3, lub 4!" << endl;
			Sleep(1000);
			system("cls");
			a = 0;
		}
	}

	

	Pytanie p[10];
	int suma = 0, strike = 0;
	int* w_strike = &strike;
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
			soundPoprawna.play();
			
		}
		else if (p[i].punkt == 0)
		{
			soundBledna.play();
		}
		
		suma += p[i].minusowe;
		suma += p[i].punkt;

		cout << "Twoja obecna ilo�� punkt�w: " << suma << endl;
		cout << endl;
		cout << "Kliknij enter, aby przej�� dalej" << endl;
		system("pause");
		system("cls");
	}
	cout << "Zdobyte punkty: " << suma << endl;
	if (suma == 5500)
	{
		cout << "Zdoby�e� wszystkie mo�liwe punkty!!!" << endl;
		soundVictory.play();
		system("pause");
	}
}
