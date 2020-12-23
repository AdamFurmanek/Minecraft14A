#ifndef Interaction_h
#define Interaction_h

#include "Map.h"
#include "Player.h"
#include <stdlib.h>
#include <GL/glut.h>

/*! \class Interaction Interaction.h
 *  \brief Klasa pozwalaj�ca na interakcj� ze �wiatem.
 *
 *  Do zada� tej klasy nale�y obliczanie �ledzonego bloku, rysowanie jego ramki oraz obs�uga budowania i niszczenia blok�w.
 */
class Interaction
{
private:
	static Map* map;
	static Player* player;

	float followedX, followedY, followedZ;
	int followedWall;
	int handID, handMax;

public:

	/*! \fn Interaction::Interaction(Map* map, Player* player, int handID = 1)
	 *  \brief Konstruktor.
	 *  \param map wska�nik na obiektu klasy Map
	 *  \param player wska�nik na obiektu klasy Player
	 *  \param handID id trzymanego przez gracza przedmiotu (domy�lnie 1)
	 *
	 */
	Interaction(Map* map, Player* player, int handID = 1);
	
	/*! \fn void Interaction::Mouse(int button, int state, int x, int y)
	 *  \brief Metoda steruj�ca obs�ug� myszki (naci�ni�tej).
	 *	\param button okre�la u�yty przycisk
	 *	\param state okre�la rodzaj eventu (keydown/keyup)
	 *  \param x wsp�rz�dna x myszki przy naci�ni�ciu
	 *  \param y wsp�rz�dna y myszki przy naci�ni�ciu
	 *
	 *	Wykonuje odpowiedni� operacj� w zale�no�ci od zdarzenia myszki.
	 *  Lewy przycisk - usuni�cie �ledzonego bloku, prawy przycisk - po�o�enie wybranego bloku,
	 *  �rodkowy przycisk - pobranie �ledzonego bloku jak wybranego, scroll - zmiana wybranego bloku.
	 */
	void Mouse(int button, int state, int x, int y);

	/*! \fn void Interaction::ComputeTracking(float x, float y, float z, float vector[3])
	 *  \brief Oblicza na jaki blok patrzy gracz.
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *  \param vector wektor kamery.
	 *
	 *	Sprawdza kilkaset punkt�w w linii prostej, w ma�ych odst�pach, w kierunku kamery.
	 *  Je�li po drodze napotka na blok, wywo�uje metod� Wall, aby sprawdzi� na kt�r� �cian� patrzy gracz.
	 *  W przeciwny wypadku gracz nie �ledzi �adnego bloku.
	 */
	void ComputeTracking(float x, float y, float z, float vector[3]);

	/*! \fn void Interaction::Wall(float x1, float y1, float z1)
	 *  \brief Oblicza na jak� �cian� patrzy gracz.
	 *  \param x1 wsp�rz�dna x1 punktu, kt�ry napotka� blok
	 *  \param y1 wsp�rz�dna x1 punktu, kt�ry napotka� blok
	 *  \param z1 wsp�rz�dna x1 punktu, kt�ry napotka� blok
	 *
	 *	Algorytm oblicza dla kt�rej �ciany punkt jest najbli�ej i wybiera j� jako �ledzon�.
	 */
	void Wall(float x1, float y1, float z1);

	/*! \fn void Interaction::DrawCubeBorder()
	 *  \brief Rysuje ramk� �ledzonego bloku.
	 *
	 *	Rysuje sze�cienn� obw�dk� �ledzonego bloku (je�li taki istnieje).
	 */
	void DrawCubeBorder();

	int getHandID() {
		return handID;
	}
};

#endif