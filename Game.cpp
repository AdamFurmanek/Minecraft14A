#include "Game.h"

Map* Game::map = NULL;
Ambient* Game::ambient = NULL;
Textures* Game::textures = NULL;

float Game::angleXZ = 0.0f;
float Game::lx = 1.0f, Game::lz = 1.0f, Game::ly = 0.0f;
float Game::x = 100.0f, Game::z = 100.0f, Game::y = 20;
float Game::deltaAngleXZ = 0.0f, Game::deltaAngleY = 0.0f, Game::deltaMoveStraight = 0.0f, Game::deltaMoveSides = 0.0f;
int Game::jump = 0;
float Game::fallingSpeed = 0.1f;
int Game::viewField = 60;
int Game::viewDistance = 40;
float Game::followedX = NULL;
float Game::followedY = NULL;
float Game::followedZ = NULL;
int Game::followedWall = NULL;
bool Game::flashlight = false;
int handID = 1, handMax = 13;

// variables to compute frames per second
int frame;
long time, timebase;
char s[50];

void Game::GameInit() {

	map = new Map();
	ambient = new Ambient();
	textures = new Textures(map);

	glutSetCursor(GLUT_CURSOR_NONE);
	// Grubość rysowania linii.
	glLineWidth(3);
	// Włączenie testu bufora głębokości.
	glEnable(GL_DEPTH_TEST);

	GLfloat ambient1[] = { 0, 0, 0, 1.0 };
	GLfloat diffuse1[] = { 1.0, 0.9, 0.7, 1.0 };
	GLfloat specular1[] = { 0, 0, 0, 1.0 };

	//glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.7);
	// Wygaszanie światła (liniowo)
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
	// Wygaszanie światła (kwadratowo)
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);

}

void Game::GameDisplay() {

	frame++;

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		printf("Lighthouse3D - FPS:%4.2f\n",
			frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	// Czyszczenie bufora koloru i bufora głębi.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Kolor tła.
	ambient->clearColor();

	// Wybór macierzy modelowania.
	glMatrixMode(GL_MODELVIEW);
	// Macierz jednostkowa.
	glLoadIdentity();
	// Rysowanie celownika.
	DrawCursor();

	// Ustawienie kamery.
	gluLookAt(x, y + 2.5, z, x + lx, y + ly + 2.5, z + lz, 0.0f, 0.9f, 0.0f);

	GLfloat position1[] = { x, y + 2.5, z, 1.0 };
	GLfloat direction1[] = { lx, ly, lz };
	glLightfv(GL_LIGHT1, GL_POSITION, position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);

	ambient->AmbientDisplay(x, y, z);

	textures->TexturesDisplay(x, y, z);

	// Rysowanie ramki śledzonego bloku.
	DrawCubeBorder();
	// Skierowanie poleceń do wykonania.
	glFlush();
	// Zamiana buforów koloru.
	glutSwapBuffers();

}

void Game::LoadGame() {

}

void Game::CreateGame() {

}

void Game::GameReshape(int w, int h) {

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(viewField, (w * 1.0 / h), 0.01, 64);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

void Game::GamePressKey(unsigned char key, int xx, int yy) {

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
		}
		break;
	case ' ':
		if (jump == 0)
			jump = 20;
		break;
	case 27:
		exit(0);
		break;
	}
}

void Game::GameReleaseKey(unsigned char key, int x, int y) {

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
		if (deltaMoveStraight > 0)
			deltaMoveStraight = 0.0f;
		break;
	case 's':
		if (deltaMoveStraight < 0)
			deltaMoveStraight = 0.0f;
		break;
	}
}

