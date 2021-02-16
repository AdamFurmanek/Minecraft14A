#include "Player.h"

Map* Player::map = NULL;

Player::Player(Map* map, float x, float y, float z, int jump, float fallingSpeed, bool flashlight, float viewField) {
	this->map = map;
	this->x = x;
	this->y = y;
	this->z = z;
	this->jump = jump;
	this->fallingSpeed = fallingSpeed;
	this->flashlight = flashlight;
	this->viewField = viewField;

	if(flashlight)
		glEnable(GL_LIGHT1);


	deltaMoveStraight = 0.0f;
	deltaMoveSides = 0.0f;

	GLfloat ambient1[] = { 0, 0, 0, 1.0 };
	GLfloat diffuse1[] = { 1.0, 0.9, 0.7, 1.0 };
	GLfloat specular1[] = { 0, 0, 0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.7);
	// Wygaszanie �wiat�a (liniowo)
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
	// Wygaszanie �wiat�a (kwadratowo)
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);
}

void Player::PressKey(unsigned char key) {

	switch (key) {
	case'f':
		if (flashlight)
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		flashlight = !flashlight;
		break;
	case 'a': deltaMoveSides = -0.12f; break;
	case 'd': deltaMoveSides = 0.12f; break;
	case 'w': deltaMoveStraight = 0.12f; break;
	case 's': deltaMoveStraight = -0.12f; break;
	case 'q':
		if (deltaMoveStraight == 0.12f) {
			deltaMoveStraight += 0.07f;
			viewField += 1.2;
		}
		break;
	case ' ':
		if (jump == 0)
			jump = 20;
		break;
	case 'r':
		ResetPosition();
		break;
	}
}

void Player::ReleaseKey(unsigned char key) {

	switch (key) {
	case 'a':
		if (deltaMoveSides < 0)
			deltaMoveSides = 0.0f;
		break;
	case 'd':
		if (deltaMoveSides > 0)
			deltaMoveSides = 0.0f;
		break;
	case 'w':
		if (deltaMoveStraight > 0.15f)
			viewField -= 1.2;
		if (deltaMoveStraight > 0)
			deltaMoveStraight = 0.0f;
		break;
	case 's':
		if (deltaMoveStraight < 0)
			deltaMoveStraight = 0.0f;
		break;
	}
}

void Player::ComputeFall() {

	// Je�li wykonywany jest skok.
	if (jump > 1) {
		// Potencjalna zmiana wysoko�ci y.
		float deltaY;
		// Zmiana wysoko�ci jest dyktowana tym, w kt�rym momencie lotu jest gracz.
		switch (jump) {
		case 20: case 19: case 18: case 17: case 16:
			deltaY = 0.15f;
			break;
		case 15: case 14: case 13:
			deltaY = 0.14f;
			break;
		case 12: case 11: case 10:
			deltaY = 0.13f;
			break;
		case 9: case 8:
			deltaY = 0.11f;
			break;
		case 7:
			deltaY = 0.09f;
			break;
		case 6:
			deltaY = 0.07f;
			break;
		case 5:
			deltaY = 0.05f;
			break;
		case 4:
			deltaY = 0.02f;
			break;
		case 3: case 2:
			deltaY = 0.00f;
			break;
		}

		// Sprawdzenie kolizji cia�a na wysoko�ci g�owy z potencjalnie now� warto�ci� y.
		if (!Collision(x, y + 2.7f + deltaY, z))
			// Przypisanie nowej warto�ci y.
			y += deltaY;

		// Zmniejszenie licznika d�ugo�ci skoku.
		jump -= 1;
	}
	// Grawitacja.
	else if (y > 0) {

		// Obliczenie potencjalnie nowej warto�ci y.
		float newY = y - fallingSpeed;
		// Sprawdzenie kolizji cia�a na wysoko�ci but�w z potencjalnie now� warto�ci� y.
		if (!Collision(x, newY, z)) {
			// Przypisanie nowej warto�ci y.
			y = newY;
			// Zwi�kszenie pr�dko�ci spadania.
			fallingSpeed += 0.006f;
		}
		else {
			// Wyr�wnanie wysoko�ci y do liczby ca�kowitej.
			y = (int)(y);
			// Zako�czenie skoku. Pozwala wykona� nowy.
			jump = 0;
			// Zresetowanie pr�dko�ci spadania do podstawowej.
			fallingSpeed = 0.1f;
		}
	}
}

