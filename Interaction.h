#ifndef Interaction_h
#define Interaction_h

#include "Map.h"
#include "Player.h"
#include <stdlib.h>
#include <GL/glut.h>

/*! \class Interaction Interaction.h
 *  \brief Klasa pozwalaj¹ca na interakcjê ze œwiatem.
 *
 *  Do zadañ tej klasy nale¿y obliczanie œledzonego bloku, rysowanie jego ramki oraz obs³uga budowania i niszczenia bloków.
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
	 *  \param map wskaŸnik na obiektu klasy Map
	 *  \param player wskaŸnik na obiektu klasy Player
	 *  \param handID id trzymanego przez gracza przedmiotu (domyœlnie 1)
	 *
	 */
	Interaction(Map* map, Player* player, int handID = 1);
	
	/*! \fn void Interaction::Mouse(int button, int state, int x, int y)
	 *  \brief Metoda steruj¹ca obs³ug¹ myszki (naciœniêtej).
	 *	\param button okreœla u¿yty przycisk
	 *	\param state okreœla rodzaj eventu (keydown/keyup)
	 *  \param x wspó³rzêdna x myszki przy naciœniêciu
	 *  \param y wspó³rzêdna y myszki przy naciœniêciu
	 *
	 *	Wykonuje odpowiedni¹ operacjê w zale¿noœci od zdarzenia myszki.
	 *  Lewy przycisk - usuniêcie œledzonego bloku, prawy przycisk - po³o¿enie wybranego bloku,
	 *  œrodkowy przycisk - pobranie œledzonego bloku jak wybranego, scroll - zmiana wybranego bloku.
	 */
	void Mouse(int button, int state, int x, int y);

	/*! \fn void Interaction::ComputeTracking(float x, float y, float z, float vector[3])
	 *  \brief Oblicza na jaki blok patrzy gracz.
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *  \param vector wektor kamery.
	 *
	 *	Sprawdza kilkaset punktów w linii prostej, w ma³ych odstêpach, w kierunku kamery.
	 *  Jeœli po drodze napotka na blok, wywo³uje metodê Wall, aby sprawdziæ na któr¹ œcianê patrzy gracz.
	 *  W przeciwny wypadku gracz nie œledzi ¿adnego bloku.
	 */
	void ComputeTracking(float x, float y, float z, float vector[3]);

	/*! \fn void Interaction::Wall(float x1, float y1, float z1)
	 *  \brief Oblicza na jak¹ œcianê patrzy gracz.
	 *  \param x1 wspó³rzêdna x1 punktu, który napotka³ blok
	 *  \param y1 wspó³rzêdna x1 punktu, który napotka³ blok
	 *  \param z1 wspó³rzêdna x1 punktu, który napotka³ blok
	 *
	 *	Algorytm oblicza dla której œciany punkt jest najbli¿ej i wybiera j¹ jako œledzon¹.
	 */
	void Wall(float x1, float y1, float z1);

	/*! \fn void Interaction::DrawCubeBorder()
	 *  \brief Rysuje ramkê œledzonego bloku.
	 *
	 *	Rysuje szeœcienn¹ obwódkê œledzonego bloku (jeœli taki istnieje).
	 */
	void DrawCubeBorder();

	int getHandID() {
		return handID;
	}
};

#endif