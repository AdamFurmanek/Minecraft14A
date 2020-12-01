#ifndef Camera_h
#define Camera_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

class Camera
{
private:
	float vector[3];
	float angleXZ;
	float deltaAngleXZ, deltaAngleY;

public:

	Camera(float vectorX = 1, float vectorY = 0, float vectorZ = 1, float angleXZ = 0);
	void Move(int x1, int y1);
	void LookAt(float x, float y, float z);
	float* getVector() {
		return vector;
	}
	float getAngleXZ() {
		return angleXZ;
	}

};

#endif
