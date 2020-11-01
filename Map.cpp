#include "Map.h"

#include <iostream>

using namespace std;

 Map::Map(){
	 for (int x = 0;x < 64;x++) {
		 for (int y = 0;y < 64;y++) {
			 for (int z = 0;z < 64;z++) {
				 map[x][y][z] = 0;
			 }
		 }
	 }
	 for (int x = 0;x < 64;x++) {
		 for (int z = 0;z < 64;z++) {
			 map[x][0][z] = 1;
		 }
	 }

	 map[10][1][10] = 2;
	 map[12][1][8] = 2;
	 map[12][1][9] = 2;

	 map[10][3][9] = 2;
	 map[6][3][8] = 2;
	 map[12][3][9] = 2;

	 map[13][4][10] = 2;
	 map[13][4][17] = 2;
	 map[13][4][14] = 2;
}