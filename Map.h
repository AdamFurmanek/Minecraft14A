#ifndef Map_h
#define Map_h

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
	char get(int x2, int y2, int z2) {
		if (x2<0 || y2<0 || z2<0 || x2>x - 1 || y2>y - 1 || z2>z - 1)
			return -1;
		return map[x2][y2][z2];
	}
	char getV(int x2, int y2, int z2) {
		if (x2<0 || y2<0 || z2<0 || x2>x - 1 || y2>y - 1 || z2>z - 1)
			return -1;
		return visibilityMap[x2][y2][z2];
	}
	void set(char value, int x1, int y1, int z1) {
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