#pragma once
#include <string>
#include "Karta.h"
//#include "Kasyno.h" //gracz ma miec swiadomosc o kasynie

class Kasyno; //deklaracja wyprzedzajaca
class Gracz
{
public:
	Gracz();
	~Gracz();
	Karta* karty[10];
	Kasyno* talia; //gracz uzywa kasyna
	std::string nazwa; //nazwa uzytkownika (imie), wedeug mnie to sie lepiej sprawdzi niz tablica char
	void DodajPunkty(int punkty_k);
	void wezKarte(int n);
	int ZdobytePunkty();
	void ZerujPunkty();
	void NoweRozdanie();
	void WypiszKarty(int n); //"Gracz posiada metode wyswietlajaca posiadane Karty"
	bool pas = true; //"Gracz ma miec mozliwosc decyzji czy dobiera dalej, czy pasuje."
protected:
	int punkty;
};