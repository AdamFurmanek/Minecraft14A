#ifndef Map_h
#define Map_h

#include <iostream>
#include <stdlib.h>
#include "FastNoiseLite.h"
#include <time.h>

using namespace std;

#define constX 2048
#define constY 128
#define constZ 2048

/*! \class Map Map.h
 *  \brief Klasa przechowuj�ca dane mapy.
 *
 * Przechowuje X * Y * Z voxeli oraz informacj�, czy voxel jest pokryty dooko�a oraz generuje map�.
 */
class Map
{
private:
	int borders;
	char map[constX][constY][constZ];
	char visibilityMap[constX][constY][constZ];
public:

	/*! \fn Map::Map(bool generate = true)
	 *  \brief Konstruktor.
	 *  \param generate m�wi czy trzeba generowa� map� czy zostanie ona wczytana (domy�lnie generuje now�)
	 *
	 *	Ustawia wielko�� mapy i je�li generate = true, generuje now� map� i sprawdza widoczno�� jej blok�w.
	 */
	Map(bool generate = true);

	/*! \fn void Map::Generate()
	 *  \brief Generator mapy.
	 *
	 */
	void Generate();

	/*! \fn void Map::checkVisibility(int x1, int y1, int z1)
	 *  \brief Sprawdza widoczno�� �cian bloku.
	 *  \param x1 wsp�rz�dna x bloku
	 *  \param y1 wsp�rz�dna y bloku
	 *  \param z1 wsp�rz�dna z bloku
	 *
	 *	Sprawdza wszystkie 6 �cian pod wzgl�dem tego czy s� zakryte innym blokiem czy powinny by� wy�wietlane.
	 *  Wynik operacji zapisywany jest w tablicy visibilityMap.
	 *  U�ywana bezpo�rednia przydaje si� przy zmianie jednego konkretnego bloku.
	 */
	void checkVisibility(int x1, int y1, int z1);

	/*! \fn void Map::checkVisibility()
	 *  \brief Sprawdza widoczno�� �cian wszystkich bloku.
	 *
	 *	Dla ka�dego bloku na mapie wywo�uje checkVisibility.
	 *  U�ywana gdy potrzeba sprawdzi� widoczno�� wszystkich blok�w mapy na raz, czyli przy jej utworzeniu/wczytaniu.
	 */
	void checkFullVisibility();

	/*! \fn char Map::get(int x2, int y2, int z2)
	 *  \brief Zwraca id bloku o konkretnych wsp�rz�dnych.
	 *	\param x2 wsp�rz�dna x bloku
	 *  \param y2 wsp�rz�dna y bloku
	 *  \param z2 wsp�rz�dna z bloku
	 *  \return id bloku
	 * 
	 *	Je�li wsp�rz�dne wychodz� poza map� to zwracane jest -1.
	 */
	char get(int x2, int y2, int z2);

	/*! \fn char Map::getV(int x2, int y2, int z2)
	 *  \brief Zwraca kod widocznych �cian bloku.
	 *	\param x2 wsp�rz�dna x bloku
	 *  \param y2 wsp�rz�dna y bloku
	 *  \param z2 wsp�rz�dna z bloku
	 *  \return kod widocznych �cian
	 *
	 *	Zwraca 8 bit�w pod postaci� char, w kt�rych 6 informuje czy dana �ciana jest widoczna, czy nie.
	 */
	char getV(int x2, int y2, int z2);

	/*! \fn void Map::set(char value, int x1, int y1, int z1)
	 *  \brief Modyfikuje blok na mapie (bezpiecznie).
	 *  \param value id nowego bloku.
	 *	\param x1 wsp�rz�dna x bloku
	 *  \param y1 wsp�rz�dna y bloku
	 *  \param z1 wsp�rz�dna z bloku
	 *
	 *	Modyfikuje blok na mapie ustawiaj�c w wybranym miejcu ten o odpowiednim id (mo�e te� by� 0, czyli usuni�cie bloku).
	 *  Po modyfikacji sprawdza widoczno�� jego, oraz wszystkich sze�ciu blok�w otaczaj�cych.
	 */
	void set(char value, int x1, int y1, int z1);

	/*! \fn void Map::set(char value, int x1, int y1, int z1)
	 *  \brief Modyfikuje blok na mapie.
	 *  \param value id nowego bloku.
	 *	\param x1 wsp�rz�dna x bloku
	 *  \param y1 wsp�rz�dna y bloku
	 *  \param z1 wsp�rz�dna z bloku
	 *
	 *	Modyfikuje blok na mapie ustawiaj�c w wybranym miejcu ten o odpowiednim id (mo�e te� by� 0, czyli usuni�cie bloku).
	 *  Nie sprawdza widoczno�ci bloku oraz blok�w dooko�a w przeciwie�stwie do metody set.
	 */
	void simpleSet(char value, int x1, int y1, int z1);

	int getX() {
		return constX;
	}

	int getY() {
		return constY;
	}

	int getZ() {
		return constZ;
	}

	int getBorders() {
		return borders;
	}
};

#endif