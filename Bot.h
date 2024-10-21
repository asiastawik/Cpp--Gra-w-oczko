#pragma once
#include "Gracz.h"

class Bot : public Gracz //dziedziczenie
{
public:
	Bot(); //konstruktor
	~Bot(); //destruktor
	int odwaga; //ryzykujacy, normalny, zachowawczy
	void UstawOdwage(int x); //x - to wybiera uzytkownik programu
};