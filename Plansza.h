#pragma once
#include "Komorki.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Plansza 
{
	friend class Komorki; //okre�lenie relacji przyja�ni z klas� Komorki
	//deklaracja zmiennych
	int rozmiar_x, //liczba wierszy
		rozmiar_y; //liczba kolumn
	int **plansza, //tablica dynamiczna dwuwymiarowa, kt�ra b�dzie wy�wietlana
		**bufor;  //tablica dynamiczna dwuwymiarowa, w kt�rej b�d� dokonywane zmiany mi�dzypokoleniowe
	int nr_pokolenia; //numer pokolenia

public:
	//! Konstruktor domy�lny
/*!
Tworzy plansze o rozmiarach 10x10, tym samym inicjuj�c pola sk�adowe klasy Plansza.
  */
	Plansza();
		//! Konstruktor z parametrami tworz�cy plansz� o 
/*!
Tworzy plansze o rozmiarach 10x10, tym samym inicjuj�c pola sk�adowe klasy Plansza.
  */
	Plansza(int rozmiar_x, int rozmiar_y); //konstruktor tworz�cy plansze o rozmiarach x*y
	~Plansza(); //destruktor
	int **getPlansza();
	void NastepnePokolenie(Plansza &p, Komorki &k, int w1, int w2, int w3); //funkcja wprowadzaj�ca zmiany w planszy, okre�laj�ca jak b�dzie wygl�da�o ast�pne pokolenie
	void Zeruj();
	void Losuj();
	void Ustaw(int x, int y); //funkcja o�ywiaj�ca kom�rk� o koordynatach (x, y)
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

