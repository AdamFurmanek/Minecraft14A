#ifndef Ambient_h
#define Ambient_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/*! \class Ambient Ambient.h
 *  \brief Klasa odpowiedzialna ze elementy otoczenia.
 *
 *  Steruje parametrami (pozycja, odleg³oœæ, kolor) nieba, œwiat³a, mg³y.
 */
class Ambient
{
private:
	float Time;
	GLfloat skyColor[3] = { 0.0f, 0.6f, 1.0f };
public:

	/*! \fn Ambient::Ambient(float Timer = 0)
	 *  \brief Konstruktor.
	 *  \param Timer aktualny czas rozgrywki (domyœlnie 0)
	 *
	 *	W³¹cza œwiat³o s³oneczne i mg³ê.
	 */
	Ambient(float Timer = 0);

	/*! \fn void Ambient::ComputeAmbient(int viewDistance)
	 *  \brief Metoda obliczaj¹ca parametry elementów otoczenia.
	 *  \param viewDistance odleg³oœæ na jak¹ renderowane s¹ obiekty
	 *
	 *	Oblicza odpowiedni¹ pozycjê s³oñca, ksiê¿yca i Ÿród³a œwiat³a oraz kolor œwiat³a na podstawie czasu.
	 *  Oblicza odleg³oœæ s³oñca, ksiê¿yca i mg³y na podstawie viewDistance.
	 */
	void ComputeAmbient(int viewDistance);

	/*! \fn void Ambient::AmbientDisplay(float x, float y, float z, int viewDistance)
	 *  \brief Wyœwietlacz otoczenia.
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *  \param viewDistance odleg³oœæ na jak¹ renderowane s¹ obiekty
	 *
	 *	Renderuje S³oñce, Ksiê¿yc i ustawia pozycjê œwiat³a s³onecznego.
	 */
	void AmbientDisplay(float x, float y, float z, int viewDistance);

	/*! \fn void Ambient::clearColor()
	 *  \brief Render nieba.
	 *
	 *	Czyœci bufor koloru na odpowiedni kolor nieba.
	 */
	void clearColor();

	float getTime() {
		return Time;
	}
};

#endif