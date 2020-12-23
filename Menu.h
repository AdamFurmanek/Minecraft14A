#ifndef Menu_h
#define Menu_h

#include "Colors.h"
#include <GL/glut.h>
#include <iostream>
#include <GL/freeglut.h>

/*! \class Menu Menu.h
 *  \brief Klasa stanowi¹ca menu aplikacji.
 *
 *  Pozwala u¿ytkownikowi na wybieranie spoœród opcji menu. Istniej¹ dwa rodzaje plansz menu.
 *  "Menu g³ówne" to pocz¹tkowa plansza (stan 0 aplikacji), w której u¿ytkownik ma mo¿liwoœæ przejœcia do rozgrywki poprzez wybór stworzenia nowego œwiata lub wczytania uprzednio stworzonego.
 *  Plansza "zapis/wczytanie" (stan 1 lub 3 aplikacji)  pozwala na wybór slotu zapisu gry. U¿ywa siê jej przy wczytywaniu jak i przy zapisywaniu œwiata.
 */
class Menu
{
private:
	bool saves[8];

	/*! \fn void Menu::RenderRectangle(float a1, float b1, float a2, float b2, const float color[3])
	 *  \brief Metoda u³atwiaj¹ca rysowanie prostok¹t w odpowiednim kolorze.
	 *	\param a1 wspó³rzêdna x górnego lewego wierzcho³ka prostok¹ta
	 *	\param b1 wspó³rzêdna y górnego lewego wierzcho³ka prostok¹ta
	 *  \param a2 wspó³rzêdna x dolnego prawego wierzcho³ka prostok¹ta
	 *  \param b2 wspó³rzêdna y dolnego prawego wierzcho³ka prostok¹ta
	 *  \param color tablica RGB stanowi¹ca kolor wype³nienie prostok¹ta
	 */
	void RenderRectangle(float a1, float b1, float a2, float b2, const float color[3]);

	/*! \fn void Menu::RenderRectangle(float a1, float b1, float a2, float b2, const float color[3])
	 *  \brief Metoda u³atwiaj¹ca rysowanie tekstu. Dla lepszego efektu nak³ada siê na siebie dwie warstwy napisu w dwóch kolorach.
	 *	\param text treœæ napisu
	 *	\param x wspó³rzêdna x pocz¹tku pisania
	 *  \param y wspó³rzêdna y pocz¹tku pisania
	 *  \param scale wielkoœæ pisanego tekstu
	 *  \param colorB tablica RGB stanowi¹ca tylny kolor napisu (background)
	 *  \param colorF tablica RGB stanowi¹ca przedni kolor napisu (foreground)
	 */
	void RenderText(std::string text, float x, float y, float scale, const float colorB[3], const float colorF[3]);

	/*! \fn void Menu::CheckSaves()
	 *  \brief Metoda sprawdzaj¹ca istniej¹ce pliki zapisu.
	 * 
	 *  W katalogu z gr¹ zapisywane s¹ pliki save1 - save8. Metoda sprawdz czy elementy istniej¹, aby wyœwietliæ odpowiedni¹ informacjê w menu.
	 */
	void CheckSaves();

public:

	/*! \fn void Menu::InitMenu()
	 *  \brief Metoda inicjuj¹ca menu.
	 *
	 *  Inicjacja nie jest u¿ywana tylko przy uruchomieniu aplikacji.
	 *  Wykorzystuje siê j¹, gdy z rozgrywki przechodzi siê do którejœ z plansz menu, aby w³¹czyæ odpowiednie parametry wyœwietlania.
	 *  Ustawiania jest odpowiednia gruboœæ linii (dla napisów), wy³¹cza siê funkcje dotycz¹ce bezpoœrednio rozrywki i wywo³uje reshape.
	 *  Na koniec sprawdzane s¹ pliki zapisu.
	 */
	void InitMenu();

	/*! \fn void Menu::MenuDisplay()
	 *  \brief Wyœwietlacz planszy "menu g³ówne".
	 *
	 *  U¿ywana gdy stan aplikacji to 0.
	 *  Wyœwietla menu g³ówne stworzone z kolorowych prostok¹tów i napisów.
	 */
	void MenuDisplay();

	/*! \fn void Menu::MenuReshape()
	 *  \brief Metoda zmieniaj¹ca rozmiar okna.
	 * 	\param w nowa szerokoœæ okna
	 *	\param h nowa wysokoœæ okna
	 * 
	 *  U¿ywana gdy stan aplikacji to 0, 1 lub 3.
	 */
	void MenuReshape(int w, int h);

