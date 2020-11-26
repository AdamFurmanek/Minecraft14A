#ifndef Map_h
#define Map_h

#include <iostream>
#include <stdlib.h>

using namespace std;

class Map
{
private:
	int x = 500;
	int y = 64;
	int z = 500;
	//U¿yte zosta³y chary, poniewa¿ zajmuj¹ najmniej miejsca.
	char map[500][64][500];
	char visibilityMap[500][64][500];
public:
	Map();
	void checkVisibility(int x1, int y1, int z1);
	char get(int x2, int y2, int z2);
	char getV(int x2, int y2, int z2);
	void set(char value, int x1, int y1, int z1);
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getZ() {
		return z;
	}
};

#endif