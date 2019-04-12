/*
"----------------------------------------------------------------------------GRA W ¯YCIE--------------------------------------------------------------------------------------------"
Gra toczy siê na planszy podzielonej na kwadratowe komórki.
Ka¿da komórka ma oœmiu „s¹siadów”, czyli komórki przylegaj¹ce do niej bokami i rogami.
Ka¿da komórka mo¿e znajdowaæ siê w jednym z dwóch stanów: mo¿e byæ albo „¿ywa”, albo „martwa”.
Komórka jest ¿ywa jeœli:
a) w poprzednim pokoleniu by³a martwa i ma 3 ¿ywych s¹siadów;
b) w poprzednim pokoleniu by³a ¿ywa i ma 2 lub 3 ¿ywych s¹siadów
W pozosta³ych przypadkach jest martwa.
Stan wszystkich komórek w pewnej jednostce czasu jest u¿ywany do obliczenia stanu wszystkich komórek w nastêpnej jednostce.
Po obliczeniu wszystkie komórki zmieniaj¹ swój stan dok³adnie w tym samym momencie.
*/
#include "Komorki.h"
#include "Plansza.h"
#include "Menu.h"
#include <iostream>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <SFML/OpenGL.hpp>

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	setlocale(LC_ALL, ""); //do³¹czenie polskich znaków
	srand(time(NULL)); //inicjalizacja generatora liczb pseudolosowych
	sf::RenderWindow okno(sf::VideoMode(1280, 960), "Gra w zycie");
	tgui::Gui gui{ okno };
	Menu m;

	m.Start(gui, okno);

	return EXIT_SUCCESS;
}