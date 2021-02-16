#include "Map.h"

Map::Map(bool generate) {

	x = 256;
	y = 64;
	z = 256;
	borders = 10;

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

	// Create and configure FastNoise object
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	// Gather noise data
	float noiseData[256][256];

	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			double nx = x / 256 - 0.5, ny = y / 256 - 0.5;
			noiseData[y][x] = noise.GetNoise((float)x, (float)y);
		}
	}

	for (int y = 0; y < 256; y++) {
		for (int x = 0; x < 256; x++) {
			int high = (int)(noiseData[y][x] * 10 + 20);
			if(high>0)
				map[y][high][x] = 4;
			for (int k = 0;k < 3;k++) {
				high--;
				if (high > 0)
					map[y][high][x] = 3;
			}
			while (high > 1) {
				high--;
				map[y][high][x] = 2;
			}
			map[y][0][x] = 1;
		}
	}

	for (int x = 0;x < getX();x++) {
		for (int y = 0;y < getY() ;y++) {
			for (int z = 0;z < getZ();z++) {
				if ((x == borders-1 || x == getX() - borders)&&( z >= borders-1 && z <= getZ() - borders)  || (z == borders-1 || z == getZ() - borders) && (x >= borders && x <= getX() - borders)) {
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