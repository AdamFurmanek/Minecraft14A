#include "Map.h"

Map::Map(bool generate) {

	x = 600;
	y = 64;
	z = 600;

	if(generate){
		Generate();
		checkFullVisibility();
	}
}

void Map::Generate() {

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
			//map[x][10][z] = (rand() % 10) > 7 ? 12 : 0;
		}
	}

	for (int x = 0;x < getX();x++) {
		for (int y = 0;y < 64;y++) {
			for (int z = 0;z < getZ();z++) {
				if ((x == 50 || x == getX() - 50 )&&( z > 50 && z < getZ() - 50)  || (z == 50 || z == getZ() - 50) && (x > 50 && x < getX() - 50)) {
					char id = map[x][y][z];
					map[x][y][z] = (rand() % 10) > 4 ? 1 : id;
				}
			}
		}
	}

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

void Map::checkFullVisibility() {
	for (int x = 0;x < getX();x++) {
		for (int y = 0;y < getY();y++) {
			for (int z = 0;z < getZ();z++) {
				checkVisibility(x, y, z);
			}
		}
	}
}

char Map::get(int x2, int y2, int z2) {
	if (x2<0 || y2<0 || z2<0 || x2>x - 1 || y2>y - 1 || z2>z - 1)
		return -1;
	return map[x2][y2][z2];
}

char Map::getV(int x2, int y2, int z2) {
	if (x2<0 || y2<0 || z2<0 || x2>x - 1 || y2>y - 1 || z2>z - 1)
		return -1;
	return visibilityMap[x2][y2][z2];
}

void Map::set(char value, int x1, int y1, int z1) {
	map[x1][y1][z1] = value;
	if (value <= 0) {
		if (y1 + 1 < y)
			visibilityMap[x1][y1 + 1][z1] &= ~(1UL << 1);
		if (y1 - 1 >= 0)
			visibilityMap[x1][y1 - 1][z1] &= ~(1UL << 0);
		if (z1 + 1 < z)
			visibilityMap[x1][y1][z1 + 1] &= ~(1UL << 3);
		if (z1 - 1 >= 0)
			visibilityMap[x1][y1][z1 - 1] &= ~(1UL << 2);
		if (x1 - 1 >= 0)
			visibilityMap[x1 - 1][y1][z1] &= ~(1UL << 5);
		if (x1 + 1 < z)
			visibilityMap[x1 + 1][y1][z1] &= ~(1UL << 4);
	}
	else {
		if (y1 + 1 < y)
			visibilityMap[x1][y1 + 1][z1] |= 1UL << 1;
		if (y1 - 1 >= 0)
			visibilityMap[x1][y1 - 1][z1] |= 1UL << 0;
		if (z1 + 1 < z)
			visibilityMap[x1][y1][z1 + 1] |= 1UL << 3;
		if (z1 - 1 >= 0)
			visibilityMap[x1][y1][z1 - 1] |= 1UL << 2;
		if (x1 - 1 >= 0)
			visibilityMap[x1 - 1][y1][z1] |= 1UL << 5;
		if (x1 + 1 < z)
			visibilityMap[x1 + 1][y1][z1] |= 1UL << 4;
	}
}

void Map::simpleSet(char value, int x1, int y1, int z1) {
	map[x1][y1][z1] = value;
}