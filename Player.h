#ifndef Player_h
#define Player_h

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Map.h"

using namespace std;

/*! \class Player Player.h
 *  \brief Klasa steruj�ca parametrami gracza.
 *
 * Klasa steruje wsp�rz�dnymi i poruszaniem gracza, skokiem i spadaniem, biegiem oraz latark�.
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
	 *  \param map wska�nik na obiektu klasy Map
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *  \param jump warto�� skoku (domy�lnie 0)
	 *  \param fallingSpeed szybko�� spadania (domy�lnie 0)
	 *  \param flashlight okre�la czy latarka jest w��czona (domy�lnie false)
	 *  \param viewField zakres widoczno�ci (domy�lnie 60)
	 *
	 *	Nadaje parametry latarce i wczytuje wszystkie parametry.
	 */
	Player(Map* map, float x = 0.0f, float y = 0.0f, float z = 0.0f, int jump = 0, float fallingSpeed = 0.1f, bool flashlight = false, float viewField = 60.0);
	
	/*! \fn void Player::PressKey(unsigned char key)
	 *  \brief Sterowanie graczem za pomoc� klawiatury (przy naci�ni�ciu klawisza).
	 *  \param key okre�la u�yty przycisk
	 *
	 *	Pozwala graczowi na w��czenie/wy��czenie latarki (f), poruszanie (w, a, s, d),
	 *  sprint (q, je�li trzymany jest w), skok (spacja) oraz reset pozycji (r).
	 */
	void PressKey(unsigned char key);

	/*! \fn void Player::ReleaseKey(unsigned char key)
	 *  \brief Sterowanie graczem za pomoc� klawiatury (przy puszczeniu klawisza).
	 *  \param key okre�la u�yty przycisk
	 *
	 *	Puszczenie przycisku poruszania sprawia, �e gracz przestaje si�porusza� w danym kierunku. Dodatkowo puszczenie w, zeruje te� sprint.
	 */
	void ReleaseKey(unsigned char key);

	/*! \fn void Player::ComputeFall()
	 *  \brief Oblicza poruszanie gracza w pionie
	 *
	 *	Je�li gracz wykonuje skok, obliczana jest jego pozycja w g�r� (o ile nie zachodzi kolizja z czym� ponad graczem [na wysoko�ci 2.7]).
	 *  Je�li jump = 0, gracza opada ruchem przy�pieszonym, dop�ki nie zetknie si� z jakim� blokiem (sprawdzenie kolizji na wysoko�ci 0).
	 */
	void ComputeFall(long int deltaTime);

	/*! \fn void Player::ComputeMove(float x1, float z1)
	 *  \brief Oblicza poruszanie gracza w p�aszczy�nie horyzontalnej.
	 *  \param x1 wsp�rz�dna x wektora kamery
	 *  \param z1 wsp�rz�dna z wektora kamery
	 *
	 *	Wykonuje ruch do przodu/do ty�u lub na poki.
	 *  Sprawdza przed tym czy nie dojdzie do kolizji w trzech punktach (0, 1, 2). Ruch nie jest wykonany je�li zasz�aby kolizja.
	 */
	void ComputeMove(float x1, float z1, long int deltaTime);

	/*! \fn bool Player::Collision(float x, float y, float z)
	 *  \brief Sprawdza kolizj�.
	 *  \param x wsp�rz�dna x punktu do sprawedznia
	 *  \param y wsp�rz�dna y punktu do sprawdzenia
	 *  \param z wsp�rz�dna z punktu do sprawedznia
	 *  \return false je�li nie ma kolizji, true je�li zachodzi kolizja
	 *
	 *	Sprawdza kolizj� gracza z blokami na podanej wysoko�ci i w podanym po�o�eniu.
	 *  W rzeczywisto�ci sprawdza 4 punkty na kraw�dzi hitboxa gracza, o podanej wysoko�ci.
	 */
	bool Collision(float x, float y, float z);

	/*! \fn void Player::Flashlight(float vector[])
	 *  \brief Ustawia pozycj� latarki.
	 *  \param vector wektor kamery
	 *
	 *	Ustawia punkt ustawienia latarki jako �rodek gracza na wysoko�ci 2.5 i kierunek ten sam co dla kamery.
	 */
	void Flashlight(float vector[]);

	/*! \fn void Player::DrawCursor()
	 *  \brief Rysuje kursor gracza.
	 *
	 *	Rysuje kursor (w postaci plusa) na �rodku ekranu, by gracz wiedzia� na co dok�adnie patrzy.
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