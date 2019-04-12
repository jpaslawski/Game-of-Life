/*
"----------------------------------------------------------------------------GRA W �YCIE--------------------------------------------------------------------------------------------"
Gra toczy si� na planszy podzielonej na kwadratowe kom�rki.
Ka�da kom�rka ma o�miu �s�siad�w�, czyli kom�rki przylegaj�ce do niej bokami i rogami.
Ka�da kom�rka mo�e znajdowa� si� w jednym z dw�ch stan�w: mo�e by� albo ��ywa�, albo �martwa�.
Kom�rka jest �ywa je�li:
a) w poprzednim pokoleniu by�a martwa i ma 3 �ywych s�siad�w;
b) w poprzednim pokoleniu by�a �ywa i ma 2 lub 3 �ywych s�siad�w
W pozosta�ych przypadkach jest martwa.
Stan wszystkich kom�rek w pewnej jednostce czasu jest u�ywany do obliczenia stanu wszystkich kom�rek w nast�pnej jednostce.
Po obliczeniu wszystkie kom�rki zmieniaj� sw�j stan dok�adnie w tym samym momencie.
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
	setlocale(LC_ALL, ""); //do��czenie polskich znak�w
	srand(time(NULL)); //inicjalizacja generatora liczb pseudolosowych
	sf::RenderWindow okno(sf::VideoMode(1280, 960), "Gra w zycie");
	tgui::Gui gui{ okno };
	Menu m;

	m.Start(gui, okno);

	return EXIT_SUCCESS;
}