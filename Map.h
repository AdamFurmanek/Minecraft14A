#ifndef Map_h
#define Map_h

#include <iostream>
#include <stdlib.h>

using namespace std;

class Map
{
private:
	int x;
	int y;
	int z;
	//U¿yte zosta³y chary, poniewa¿ zajmuj¹ najmniej miejsca.
	char map[600][64][600];
	char visibilityMap[600][64][600];
public:
	Map(bool generate = true);

	void Generate();
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