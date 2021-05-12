#include "Map.h"

Map::Map(bool generate) {

	borders = 10;

	if(generate){
		Generate();
		checkFullVisibility();
	}
}

void Map::Generate() {
	
	int seed = time(NULL);

	//Na podstawie paru map wysokoœci mo¿na robiæ bardzo ciekawe tereny.

	//mapa wysokoœci.
	FastNoiseLite* noise = new FastNoiseLite(seed);
	(*noise).SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

	//(*noise).SetNoiseType(FastNoiseLite::NoiseType_Cellular);
	//(*noise).SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	//(*noise).SetNoiseType(FastNoiseLite::NoiseType_Value);
	//(*noise).SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);

	for (int x = 0; x < getX(); x++) {
		for (int z = 0; z < getZ(); z++) {
			int high = (*noise).GetNoise((float)z, (float)x) * 20 + 10;
			if(high>0)
				map[x][high][z] = 4;
			for (int k = 0;k < 3;k++) {
				high--;
				if (high > 0)
					map[x][high][z] = 3;
			}
			while (high > 1) {
				high--;
				map[x][high][z] = 2;
			}
			map[x][0][z] = 1;
		}
	}

	//drzewa
	FastNoiseLite* noise2 = new FastNoiseLite(seed + 1);
	(*noise2).SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

	for (int x = 0 + 3; x < getX() - 3; x += 3) {
		for (int z = 0 + 3; z < getZ() - 3; z += 3) {
			int probability = (*noise2).GetNoise((float)z, (float)x) * 15 + 15;
			if ((rand() % 3200) < (probability * probability)) {
				for (int y = 1; y < getY(); y++) {
					if (map[x][y][z] == 0) {

						if (y <= 2)
							break;

						map[x][y][z] = 7;
						int maxY = rand() % 5 + 3;
						for(int actualY = y; actualY < y+maxY; actualY++)
							map[x][actualY][z] = 7;
						for (int actualY = y+maxY; actualY < y+maxY + 4; actualY++) {
							for (int newX = x - 1; newX < x + 2; newX++) {
								for (int newZ = z - 1; newZ < z + 2; newZ++) {
									map[newX][actualY][newZ] = 8;
								}
							}
						}

						for (int actualY = y + maxY + 1; actualY < y + maxY + 3; actualY++) {
							for (int newX = x - 1; newX < x + 2; newX++) {
								map[newX][actualY][z + 2] = 8;
								map[newX][actualY][z - 2] = 8;
							}
							for (int newZ = z - 1; newZ < z + 2; newZ++) {
								map[x + 2][actualY][newZ] = 8;
								map[x - 2][actualY][newZ] = 8;
							}
						}

						break;
					}
				}
			}
		}
	}

	for (int x = 0;x < getX();x++) {
		for (int z = 0;z < getZ();z++) {
			for (int x2 = x - 3;x2 < x + 3;x2++) {
				for (int z2 = z - 3;z2 < z + 3;z2++) {
					if(x2 > 0 && x2 < getX() && z2 > 0 && z2 < getZ())
						if (map[x2][1][z2] == 0 && map[x][1][z] == 4)
							map[x][1][z] = 5;
				}
			}
		}
	}

	//woda
	for (int x = 0;x < getX();x++) {
		for (int z = 0;z < getZ();z++) {
			if (map[x][1][z] == 0)
				map[x][1][z] = 100;
		}
	}

	//Granice œwiata.
	for (int x = 0;x < getX();x++) {
		for (int y = 0;y < getY();y++) {
			for (int z = 0;z < getZ();z++) {
				if ((x == borders - 1 || x == getX() - borders) && (z >= borders - 1 && z <= getZ() - borders) || (z == borders - 1 || z == getZ() - borders) && (x >= borders && x <= getX() - borders)) {
					char id = map[x][y][z];
					map[x][y][z] = (rand() % 10) > 4 ? 1 : id;
				}
			}
		}
	}

}

void Map::checkVisibility(int x1, int y1, int z1) {
	char code = 0;
	if (y1 + 1 >= getY() || map[x1][y1 + 1][z1] > 0)
		code |= 1UL << 0;
	if (y1 - 1 < 0 || map[x1][y1 - 1][z1] > 0)
		code |= 1UL << 1;
	if (z1 + 1 >= getZ() || map[x1][y1][z1 + 1] > 0 && map[x1][y1][z1 + 1] != 100)
		code |= 1UL << 2;
	if (z1 - 1 < 0 || map[x1][y1][z1 - 1] > 0 && map[x1][y1][z1 - 1] != 100)
		code |= 1UL << 3;
	if (x1 - 1 < 0 || map[x1 - 1][y1][z1] > 0 && map[x1 - 1][y1][z1] != 100)
		code |= 1UL << 4;
	if (x1 + 1 >= getZ() || map[x1 + 1][y1][z1] > 0 && map[x1 + 1][y1][z1] != 100)
		code |= 1UL << 5;

	//woda
	if (map[x1][y1][z1] == 100) {
		code = 0;
		code |= 1UL << 1;
	}
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
	if (x2<0 || y2<0 || z2<0 || x2>getX() - 1 || y2>getY() - 1 || z2>getZ() - 1)
		return -1;
	return map[x2][y2][z2];
}

char Map::getV(int x2, int y2, int z2) {
	if (x2<0 || y2<0 || z2<0 || x2>getX() - 1 || y2>getY() - 1 || z2>getZ() - 1)
		return -1;
	return visibilityMap[x2][y2][z2];
}

void Map::set(char value, int x1, int y1, int z1) {
	map[x1][y1][z1] = value;
	if (y1 + 1 < getY())
		checkVisibility(x1, y1 + 1, z1);
	if (y1 - 1 >= 0)
		checkVisibility(x1, y1 - 1, z1);
	if (z1 + 1 < getZ())
		checkVisibility(x1, y1, z1 + 1);
	if (z1 - 1 >= 0)
		checkVisibility(x1, y1, z1 - 1);
	if (x1 - 1 >= 0)
		checkVisibility(x1 + 1, y1, z1);
	if (x1 + 1 < getZ())
		checkVisibility(x1 - 1, y1, z1);

}

void Map::simpleSet(char value, int x1, int y1, int z1) {
	map[x1][y1][z1] = value;
}

bool Map::getCollision(int x, int y, int z) {
	int blockID = get(x, y, z);
	if (blockID > 0 && blockID < 100)
		return true;
	else
		return false;
}