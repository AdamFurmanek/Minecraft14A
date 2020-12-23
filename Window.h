#ifndef Window_h
#define Window_h

#include <GL/glut.h>
#include "Game.h"
#include "Menu.h"

/*! \class Window Window.h
 *  \brief Klasa obs�uguj�ca okno aplikacji.
 *
 *	Jest singletonem, kt�ry tworzy okno i obs�uguje jego rendering, zmian� rozmiaru, timer oraz pozwala na interakcj� za pomoc� myszy i klawiatury.
 *  Wi�kszo�� metod tej klasy jest tylko metod� steruj�c�, kt�ra oddelegowuje wykonanie operacji obiektowi odpowiedniej klasy (Game lub Menu) w zale�no�ci od stanu.
 *  Stany: 0 - g��wne menu, 1 - menu wczytywania mapy, 2 - rozgrywka, 3 - menu zapisu mapy.
 */
class Window
{
private:

	static Window* engine;
	static Menu* menu;
	static Game* game;
	static int state;

	/*! \fn static void Window::Display()
	 *  \brief Metoda steruj�ca wy�wietlaniem obrazu.
	 * 
	 *  Na koniec wy�wietlenie wywo�uj Redisplay.
	 */
	static void Display();

	/*! \fn static void Window::Reshape(int w, int h)
	 *  \brief Metoda steruj�ca zmienianiem rozmiaru okna.
	 *	\param w nowa szeroko�� okna
	 *	\param h nowa wysoko�� okna
	 */
	static void Reshape(int w, int h);

	/*! \fn static void Window::Mouse(int button, int state1, int x, int y)
	 *  \brief Metoda steruj�ca obs�ug� myszki (naci�ni�tej).
	 *	\param button okre�la u�yty przycisk
	 *	\param state1 okre�la rodzaj eventu (keydown/keyup)
	 *  \param x wsp�rz�dna x myszki przy naci�ni�ciu
	 *  \param y wsp�rz�dna y myszki przy naci�ni�ciu
	 */
	static void Mouse(int button, int state1, int x, int y);

	/*! \fn static void Window::MouseMove(int x1, int y1)
	 *  \brief Metoda steruj�ca obs�ug� myszki (ruszonej).
	 *  \param x nowa wsp�rz�dna x myszki
	 *  \param y nowa wsp�rz�dna y myszki
	 */
	static void MouseMove(int x1, int y1);

	/*! \fn static void Window::PressKey(unsigned char key, int xx, int yy)
	 *  \brief Metoda steruj�ca obs�ug� klawiatury (przy naci�ni�ciu klawisza).
	 *	\param key okre�la u�yty przycisk
	 *	\param xx nieu�ywane
	 *  \param yy nieu�ywane
	 */
	static void PressKey(unsigned char key, int xx, int yy);

	/*! \fn static void Window::PressKey(unsigned char key, int xx, int yy)
	 *  \brief Metoda steruj�ca obs�ug� klawiatury (przy puszczeniu klawisza).
	 *	\param key okre�la u�yty przycisk
	 *	\param xx nieu�ywane
	 *  \param yy nieu�ywane
	 */
	static void ReleaseKey(unsigned char key, int xx, int yy);

	/*! \fn static void Window::PressKey(unsigned char key, int xx, int yy)
	 *  \brief Metoda steruj�ca timerem (wykorzystywany jedynie przez obiekt klasy Game).
	 *	\param parametr nieu�ywane
	 * 
	 *  Timer wywo�uje si� co 15 milisekund.
	 */
	static void Timer(int parameter);

public:

	/*! \fn static Window* Window::getInstance()
	 *  \brief Metoda zwracaj�ca wska�nik na obiekt klasy Window. 
	 *
	 *  Zapewnia, �e klasa Window pozostanie singletonem.
	 */
	static Window* getInstance();

	/*! \fn static void Window::Init(int argc, char* argv[])
	 *  \brief Metoda inicjuj�ca singleton.
	 *
	 *  Inicjuje bibliotek� GLUT oraz jej funkcje, tworzy okno, ustawia potrzebne parametry i instaluje obs�ug� myszy i klawiatury.
	 *	Na koniec wywo�uje inicjalizacj� Menu, wywo�uje Timera oraz uruchamia p�tl� g��wn�.
	 */
	static void Init(int argc, char* argv[]);

};

#endif