void Game::GameMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (followedY != 0)
				map->set(0, followedX, followedY, followedZ);
			break;
		case GLUT_RIGHT_BUTTON:
			if (followedWall != NULL) {
				switch (followedWall) {
				case 1:
					followedX += 1;
					break;
				case 2:
					followedX -= 1;
					break;
				case 3:
					followedY += 1;
					break;
				case 4:
					followedY -= 1;
					break;
				case 5:
					followedZ += 1;
					break;
				case 6:
					followedZ -= 1;
					break;

				}
				map->set(handID, followedX, followedY, followedZ);
				// Jeśli dochodzi do kolizji, usuń postawiony blok.
				if (Collision(Game::x, Game::y, Game::z) || Collision(Game::x, Game::y + 1, Game::z) || Collision(Game::x, Game::y + 2, Game::z)) {
					map->set(0, followedX, followedY, followedZ);
				}
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			handID = map->get(followedX, followedY, followedZ);
			break;
		}
	else if (button == 3) {
		handID++;
		if (handID > handMax)
			handID = 1;
	}
	else if (button == 4) {
		handID--;
		if (handID <= 0)
			handID = handMax;
	}
}

void Game::GameMouseMove(int x1, int y1) {

	// Ustawienie kursor z powrotem na środek.
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	// Obliczenie ruchu myszki i przypisanie do deltaAngleXZ i deltaAngleY.
	deltaAngleXZ = (x1 - (glutGet(GLUT_WINDOW_WIDTH) / 2)) * 0.0006f;
	deltaAngleY = (y1 - (glutGet(GLUT_WINDOW_HEIGHT) / 2)) * 0.0006f;

	// Aktualizacja wektora kamery.
	angleXZ += deltaAngleXZ * 2;
	lx = sin(angleXZ);
	lz = -cos(angleXZ);

	if (deltaAngleY > 0)
		deltaAngleY += ly * ly / 98;
	else if (deltaAngleY < 0)
		deltaAngleY -= ly * ly / 98;
	ly = ly - deltaAngleY;
	if (ly > 7)
		ly = 7;
	if (ly < -7)
		ly = -7;

}

bool Game::Collision(float x, float y, float z) {
	int edgeDistance = 40;
	int x1, x2, y1, z1, z2;
	float space = 0.4;
	x1 = (int)(x + space);
	x2 = (int)(x - space);
	y1 = (int)(y);
	z1 = (int)(z + space);
	z2 = (int)(z - space);
	if (map->get(x1, y1, z1) == 0 && map->get(x2, y1, z1) == 0 && map->get(x1, y1, z2) == 0 && map->get(x2, y1, z2) == 0
		&& x1 > edgeDistance && x1<map->getX() - edgeDistance && z1> edgeDistance && z1 < map->getZ() - edgeDistance)
		return false;
	else
		return true;
}

void Game::GameTimer() {
	ambient->ComputeSun();
	ComputeFall();

	ComputeMove();

	ComputeTracking();
}

void Game::ComputeFall() {
	// Jeśli wykonywany jest skok.
	if (jump > 1) {
		// Potencjalna zmiana wysokości y.
		float deltaY;
		// Zmiana wysokości jest dyktowana tym, w którym momencie lotu jest gracz.
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

		// Sprawdzenie kolizji ciała na wysokości głowy z potencjalnie nową wartością y.
		if (!Collision(x, y + 2.7f + deltaY, z))
			// Przypisanie nowej wartości y.
			y += deltaY;

		// Zmniejszenie licznika długości skoku.
		jump -= 1;
	}
	// Grawitacja.
	else if (y > 0) {

		// Obliczenie potencjalnie nowej wartości y.
		float newY = y - fallingSpeed;
		// Sprawdzenie kolizji ciała na wysokości butów z potencjalnie nową wartością y.
		if (!Collision(x, newY, z)) {
			// Przypisanie nowej wartości y.
			y = newY;
			// Zwiększenie prędkości spadania.
			fallingSpeed += 0.006f;
		}
		else {
			// Wyrównanie wysokości y do liczby całkowitej.
			y = (int)(y);
			// Zakończenie skoku. Pozwala wykonać nowy.
			jump = 0;
			// Zresetowanie prędkości spadania do podstawowej.
			fallingSpeed = 0.1f;
		}
	}
}

