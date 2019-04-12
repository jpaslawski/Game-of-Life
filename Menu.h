#pragma once
#include "Plansza.h"
#include "Komorki.h"
#include <string.h>
#include <iostream>
#include <windows.h>
#include <TGUI/TGUI.hpp>
#include <algorithm> 
#include <cctype>

using namespace sf;
using namespace tgui;

class Menu
{
private:

public:
	int szerokosc = 100;
	int wysokosc = 100;
	float wielkosc = 8;
	int fps = 30;
	int stan = 0;
	int pauza = 1;
	int w1 = 3; int w2 = 2; int w3 = 3;

	Menu();
	~Menu();
	void Start(tgui::Gui& gui, sf::RenderWindow& window);
	void Symuluj(tgui::Gui& gui, sf::RenderWindow& window, tgui::EditBox::Ptr rozmiar_x, tgui::EditBox::Ptr rozmiar_y, tgui::EditBox::Ptr komorka);
	void Opcje(tgui::Gui& gui, sf::RenderWindow& window);
	void ZmienStan(sf::String nazwa);
	void Pauza(sf::String nazwa);
	void ZmienWarunki(tgui::EditBox::Ptr warunek1, tgui::EditBox::Ptr warunek2, tgui::EditBox::Ptr warunek3);
	bool is_number(const std::string& s);
	void ZmienFps(tgui::EditBox::Ptr klatki);
};

