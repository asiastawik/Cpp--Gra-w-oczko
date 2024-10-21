#pragma once
#include "Karta.h"
//#include "Gracz.h"
#include "Bot.h"

class Gracz; //deklaracja wyprzedzajaca
class Kasyno
{
public:
	Kasyno(); //konstruktor
	~Kasyno(); //destruktor
	Karta* talia[52]; //talia zawiera 52 karty
	void GenerujTalie();
	//void WyswietlTalie(); 
	void Tasuj(); //sztuczne tasowanie
	Karta* DajKarte();
	void WszystkieKarty();
	int ktoWygral(Gracz* gracz, Bot* bot, int gracze, int boty); //"Kasyno ma miec mozliwosc okreslenia, ktory Gracz wygral"
	Gracz* ustawGraczy(int x); //pamiec dynamiczna
	Bot* ustawBoty(int x); //pamiec dynamiczna
	void nowaGra(Gracz* gracz, Bot* bot, int gracze, int boty); //"Kasyno ma miec mozliwosc rozpoczecia nowej gry."
private:
	Gracz* gracz = nullptr;
	Bot* bot = nullptr;
	int ilosc[52]; //ilosc kart w talii
};