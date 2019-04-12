#include "Menu.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}


void Menu::Start(tgui::Gui& gui, sf::RenderWindow& window)
{
	gui.removeAllWidgets();
	window.setPosition(sf::Vector2i(200, 0));
	tgui::Theme theme;
	theme.load("themes/Black.txt");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	tgui::Button::Ptr p_opcje = tgui::Button::create("OPCJE");
	p_opcje->setPosition({ "20%", "30%" });
	p_opcje->setSize({ "60%", "20%" });
	p_opcje->setTextSize(30);
	p_opcje->setRenderer(theme.getRenderer("button"));
	p_opcje->connect("clicked", &Menu::Opcje, this, std::ref(gui), std::ref(window));

	auto komorka = tgui::EditBox::create();
	komorka->setSize( 384, 96);
	komorka->setPosition({ "50%", "85%" });
	komorka->setText("8");
	komorka->setTextSize(40);
	komorka->setRenderer(theme.getRenderer("editbox"));

	auto rozmiar_x = tgui::EditBox::create();
	rozmiar_x->setSize(384, 96);
	rozmiar_x->setPosition({ "50%", "55%" });
	rozmiar_x->setText("100");
	rozmiar_x->setTextSize(40);
	rozmiar_x->setRenderer(theme.getRenderer("editbox"));

	auto rozmiar_y = tgui::EditBox::create();
	rozmiar_y->setSize( 384, 96);
	rozmiar_y->setPosition({ "50%", "70%" });
	rozmiar_y->setTextSize(40);
	rozmiar_y->setText("100");
	rozmiar_y->setRenderer(theme.getRenderer("editbox"));

	sf::Text szer;
	szer.setFont(font);
	szer.setString("Szerokosc planszy:");
	szer.setCharacterSize(40);
	szer.setFillColor(sf::Color::Black);
	szer.setPosition(250, 550);

	sf::Text wys;
	wys.setFont(font);
	wys.setString("Wysokosc planszy:");
	wys.setCharacterSize(40);
	wys.setFillColor(sf::Color::Black);
	wys.setPosition(250, 690);

	sf::Text wiel;
	wiel.setFont(font);
	wiel.setString("Wielkosc komorki:");
	wiel.setCharacterSize(40);
	wiel.setFillColor(sf::Color::Black);
	wiel.setPosition(250, 830);

	tgui::Button::Ptr p_start = tgui::Button::create("URUCHOM");
	p_start->setPosition({ "20%", "5%" });
	p_start->setSize({ "60%", "20%" });
	p_start->setTextSize(30);
	p_start->setRenderer(theme.getRenderer("button"));
	p_start->connect("clicked", &Menu::Symuluj, this, std::ref(gui), std::ref(window), std::ref(rozmiar_x), std::ref(rozmiar_y), std::ref(komorka));

	gui.add(p_start);
	gui.add(p_opcje);
	gui.add(komorka);
	gui.add(rozmiar_x);
	gui.add(rozmiar_y);

	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color(229, 229, 229));

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				gui.setView(window.getView());
			}
			gui.handleEvent(event);
		}
		gui.draw();
		window.draw(szer);
		window.draw(wys);
		window.draw(wiel);
		window.display();
	}
}


