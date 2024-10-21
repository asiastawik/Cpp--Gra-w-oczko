#include "Bot.h"

Bot::Bot() //konstruktor
{

}

Bot::~Bot() //destruktor
{

}

void Bot::UstawOdwage(int x) //ustawienie poziomu ryzyka botow
{
	odwaga = x + 16;  //x to 1, 2 lub 3, odwaga to ilosc punktow, po ktorej bot spasuje automatycznie
}