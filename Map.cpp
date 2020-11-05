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
		 }
	 }

	 map[10][1][10] = 2;
	 map[12][1][8] = 2;
	 map[12][1][9] = 2;

	 map[18][1][5] = 2;
	 map[18][2][6] = 2;
	 map[18][3][7] = 2;
	 map[18][4][8] = 2;
	 map[18][5][9] = 2;
	 map[17][6][10] = 2;
	 map[16][7][10] = 2;
	 map[15][8][10] = 2;
	 map[14][9][10] = 2;
	 map[13][10][10] = 2;
	 map[12][11][10] = 2;
	 map[11][12][10] = 2;


	 map[10][3][9] = 2;
	 map[6][3][8] = 2;
	 map[12][3][9] = 2;

	 map[13][4][10] = 2;
	 map[13][4][17] = 2;
	 map[13][4][14] = 2;
}