void Menu::Symuluj(tgui::Gui& gui, sf::RenderWindow& window, tgui::EditBox::Ptr rozmiar_x, tgui::EditBox::Ptr rozmiar_y, tgui::EditBox::Ptr komorka)
{
	gui.removeAllWidgets();
	tgui::Theme theme;
	theme.load("themes/Black.txt");

	if (is_number(rozmiar_x->getText().toAnsiString()) == true)
	{
		int x = std::stoi(rozmiar_x->getText().toAnsiString(), nullptr, 10); //konwersja wprowadzonej wartoœci typu string do typu int
		szerokosc = x;
	}

	if (is_number(rozmiar_y->getText().toAnsiString()) == true)
	{
		int y = std::stoi(rozmiar_y->getText().toAnsiString(), nullptr, 10);
		wysokosc = y;
	}

	if (is_number(komorka->getText().toAnsiString()) == true)
	{
		float rozmiar = std::stof(komorka->getText().toAnsiString(), nullptr);
		wielkosc = rozmiar;
	}
	
	Plansza p(szerokosc, wysokosc);
	Komorki k;
	p.Zeruj();

	tgui::Button::Ptr jedna = tgui::Button::create("Komorka");
	jedna->setPosition(szerokosc * wielkosc, 0);
	jedna->setSize(100, 100);
	jedna->setTextSize(15);
	jedna->setRenderer(theme.getRenderer("button"));
	jedna->connect("clicked", &Menu::ZmienStan, this, "Komorka");

	tgui::Button::Ptr klocek = tgui::Button::create("Klocek");
	klocek->setPosition(szerokosc * wielkosc + 100, 0);
	klocek->setSize(100, 100);
	klocek->setTextSize(15);
	klocek->setRenderer(theme.getRenderer("button"));
	klocek->connect("clicked", &Menu::ZmienStan, this, "Klocek");

	tgui::Button::Ptr lodz = tgui::Button::create("Lodz");
	lodz->setPosition(szerokosc * wielkosc, 100);
	lodz->setSize(100, 100);
	lodz->setTextSize(15);
	lodz->setRenderer(theme.getRenderer("button"));
	lodz->connect("clicked", &Menu::ZmienStan, this, "Lodz");

	tgui::Button::Ptr bochenek = tgui::Button::create("Bochenek");
	bochenek->setPosition(szerokosc * wielkosc + 100, 100);
	bochenek->setSize(100, 100);
	bochenek->setTextSize(15);
	bochenek->setRenderer(theme.getRenderer("button"));
	bochenek->connect("clicked", &Menu::ZmienStan, this, "Bochenek");

	tgui::Button::Ptr krysztal = tgui::Button::create("Krysztal");
	krysztal->setPosition(szerokosc * wielkosc, 200);
	krysztal->setSize(100, 100);
	krysztal->setTextSize(15);
	krysztal->setRenderer(theme.getRenderer("button"));
	krysztal->connect("clicked", &Menu::ZmienStan, this, "Krysztal");

	tgui::Button::Ptr koniczynka = tgui::Button::create("Koniczynka");
	koniczynka->setPosition(szerokosc * wielkosc + 100, 200);
	koniczynka->setSize(100, 100);
	koniczynka->setTextSize(15);
	koniczynka->setRenderer(theme.getRenderer("button"));
	koniczynka->connect("clicked", &Menu::ZmienStan, this, "Koniczynka");

	tgui::Button::Ptr staw = tgui::Button::create("Staw");
	staw->setPosition(szerokosc * wielkosc, 300);
	staw->setSize(100, 100);
	staw->setTextSize(15);
	staw->setRenderer(theme.getRenderer("button"));
	staw->connect("clicked", &Menu::ZmienStan, this, "Staw");

	tgui::Button::Ptr krokodyl = tgui::Button::create("Krokodyl");
	krokodyl->setPosition(szerokosc * wielkosc + 100, 300);
	krokodyl->setSize(100, 100);
	krokodyl->setTextSize(15);
	krokodyl->setRenderer(theme.getRenderer("button"));
	krokodyl->connect("clicked", &Menu::ZmienStan, this, "Krokodyl");

	tgui::Button::Ptr lot = tgui::Button::create("Lot Szybowca");
	lot->setPosition(szerokosc * wielkosc, 400);
	lot->setSize(100, 100);
	lot->setTextSize(13);
	lot->setRenderer(theme.getRenderer("button"));
	lot->connect("clicked", &Menu::ZmienStan, this, "Lot Szybowca");

	tgui::Button::Ptr fontanna = tgui::Button::create("Fontanna");
	fontanna->setPosition(szerokosc * wielkosc + 100, 400);
	fontanna->setSize(100, 100);
	fontanna->setTextSize(15);
	fontanna->setRenderer(theme.getRenderer("button"));
	fontanna->connect("clicked", &Menu::ZmienStan, this, "Fontanna");

	tgui::Button::Ptr dakota = tgui::Button::create("Lot Dakoty");
	dakota->setPosition(szerokosc * wielkosc, 500);
	dakota->setSize(100, 100);
	dakota->setTextSize(15);
	dakota->setRenderer(theme.getRenderer("button"));
	dakota->connect("clicked", &Menu::ZmienStan, this, "Lot Dakoty");

	tgui::Button::Ptr wyrzutnie = tgui::Button::create("Wyrzutnie");
	wyrzutnie->setPosition(szerokosc * wielkosc + 100, 500);
	wyrzutnie->setSize(100, 100);
	wyrzutnie->setTextSize(15);
	wyrzutnie->setRenderer(theme.getRenderer("button"));
	wyrzutnie->connect("clicked", &Menu::ZmienStan, this, "Wyrzutnie");

	tgui::Button::Ptr wznow = tgui::Button::create("Wznow");
	wznow->setPosition(0, wysokosc * wielkosc);
	wznow->setSize(100, 100);
	wznow->setTextSize(15);
	wznow->setRenderer(theme.getRenderer("button"));
	wznow->connect("clicked", &Menu::Pauza, this, "Wznow");

	tgui::Button::Ptr zatrzymaj = tgui::Button::create("Zatrzymaj");
	zatrzymaj->setPosition(100, wysokosc * wielkosc);
	zatrzymaj->setSize(100, 100);
	zatrzymaj->setTextSize(15);
	zatrzymaj->setRenderer(theme.getRenderer("button"));
	zatrzymaj->connect("clicked", &Menu::Pauza, this, "Zatrzymaj");

	tgui::Button::Ptr nastepne = tgui::Button::create("Nastepne");
	nastepne->setPosition(200, wysokosc * wielkosc);
	nastepne->setSize(100, 100);
	nastepne->setTextSize(15);
	nastepne->setRenderer(theme.getRenderer("button"));
	nastepne->connect("clicked", &Menu::Pauza, this, "Nastepne");

	auto klatki = tgui::EditBox::create();
	klatki->setSize(100, 100);
	klatki->setPosition(400, wysokosc * wielkosc);
	klatki->setTextSize(40);
	klatki->setText("30");
	klatki->setRenderer(theme.getRenderer("editbox"));

	tgui::Button::Ptr zmianaklatek = tgui::Button::create("Zmien \n  FPS");
	zmianaklatek->setPosition(500, wysokosc * wielkosc);
	zmianaklatek->setSize(100, 100);
	zmianaklatek->setTextSize(15);
	zmianaklatek->setRenderer(theme.getRenderer("button"));
	zmianaklatek->connect("clicked", &Menu::ZmienFps, this, std::ref(klatki));

	tgui::Button::Ptr losuj = tgui::Button::create("Losuj");
	losuj->setPosition(szerokosc * wielkosc, wysokosc * wielkosc);
	losuj->setSize(100, 100);
	losuj->setTextSize(15);
	losuj->setRenderer(theme.getRenderer("button"));
	losuj->connect("clicked", &Menu::ZmienStan, this, "Losuj");

	tgui::Button::Ptr wyczysc = tgui::Button::create("Wyczysc");
	wyczysc->setPosition(szerokosc * wielkosc + 100, wysokosc * wielkosc);
	wyczysc->setSize(100, 100);
	wyczysc->setTextSize(15);
	wyczysc->setRenderer(theme.getRenderer("button"));
	wyczysc->connect("clicked", &Menu::ZmienStan, this, "Wyczysc");

	window.setSize(sf::Vector2u(szerokosc * wielkosc + 200, wysokosc * wielkosc + 100));
	window.setVerticalSyncEnabled(true);
	gui.add(jedna);
	gui.add(klocek);
	gui.add(lodz);
	gui.add(bochenek);
	gui.add(krysztal);
	gui.add(koniczynka);
	gui.add(staw);
	gui.add(krokodyl);
	gui.add(lot);
	gui.add(fontanna);
	gui.add(dakota);
	gui.add(wyrzutnie);
	gui.add(wznow);
	gui.add(zatrzymaj);
	gui.add(nastepne);
	gui.add(klatki);
	gui.add(zmianaklatek);
	gui.add(losuj);
	gui.add(wyczysc);

	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color(229, 229, 229));
		window.setFramerateLimit(fps);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				gui.setView(window.getView());
			}
			else if (event.type == sf::Event::MouseButtonPressed) 
			{
				int _x = Mouse::getPosition(window).x / wielkosc;
				int _y = Mouse::getPosition(window).y / wielkosc;

				if ((stan == 0) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Ustaw(_x, _y);
				}
				else if ((stan == 1) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Klocek(_x, _y);
				}
				else if ((stan == 2) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Lodz(_x, _y);
				}
				else if ((stan == 3) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Bochenek(_x, _y);
				}
				else if ((stan == 4) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Krysztal(_x, _y);
				}
				else if ((stan == 5) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Koniczynka(_x, _y);
				}
				else if ((stan == 6) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Staw(_x, _y);
				}
				else if ((stan == 7) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Krokodyl(_x, _y);
				}
				else if ((stan == 8) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.LotSzybowca(_x, _y);
				}
				else if ((stan == 9) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Fontanna(_x, _y);
				}
				else if ((stan == 10) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.LotDakoty(_x, _y);
				}
				else if ((stan == 11) && (_x <= szerokosc - 1) && (_y <= wysokosc - 1))
				{
					p.Wyrzutnie(_x, _y);
				}
			}
			gui.handleEvent(event);
		}

		if (stan == 19)
	    {
			p.Losuj();
			stan = 0;
		}
		
		if (stan == 20)
		{
			p.Zeruj();
		}

		k.Rysuj(p, szerokosc, wysokosc, wielkosc, window);
		gui.draw();
		window.display();
		Sleep(50);
		if (pauza != 0)
		{	
			p.NastepnePokolenie(p, k, w1, w2 ,w3);
			if (pauza == 2) pauza = 0;
		}
	}
}


