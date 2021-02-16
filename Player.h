#ifndef Player_h
#define Player_h

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Map.h"

using namespace std;

/*! \class Player Player.h
 *  \brief Klasa steruj¹ca parametrami gracza.
 *
 * Klasa steruje wspó³rzêdnymi i poruszaniem gracza, skokiem i spadaniem, biegiem oraz latark¹.
 */
class Player
{
private:
	static Map* map;
	float x, y, z;
	float jump;
	float fallingSpeed;
	bool flashlight;
	float viewField;
	bool autojump;

	float deltaMoveStraight, deltaMoveSides;
public:

	/*! \fn Player::Player(Map* map, float x = 300.0f, float y = 60.0f, float z = 300.0f, int jump = 0, float fallingSpeed = 0.1f, bool flashlight = false, float viewField = 60.0)
	 *  \brief Konstruktor.
	 *  \param map wskaŸnik na obiektu klasy Map
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *  \param jump wartoœæ skoku (domyœlnie 0)
	 *  \param fallingSpeed szybkoœæ spadania (domyœlnie 0)
	 *  \param flashlight okreœla czy latarka jest w³¹czona (domyœlnie false)
	 *  \param viewField zakres widocznoœci (domyœlnie 60)
	 *
	 *	Nadaje parametry latarce i wczytuje wszystkie parametry.
	 */
	Player(Map* map, float x = 0.0f, float y = 0.0f, float z = 0.0f, int jump = 0, float fallingSpeed = 0.1f, bool flashlight = false, float viewField = 60.0);
	
	/*! \fn void Player::PressKey(unsigned char key)
	 *  \brief Sterowanie graczem za pomoc¹ klawiatury (przy naciœniêciu klawisza).
	 *  \param key okreœla u¿yty przycisk
	 *
	 *	Pozwala graczowi na w³¹czenie/wy³¹czenie latarki (f), poruszanie (w, a, s, d),
	 *  sprint (q, jeœli trzymany jest w), skok (spacja) oraz reset pozycji (r).
	 */
	void PressKey(unsigned char key);

	/*! \fn void Player::ReleaseKey(unsigned char key)
	 *  \brief Sterowanie graczem za pomoc¹ klawiatury (przy puszczeniu klawisza).
	 *  \param key okreœla u¿yty przycisk
	 *
	 *	Puszczenie przycisku poruszania sprawia, ¿e gracz przestaje siêporuszaæ w danym kierunku. Dodatkowo puszczenie w, zeruje te¿ sprint.
	 */
	void ReleaseKey(unsigned char key);

	/*! \fn void Player::ComputeFall()
	 *  \brief Oblicza poruszanie gracza w pionie
	 *
	 *	Jeœli gracz wykonuje skok, obliczana jest jego pozycja w górê (o ile nie zachodzi kolizja z czymœ ponad graczem [na wysokoœci 2.7]).
	 *  Jeœli jump = 0, gracza opada ruchem przyœpieszonym, dopóki nie zetknie siê z jakimœ blokiem (sprawdzenie kolizji na wysokoœci 0).
	 */
	void ComputeFall(long int deltaTime);

	/*! \fn void Player::ComputeMove(float x1, float z1)
	 *  \brief Oblicza poruszanie gracza w p³aszczyŸnie horyzontalnej.
	 *  \param x1 wspó³rzêdna x wektora kamery
	 *  \param z1 wspó³rzêdna z wektora kamery
	 *
	 *	Wykonuje ruch do przodu/do ty³u lub na poki.
	 *  Sprawdza przed tym czy nie dojdzie do kolizji w trzech punktach (0, 1, 2). Ruch nie jest wykonany jeœli zasz³aby kolizja.
	 */
	void ComputeMove(float x1, float z1, long int deltaTime);

	/*! \fn bool Player::Collision(float x, float y, float z)
	 *  \brief Sprawdza kolizjê.
	 *  \param x wspó³rzêdna x punktu do sprawedznia
	 *  \param y wspó³rzêdna y punktu do sprawdzenia
	 *  \param z wspó³rzêdna z punktu do sprawedznia
	 *  \return false jeœli nie ma kolizji, true jeœli zachodzi kolizja
	 *
	 *	Sprawdza kolizjê gracza z blokami na podanej wysokoœci i w podanym po³o¿eniu.
	 *  W rzeczywistoœci sprawdza 4 punkty na krawêdzi hitboxa gracza, o podanej wysokoœci.
	 */
	bool Collision(float x, float y, float z);

	/*! \fn void Player::Flashlight(float vector[])
	 *  \brief Ustawia pozycjê latarki.
	 *  \param vector wektor kamery
	 *
	 *	Ustawia punkt ustawienia latarki jako œrodek gracza na wysokoœci 2.5 i kierunek ten sam co dla kamery.
	 */
	void Flashlight(float vector[]);

	/*! \fn void Player::DrawCursor()
	 *  \brief Rysuje kursor gracza.
	 *
	 *	Rysuje kursor (w postaci plusa) na œrodku ekranu, by gracz wiedzia³ na co dok³adnie patrzy.
	 */
	void DrawCursor();

	void ResetPosition();

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
	int getJump() {
		return jump;
	}
	float getFallingSpeed() {
		return fallingSpeed;
	}
	bool getFlashlight() {
		return flashlight;
	}
	float getViewField() {
		return viewField;
	}
	void setViewField(float viewField) {
		this -> viewField = viewField;
	}
};

#endif