	/*! \fn int Menu::MenuMouse(int x, int y)
	 *  \brief Obs³uga myszki (naciœniêtej).
	 *  \param x wspó³rzêdna x myszki przy naciœniêciu
	 *  \param y wspó³rzêdna y myszki przy naciœniêciu
	 *  \return 1 - naciœniêty przycisk New Game; 2 - naciœniêty przycisk Load Game; 0 - ¿aden z przycisków nie zosta³ naciœniêty
	 * 
	 *  U¿ywana gdy stan aplikacji to 0.
	 *  Pobiera wspó³rzêdne myszki przy klikniêciu.
	 *  Zwraca 1 2 lub 0 w zale¿noœci czy wspó³rzêdne myszki mieszcz¹ siê w polu jakiegoœ przycisku.
	 */
	int MenuMouse(int x, int y);

	/*! \fn void Menu::MenuMouseMove(int x, int y)
	 *  \brief Obs³uga myszki (ruszonej).
	 *  \param x nowa wspó³rzêdna x myszki
	 *  \param y nowa wspó³rzêdna y myszki
	 * 
	 *  U¿ywana gdy stan aplikacji to 0.
	 *  Pobiera wspó³rzêdne myszki po ruszeniu.
	 *  Jeœli wspó³rzêdne mieszcz¹ siê w polu jakiegoœ przycisku, kszta³t myszki zmienia siê w krzy¿yk.
	 *  W przeciwnym wypadku kursor wraca do zwyk³ej formy.
	 */
	void MenuMouseMove(int x, int y);

	/*! \fn void Menu::SavingMenuDisplay()
	 *  \brief Wyœwietlacz planszy "zapis/wczytanie"
	 *
	 *  U¿ywana gdy stan aplikacji to 1 lub 3.
	 *  Wyœwietla menu zapisu/wczytania stworzone z kolorowych prostok¹tów i napisów.
	 *  Wyœwietla 8 slotów zapisu, a w nich odpowiedni¹ informacjê czy zapis (plik) istnieje.
	 */
	void SavingMenuDisplay();

	/*! \fn int Menu::SavingMenuMouse(int x, int y)
	 *  \brief Obs³uga myszki (naciœniêtej).
	 *  \param x wspó³rzêdna x myszki przy naciœniêciu
	 *  \param y wspó³rzêdna y myszki przy naciœniêciu
	 *  \return numer slotu zapisu
	 *
	 *  U¿ywana bezpoœrednio gdy stan aplikacji to 3. Poœrednio u¿ywana przy stanie 1.
	 *  Pobiera wspó³rzêdne myszki przy klikniêciu.
	 *  Zwraca numer slotu zapisu, do którego gracz chce zapisaæ œwiat, w zale¿noœci czy wspó³rzêdne myszki mieszcz¹ siê w pol któregoœ z nich.
	 */
	int SavingMenuMouse(int x, int y);

	/*! \fn int Menu::SavingMenuMouseChecked(int x, int y)
	 *  \brief Obs³uga myszki (naciœniêtej).
	 *  \param x wspó³rzêdna x myszki przy naciœniêciu
	 *  \param y wspó³rzêdna y myszki przy naciœniêciu
	 *  \return numer slotu zapisu
	 *
	 *  U¿ywana gdy stan aplikacji to 1.
	 *  Pobiera wspó³rzêdne myszki przy klikniêciu.
	 *  Wywo³uje metodê SavingMenuMouse, a nastêpnie dodatkowo sprawdza czy œwiat w tym slocie istnieje.
	 *  Zwraca numer slotu zapisu, który gracz chce wczytaæ, w zale¿noœci czy wspó³rzêdne myszki mieszcz¹ siê w pol któregoœ z nich oraz jeœli dany zapis istnieje.
	 */
	int SavingMenuMouseChecked(int x, int y);

	/*! \fn void Menu::SavingMenuMouseMove(int x, int y)
	 *  \brief Obs³uga myszki (ruszonej).
	 *  \param x nowa wspó³rzêdna x myszki
	 *  \param y nowa wspó³rzêdna y myszki
	 *
	 *  U¿ywana gdy stan aplikacji to 1 lub 3.
	 *  Pobiera wspó³rzêdne myszki po ruszeniu.
	 *  Jeœli wspó³rzêdne mieszcz¹ siê w polu jakiegoœ slotu, kszta³t myszki zmienia siê w krzy¿yk.
	 *  W przeciwnym wypadku kursor wraca do zwyk³ej formy.
	 */
	void SavingMenuMouseMove(int x, int y);

};

#endif