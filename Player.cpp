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
	autojump = false;

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

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.8);
	// Wygaszanie œwiat³a (liniowo)
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.005);
	// Wygaszanie œwiat³a (kwadratowo)
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001);

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
		if (jump == -1 || autojump) {
			autojump = false;
			jump = 20;
		}
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

void Player::ComputeFall(long int deltaTime) {
	// Jeœli wykonywany jest skok.
	if (jump > 0) {
		// Potencjalna zmiana wysokoœci y.
		float deltaY;
		// Zmiana wysokoœci jest dyktowana tym, w którym momencie lotu jest gracz.
		switch ((int)jump) {
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

		// Sprawdzenie kolizji cia³a na wysokoœci g³owy z potencjalnie now¹ wartoœci¹ y.
		if (!Collision(x, y + 2.7f + deltaY * deltaTime / 16, z))
			// Przypisanie nowej wartoœci y.
			y += deltaY * deltaTime / 16;

		// Zmniejszenie licznika d³ugoœci skoku.
		jump -= 1 * deltaTime / 16;
	}
	// Grawitacja.
	else if (y > 0) {

		// Obliczenie potencjalnie nowej wartoœci y.
		float newY = y - fallingSpeed * deltaTime / 16;
		// Sprawdzenie kolizji cia³a na wysokoœci butów z potencjalnie now¹ wartoœci¹ y.
		if (!Collision(x, newY, z)) {
			// Przypisanie nowej wartoœci y.
			y = newY;
			// Zwiêkszenie prêdkoœci spadania.
			fallingSpeed += 0.006f * deltaTime / 16;
		}
		else {
			// Wyrównanie wysokoœci y do liczby ca³kowitej.
			y = (int)(y);
			// Zakoñczenie skoku. Pozwala wykonaæ nowy.
			jump = -1;
			// Zresetowanie prêdkoœci spadania do podstawowej.
			fallingSpeed = 0.1f;
			autojump = false;
		}
	}
	else
		ResetPosition();
}

void Player::ComputeMove(float x1, float z1, long int deltaTime) {
	// Jeœli wykonano ruch w przód/ty³.
	if (deltaMoveStraight) {
		// Obliczenie potencjalnie nowej wartoœci x.
		float newX = x + (deltaMoveStraight * x1 * deltaTime/20);
		// Sprawdzenie kolizji cia³a na wysokoœci pasa i g³owy z potencjalnie now¹ wartoœci¹ x.
		if (!Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Sprawdzenie kolizji cia³a na wysokoœci butów.
			if (!Collision(newX, y, z))
				// Przypisanie nowej wartoœci do x.
				x = newX;
			//Autoskok na wysokoœæ jednego bloku.
			else if (jump == -1) {
				jump = 13;
				autojump = true;
			}
		// Obliczenie potencjalnie nowej wartoœci z.
		float newZ = z + (deltaMoveStraight * z1 * deltaTime / 20);
		// Sprawdzenie kolizji cia³a na wysokoœci pasa i g³owy z potencjalnie now¹ wartoœci¹ z.
		if (!Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Sprawdzenie kolizji cia³a na wysokoœci butów.
			if (!Collision(x, y, newZ))
				// Przypisanie nowej wartoœci z.
				z = newZ;
			//Autoskok na wysokoœæ jednego bloku.
			else if (jump == -1){
				jump = 13;
				autojump = true;
			}

	}
	// Jeœli wykonano ruch na bok.
	if (deltaMoveSides) {
		// Obliczenie potencjalnie nowej wartoœci x.
		float newX = x + (deltaMoveSides * -z1 * deltaTime / 20);
		// Sprawdzenie kolizji cia³a na wysokoœci pasa i g³owy z potencjalnie now¹ wartoœci¹ x.
		if (!Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Sprawdzenie kolizji cia³a na wysokoœci butów.
			if (!Collision(newX, y, z))
				// Przypisanie nowej wartoœci do x.
				x = newX;
			//Autoskok na wysokoœæ jednego bloku.
			else if (jump == -1){
				jump = 13;
				autojump = true;
			}
		// Obliczenie potencjalnie nowej wartoœci z.
		float newZ = z + (deltaMoveSides * x1 * deltaTime / 20);
		// Sprawdzenie kolizji cia³a na wysokoœci pasa i g³owy z potencjalnie now¹ wartoœci¹ z.
		if (!Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Sprawdzenie kolizji cia³a na wysokoœci butów.
			if (!Collision(x, y, newZ))
				// Przypisanie nowej wartoœci z.
				z = newZ;
			//Autoskok na wysokoœæ jednego bloku.
			else if(jump == -1){
				jump = 13;
				autojump = true;
			}
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
	if (!(map->getCollision(x1, y1, z1)) && !(map->getCollision(x2, y1, z1)) && !(map->getCollision(x1, y1, z2)) && !(map->getCollision(x2, y1, z2))
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
