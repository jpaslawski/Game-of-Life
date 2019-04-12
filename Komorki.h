#pragma once
#include "Plansza.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
//!  Klasa Komorki 
/*!
  W tej klasie znajduja sie metody zwracajace charakterystyke kazdej komorki planszy z osobna. Za pomoca tej klasy ustala sie rowniez unikalne w³asnosci kazdej komorki.
*/
class Komorki : public sf::Drawable
{
	//! Definicja przyjaŸni klasy Komorki z klas¹ Plansza. 
 /*!
   Takie rozwi¹zanie jest potrzebne, aby klasa Plansza mog³a korzystaæ ze zmiennych oraz funkcji zadeklarowanych w prywatnej czêœci klasy Komorki.
 */
	friend class Plansza;
private:
	//! Nadpisanie funkcji draw nale¿¹cej do biblioteki SFML. 
 /*!
 \funkcja draw()
 \target - pierwszy argument funkcji nale¿¹cy do klasy RenderTarget (SFML), który wskazuje na obiekt w którym chcemy narysowaæ dany kszta³t. W tym przypadku bêdzie to obiekt klasy RenderWindow. 
 \state - drugi argument funkcji nale¿¹cy do klasy RenderStates (SFML), który przechowuje obecnie u¿ywany stan renderowania 
   */
	virtual void draw(sf::RenderTarget & target, sf::RenderStates state) const override;

	//! Deklaracja pola klasy Komorki typu RectangleShape. 
/*!
W³asnoœci tego pola s¹ inicjowane w konstruktorze klasy Komorki i dotycz¹ pojedynczej komórki.
  */
	sf::RectangleShape kom;

public:
	//! Konstruktor z parametrami tworzacy kwadrat (komorke) o okreœlonym rozmiarze w wybranej pozycji na ekranie.
/*!
\p - obiekt klasy Plansza przekazywany do konstruktora, aby ustalic kolor komorki w zaleznosci od zawartosci tablicy.
\x - zmienna typu float przekazujaca numer kolumny, w ktorej powinna zostac narysowana komorka.
\y - zmienna typu float przekazujaca numer wiersza, w ktorym powinna zostac narysowana komorka.
\romiar - zmienna typu float przekazujaca wielkosc jaka bedzie miala komorka.
\window - obiekt klasy RenderWindow (SFML) przekazany do konstruktora, aby istniala mozliwosc narysowania utworzonej komorki.
  */
	Komorki(Plansza & p, float x, float y, float rozmiar, sf::RenderWindow& window);

	//! Konstruktor bezparametrowy
/*!
Ten konstruktor sluzy do utworzenia obiektu, ktory bedzie stosowany w innych klasach do korzystania z metod klasy Komorki.
  */
	Komorki();

	//! Destruktor
/*!
  */
	~Komorki();

	//! Metoda rysujaca/ aktualizujaca plansze na ekranie. 
/*!
\p - obiekt klasy Plansza jest przekazywany do metody Rysuj ze wzglêdu na to, ¿e w tej metodzie wywo³ywany jest konstruktor z parametrami.
\roz_x - zmienna typu int przekazujaca szerokosc planszy.
\roz_y - zmienna typu int przekazujaca wysokosc planszy.
\romiar - zmienna typu float przekazujaca wielkosc jaka bedzie miala komorka.
\window - obiekt klasy RenderWindow (SFML) przekazany do metody Rysuj ze wzglêdu na to, ¿e w tej metodzie wywo³ywany jest konstruktor z parametrami.
  */
	void Rysuj(Plansza &p, int roz_x, int roz_y, float rozmiar, sf::RenderWindow& window);

	//! Metoda zwracaj¹ca wartosc typu int wskazujaca ilosc zywych komorek wokol komorki o koordynatach (x, y). Ilosc zywych komorek jest ustalana na podstawie zsumowania zawartosci komorek o indeksach sasiadujacych ze wskazana komorka. 
	//! Taka mozliwosc istnieje, poniewaz stan komorki jest zapisany nastepujaco: komorka martwa (0), komorka zywa (1).
/*!
\p - obiekt klasy Plansza jest przekazywany do metody IloscSasiadow, aby skorzystac z tablicy tej klasy, ktora przechowuje stan wszystkich komorek.
\x - zmienna typu int przekazujaca numer kolumny sprawdzanej komorki.
\y - zmienna typu int przekazujaca numer wiersza sprawdzanej komorki.
  */
	int IloscSasiadow(Plansza &p, int x, int y); 

	//! Metoda zwracaj¹ca zawartosc tablicy klasy Plansza pod indeksami (x, y). Za pomoca tej metody mozna stwierdzic czy wskazana komorka jest zywa badz martwa.
/*!
\p - obiekt klasy Plansza jest przekazywany do metody IloscSasiadow, aby skorzystac z tablicy tej klasy, ktora przechowuje stan wszystkich komorek.
\x - zmienna typu int przekazujaca numer kolumny sprawdzanej komorki.
\y - zmienna typu int przekazujaca numer wiersza sprawdzanej komorki.
  */
	int StanKomorki(Plansza &p, int x, int y);
};