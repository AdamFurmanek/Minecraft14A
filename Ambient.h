#ifndef Ambient_h
#define Ambient_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/*! \class Ambient Ambient.h
 *  \brief Klasa odpowiedzialna ze elementy otoczenia.
 *
 *  Steruje parametrami (pozycja, odleg�o��, kolor) nieba, �wiat�a, mg�y.
 */
class Ambient
{
private:
	float Time;
	GLfloat skyColor[3] = { 0.0f, 0.6f, 1.0f };
public:

	/*! \fn Ambient::Ambient(float Timer = 0)
	 *  \brief Konstruktor.
	 *  \param Timer aktualny czas rozgrywki (domy�lnie 0)
	 *
	 *	W��cza �wiat�o s�oneczne i mg��.
	 */
	Ambient(float Timer = 0);

	/*! \fn void Ambient::ComputeAmbient(int viewDistance)
	 *  \brief Metoda obliczaj�ca parametry element�w otoczenia.
	 *  \param viewDistance odleg�o�� na jak� renderowane s� obiekty
	 *
	 *	Oblicza odpowiedni� pozycj� s�o�ca, ksi�yca i �r�d�a �wiat�a oraz kolor �wiat�a na podstawie czasu.
	 *  Oblicza odleg�o�� s�o�ca, ksi�yca i mg�y na podstawie viewDistance.
	 */
	void ComputeAmbient(int viewDistance);

	/*! \fn void Ambient::AmbientDisplay(float x, float y, float z, int viewDistance)
	 *  \brief Wy�wietlacz otoczenia.
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *  \param viewDistance odleg�o�� na jak� renderowane s� obiekty
	 *
	 *	Renderuje S�o�ce, Ksi�yc i ustawia pozycj� �wiat�a s�onecznego.
	 */
	void AmbientDisplay(float x, float y, float z, int viewDistance);

	/*! \fn void Ambient::clearColor()
	 *  \brief Render nieba.
	 *
	 *	Czy�ci bufor koloru na odpowiedni kolor nieba.
	 */
	void clearColor();

	float getTime() {
		return Time;
	}
};

#endif