void Player::ComputeMove(float x1, float z1) {
	// Je�li wykonano ruch w prz�d/ty�.
	if (deltaMoveStraight) {
		// Obliczenie potencjalnie nowej warto�ci x.
		float newX = x + (deltaMoveStraight * x1);
		// Sprawdzenie kolizji cia�a na wysoko�ci pasa i g�owy z potencjalnie now� warto�ci� x.
		if (!Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Sprawdzenie kolizji cia�a na wysoko�ci but�w.
			if (!Collision(newX, y, z))
				// Przypisanie nowej warto�ci do x.
				x = newX;
			//Autoskok na wysoko�� jednego bloku.
			else if (jump == 0)
				jump = 14;
		// Obliczenie potencjalnie nowej warto�ci z.
		float newZ = z + (deltaMoveStraight * z1);
		// Sprawdzenie kolizji cia�a na wysoko�ci pasa i g�owy z potencjalnie now� warto�ci� z.
		if (!Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Sprawdzenie kolizji cia�a na wysoko�ci but�w.
			if (!Collision(x, y, newZ))
				// Przypisanie nowej warto�ci z.
				z = newZ;
			//Autoskok na wysoko�� jednego bloku.
			else if (jump == 0)
				jump = 14;

	}
	// Je�li wykonano ruch na bok.
	if (deltaMoveSides) {
		// Obliczenie potencjalnie nowej warto�ci x.
		float newX = x + (deltaMoveSides * -z1);
		// Sprawdzenie kolizji cia�a na wysoko�ci pasa i g�owy z potencjalnie now� warto�ci� x.
		if (!Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Sprawdzenie kolizji cia�a na wysoko�ci but�w.
			if (!Collision(newX, y, z))
				// Przypisanie nowej warto�ci do x.
				x = newX;
			//Autoskok na wysoko�� jednego bloku.
			else if (jump == 0)
				jump = 14;
		// Obliczenie potencjalnie nowej warto�ci z.
		float newZ = z + (deltaMoveSides * x1);
		// Sprawdzenie kolizji cia�a na wysoko�ci pasa i g�owy z potencjalnie now� warto�ci� z.
		if (!Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Sprawdzenie kolizji cia�a na wysoko�ci but�w.
			if (!Collision(x, y, newZ))
				// Przypisanie nowej warto�ci z.
				z = newZ;
			//Autoskok na wysoko�� jednego bloku.
			else if(jump==0)
				jump = 14;
	}
}

bool Player::Collision(float x, float y, float z) {
	int x1, x2, y1, z1, z2;
	float space = 0.4;
	x1 = (int)(x + space);
	x2 = (int)(x - space);
	y1 = (int)(y);
	z1 = (int)(z + space);
	z2 = (int)(z - space);
	if (map->get(x1, y1, z1) == 0 && map->get(x2, y1, z1) == 0 && map->get(x1, y1, z2) == 0 && map->get(x2, y1, z2) == 0
		&& x1 > map->getBorders()-1 && x1<map->getX() - map->getBorders()+1 && z1> map->getBorders()-1 && z1 < map->getZ() - map->getBorders()+1)
		return false;
	else
		return true;
}

void Player::Flashlight(float vector[]) {
	GLfloat position1[] = { x, y + 2.5, z, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, vector);
}

void Player::DrawCursor() {
	glLineWidth(2);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(-0.002, 0, -0.1);
	glVertex3f(0.002, 0, -0.1);
	glVertex3f(0, -0.002, -0.1);
	glVertex3f(0, 0.002, -0.1);
	glEnd();
}

void Player::ResetPosition() {
	x = map->getX() /2;
	y = map->getY();
	z = map->getZ() /2;
	fallingSpeed = 0;
	jump = 0;
}
