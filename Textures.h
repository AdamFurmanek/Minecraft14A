#ifndef Textures_h
#define Textures_h

#include "Targa.h"
#include "Map.h"
#include <GL/glut.h>
#include <math.h>

/*! \class Textures Textures.h
 *  \brief Klasa odpowiedzialna za tekstury.
 *
 *  Wczytuje tekstury przy pomocy klasy Targa i wy�wietla map� stworzon� z oteksturowanych sze�cian�w.
 */
class Textures
{
private:
	static Map* map;
	GLuint TextureID[14];
	int viewDistance;
public:

	/*! \fn Textures::Textures(Map* map, float viewDistance = 30)
	 *  \brief Konstruktor.
	 *  \param map wska�nik na obiektu klasy Map
	 *  \param viewDistance odleg�o�� na jak� renderowane s� obiekty
	 *
	 *	Konstruktor wczytuje kilkana�cie tekstur formatu .tga i zaznacza odpowiednie tablice wierzcho�k�w, �cian i wektor�w normalnych.
	 */
	Textures(Map* map, float viewDistance = 30);

	/*! \fn void Textures::TexturesDisplay(float x, float y, float z)
	 *  \brief Metoda renderuj�ca �wiat.
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *
	 *	W��cza o�wietlenie, teksturowanie i renderuje odpowiednie �ciany poszczeg�lnych blok�w w obr�bie viewDistance gracza.
	 *  Sprawdza dodatkowo czy bloki s� widoczne na ekranie i nie renderuje ich je�li nie s�.
	 *  Na koniec renderuje ponownie najbli�sze otoczenia gracza, by zabezpieczy� render przed znikaj�cymi bliskimi blokami.
	 */
	void TexturesDisplay(float x, float y, float z);

	/*! \fn void Textures::DrawSelectedBlock(int id)
	 *  \brief Wy�wietla aktualnie trzymany blok.
	 *  \param id identyfikator trzymanego bloku
	 *
	 *	Wy�wietla w prawym dolnym rogu ikon� trzymanego bloku. Wy��cza przed tym o�wietlenie, ale w��cza teksturowanie.
	 */
	void DrawSelectedBlock(int id);

	int getViewDistance() {
		return viewDistance;
	}

	void setViewDistance(int viewDistance) {
		this->viewDistance = viewDistance;
	}
};

#endif
