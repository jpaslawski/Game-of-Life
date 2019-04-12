#include "Komorki.h"
#include "Plansza.h"
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

Komorki::Komorki(Plansza & p, float x, float y, float rozmiar, sf::RenderWindow& window)
{
	int a = (int)x / rozmiar;
	int b = (int)y / rozmiar;
	kom.setPosition(x, y);
	kom.setSize({ rozmiar, rozmiar });
	kom.setOutlineThickness(-0.5);
	kom.setOutlineColor(Color::Color(100, 100, 100));
	if (*(*(p.plansza + a) + b) == 1)
	{
		kom.setFillColor(Color::Black);
	}
	else if (*(*(p.plansza + a) + b) == 0)
	{
		kom.setFillColor(Color::White);
	}
	else
		kom.setFillColor(Color::Red); //w razie b³êdów

	window.draw(kom);
}

Komorki::Komorki()
{
}

Komorki::~Komorki()
{
}


void Komorki::draw(sf::RenderTarget & target, sf::RenderStates state) const
{
	target.draw(this->kom, state);
}


void Komorki::Rysuj(Plansza &p, int roz_x, int roz_y, float rozmiar, sf::RenderWindow& window)
{
	for (int i = 0; i < roz_x; i++)
	{
		for (int j = 0; j < roz_y; j++)
		{
				Komorki kom(p, i * rozmiar, j * rozmiar, rozmiar, window);
		}
	}
}


//obliczenie iloœci zyj¹cych komórek s¹siaduj¹cych z komórk¹ (x,y) 
int Komorki::IloscSasiadow(Plansza &p, int x, int y)
{
	int ilosc = 0;
	ilosc = *(*(p.plansza + (x - 1 + p.rozmiar_x) % p.rozmiar_x) + (y - 1 + p.rozmiar_y) % p.rozmiar_y) + *(*(p.plansza + (x - 1 + p.rozmiar_x) % p.rozmiar_x) + (y + p.rozmiar_y) % p.rozmiar_y) +
		*(*(p.plansza + (x - 1 + p.rozmiar_x) % p.rozmiar_x) + (y + 1 + p.rozmiar_y) % p.rozmiar_y) + *(*(p.plansza + (x + p.rozmiar_x) % p.rozmiar_x) + (y - 1 + p.rozmiar_y) % p.rozmiar_y) + 
		*(*(p.plansza + (x + p.rozmiar_x) % p.rozmiar_x) + (y + 1 + p.rozmiar_y) % p.rozmiar_y) + *(*(p.plansza + (x + 1 + p.rozmiar_x) % p.rozmiar_x) + (y - 1 + p.rozmiar_y) % p.rozmiar_y) + 
		*(*(p.plansza + (x + 1 + p.rozmiar_x) % p.rozmiar_x) + (y + p.rozmiar_y) % p.rozmiar_y) + *(*(p.plansza + (x + 1 + p.rozmiar_x) % p.rozmiar_x) + (y + 1 + p.rozmiar_y) % p.rozmiar_y);

	return ilosc;
}

//sprawdzenie stanu komórki (¿ywa/ martwa)
int Komorki::StanKomorki(Plansza &p, int x, int y)
{
	int stan_kom = *(*(p.plansza + x) + y);
	return stan_kom;
}

