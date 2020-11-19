#ifndef Map_h
#define Map_h

class Map
{
private:
	int x = 32;
	int y = 32;
	int z = 32;
	float map[32][32][32];
public:
	Map();
	float get(int x2, int y2, int z2) {
		if (x2<0 || y2<0 || z2<0 || x2>x - 1 || y2>y - 1 || z2>z - 1)
			return 1;
		return map[x2][y2][z2];
	}
	void set(float value, int x, int y, int z) {
		map[x][y][z] = value;
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