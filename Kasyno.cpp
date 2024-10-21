#define _CRT_SECURE_NO_WARNINGS
#include "Kasyno.h"
#include "Gracz.h"
#include <iostream>
#include <string.h>

Kasyno::Kasyno() //konstruktor - ustawiamy karty
{
	for (int i = 0; i < 52; i++)
	{
		talia[i] = new Karta;
	}
}

Kasyno::~Kasyno() //destruktor - usuwamy talie
{
	for (int i = 0; i < 52; i++)
	{
		delete talia[i];
	}
}

void Kasyno::GenerujTalie() //generowanie talii
{
	int kolor = 0, k = 0; //k to jakby rodzaj karty, np. jak wygenerujemy wszystkie trefle, to trzeba wygenerowac piki, itp.
	while (kolor < 4)
	{
		for (int i = 0; i < 13; i++)
		{
			talia[i + k]->setKolor(kolor); //za kazdym razem inny kolor
			talia[i + k]->setWartosc(i);
		}
		k = k + 13; //zeby nie powielalo, aby tablica byla plynna
		kolor++;
	}
}

/*void Kasyno::WyswietlTalie() //wyswietlanie talii
{
	for (int i = 0; i < 52; i++)
	{
		talia[i]->wypisz(); //wypisz() jest w niezmienianym pliku Karta.h i Karta.cpp
	}
}*/

void Kasyno::Tasuj() //tasowanie
{
	int a, b;
	do
	{
		a = rand() % 52; //losowo wybieramy dwie karty z zakresu calej talii i zamieniamy je ze soba - typowe tasowanie
		b = rand() % 52;
	} while (a == b);
	Karta* temp = talia[a];
	talia[a] = talia[b];
	talia[b] = temp;
}

Karta* Kasyno::DajKarte() //metoda pobierajaca karte tak aby nie wydawac 2 razy tej samej karty
{
	int i;
	for (i = 0; i < 52; i++) //przechodzimy tak dlugo, az nie znajdziemy karty "1" czyli niepodniesionej
	{
		if (ilosc[i] == 1)
			break;
	}
	ilosc[i] = 0; //teraz tej karty podniesc juz nie mozna
	return talia[i];
}

void Kasyno::WszystkieKarty() //Kazdej karcie nadajemy jedynke, mozna podniesc. Jak zero to nie mozna podniesc. 
{
	for (int i = 0; i < 52; i++)
	{
		ilosc[i] = 1;
	}
}

int Kasyno::ktoWygral(Gracz* gracz, Bot* bot, int gracze, int boty)
{
	int  g[3]; //gracze
	int  b[3]; //boty

	for (int i = 0; i < gracze; i++)
	{
		g[i] = gracz[i].ZdobytePunkty(); //wpisujemy do utowrzonych tablic ich punkty i bedziemy poszukiwac najwiekszej ilosci punktowej
	}

	for (int i = 0; i < boty; i++)
	{
		b[i] = bot[i].ZdobytePunkty();
	}

	if (g[0] == NULL || g[0] > 21)   //jeeli przekroczyl 21 to przegral, wiec zerujemy mu punkty (ale TYLKO w tej funkcji, nie ogolnie)
		g[0] = 0;

	if (g[1] == NULL || g[1] > 21)
		g[1] = 0;

	if (g[2] == NULL || g[2] > 21)
		g[2] = 0;

	if (b[0] == NULL || b[0] > 21)
		b[0] = 0;

	if (b[1] == NULL || b[1] > 21)
		b[1] = 0;

	if (b[2] == NULL || b[2] > 21)
		b[2] = 0;

	int x = g[0]; //gracz 1
	if (g[1] > x)
		x = g[1];
	if (g[2] > x)
		x = g[2];
	if (b[0] > x)
		x = b[0];
	if (b[1] > x)
		x = b[1];
	if (b[2] > x)
		x = b[2];
	//powyzej szukamy najwiekszej wartosci punktowej u graczy

	return x; //zwracamy ile punktow mial gracz ktory wygral
}

Gracz* Kasyno::ustawGraczy(int x)
{
	this->gracz = new Gracz[x]; //dynamiczna alokacja
	return gracz;
}

Bot* Kasyno::ustawBoty(int x)
{
	this->bot = new Bot[x]; //dynamiczna alokacja
	return bot;
}

void Kasyno::nowaGra(Gracz* gracz, Bot* bot, int gracze, int boty)
{
	for (int i = 0; i < gracze; i++)
	{
		gracz[i].ZerujPunkty();
		gracz[i].NoweRozdanie();
	}

	for (int i = 0; i < boty; i++)
	{
		bot[i].ZerujPunkty();
		bot[i].NoweRozdanie();
	}
}