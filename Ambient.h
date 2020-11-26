#ifndef Ambient_h
#define Ambient_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

class Ambient
{
private:
	float sunPosition = 0, sunTimer = 0;
	GLfloat skyColor[3] = { 0.0f, 0.6f, 1.0f };
public:
	Ambient();
	void ComputeSun();
	void AmbientDisplay(float x, float y, float z);
	void clearColor();
};

#endif