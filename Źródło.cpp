#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string> //tablice znakow
#include <time.h>
#include "Kasyno.h"
#include "Gracz.h"
#include "Karta.h"
#include "Bot.h"
#include <fstream> //do zapisu pliku
#include <iomanip> //do wyrownania w pliku -> plik<<right
#include <clocale> //do jezyka polskiego

void Zapis(Gracz* gracz, Bot* bot, int gracze, int boty, int ilosc_kart[3], int ilosc_kart_b[3])
{
	std::ofstream plik;
	plik.open("wynik.txt", std::ifstream::out); //otwieranie plikow 
	//plik.open("wynik.txt", std::ios::out);

	if (plik.good()) //plik.good() to do sprawdzenia czy plik sie dobrze otworzyl
	{
		for (int i = 0; i < gracze; i++)
		{
			plik << gracz[i].nazwa << "\t\t"; //nazwa gracza
			int j = 0;
			while (j < ilosc_kart[i]) //wypisuj, dopoki gracz ma karty
			{
				plik << gracz[i].karty[j]->getFigura() << gracz[i].karty[j]->getKolor() << " ";
				j++;
			}
			plik << "\t\t" << std::right << gracz[i].ZdobytePunkty() << std::endl; //wyrownanie do prawej w pliku
		}

		for (int i = 0; i < boty; i++)
		{
			plik << bot[i].nazwa << "\t\t";
			int j = 0;
			while (j < ilosc_kart_b[i]) //wypisuj, dopoki bot ma karty
			{
				plik << bot[i].karty[j]->getFigura() << bot[i].karty[j]->getKolor() << " ";
				j++;
			}
			plik << "\t\t" << std::right << bot[i].ZdobytePunkty() << std::endl;
		}

		std::cout << "Wyniki poprawnie zapisano do pliku wyniki.txt.\n";
	}

	else
	{
		std::cout << "Niestety, nie udalo sie otworzyc pliku.\n" << std::endl;
	}

	plik.close();
}

bool czySpasowali(Gracz* gracz, Bot* bot, int gracze, int boty)
{
	for (int i = 0; i < gracze; i++)
	{
		if (gracz[i].pas == false)
			return false; //nie spasowal
	}

	for (int i = 0; i < boty; i++)
	{
		if (bot[i].pas == false)
			return false; //nie spasowal
	}
	return true; //spasowal
}

