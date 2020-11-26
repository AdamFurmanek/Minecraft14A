#include "Ambient.h"

Ambient::Ambient() {
	glEnable(GL_LIGHT2);

	sunPosition = 0;
	sunTimer = 0;
	skyColor[0] = 0.0f;
	skyColor[1] = 0.6f;
	skyColor[2] = 1.0f;

	glEnable(GL_FOG);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogfv(GL_FOG_COLOR, skyColor);
	glFogf(GL_FOG_DENSITY, 0.001);
	glFogf(GL_FOG_MODE, GL_LINEAR);
	//TRZEBA UZALE¯NIÆ OD VIEWDISTANCE
	glFogf(GL_FOG_START, 34);
	glFogf(GL_FOG_END, 36);

}

void Ambient::ComputeSun() {
	sunTimer += 0.01;

	if (sunTimer < 0 || sunTimer > 360)
		sunTimer = 0;


	if (sunTimer <= 75) {
		sunPosition = sunTimer;
		skyColor[0] = 0;
		skyColor[1] = 0.6;
		skyColor[2] = 1;

		GLfloat ambient2[] = { 2,2,2, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
		GLfloat diffuse2[] = { 0.4, 0.4, 0.4, 1.0 };
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);

	}
	else if (sunTimer <= 120) {
		sunPosition = 75;

		float delta1 = (1 - pow(((sunTimer - 75) / 45), 2));
		float delta2 = (1 - pow(((sunTimer - 75) / 45), 1.5));
		float delta3 = (1 - pow(((sunTimer - 75) / 45), 1));

		skyColor[0] = delta3 - 1.0;
		skyColor[1] = delta3 - 0.4;
		skyColor[2] = delta3;

		GLfloat ambient2[] = { delta1 * 2, delta2 * 2, delta3 * 2, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);

		delta1 -= 0.54;
		delta2 -= 0.54;
		delta3 -= 0.54;
		if (delta1 < 0.06)
			delta1 = 0.06;
		if (delta2 < 0.06)
			delta2 = 0.06;
		if (delta3 < 0.06)
			delta3 = 0.06;

		GLfloat diffuse2[] = { delta1, delta2, delta3, 1.0 };
		for (int i = 0;i < 3;i++)
			if (diffuse2[i] < 0)
				diffuse2[i] = 0;
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);

	}
	else if (sunTimer <= 180) {
		sunPosition = 75;
		skyColor[0] = 0;
		skyColor[1] = 0;
		skyColor[2] = 0;

		GLfloat ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
		GLfloat diffuse2[] = { 0.06, 0.06, 0.06, 1.0 };
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	}
	else if (sunTimer <= 240) {
		sunPosition = 285;
		skyColor[0] = 0;
		skyColor[1] = 0;
		skyColor[2] = 0;

		GLfloat ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
		GLfloat diffuse2[] = { 0.06, 0.06, 0.06, 1.0 };
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	}
	else if (sunTimer <= 285) {
		sunPosition = 285;

		float delta1 = pow(((sunTimer - 240) / 45), 1);
		float delta2 = pow(((sunTimer - 240) / 45), 1.5);
		float delta3 = pow(((sunTimer - 240) / 45), 2);

		skyColor[0] = delta3 - 1.0;
		skyColor[1] = delta3 - 0.4;
		skyColor[2] = delta3;

		GLfloat ambient2[] = { delta1 * 2, delta2 * 2, delta3 * 2, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);

		delta1 -= 0.54;
		delta2 -= 0.54;
		delta3 -= 0.54;
		if (delta1 < 0.06)
			delta1 = 0.06;
		if (delta2 < 0.06)
			delta2 = 0.06;
		if (delta3 < 0.06)
			delta3 = 0.06;

		GLfloat diffuse2[] = { delta1, delta2, delta3, 1.0 };
		for (int i = 0;i < 3;i++)
			if (diffuse2[i] < 0)
				diffuse2[i] = 0;
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	}
	else if (sunTimer <= 360) {
		sunPosition = sunTimer;
		skyColor[0] = 0;
		skyColor[1] = 0.6;
		skyColor[2] = 1;

		GLfloat ambient2[] = { 2.0, 2.0, 2.0, 1.0 };
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
		GLfloat diffuse2[] = { 0.4, 0.4, 0.4, 1.0 };
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
	}
}

void Ambient::AmbientDisplay(float x, float y, float z) {
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(0, 0, z);
	glRotatef(sunPosition, 1, 0, 0);
	GLfloat position2[] = { x, y + 30 , 0, 1.0 };
	GLfloat direction2[] = { 0, -1, 0 };
	glLightfv(GL_LIGHT2, GL_POSITION, position2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction2);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, z);
	glRotatef(sunTimer, 1, 0, 0);
	glTranslatef(x, y + 30, 0);
	glColor3f(1, 1, 0.7);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, z);
	glRotatef(sunTimer + 180, 1, 0, 0);
	glTranslatef(x, y + 30, 0);
	glColor3f(1, 1, 1);
	glutSolidSphere(0.8, 10, 10);
	glPopMatrix();
}

void Ambient::clearColor() {
	glClearColor(skyColor[0], skyColor[1], skyColor[2], 1.0);
}