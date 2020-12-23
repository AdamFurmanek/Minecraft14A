#ifndef Window_h
#define Window_h

#include <GL/glut.h>
#include "Game.h"
#include "Menu.h"

/*! \class Window Window.h
 *  \brief Klasa obs³uguj¹ca okno aplikacji.
 *
 *	Jest singletonem, który tworzy okno i obs³uguje jego rendering, zmianê rozmiaru, timer oraz pozwala na interakcjê za pomoc¹ myszy i klawiatury.
 *  Wiêkszoœæ metod tej klasy jest tylko metod¹ steruj¹c¹, która oddelegowuje wykonanie operacji obiektowi odpowiedniej klasy (Game lub Menu) w zale¿noœci od stanu.
 *  Stany: 0 - g³ówne menu, 1 - menu wczytywania mapy, 2 - rozgrywka, 3 - menu zapisu mapy.
 */
class Window
{
private:

	static Window* engine;
	static Menu* menu;
	static Game* game;
	static int state;

	/*! \fn static void Window::Display()
	 *  \brief Metoda steruj¹ca wyœwietlaniem obrazu.
	 * 
	 *  Na koniec wyœwietlenie wywo³uj Redisplay.
	 */
	static void Display();

	/*! \fn static void Window::Reshape(int w, int h)
	 *  \brief Metoda steruj¹ca zmienianiem rozmiaru okna.
	 *	\param w nowa szerokoœæ okna
	 *	\param h nowa wysokoœæ okna
	 */
	static void Reshape(int w, int h);

	/*! \fn static void Window::Mouse(int button, int state1, int x, int y)
	 *  \brief Metoda steruj¹ca obs³ug¹ myszki (naciœniêtej).
	 *	\param button okreœla u¿yty przycisk
	 *	\param state1 okreœla rodzaj eventu (keydown/keyup)
	 *  \param x wspó³rzêdna x myszki przy naciœniêciu
	 *  \param y wspó³rzêdna y myszki przy naciœniêciu
	 */
	static void Mouse(int button, int state1, int x, int y);

	/*! \fn static void Window::MouseMove(int x1, int y1)
	 *  \brief Metoda steruj¹ca obs³ug¹ myszki (ruszonej).
	 *  \param x nowa wspó³rzêdna x myszki
	 *  \param y nowa wspó³rzêdna y myszki
	 */
	static void MouseMove(int x1, int y1);

	/*! \fn static void Window::PressKey(unsigned char key, int xx, int yy)
	 *  \brief Metoda steruj¹ca obs³ug¹ klawiatury (przy naciœniêciu klawisza).
	 *	\param key okreœla u¿yty przycisk
	 *	\param xx nieu¿ywane
	 *  \param yy nieu¿ywane
	 */
	static void PressKey(unsigned char key, int xx, int yy);

	/*! \fn static void Window::PressKey(unsigned char key, int xx, int yy)
	 *  \brief Metoda steruj¹ca obs³ug¹ klawiatury (przy puszczeniu klawisza).
	 *	\param key okreœla u¿yty przycisk
	 *	\param xx nieu¿ywane
	 *  \param yy nieu¿ywane
	 */
	static void ReleaseKey(unsigned char key, int xx, int yy);

	/*! \fn static void Window::PressKey(unsigned char key, int xx, int yy)
	 *  \brief Metoda steruj¹ca timerem (wykorzystywany jedynie przez obiekt klasy Game).
	 *	\param parametr nieu¿ywane
	 * 
	 *  Timer wywo³uje siê co 15 milisekund.
	 */
	static void Timer(int parameter);

public:

	/*! \fn static Window* Window::getInstance()
	 *  \brief Metoda zwracaj¹ca wskaŸnik na obiekt klasy Window. 
	 *
	 *  Zapewnia, ¿e klasa Window pozostanie singletonem.
	 */
	static Window* getInstance();

	/*! \fn static void Window::Init(int argc, char* argv[])
	 *  \brief Metoda inicjuj¹ca singleton.
	 *
	 *  Inicjuje bibliotekê GLUT oraz jej funkcje, tworzy okno, ustawia potrzebne parametry i instaluje obs³ugê myszy i klawiatury.
	 *	Na koniec wywo³uje inicjalizacjê Menu, wywo³uje Timera oraz uruchamia pêtlê g³ówn¹.
	 */
	static void Init(int argc, char* argv[]);

};

#endif