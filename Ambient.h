#ifndef Ambient_h
#define Ambient_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

class Ambient
{
private:
	float Time;
	GLfloat skyColor[3] = { 0.0f, 0.6f, 1.0f };
public:
	Ambient(float Timer = 0);
	void ComputeAmbient(int viewDistance);
	void AmbientDisplay(float x, float y, float z, int viewDistance);
	void clearColor();
	float getTime() {
		return Time;
	}
};

#endif