void Menu::Opcje(tgui::Gui& gui, sf::RenderWindow& window)
{
	gui.removeAllWidgets();
	tgui::Theme theme;
	theme.load("themes/Black.txt");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}

	tgui::Button::Ptr p_wroc = tgui::Button::create("WSTECZ");
	p_wroc->setPosition(0, 0);
	p_wroc->setSize(300, 100);
	p_wroc->setTextSize(30);
	p_wroc->setRenderer(theme.getRenderer("button"));
	p_wroc->connect("clicked", &Menu::Start, this, std::ref(gui), std::ref(window));

	sf::Text napis1;
	napis1.setFont(font);
	napis1.setString("Komorka zywa wtedy, gdy ma           sasiadow zywych,\na w poprzednim pokoleniu byla martwa.");
	napis1.setCharacterSize(40);
	napis1.setFillColor(sf::Color::Black);
	napis1.setPosition(150, 200);

	sf::Text napis2;
	napis2.setFont(font);
	napis2.setString("Komorka zywa wtedy, gdy ma           lub          \nsasiadow zywych, a w poprzednim pokoleniu byla zywa.");
	napis2.setCharacterSize(40);
	napis2.setFillColor(sf::Color::Black);
	napis2.setPosition(150, 400);

	sf::Text napis3;
	napis3.setFont(font);
	napis3.setString("UWAGA! Po zmianie warunków stale figury zmienia zachowanie.");
	napis3.setCharacterSize(40);
	napis3.setFillColor(sf::Color::Black);
	napis3.setPosition(50, 880);

	auto warunek1 = tgui::EditBox::create();
	warunek1->setSize(100, 50);
	warunek1->setPosition(690, 200);
	warunek1->setTextSize(40);
	warunek1->setText("3");
	warunek1->setRenderer(theme.getRenderer("editbox"));

	auto warunek2 = tgui::EditBox::create();
	warunek2->setSize(100, 50);
	warunek2->setPosition(690, 400);
	warunek2->setTextSize(40);
	warunek2->setText("2");
	warunek2->setRenderer(theme.getRenderer("editbox"));

	auto warunek3 = tgui::EditBox::create();
	warunek3->setSize(100, 50);
	warunek3->setPosition(870, 400);
	warunek3->setTextSize(40);
	warunek3->setText("3");
	warunek3->setRenderer(theme.getRenderer("editbox"));

	tgui::Button::Ptr zatwierdz = tgui::Button::create("ZATWIERDZ");
	zatwierdz->setPosition(500, 700);
	zatwierdz->setSize(300, 100);
	zatwierdz->setTextSize(30);
	zatwierdz->setRenderer(theme.getRenderer("button"));
	zatwierdz->connect("clicked", &Menu::ZmienWarunki, this, std::ref(warunek1), std::ref(warunek2), std::ref(warunek3));

	gui.add(p_wroc);
	gui.add(zatwierdz);
	gui.add(warunek1);
	gui.add(warunek2);
	gui.add(warunek3);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				gui.setView(window.getView());
			}
			gui.handleEvent(event);
		}
		gui.draw();
		window.draw(napis1);
		window.draw(napis2);
		window.draw(napis3);
		window.display();
		window.clear(sf::Color(229, 229, 229));
	}
}


