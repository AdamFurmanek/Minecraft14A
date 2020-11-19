#include "Map.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

 Map::Map(){

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
			 map[x][16][z] = (rand() % 10) > 7 ? 1 : 0;
		 }
	 }

	 map[10][5][10] = 2;
	 map[12][5][8] = 2;
	 map[12][5][9] = 2;

	 map[18][6][5] = 2;
	 map[18][7][6] = 2;
	 map[18][8][7] = 2;
	 map[18][9][8] = 2;
	 map[18][10][9] = 2;
	 map[17][11][10] = 2;
	 map[16][12][10] = 2;
	 map[15][13][10] = 2;
	 map[14][14][10] = 2;
	 map[13][15][10] = 2;
	 map[12][16][10] = 2;
	 map[11][17][10] = 2;


	 map[10][8][9] = 2;
	 map[6][8][8] = 2;
	 map[12][8][9] = 2;

	 map[13][9][10] = 2;
	 map[13][9][17] = 2;
	 map[13][9][14] = 2;
}