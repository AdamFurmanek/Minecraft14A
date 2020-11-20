#include "Map.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

Map::Map() {

	srand(NULL);

	for (int x = 0;x < getX();x++) {
		for (int y = 0;y < getY();y++) {
			for (int z = 0;z < getZ();z++) {
				map[x][y][z] = 0;
			}
		}
	}
	for (int x = 0;x < getX();x++) {
		for (int z = 0;z < getZ();z++) {
			map[x][0][z] = 1;
			map[x][1][z] = 2;
			map[x][2][z] = 2;
			map[x][3][z] = 2;
			map[x][4][z] = 2;
			map[x][5][z] = 3;
			map[x][6][z] = 3;
			map[x][7][z] = 3;
			map[x][7][z] = 3;
			map[x][8][z] = 4;
			map[x][10][z] = (rand() % 10) > 7 ? 10 : 0;
		}
	}
	for (int x = 0;x < getX();x++) {
		for (int y = 0;y < getY();y++) {
			for (int z = 0;z < getZ();z++) {
				checkVisibility(x, y, z);
			}
		}
	}
	cout << (int)visibilityMap[0][0][0] << endl;
	cout << (int)visibilityMap[1][1][1] << endl;
	cout << (int)visibilityMap[20][20][20] << endl;
}

void Map::checkVisibility(int x1, int y1, int z1) {
	char code = 0;
	if (y1 + 1 >= y || map[x1][y1 + 1][z1] > 0)
		code |= 1UL << 0;
	if (y1 - 1 < 0 || map[x1][y1 - 1][z1] > 0)
		code |= 1UL << 1;
	if (z1 + 1 >= z || map[x1][y1][z1 + 1] > 0)
		code |= 1UL << 2;
	if (z1 - 1 < 0 || map[x1][y1][z1 - 1] > 0)
		code |= 1UL << 3;
	if (x1 - 1 < 0 || map[x1 - 1][y1][z1] > 0)
		code |= 1UL << 4;
	if (x1 + 1 >= z || map[x1 + 1][y1][z1] > 0)
		code |= 1UL << 5;
	visibilityMap[x1][y1][z1] = code;
}