void Menu::ZmienStan(sf::String nazwa)
{
	if (nazwa == "Komorka")
	{
		stan = 0;
		return;
	}
	else if (nazwa == "Klocek")
	{
		stan = 1;
		return;
	}
	else if (nazwa == "Lodz")
	{
		stan = 2;
		return;
	}
	else if (nazwa == "Bochenek")
	{
		stan = 3;
		return;
	}
	else if (nazwa == "Krysztal")
	{
		stan = 4;
		return;
	}
	else if (nazwa == "Koniczynka")
	{
		stan = 5;
		return;
	}
	else if (nazwa == "Staw")
	{
		stan = 6;
		return;
	}
	else if (nazwa == "Krokodyl")
	{
		stan = 7;
		return;
	}
	else if (nazwa == "Lot Szybowca")
	{
		stan = 8;
		return;
	}
	else if (nazwa == "Fontanna")
	{
		stan = 9;
		return;
	}
	else if (nazwa == "Lot Dakoty")
	{
		stan = 10;
		return;
	}
	else if (nazwa == "Wyrzutnie")
	{
		stan = 11;
		return;
	}
	else if (nazwa == "Losuj")
	{
		stan = 19;
		return;
	}
	else if (nazwa == "Wyczysc")
	{
		stan = 20;
		return;
	}
}


