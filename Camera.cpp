#include "Camera.h"

Camera::Camera(float vectorX, float vectorY, float vectorZ, float angleXZ) {
	vector[0] = vectorX;
	vector[1] = vectorY;
	vector[2] = vectorZ;
	this->angleXZ = angleXZ;
	deltaAngleXZ = 0;
	deltaAngleY = 0;
}

void Camera::LookAt(float x, float y, float z) {
	gluLookAt(x, y + 2.5, z, x + vector[0], y + vector[1] + 2.5, z + vector[2], 0.0f, 1.0f, 0.0f);
}

void Camera::Move(int x1, int y1) {
	glutSetCursor(GLUT_CURSOR_NONE);
	// Ustawienie kursor z powrotem na œrodek.
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	// Obliczenie ruchu myszki i przypisanie do deltaAngleXZ i deltaAngleY.
	deltaAngleXZ = (x1 - (glutGet(GLUT_WINDOW_WIDTH) / 2)) * 0.0006f;
	deltaAngleY = (y1 - (glutGet(GLUT_WINDOW_HEIGHT) / 2)) * 0.0006f;

	// Aktualizacja wektora kamery.
	angleXZ += deltaAngleXZ * 2;
	vector[0] = sin(angleXZ);
	vector[2] = -cos(angleXZ);

	if (deltaAngleY > 0)
		deltaAngleY += vector[1] * vector[1] / 98;
	else if (deltaAngleY < 0)
		deltaAngleY -= vector[1] * vector[1] / 98;
	vector[1] = vector[1] - deltaAngleY;
	if (vector[1] > 7)
		vector[1] = 7;
	if (vector[1] < -7)
		vector[1] = -7;
}