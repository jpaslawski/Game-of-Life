#include "Plansza.h"
#include "Komorki.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

//konstruktor bezargumentowy, domyœlna wielkoœæ planszy to 10x10
Plansza::Plansza()
{
	nr_pokolenia = 0; //zainicjowanie zmiennej dotycz¹cej pokolenia
	rozmiar_x = 10; //domyœlny rozmiar wierszy
	rozmiar_y = 10; //domyœlny rozmiar kolumn
	plansza = new int *[rozmiar_x];  //inicjalizacja planszy
	for (int i = 0; i < rozmiar_x; i++)
	{
		plansza[i] = new int[rozmiar_y];
	}
	bufor = new int *[rozmiar_x]; //inicjalizacja bufora planszy 
	for (int i = 0; i < rozmiar_x; i++)
	{
		bufor[i] = new int[rozmiar_y];
	}
}

//konstruktor tworz¹cy planszê o podanych rozmiarach
Plansza::Plansza(const int _rozmiar_x, const int _rozmiar_y)
{
	nr_pokolenia = 0; 
	rozmiar_x = _rozmiar_x;
	rozmiar_y = _rozmiar_y;
	plansza = new int *[rozmiar_x];
	for (int i = 0; i < rozmiar_x; i++)
	{
		plansza[i] = new int[rozmiar_y];
	}
	bufor = new int *[rozmiar_x];

	for (int i = 0; i < rozmiar_x; i++)
	{
		bufor[i] = new int[rozmiar_y];
	}
}


Plansza::~Plansza()
{
	for (int i = 0; i < rozmiar_x; i++)
	{
		delete[] plansza[i];
		delete[] bufor[i];
	}
	delete[] plansza;
	delete[] bufor;
}


int **Plansza::getPlansza()
{
	return plansza;
}

void Plansza::NastepnePokolenie(Plansza &p, Komorki &k, int w1, int w2, int w3)
{
	//zmiana stanu planszy w buforze
	for (int i = 0; i < rozmiar_x; i++)
	{
		for (int j = 0; j < rozmiar_y; j++)
		{
			if ((k.StanKomorki(p, i, j) == 0) && (k.IloscSasiadow(p, i, j) == w1)) //komórka jest martwa i ma 3 ¿ywych s¹siadów
			{
				bufor[i][j] = 1; //wiêc w nastêpnym pokoleniu o¿yje
			}
			else if ((k.StanKomorki(p, i, j) == 1) && ((k.IloscSasiadow(p, i, j) == w2) || (k.IloscSasiadow(p, i, j) == w3))) //komórka jest ¿ywa i ma 2 lub 3 ¿ywych s¹siadów
			{
				bufor[i][j] = 1; //wiêc w nastêpnym pokoleniu o¿yje
			}
			else //poprzednie warunki nie s¹ spe³nione
			{
				bufor[i][j] = 0; //wiêc w nastêpnym pokoleniu umrze
			}
		}
	}
	//implementacja zmiany do planszy 
	for (int i = 0; i < rozmiar_x; i++)
	{
		for (int j = 0; j < rozmiar_y; j++)
		{
			plansza[i][j] = bufor[i][j]; //aktualizacja adresów planszy
			bufor[i][j] = 0;
		}
	}
	nr_pokolenia++; //zwiêkszenie numeru pokolenia
}

//losowanie stanu pocz¹tkowego komórek
void Plansza::Losuj()
{
	srand(time(NULL)); //inicjalizacja generatora liczb pseudolosowych
	for (int i = 0; i < rozmiar_x; i++)
	{
		for (int j = 0; j < rozmiar_y; j++)
		{
			plansza[i][j] = rand() % 2; //losowanie wartoœci z przedzia³u (0,1)
		}
	}
}

//wyzerowanie planszy
void Plansza::Zeruj()
{
	for (int i = 0; i < rozmiar_x; i++)
	{
		for (int j = 0; j < rozmiar_y; j++)
		{
			plansza[i][j] = 0;
		}
	}
}

//ustawienie stanu komórki na ¿ywy
void Plansza::Ustaw(int x, int y)
{
	*(*(plansza + x) + y) = 1;
}