int main()
{
	Kasyno* talia = new Kasyno;
	Gracz* gracz = nullptr;
	Bot* bot = nullptr;
	char c[10]; //wybor

	char decyzja;
	std::string nazwa; //tablica do ktorej wpisujemy imie/nazwe graczy
	int i, j, x, y, boty, gracze; //wszystko co bedzie nam potrzebne w mainie

	srand(time(NULL));
	talia->GenerujTalie(); //generujemy talie w kasynie

	std::locale pol("pl_PL");
	std::locale::global(pol);
	//setlocale(LC_ALL, "");	//do polskich znakow w konsoli
	setlocale(LC_ALL, "");

	std::cout.width(75); //ustawienie szerokosci, aby ponizszy napis byl blizej srodka
	std::cout << "WITAMY W KASYNIE!\n";
	std::cout.width(73);
	std::cout << "Gra w oczko\n\n";

	//tu zaczynamy partie:
	do
	{
		int k1 = 0, k2 = 0, k3 = 0, kb1 = 0, kb2 = 0, kb3 = 0; // ilosc kart, ktore maja gracze i boty

		talia->WszystkieKarty(); //kazdej karcie nadajemy "1" - czyli mozna ja podniesc

		for (i = 0; i < 25; i++) //25 tasowan jest optymalne
		{
			talia->Tasuj();
		}

		std::cout << "Ile graczy bedzie grac? (maksymalnie 3)" << std::endl;
		do //zabezpieczenie przed wprowadzaniem liter/zlych wartosci - uzywam pozniej w kazdym miejscu
		{
			std::cin >> c;

			int m = strlen(c);
			for (i = 0; i < m; i++)
			{
				if (c[i] >= 49 && c[i] <= 51) //przedzial [1;3]
				{
					x = atoi(c);
				}
				else
				{
					x = -1;
					std::cout << "Niepoprawna wartosc. Prosze podac liczbe z przedzialu od 1 do 3.\n" << std::endl;
				}
			}
		} while (x < 1 || x > 3);

		gracze = x;
		gracz = talia->ustawGraczy(gracze);

		if (gracze >= 1)
		{
			gracz[0].talia = talia; //talia wygenerowana dla pierwszego gracza

			std::cout << "Prosze wpisac nazwe gracza 1:  ";
			std::cin >> nazwa;
			std::cout << "\n";
			gracz[0].nazwa = nazwa;
			gracz[0].pas = false; //nie spasowal
			gracz[0].wezKarte(0); //podnosimy jedna karte, druga dostanie w swojej kolejce
			gracz[0].DodajPunkty(gracz[0].karty[0]->getWartosc()); //karty od 0, bo to pierwsza karta, ktora posiada
			k1++;
		}

		if (gracze >= 2)
		{
			gracz[1].talia = talia; //talia wygenerowana dla dwoch graczy

			std::cout << "Prosze wpisac nazwe gracza 2:  ";
			std::cin >> nazwa;
			std::cout << "\n";
			gracz[1].nazwa = nazwa;
			gracz[1].pas = false;
			gracz[1].wezKarte(0);
			gracz[1].DodajPunkty(gracz[1].karty[0]->getWartosc());
			k2++;
		}

		if (gracze >= 3)
		{
			gracz[2].talia = talia; //kazdy z trzech graczy otrzymuje swoja talie

			std::cout << "Prosze wpisac nazwe gracza 3:  ";
			std::cin >> nazwa;
			std::cout << "\n";
			gracz[2].nazwa = nazwa;
			gracz[2].pas = false;
			gracz[2].wezKarte(0);
			gracz[2].DodajPunkty(gracz[2].karty[0]->getWartosc());
			k3++;
		}

		std::cout << "Ile botow bedzie grac? (maksymalnie 3)" << std::endl;
		do
		{
			std::cin >> c;

			int m = strlen(c);
			for (i = 0; i < m; i++)
			{
				if (c[i] >= 49 && c[i] <= 51) //przedzial [1;3]
				{
					x = atoi(c);
				}
				else
				{
					x = -1;
					std::cout << "Niepoprawna wartosc. Prosze podac liczbe z przedzialu od 1 do 3.\n" << std::endl;
				}
			}
		} while (x < 1 || x > 3);

		boty = x;
		bot = talia->ustawBoty(boty);

		if (boty >= 1)
		{
			bot[0].talia = talia;
			bot[0].nazwa = "Bot1";
			std::cout << "Wybierz poziom odwagi bota 1\n1. Zachowawczy\n2. Normalny\n3. Ryzykujacy\n\n" << std::endl;

			do
			{
				std::cin >> c;

				int m = strlen(c);
				for (i = 0; i < m; i++)
				{
					if (c[i] >= 49 && c[i] <= 51) //przedzial [1;3]
					{
						y = atoi(c);
					}
					else
					{
						y = -1;
						std::cout << "Niepoprawna wartosc. Prosze podac liczbe z przedzialu od 1 do 3.\n" << std::endl;
					}
				}
			} while (y < 1 || y > 3);

			bot[0].UstawOdwage(y);
			bot[0].pas = false;
			bot[0].wezKarte(0);
			bot[0].DodajPunkty(bot[0].karty[0]->getWartosc());
			kb1++;
		}

		if (boty >= 2)
		{
			bot[1].talia = talia;
			bot[1].nazwa = "Bot2";
			std::cout << "Wybierz poziom odwagi bota 1\n1. Zachowawczy\n2. Normalny\n3. Ryzykujacy\n\n" << std::endl;

			do
			{
				std::cin >> c;

				int m = strlen(c);
				for (i = 0; i < m; i++)
				{
					if (c[i] >= 49 && c[i] <= 51) //przedzial [1;3]
					{
						y = atoi(c);
					}
					else
					{
						y = -1;
						std::cout << "Niepoprawna wartosc. Prosze podac liczbe z przedzialu od 1 do 3.\n" << std::endl;
					}
				}
			} while (y < 1 || y > 3);

			bot[1].UstawOdwage(y);
			bot[1].pas = false;
			bot[1].wezKarte(0);
			bot[1].DodajPunkty(bot[1].karty[0]->getWartosc());
			kb2++;
		}

		if (boty >= 3)
		{
			bot[2].talia = talia;
			bot[2].nazwa = "Bot3";
			std::cout << "Wybierz poziom odwagi bota 1\n1. Zachowawczy\n2. Normalny\n3. Ryzykujacy\n\n" << std::endl;

			do
			{
				std::cin >> c;

				int m = strlen(c);
				for (i = 0; i < m; i++)
				{
					if (c[i] >= 49 && c[i] <= 51) //przedzial [1;3]
					{
						y = atoi(c);
					}
					else
					{
						y = -1;
						std::cout << "Niepoprawna wartosc. Prosze podac liczbe z przedzialu od 1 do 3.\n" << std::endl;
					}
				}
			} while (y < 1 || y > 3);

			bot[2].UstawOdwage(y);
			bot[2].pas = false;
			bot[2].wezKarte(0);
			bot[2].DodajPunkty(bot[2].karty[0]->getWartosc());
			kb3++;
		}

		decyzja = NULL; //zmienna, ktora okresla czy dana osoba chce grac (1), czy nie (0)
		i = 1; //miejsce w ktorym podnosimy karte komukolwiek, drugie miejsce w kartach uzytkownika

		//Rozwiniecie gry
		do
		{
			if (gracze >= 1 && gracz[0].pas == false) //Gracz1 gra
			{
				decyzja = NULL; //czyszczenie zmiennej
				system("cls"); //czyszczenie konsoli, aby nie widziec kart innych graczy
				gracz[0].wezKarte(i); //podnosimy na drugim miejscu na rece gracza (w jego kartach) (i = 1, a zaczynamy od 0)
				gracz[0].DodajPunkty(gracz[0].karty[i]->getWartosc());
				k1++;
				std::cout << gracz[0].nazwa << ",Twoje karty to:" << std::endl;
				gracz[0].WypiszKarty(k1);
				std::cout << "\nOto Twoje punkty:  " << gracz[0].ZdobytePunkty() << std::endl;

				if (gracz[0].ZdobytePunkty() > 21)
				{
					std::cout << "Przegrales. Przekroczyles 21 punktow!\n" << std::endl;
					system("pause"); //wstrzymuje prace programu i czeka na wcisniecie klawisza
					gracz[0].pas = true; //spasowanie
				}

				else
				{
					do
					{
						std::cout << "\nGrasz dalej?\n" << "Tak - 1\n" << "Nie - 0" << std::endl;
						std::cin >> decyzja;
						if (decyzja != '0' && decyzja != '1') //zabezpieczenie
						{
							std::cout << "Oczekiwano wartosci 0 lub 1!\n";
						}
					} while (decyzja != '0' && decyzja != '1');

					if (decyzja == '0')
						gracz[0].pas = true; //jezli nie chce grac to pasujemy
				}
			}

			if (gracze >= 2 && gracz[1].pas == false)
			{
				decyzja = NULL; //czyszczenie zmiennej
				system("cls"); //czyszczenie konsoli, aby nie widziec kart innych graczy
				gracz[1].wezKarte(i); //podnosimy na drugim miejscu na rece (i = 1, a zaczynamy od 0)
				gracz[1].DodajPunkty(gracz[1].karty[i]->getWartosc());
				k2++;
				std::cout << gracz[1].nazwa << ",Twoje karty to:" << std::endl;
				gracz[1].WypiszKarty(k2);
				std::cout << "\nOto Twoje punkty:  " << gracz[1].ZdobytePunkty() << std::endl;

				if (gracz[1].ZdobytePunkty() > 21)
				{
					std::cout << "Przegrales. Przekroczyles 21 punktow!\n" << std::endl;
					system("pause"); //wstrzymuje prace programu i czeka na wcisniecie klawisza
					gracz[1].pas = true; //spasowanie
				}

				else
				{
					do
					{
						std::cout << "\nGrasz dalej?\n" << "Tak - 1\n" << "Nie - 0" << std::endl;
						std::cin >> decyzja;
						if (decyzja != '0' && decyzja != '1') //zabezpieczenie
						{
							std::cout << "Oczekiwano wartosci 0 lub 1!\n";
						}
					} while (decyzja != '0' && decyzja != '1');

					if (decyzja == '0')
						gracz[1].pas = true; //jezli nie chce grac to pasujemy
				}
			}

			if (gracze >= 3 && gracz[2].pas == false) //Gracz3 gra
			{
				decyzja = NULL; //czyszczenie zmiennej
				system("cls"); //czyszczenie konsoli, aby nie widziec kart innych graczy
				gracz[2].wezKarte(i); //podnosimy na drugim miejscu na rece (i = 1, a zaczynamy od 0)
				gracz[2].DodajPunkty(gracz[2].karty[i]->getWartosc());
				k3++;
				std::cout << gracz[2].nazwa << ",Twoje karty to:" << std::endl;
				gracz[2].WypiszKarty(k3);
				std::cout << "\nOto Twoje punkty:  " << gracz[2].ZdobytePunkty() << std::endl;

				if (gracz[2].ZdobytePunkty() > 21)
				{
					std::cout << "Przegrales. Przekroczyles 21 punktow!\n" << std::endl;
					system("pause"); //wstrzymuje prace programu i czeka na wcisniecie klawisza
					gracz[2].pas = true; //spasowanie
				}

				else
				{
					do
					{
						std::cout << "\nGrasz dalej?\n" << "Tak - 1\n" << "Nie - 0" << std::endl;
						std::cin >> decyzja;
						if (decyzja != '0' && decyzja != '1') //zabezpieczenie
						{
							std::cout << "Oczekiwano wartosci 0 lub 1!\n";
						}
					} while (decyzja != '0' && decyzja != '1');

					if (decyzja == '0')
						gracz[2].pas = true; //jezli nie chce grac to pasujemy
				}
			}

			if (boty >= 1 && bot[0].pas == false)
			{
				bot[0].wezKarte(i);
				bot[0].DodajPunkty(bot[0].karty[i]->getWartosc());
				kb1++;
				if (bot[0].ZdobytePunkty() >= bot[0].odwaga) //gra dopoki nie przekroczy poziom odwagi, jak przekroczy to pasuje
					bot[0].pas = true;
			}

			if (boty >= 2 && bot[1].pas == false)
			{
				bot[1].wezKarte(i);
				bot[1].DodajPunkty(bot[1].karty[i]->getWartosc());
				kb2++;
				if (bot[1].ZdobytePunkty() >= bot[1].odwaga)
					bot[1].pas = true;
			}

			if (boty >= 3 && bot[2].pas == false)
			{
				bot[2].wezKarte(i);
				bot[2].DodajPunkty(bot[2].karty[i]->getWartosc());
				kb3++;
				if (bot[2].ZdobytePunkty() >= bot[2].odwaga)
					bot[2].pas = true;
			}

			i++; //i = 2, 3... i tak idziemy przez wszystkie 10 kart, ktore mozna miec
		} while (czySpasowali(gracz, bot, gracze, boty) == false); //dopoki ktokolwiek nie spasowal; wszyscy musza spasowac, wtedy koniec gry

		system("cls"); //czyszczenie okna konsoli

		//wypisujemy wszystkie karty 
		if (gracze >= 1)
		{
			std::cout << "\nKarty gracza " << gracz[0].nazwa << ": " << std::endl;
			gracz[0].WypiszKarty(k1);
			std::cout << "\nPunkty gracza " << gracz[0].nazwa << ": " << gracz[0].ZdobytePunkty() << std::endl;
		}

		if (gracze >= 2)
		{
			std::cout << "\nKarty gracza " << gracz[1].nazwa << ": " << std::endl;
			gracz[1].WypiszKarty(k2);
			std::cout << "\nPunkty gracza " << gracz[1].nazwa << ": " << gracz[1].ZdobytePunkty() << std::endl;
		}

		if (gracze >= 3)
		{
			std::cout << "\nKarty gracza " << gracz[2].nazwa << ": " << std::endl;
			gracz[2].WypiszKarty(k3);
			std::cout << "\nPunkty gracza " << gracz[2].nazwa << ": " << gracz[2].ZdobytePunkty() << std::endl;
		}

		if (boty >= 1)
		{
			std::cout << "\nKarty gracza " << bot[0].nazwa << ": " << std::endl;
			bot[0].WypiszKarty(kb1);
			std::cout << "\nPunkty gracza " << bot[0].nazwa << ": " << bot[0].ZdobytePunkty() << std::endl;
		}

		if (boty >= 2)
		{
			std::cout << "\nKarty gracza " << bot[1].nazwa << ": " << std::endl;
			bot[1].WypiszKarty(kb2);
			std::cout << "\nPunkty gracza " << bot[1].nazwa << ": " << bot[1].ZdobytePunkty() << std::endl;
		}

		if (boty >= 3)
		{
			std::cout << "\nKarty gracza " << bot[2].nazwa << ": " << std::endl;
			bot[2].WypiszKarty(kb3);
			std::cout << "\nPunkty gracza " << bot[2].nazwa << ": " << bot[2].ZdobytePunkty() << std::endl;
		}

		int wygrana = talia->ktoWygral(gracz, bot, gracze, boty);

		if (wygrana == 0) //jezli nikt nie wygral
		{
			std::cout << "Niestety kazdy z graczy przekroczyl 21 punktow. Wszyscy przegrali." << std::endl;
		}

		else
		{
			std::cout << "\n\nGratulacje! Zwyciezyl gracz: ";

			if (gracz[0].ZdobytePunkty() == wygrana)
				std::cout << gracz[0].nazwa << " ";

			if (gracz[1].ZdobytePunkty() == wygrana)
				std::cout << gracz[1].nazwa << " ";

			if (gracz[2].ZdobytePunkty() == wygrana)
				std::cout << gracz[2].nazwa << " ";

			if (bot[0].ZdobytePunkty() == wygrana)
				std::cout << bot[0].nazwa << " ";

			if (bot[1].ZdobytePunkty() == wygrana)
				std::cout << bot[1].nazwa << " ";

			if (bot[2].ZdobytePunkty() == wygrana)
				std::cout << bot[2].nazwa << " ";
		}

		decyzja = NULL;
		do
		{
			std::cout << "\n\nCzy zapisac wynik gry do pliku tekstowego?\n" << "Tak - 1\nNie - 0\n";
			std::cout << "Dla poprawnego wyswietlania prosze pamietac zmienic czcionke!\n";
			std::cin >> decyzja;
			if (decyzja != '0' && decyzja != '1') //zabezpieczenie
			{
				std::cout << "Oczekiwano wartosci 0 lub 1!\n";
			}
		} while (decyzja != '0' && decyzja != '1');

		int ilosc_kart[3];
		ilosc_kart[0] = k1;
		ilosc_kart[1] = k2;
		ilosc_kart[2] = k3;
		int ilosc_kart_b[3];
		ilosc_kart_b[0] = kb1;
		ilosc_kart_b[1] = kb2;
		ilosc_kart_b[2] = kb3;

		if (decyzja == '1')
		{
			Zapis(gracz, bot, gracze, boty, ilosc_kart, ilosc_kart_b); //zapis do pliku
		}

		decyzja = NULL;

		std::cout << "\nCzy chcesz zagrac ponownie?\nJesli tak - nacisnij 1, jesli nie - nacisnij inny dowolny przycisk, aby zakonczyc program.\n";
		std::cin >> decyzja;
		if (decyzja == '1')
		{
			talia->nowaGra(gracz, bot, gracze, boty);

			system("cls");
		}
	} while (decyzja == '1');

	delete talia;
	delete[] gracz;
	delete[] bot;

	return 0;
}