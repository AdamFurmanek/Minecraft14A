#ifndef Menu_h
#define Menu_h

#include "Colors.h"
#include <GL/glut.h>
#include <iostream>
#include <GL/freeglut.h>

/*! \class Menu Menu.h
 *  \brief Klasa stanowi�ca menu aplikacji.
 *
 *  Pozwala u�ytkownikowi na wybieranie spo�r�d opcji menu. Istniej� dwa rodzaje plansz menu.
 *  "Menu g��wne" to pocz�tkowa plansza (stan 0 aplikacji), w kt�rej u�ytkownik ma mo�liwo�� przej�cia do rozgrywki poprzez wyb�r stworzenia nowego �wiata lub wczytania uprzednio stworzonego.
 *  Plansza "zapis/wczytanie" (stan 1 lub 3 aplikacji)  pozwala na wyb�r slotu zapisu gry. U�ywa si� jej przy wczytywaniu jak i przy zapisywaniu �wiata.
 */
class Menu
{
private:
	bool saves[8];

	/*! \fn void Menu::RenderRectangle(float a1, float b1, float a2, float b2, const float color[3])
	 *  \brief Metoda u�atwiaj�ca rysowanie prostok�t w odpowiednim kolorze.
	 *	\param a1 wsp�rz�dna x g�rnego lewego wierzcho�ka prostok�ta
	 *	\param b1 wsp�rz�dna y g�rnego lewego wierzcho�ka prostok�ta
	 *  \param a2 wsp�rz�dna x dolnego prawego wierzcho�ka prostok�ta
	 *  \param b2 wsp�rz�dna y dolnego prawego wierzcho�ka prostok�ta
	 *  \param color tablica RGB stanowi�ca kolor wype�nienie prostok�ta
	 */
	void RenderRectangle(float a1, float b1, float a2, float b2, const float color[3]);

	/*! \fn void Menu::RenderRectangle(float a1, float b1, float a2, float b2, const float color[3])
	 *  \brief Metoda u�atwiaj�ca rysowanie tekstu. Dla lepszego efektu nak�ada si� na siebie dwie warstwy napisu w dw�ch kolorach.
	 *	\param text tre�� napisu
	 *	\param x wsp�rz�dna x pocz�tku pisania
	 *  \param y wsp�rz�dna y pocz�tku pisania
	 *  \param scale wielko�� pisanego tekstu
	 *  \param colorB tablica RGB stanowi�ca tylny kolor napisu (background)
	 *  \param colorF tablica RGB stanowi�ca przedni kolor napisu (foreground)
	 */
	void RenderText(std::string text, float x, float y, float scale, const float colorB[3], const float colorF[3]);

	/*! \fn void Menu::CheckSaves()
	 *  \brief Metoda sprawdzaj�ca istniej�ce pliki zapisu.
	 * 
	 *  W katalogu z gr� zapisywane s� pliki save1 - save8. Metoda sprawdz czy elementy istniej�, aby wy�wietli� odpowiedni� informacj� w menu.
	 */
	void CheckSaves();

public:

	/*! \fn void Menu::InitMenu()
	 *  \brief Metoda inicjuj�ca menu.
	 *
	 *  Inicjacja nie jest u�ywana tylko przy uruchomieniu aplikacji.
	 *  Wykorzystuje si� j�, gdy z rozgrywki przechodzi si� do kt�rej� z plansz menu, aby w��czy� odpowiednie parametry wy�wietlania.
	 *  Ustawiania jest odpowiednia grubo�� linii (dla napis�w), wy��cza si� funkcje dotycz�ce bezpo�rednio rozrywki i wywo�uje reshape.
	 *  Na koniec sprawdzane s� pliki zapisu.
	 */
	void InitMenu();

	/*! \fn void Menu::MenuDisplay()
	 *  \brief Wy�wietlacz planszy "menu g��wne".
	 *
	 *  U�ywana gdy stan aplikacji to 0.
	 *  Wy�wietla menu g��wne stworzone z kolorowych prostok�t�w i napis�w.
	 */
	void MenuDisplay();

	/*! \fn void Menu::MenuReshape()
	 *  \brief Metoda zmieniaj�ca rozmiar okna.
	 * 	\param w nowa szeroko�� okna
	 *	\param h nowa wysoko�� okna
	 * 
	 *  U�ywana gdy stan aplikacji to 0, 1 lub 3.
	 */
	void MenuReshape(int w, int h);