//wstawienie sta³ej figury "klocek" do planszy w miejscu (x, y) 
void Plansza::Klocek(int x, int y)
{
	if ((rozmiar_x < 4) || (rozmiar_y < 4) || (x + 4 > rozmiar_x) || (y + 4 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 4; i++)
	{
		for (int j = y; j < y + 4; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 1) = *(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 2) + y + 2) = 1;
}

//wstawienie sta³ej figury "³ódŸ" do planszy w miejscu (x, y)
void Plansza::Lodz(int x, int y)
{
	if ((rozmiar_x < 5) || (rozmiar_y < 5) || (x + 5 > rozmiar_x) || (y + 5 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 5; i++)
	{
		for (int j = y; j < y + 5; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 1) = *(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 2) + y + 3) = *(*(plansza + x + 3) + y + 2) = 1;
	
}


void Plansza::Bochenek(int x, int y)
{
	if ((rozmiar_x < 6) || (rozmiar_y < 6) || (x + 6 > rozmiar_x) || (y + 6 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 6; i++)
	{
		for (int j = y; j < y + 6; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 1) + y + 3) = *(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 2) + y + 4) = *(*(plansza + x + 3) + y + 1) = *(*(plansza + x + 3) + y + 3) = *(*(plansza + x + 4) + y + 2) = 1;
}


void Plansza::Krysztal(int x, int y)
{
	if ((rozmiar_x < 6) || (rozmiar_y < 5) || (x + 6 > rozmiar_x) || (y + 5 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 6; i++)
	{
		for (int j = y; j < y + 5; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 3) + y + 2) = *(*(plansza + x + 1) + y + 3) = *(*(plansza + x + 3) + y + 3) = *(*(plansza + x + 2) + y + 4) = 1;
}


void Plansza::Koniczynka(int x, int y)
{
	if ((rozmiar_x < 5) || (rozmiar_y < 5) || (x + 5 > rozmiar_x) || (y + 5 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 5; i++)
	{
		for (int j = y; j < y + 5; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 2) + y + 3) = *(*(plansza + x + 3) + y + 2) = 1;
}


void Plansza::Staw(int x, int y)
{
	if ((rozmiar_x < 6) || (rozmiar_y < 6) || (x + 6 > rozmiar_x) || (y + 6 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 6; i++)
	{
		for (int j = y; j < y + 6; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 1) + y + 3) = *(*(plansza + x + 4) + y + 2) = *(*(plansza + x + 4) + y + 3) = *(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 3) + y + 1) = *(*(plansza + x + 2) + y + 4) = *(*(plansza + x + 3) + y + 4) = 1;
}


void Plansza::Krokodyl(int x, int y)
{
	if ((rozmiar_x < 16) || (rozmiar_y < 9) || (x + 16 > rozmiar_x) || (y + 9 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 16; i++)
	{
		for (int j = y; j < y + 9; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 5) + y + 2) = *(*(plansza + x + 6) + y + 2) = *(*(plansza + x + 7) + y + 2) = *(*(plansza + x + 8) + y + 2) = *(*(plansza + x + 9) + y + 2) = *(*(plansza + x + 10) + y + 2) = 1;
	*(*(plansza + x + 4) + y + 3) = *(*(plansza + x + 11) + y + 3) = 1;
	*(*(plansza + x + 3) + y + 4) = *(*(plansza + x + 12) + y + 4) = 1;
	*(*(plansza + x + 4) + y + 5) = *(*(plansza + x + 11) + y + 5) = 1;
	*(*(plansza + x + 5) + y + 6) = *(*(plansza + x + 6) + y + 6) = *(*(plansza + x + 7) + y + 6) = *(*(plansza + x + 8) + y + 6) = *(*(plansza + x + 9) + y + 6) = *(*(plansza + x + 10) + y + 6) = 1;
} 


void Plansza::LotSzybowca(int x, int y)
{

	if ((rozmiar_x < 5) || (rozmiar_y < 5) || (x + 5 > rozmiar_x) || (y + 5 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 5; i++)
	{
		for (int j = y; j < y + 5; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 2) + y + 3) = *(*(plansza + x + 3) + y + 1) = *(*(plansza + x + 3) + y + 2) = *(*(plansza + x + 3) + y + 3) = 1;
}


void Plansza::Fontanna(int x, int y)
{
	if ((rozmiar_x < 9) || (rozmiar_y < 11) || (x + 9 > rozmiar_x) || (y + 11 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 9; i++)
	{
		for (int j = y; j < y + 11; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 2) + y + 1) = *(*(plansza + x + 8) + y + 1) = *(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 3) + y + 2) = *(*(plansza + x + 7) + y + 2) = *(*(plansza + x + 9) + y + 2) = 1; 
	*(*(plansza + x + 3) + y + 3) = *(*(plansza + x + 4) + y + 3) = *(*(plansza + x + 6) + y + 3) = *(*(plansza + x + 7) + y + 3) = 1;
	*(*(plansza + x + 2) + y + 4) = *(*(plansza + x + 3) + y + 4) = *(*(plansza + x + 7) + y + 4) = *(*(plansza + x + 8) + y + 4) = 1;
	*(*(plansza + x + 3) + y + 5) = *(*(plansza + x + 4) + y + 5) = *(*(plansza + x + 6) + y + 5) = *(*(plansza + x + 7) + y + 5) = 1;
}


void Plansza::LotDakoty(int x, int y)
{
	if ((rozmiar_x < 7) || (rozmiar_y < 8) || (x + 7 > rozmiar_x) || (y + 8 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 7; i++)
	{
		for (int j = y; j < y + 8; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 1) + y + 2) = *(*(plansza + x + 2) + y + 2) = *(*(plansza + x + 3) + y + 2) = *(*(plansza + x + 4) + y + 2) = *(*(plansza + x + 5) + y + 2) = 1;
	*(*(plansza + x + 1) + y + 3) = *(*(plansza + x + 6) + y + 3) = 1;
	*(*(plansza + x + 1) + y + 4) = 1;
	*(*(plansza + x + 2) + y + 5) = *(*(plansza + x + 6) + y + 5) = 1;
	*(*(plansza + x + 4) + y + 6) = 1;
}

void Plansza::Wyrzutnie(int x, int y)
{
	if ((rozmiar_x < 11) || (rozmiar_y < 38) || (x + 11 > rozmiar_x) || (y + 38 > rozmiar_y))
	{
		return;
	}
	//wyzerowanie obszaru w którym zostanie wstawiona figura
	for (int i = x; i < x + 11; i++)
	{
		for (int j = y; j < y + 38; j++)
		{
			plansza[i][j] = 0;
		}
	}
	*(*(plansza + x + 24) + y + 1) = *(*(plansza + x + 22) + y + 2) = *(*(plansza + x + 24) + y + 2) = *(*(plansza + x + 13) + y + 3) = *(*(plansza + x + 21) + y + 3) = *(*(plansza + x + 23) + y + 3) = 1;
	*(*(plansza + x + 12) + y + 4) = *(*(plansza + x + 13) + y + 4) = *(*(plansza + x + 20) + y + 4) = *(*(plansza + x + 23) + y + 4) = 1;
	Klocek(x, y + 5);
	Klocek(x + 34, y + 3);
	*(*(plansza + x + 11) + y + 5) = *(*(plansza + x + 12) + y + 5) = *(*(plansza + x + 17) + y + 5) = *(*(plansza + x + 18) + y + 5) = *(*(plansza + x + 21) + y + 5) = *(*(plansza + x + 23) + y + 5) = 1;
	*(*(plansza + x + 10) + y + 6) = *(*(plansza + x + 11) + y + 6) = *(*(plansza + x + 12) + y + 6) = *(*(plansza + x + 17) + y + 6) = *(*(plansza + x + 18) + y + 6) = *(*(plansza + x + 22) + y + 6) = *(*(plansza + x + 24) + y + 6) = 1;
	*(*(plansza + x + 11) + y + 7) = *(*(plansza + x + 12) + y + 7) = *(*(plansza + x + 17) + y + 7) = *(*(plansza + x + 18) + y + 7) = *(*(plansza + x + 24) + y + 7) = 1;
	*(*(plansza + x + 12) + y + 8) = *(*(plansza + x + 13) + y + 8) = *(*(plansza + x + 13) + y + 9) = 1;
}