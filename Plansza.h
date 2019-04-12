#pragma once
#include "Komorki.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Plansza 
{
	friend class Komorki; //okreœlenie relacji przyjaŸni z klas¹ Komorki
	//deklaracja zmiennych
	int rozmiar_x, //liczba wierszy
		rozmiar_y; //liczba kolumn
	int **plansza, //tablica dynamiczna dwuwymiarowa, która bêdzie wyœwietlana
		**bufor;  //tablica dynamiczna dwuwymiarowa, w której bêd¹ dokonywane zmiany miêdzypokoleniowe
	int nr_pokolenia; //numer pokolenia

public:
	//! Konstruktor domyœlny
/*!
Tworzy plansze o rozmiarach 10x10, tym samym inicjuj¹c pola sk³adowe klasy Plansza.
  */
	Plansza();
		//! Konstruktor z parametrami tworz¹cy planszê o 
/*!
Tworzy plansze o rozmiarach 10x10, tym samym inicjuj¹c pola sk³adowe klasy Plansza.
  */
	Plansza(int rozmiar_x, int rozmiar_y); //konstruktor tworz¹cy plansze o rozmiarach x*y
	~Plansza(); //destruktor
	int **getPlansza();
	void NastepnePokolenie(Plansza &p, Komorki &k, int w1, int w2, int w3); //funkcja wprowadzaj¹ca zmiany w planszy, okreœlaj¹ca jak bêdzie wygl¹da³o astêpne pokolenie
	void Zeruj();
	void Losuj();
	void Ustaw(int x, int y); //funkcja o¿ywiaj¹ca komórkê o koordynatach (x, y)
	void Klocek(int x, int y);
	void Lodz(int x, int y);
	void Bochenek(int x, int y);
	void Krysztal(int x, int y);
	void Koniczynka(int x, int y);
	void Staw(int x, int y);
	void Krokodyl(int x, int y);
	void LotSzybowca(int x, int y);
	void Fontanna(int x, int y);
	void LotDakoty(int x, int y);
	void Wyrzutnie(int x, int y);
};

