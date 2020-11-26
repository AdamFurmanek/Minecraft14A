#ifndef Camera_h
#define Camera_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

class Camera
{
private:
	float angleXZ;
	float vector[3];
	float deltaAngleXZ, deltaAngleY;
public:

	Camera();
	void Move(int x1, int y1);
	void LookAt(float x, float y, float z);
	float* getVector() {
		return vector;
	}

};

#endif
