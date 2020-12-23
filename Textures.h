#ifndef Textures_h
#define Textures_h

#include "Targa.h"
#include "Map.h"
#include <GL/glut.h>
#include <math.h>

/*! \class Textures Textures.h
 *  \brief Klasa odpowiedzialna za tekstury.
 *
 *  Wczytuje tekstury przy pomocy klasy Targa i wyœwietla mapê stworzon¹ z oteksturowanych szeœcianów.
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
	 *  \param map wskaŸnik na obiektu klasy Map
	 *  \param viewDistance odleg³oœæ na jak¹ renderowane s¹ obiekty
	 *
	 *	Konstruktor wczytuje kilkanaœcie tekstur formatu .tga i zaznacza odpowiednie tablice wierzcho³ków, œcian i wektorów normalnych.
	 */
	Textures(Map* map, float viewDistance = 30);

	/*! \fn void Textures::TexturesDisplay(float x, float y, float z)
	 *  \brief Metoda renderuj¹ca œwiat.
	 *  \param x pozycja x gracza
	 *  \param y pozycja y gracza
	 *  \param z pozycja z gracza
	 *
	 *	W³¹cza oœwietlenie, teksturowanie i renderuje odpowiednie œciany poszczególnych bloków w obrêbie viewDistance gracza.
	 *  Sprawdza dodatkowo czy bloki s¹ widoczne na ekranie i nie renderuje ich jeœli nie s¹.
	 *  Na koniec renderuje ponownie najbli¿sze otoczenia gracza, by zabezpieczyæ render przed znikaj¹cymi bliskimi blokami.
	 */
	void TexturesDisplay(float x, float y, float z);

	/*! \fn void Textures::DrawSelectedBlock(int id)
	 *  \brief Wyœwietla aktualnie trzymany blok.
	 *  \param id identyfikator trzymanego bloku
	 *
	 *	Wyœwietla w prawym dolnym rogu ikonê trzymanego bloku. Wy³¹cza przed tym oœwietlenie, ale w³¹cza teksturowanie.
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