void Game::ComputeMove() {
	// Jeśli wykonano ruch w przód/tył.
	if (deltaMoveStraight) {
		// Obliczenie potencjalnie nowej wartości x.
		float newX = x + (deltaMoveStraight * lx);
		// Sprawdzenie kolizji ciała na wysokości butów, pasa i głowy z potencjalnie nową wartością x.
		if (!Collision(newX, y, z) && !Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Przypisanie nowej wartości do x.
			x = newX;
		// Obliczenie potencjalnie nowej wartości z.
		float newZ = z + (deltaMoveStraight * lz);
		// Sprawdzenie kolizji ciała na wysokości butów, pasa i głowy z potencjalnie nową wartością z.
		if (!Collision(x, y, newZ) && !Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Przypisanie nowej wartości z.
			z = newZ;

	}
	// Jeśli wykonano ruch na bok.
	if (deltaMoveSides) {
		// Obliczenie potencjalnie nowej wartości x.
		float newX = x + (deltaMoveSides * -lz);
		// Sprawdzenie kolizji ciała na wysokości butów, pasa i głowy z potencjalnie nową wartością x.
		if (!Collision(newX, y, z) && !Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Przypisanie nowej wartości do x.
			x = newX;
		// Obliczenie potencjalnie nowej wartości z.
		float newZ = z + (deltaMoveSides * lx);
		// Sprawdzenie kolizji ciała na wysokości butów, pasa i głowy z potencjalnie nową wartością z.
		if (!Collision(x, y, newZ) && !Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Przypisanie nowej wartości z.
			z = newZ;
	}
}

void Game::ComputeTracking() {
	float x1 = x, y1 = y + 2.5, z1 = z;
	float x2 = x, y2 = y + 2, z2 = z;
	float lx1 = lx;
	float lz1 = lz;

	float ly1 = ly;
	for (int i = 0;i < 450;i++) {
		x1 += lx1 * 0.01;
		z1 += lz1 * 0.01;
		y1 += ly1 * 0.01;
		x2 = (int)(x1);
		y2 = (int)(y1);
		z2 = (int)(z1);
		if (y2 > y + 6 || y2 < y - 3)
			break;
		if (map->get(x2, y2, z2) > 0) {
			//cout << x << "   " << y << "   " << z << endl;
			//cout << x2 << "   " << y2 << "   " << z2 << endl;
			followedX = x2;
			followedY = y2;
			followedZ = z2;
			Wall(x1, y1, z1);
			return;
		}
	}

	followedX = NULL;
	followedY = NULL;
	followedZ = NULL;
	followedWall = NULL;
	//cout << " Koniec petli: " << x1 << "   " << y1 << "   " << z1 << endl;
}

void Game::Wall(float x1, float y1, float z1) {
	x1 = x1 - (int)x1 - 0.5;
	y1 = y1 - (int)y1 - 0.5;
	z1 = z1 - (int)z1 - 0.5;

	if (abs(x1) > abs(y1) && abs(x1) > abs(z1)) {
		if (x1 >= 0)
			followedWall = 1;
		else if (x1 < 0)
			followedWall = 2;
	}
	else if (abs(y1) > abs(x1) && abs(y1) > abs(z1)) {
		if (y1 >= 0)
			followedWall = 3;
		else if (y1 < 0)
			followedWall = 4;
	}
	else if (abs(z1) > abs(x1) && abs(z1) > abs(y1)) {
		if (z1 >= 0)
			followedWall = 5;
		else if (z1 < 0)
			followedWall = 6;
	}
	//cout << followedWall << endl;

}

void Game::DrawCursor() {
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);
	//GLfloat diffuse[4] = { 0, 0, 0, 0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glBegin(GL_LINES);
	glVertex3f(-0.002, 0, -0.1);
	glVertex3f(0.002, 0, -0.1);
	glVertex3f(0, -0.002, -0.1);
	glVertex3f(0, 0.002, -0.1);
	glEnd();
}

void Game::DrawCubeBorder() {
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);
	//GLfloat diffuse[4] = { 0, 0, 0, 0 };
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glTranslatef(followedX + 0.5, followedY + 0.5, followedZ + 0.5);
	glutWireCube(1.005);
	glTranslatef(-followedX - 0.5, -followedY - 0.5, -followedZ - 0.5);

}