void Menu::Pauza(sf::String nazwa)
{
	if (nazwa == "Wznow")
	{
	pauza = 1;
	return;
	}
	else if (nazwa == "Zatrzymaj")
	{
	pauza = 0;
	return;
	}
	else if (nazwa == "Nastepne")
	{
		pauza = 2;
		return;
	}
}


void Menu::ZmienWarunki(tgui::EditBox::Ptr warunek1, tgui::EditBox::Ptr warunek2, tgui::EditBox::Ptr warunek3)
{
	if (is_number(warunek1->getText().toAnsiString()) == true)
	{
		int war1 = std::stoi(warunek1->getText().toAnsiString(), nullptr, 10); //konwersja wprowadzonej wartoœci typu string do typu int
		w1 = war1;
	}
	
	if (is_number(warunek2->getText().toAnsiString()) == true)
	{
		int war2 = std::stoi(warunek2->getText().toAnsiString(), nullptr, 10); //konwersja wprowadzonej wartoœci typu string do typu int
		w2 = war2;
	}
	
	if (is_number(warunek3->getText().toAnsiString()) == true)
	{
		int war3 = std::stoi(warunek3->getText().toAnsiString(), nullptr, 10); //konwersja wprowadzonej wartoœci typu string do typu int
		w3 = war3;
	}
}


bool Menu::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void Menu::ZmienFps(tgui::EditBox::Ptr klatki)
{
	if (is_number(klatki->getText().toAnsiString()) == true)
	{
		int k = std::stoi(klatki->getText().toAnsiString(), nullptr, 10); //konwersja wprowadzonej wartoœci typu string do typu int
		fps = k;
	}
}