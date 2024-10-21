#include "Gracz.h"
#include "Kasyno.h"
#include <iostream>

Gracz::Gracz() //konstruktor
{
	punkty = 0; //z poczatku gracz ma 0 punktow
}

Gracz::~Gracz() //destruktor
{

}

void Gracz::DodajPunkty(int punkty_k) //dodawanie kolejnych punktow gracza z kolejnych kart
{
	punkty += punkty_k; //punkty_k - punkty karty
}


void Gracz::wezKarte(int n) //podnosimy karte o numerze n
{
	karty[n] = talia->DajKarte(); //pierwsza z gory karta niepodniesiona (opis dlaczego tak w funkcji DajKarte())
}

int Gracz::ZdobytePunkty() //zwraca zdobyte punkty
{
	return punkty;
}

void::Gracz::ZerujPunkty() //zerowanie punktacji danego gracza
{
	punkty = 0;
}

void::Gracz::NoweRozdanie() //"opuszczanie" kart - z "1" (niepodniesiona) na "0" (podniesiona)
{
	for (int i = 0; i < 10; i++)
	{
		karty[i] = NULL;
	}
}

void Gracz::WypiszKarty(int n)
{
	for (int i = 0; i < n; i++)
	{
		karty[i]->wypisz();
		std::cout << "  ";
	}
}