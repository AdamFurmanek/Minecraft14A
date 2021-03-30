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
 *  \brief Klasa przechowuj¹ca dane mapy.
 *
 * Przechowuje X * Y * Z voxeli oraz informacjê, czy voxel jest pokryty dooko³a oraz generuje mapê.
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
	 *  \param generate mówi czy trzeba generowaæ mapê czy zostanie ona wczytana (domyœlnie generuje now¹)
	 *
	 *	Ustawia wielkoœæ mapy i jeœli generate = true, generuje now¹ mapê i sprawdza widocznoœæ jej bloków.
	 */
	Map(bool generate = true);

	/*! \fn void Map::Generate()
	 *  \brief Generator mapy.
	 *
	 */
	void Generate();

	/*! \fn void Map::checkVisibility(int x1, int y1, int z1)
	 *  \brief Sprawdza widocznoœæ œcian bloku.
	 *  \param x1 wspó³rzêdna x bloku
	 *  \param y1 wspó³rzêdna y bloku
	 *  \param z1 wspó³rzêdna z bloku
	 *
	 *	Sprawdza wszystkie 6 œcian pod wzglêdem tego czy s¹ zakryte innym blokiem czy powinny byæ wyœwietlane.
	 *  Wynik operacji zapisywany jest w tablicy visibilityMap.
	 *  U¿ywana bezpoœrednia przydaje siê przy zmianie jednego konkretnego bloku.
	 */
	void checkVisibility(int x1, int y1, int z1);

	/*! \fn void Map::checkVisibility()
	 *  \brief Sprawdza widocznoœæ œcian wszystkich bloku.
	 *
	 *	Dla ka¿dego bloku na mapie wywo³uje checkVisibility.
	 *  U¿ywana gdy potrzeba sprawdziæ widocznoœæ wszystkich bloków mapy na raz, czyli przy jej utworzeniu/wczytaniu.
	 */
	void checkFullVisibility();

	/*! \fn char Map::get(int x2, int y2, int z2)
	 *  \brief Zwraca id bloku o konkretnych wspó³rzêdnych.
	 *	\param x2 wspó³rzêdna x bloku
	 *  \param y2 wspó³rzêdna y bloku
	 *  \param z2 wspó³rzêdna z bloku
	 *  \return id bloku
	 * 
	 *	Jeœli wspó³rzêdne wychodz¹ poza mapê to zwracane jest -1.
	 */
	char get(int x2, int y2, int z2);

	/*! \fn char Map::getV(int x2, int y2, int z2)
	 *  \brief Zwraca kod widocznych œcian bloku.
	 *	\param x2 wspó³rzêdna x bloku
	 *  \param y2 wspó³rzêdna y bloku
	 *  \param z2 wspó³rzêdna z bloku
	 *  \return kod widocznych œcian
	 *
	 *	Zwraca 8 bitów pod postaci¹ char, w których 6 informuje czy dana œciana jest widoczna, czy nie.
	 */
	char getV(int x2, int y2, int z2);

	/*! \fn void Map::set(char value, int x1, int y1, int z1)
	 *  \brief Modyfikuje blok na mapie (bezpiecznie).
	 *  \param value id nowego bloku.
	 *	\param x1 wspó³rzêdna x bloku
	 *  \param y1 wspó³rzêdna y bloku
	 *  \param z1 wspó³rzêdna z bloku
	 *
	 *	Modyfikuje blok na mapie ustawiaj¹c w wybranym miejcu ten o odpowiednim id (mo¿e te¿ byæ 0, czyli usuniêcie bloku).
	 *  Po modyfikacji sprawdza widocznoœæ jego, oraz wszystkich szeœciu bloków otaczaj¹cych.
	 */
	void set(char value, int x1, int y1, int z1);

	/*! \fn void Map::set(char value, int x1, int y1, int z1)
	 *  \brief Modyfikuje blok na mapie.
	 *  \param value id nowego bloku.
	 *	\param x1 wspó³rzêdna x bloku
	 *  \param y1 wspó³rzêdna y bloku
	 *  \param z1 wspó³rzêdna z bloku
	 *
	 *	Modyfikuje blok na mapie ustawiaj¹c w wybranym miejcu ten o odpowiednim id (mo¿e te¿ byæ 0, czyli usuniêcie bloku).
	 *  Nie sprawdza widocznoœci bloku oraz bloków dooko³a w przeciwieñstwie do metody set.
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