	/*! \fn int Menu::MenuMouse(int x, int y)
	 *  \brief Obs�uga myszki (naci�ni�tej).
	 *  \param x wsp�rz�dna x myszki przy naci�ni�ciu
	 *  \param y wsp�rz�dna y myszki przy naci�ni�ciu
	 *  \return 1 - naci�ni�ty przycisk New Game; 2 - naci�ni�ty przycisk Load Game; 0 - �aden z przycisk�w nie zosta� naci�ni�ty
	 * 
	 *  U�ywana gdy stan aplikacji to 0.
	 *  Pobiera wsp�rz�dne myszki przy klikni�ciu.
	 *  Zwraca 1 2 lub 0 w zale�no�ci czy wsp�rz�dne myszki mieszcz� si� w polu jakiego� przycisku.
	 */
	int MenuMouse(int x, int y);

	/*! \fn void Menu::MenuMouseMove(int x, int y)
	 *  \brief Obs�uga myszki (ruszonej).
	 *  \param x nowa wsp�rz�dna x myszki
	 *  \param y nowa wsp�rz�dna y myszki
	 * 
	 *  U�ywana gdy stan aplikacji to 0.
	 *  Pobiera wsp�rz�dne myszki po ruszeniu.
	 *  Je�li wsp�rz�dne mieszcz� si� w polu jakiego� przycisku, kszta�t myszki zmienia si� w krzy�yk.
	 *  W przeciwnym wypadku kursor wraca do zwyk�ej formy.
	 */
	void MenuMouseMove(int x, int y);

	/*! \fn void Menu::SavingMenuDisplay()
	 *  \brief Wy�wietlacz planszy "zapis/wczytanie"
	 *
	 *  U�ywana gdy stan aplikacji to 1 lub 3.
	 *  Wy�wietla menu zapisu/wczytania stworzone z kolorowych prostok�t�w i napis�w.
	 *  Wy�wietla 8 slot�w zapisu, a w nich odpowiedni� informacj� czy zapis (plik) istnieje.
	 */
	void SavingMenuDisplay();

	/*! \fn int Menu::SavingMenuMouse(int x, int y)
	 *  \brief Obs�uga myszki (naci�ni�tej).
	 *  \param x wsp�rz�dna x myszki przy naci�ni�ciu
	 *  \param y wsp�rz�dna y myszki przy naci�ni�ciu
	 *  \return numer slotu zapisu
	 *
	 *  U�ywana bezpo�rednio gdy stan aplikacji to 3. Po�rednio u�ywana przy stanie 1.
	 *  Pobiera wsp�rz�dne myszki przy klikni�ciu.
	 *  Zwraca numer slotu zapisu, do kt�rego gracz chce zapisa� �wiat, w zale�no�ci czy wsp�rz�dne myszki mieszcz� si� w pol kt�rego� z nich.
	 */
	int SavingMenuMouse(int x, int y);

	/*! \fn int Menu::SavingMenuMouseChecked(int x, int y)
	 *  \brief Obs�uga myszki (naci�ni�tej).
	 *  \param x wsp�rz�dna x myszki przy naci�ni�ciu
	 *  \param y wsp�rz�dna y myszki przy naci�ni�ciu
	 *  \return numer slotu zapisu
	 *
	 *  U�ywana gdy stan aplikacji to 1.
	 *  Pobiera wsp�rz�dne myszki przy klikni�ciu.
	 *  Wywo�uje metod� SavingMenuMouse, a nast�pnie dodatkowo sprawdza czy �wiat w tym slocie istnieje.
	 *  Zwraca numer slotu zapisu, kt�ry gracz chce wczyta�, w zale�no�ci czy wsp�rz�dne myszki mieszcz� si� w pol kt�rego� z nich oraz je�li dany zapis istnieje.
	 */
	int SavingMenuMouseChecked(int x, int y);

	/*! \fn void Menu::SavingMenuMouseMove(int x, int y)
	 *  \brief Obs�uga myszki (ruszonej).
	 *  \param x nowa wsp�rz�dna x myszki
	 *  \param y nowa wsp�rz�dna y myszki
	 *
	 *  U�ywana gdy stan aplikacji to 1 lub 3.
	 *  Pobiera wsp�rz�dne myszki po ruszeniu.
	 *  Je�li wsp�rz�dne mieszcz� si� w polu jakiego� slotu, kszta�t myszki zmienia si� w krzy�yk.
	 *  W przeciwnym wypadku kursor wraca do zwyk�ej formy.
	 */
	void SavingMenuMouseMove(int x, int y);

};

#endif