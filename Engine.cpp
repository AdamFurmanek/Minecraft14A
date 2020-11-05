#include "Engine.h"
#include <math.h>

Engine* Engine::engine = NULL;
Map* Engine::map = new Map();

float Engine::angleXZ = 0.0f;
float Engine::lx = -10.0f, Engine::lz = -1.0f, Engine::ly = -1.0f;
float Engine::x = 5.0f, Engine::z = 5.0f, Engine::y = 60.0f;
float Engine::deltaAngleXZ = 0.0f, Engine::deltaAngleY = 0.0f, Engine::deltaMoveStraight = 0.0f, Engine::deltaMoveSides = 0.0f;
int Engine::jump = 0;
float Engine::fallingSpeed = 0.1f;
int Engine::viewField = 60;
float Engine::followedX = NULL;
float Engine::followedY = NULL;
float Engine::followedZ = NULL;
int Engine::followedWall = NULL;

Engine::Engine()
{
	
}

Engine::~Engine() {

}

Engine* Engine::getInstance() {
	if (Engine::engine == NULL)
		Engine::engine = new Engine();
	return Engine::engine;
}

void Engine::init(int argc, char* argv[], int w, int h, bool fullscreen) {

	// Inicjalizacja biblioteki GLUT.
	glutInit(&argc, argv);
	// Inicjalizacja podwójnego bufora ramki i system kolorów RGB.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Rozmiary g³ównego okna programu.
	glutInitWindowSize(w, h);
	// Utworzenie g³ównego okna programu.
	glutCreateWindow("Minecraft 14A");
	// Pe³na ekran okna programu.
	if (fullscreen)
		glutFullScreen();
	// Do³¹czenie funkcji generuj¹cej scenê 3D.
	glutDisplayFunc(Display);
	// Do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// Do³¹czenie funkcji obs³ugi klawiatury.
	glutKeyboardFunc(Keyboard);
	// Do³¹czenie funkcji obs³ugi snaków specjalnych klawiatury.
	glutSpecialFunc(SpecialKeyboard);
	// Do³¹czenie funkcji obs³ugi myszy.
	glutMouseFunc(Mouse);
	// Do³¹czenie funkcji obs³ugi ruchu myszy.
	glutPassiveMotionFunc(MouseMove);
	glutMotionFunc(MouseMove);
	// Do³¹czenie funkcji obs³ugi naciœniêcia klawiszy
	glutKeyboardFunc(PressKey);
	// Do³¹czenie funkcji obs³ugi zwolnienia klawiszy
	glutKeyboardUpFunc(ReleaseKey);
	// Funkcja blokuje wykonywanie powtarzaj¹cyh wciœnieñ.
	glutIgnoreKeyRepeat(1);
	// Ukrycie kursora.
	glutSetCursor(GLUT_CURSOR_NONE);


	// Wywo³anie funkcji timera.
	glutTimerFunc(15, Timer, 1);
	// Wprowadzenie programu do obs³ugi pêtli komunikatów.
	glutMainLoop();
}

void DrawCursor() {
	GLfloat diffuse[4] = { 0, 0, 0, 0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glBegin(GL_LINES);
	glVertex3f(-0.002, 0, -0.1);
	glVertex3f(0.002, 0, -0.1);
	glVertex3f(0, -0.002, -0.1);
	glVertex3f(0, 0.002, -0.1);
	glEnd();
}

void DrawCube(int x, int y, int z, int id) {

	GLfloat diffuse[4] = { 0, 0, 0, 0 };
	GLfloat ambient[4] = { 0, 0, 0, 0 };
	GLfloat specular[4] = { 0, 0, 0, 0 };
	GLfloat shininess = 0;

	// Pocz¹tek definicji czworok¹ta.
	glBegin(GL_QUADS);
	// Ustawienie koloru na podstawie id.
	switch (id) {
	case 1:
		// Zielony
		diffuse[1] = 1;
		break;
	case 2:
		// Czerwony
		diffuse[0] = 1;
		break;
	}

	// w³aœciwoœci materia³u

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	/*
	// Góra
	glNormal3f(x + 1, y + 1, z - 1);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glNormal3f(x - 1, y + 1, z - 1);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glNormal3f(x + - 1, y + 1, z + 1);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glNormal3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);

	// Dó³
	glNormal3f(x + 1, y - 1, z + 1);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glNormal3f(x - 1, y - 1, z + 1);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glNormal3f(x - 1, y - 1, z - 1);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glNormal3f(x + 1, y - 1, z - 1);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);

	// Przód
	glNormal3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glNormal3f(x - 1, y + 1, z + 1);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glNormal3f(x - 1, y - 1, z + 1);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glNormal3f(x + 1, y - 1, z + 1);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);

	// Ty³
	glNormal3f(x + 1, y - 1, z - 1);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	glNormal3f(x - 1, y - 1, z - 1);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glNormal3f(x - 1, y + 1, z - 1);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glNormal3f(x + 1, y + 1, z - 1);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);

	// Lewo
	glNormal3f(x - 1, y + 1, z + 1);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glNormal3f(x - 1, y + 1, z - 1);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glNormal3f(x - 1, y - 1, z - 1);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glNormal3f(x - 1, y - 1, z + 1);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);

	// Prawo
	glNormal3f(x + 1, y + 1, z - 1);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glNormal3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glNormal3f(x + 1, y - 1, z + 1);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glNormal3f(x + 1, y - 1, z - 1);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	*/


	glNormal3f(x, y + 2.0f, z);
	// Góra
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);

	glNormal3f(x, y - 1.0f, z);
	// Dó³
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);

	glNormal3f(x, y, z + 2.0f);
	// Przód
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);

	glNormal3f(x, y, z - 1.0f);
	// Ty³
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);

	glNormal3f(x - 1.0f, y, z);
	// Lewo
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);

	glNormal3f(x + 2.0f, y, z);
	// Prawo
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	
	// Koniec definicji prymitywu.
	glEnd();
}

void Engine::DrawCubeBorder() {
	GLfloat diffuse[4] = { 0, 0, 0, 0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glTranslatef(followedX + 0.5, followedY + 0.5, followedZ + 0.5);
	glutWireCube(1);
	glTranslatef(-followedX - 0.5, -followedY - 0.5, -followedZ - 0.5);

}

void Engine::Display() {

	glLineWidth(2);
	// Czyszczenie bufora koloru i bufora g³êbi.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Kolor t³a.
	glClearColor(0.431f, 0.698f, 0.98f, 1.0);
	// Wybór macierzy modelowania.
	glMatrixMode(GL_MODELVIEW);
	// Macierz jednostkowa.
	glLoadIdentity();

	DrawCursor();

	// Ustawienie kamery.
	gluLookAt(x, y + 2.5, z, x + lx, y + ly + 2.5, z + lz, 0.0f, 1.0f, 0.0f);

	DrawCubeBorder();
	// W³¹czenie testu bufora g³êbokoœci.
	glEnable(GL_DEPTH_TEST);
	// w³¹czenie oœwietlenia
	glEnable(GL_LIGHTING);
	// w³¹czenie œwiat³a GL_LIGHT0 z parametrami domyœlnymi
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 0.0 };
	GLfloat light_specular[] = { 0, 0, 0, 0.0 };
	GLfloat light_position[] = { 64.0, 64.0, 64.0, 0.0 };
	GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

	//cout << "Gracz: " << x << "   " << y << "   " << z << "   ";
	//glGetLightfv(GL_LIGHT0, GL_POSITION, light_position);
	//cout << "Kamera: " << light_position[0] << "   " << light_position[1] << "   " << light_position[2] << "   Kierunek: ";
	//glGetLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//cout << spot_direction[0] << "   " << spot_direction[1] << "   " << spot_direction[2] << "   " << endl;



	for (int x1 = 0;x1 < map->getX(); x1++) {
		for (int y1 = 0;y1 < map->getY();y1++) {
			for (int z1 = 0;z1 < map->getZ();z1++) {
				if (map->get(x1, y1, z1) != 0) {
					DrawCube(x1, y1, z1, map->get(x1, y1, z1));
				}
			}
		}
	}

	// Skierowanie poleceñ do wykonania.
	glFlush();
	// Zamiana buforów koloru.
	glutSwapBuffers();

}

void Engine::Reshape(int w, int h) {

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(viewField, (w * 1.0 / h), 0.01, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

void Engine::SpecialKeyboard(int key, int x, int y) {

}

void Engine::Keyboard(unsigned char key, int x, int y) {

}

void Engine::PressKey(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'a': deltaMoveSides = -0.12f; break;
	case 'd': deltaMoveSides = 0.12f; break;
	case 'w': deltaMoveStraight = 0.12f; break;
	case 's': deltaMoveStraight = -0.12f; break;
	case 'q':
		if (deltaMoveStraight== 0.12f) {
			deltaMoveStraight += 0.07f;
		}
		break;
	case ' ':
		if(jump==0)
			jump = 20;
		break;
	case 27:
		exit(0);
		break;
	}
}

void Engine::ReleaseKey(unsigned char key, int x, int y) {

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

void Engine::Mouse(int button, int state, int x, int y) {
	if(state== GLUT_DOWN)
	switch(button) {
		case GLUT_LEFT_BUTTON:
			if (followedX != NULL)
				map->set(0, followedX, followedY, followedZ);
		break;
		case GLUT_RIGHT_BUTTON:
			if (followedWall != NULL) {
				switch (followedWall) {
				case 0:
					followedX += 1;
					break;
				case 1:
					followedX -= 1;
					break;
				case 2:
					followedY += 1;
					break;
				case 3:
					followedY -= 1;
					break;
				case 4:
					followedZ += 1;
					break;
				case 5:
					followedZ -= 1;
					break;

				}
				map->set(2, followedX, followedY, followedZ);
				// Jeœli dochodzi do kolizji, usuñ postawiony blok.
				if (Collision(Engine::x, Engine::y, Engine::z) || Collision(Engine::x, Engine::y + 1, Engine::z) || Collision(Engine::x, Engine::y + 2, Engine::z)) {
					map->set(0, followedX, followedY, followedZ);
				}
			}
			break;
	}
}

void Engine::MouseMove(int x, int y) {

		// Ustawienie kursor z powrotem na œrodek.
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		// Obliczenie ruchu myszki i przypisanie do deltaAngleXZ i deltaAngleY.
		deltaAngleXZ = (x - (glutGet(GLUT_WINDOW_WIDTH) / 2)) * 0.001f;
		deltaAngleY = (y - (glutGet(GLUT_WINDOW_HEIGHT) / 2)) * 0.001f;

		// Aktualizacja wektora kamery.
		lx = sin(angleXZ + deltaAngleXZ);
		lz = -cos(angleXZ + deltaAngleXZ);
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

void Engine::Timer(int parameter)
{
	// Jeœli wykonywany jest skok.
	if (jump > 1) {
		// Potencjalna zmiana wysokoœci y.
		float deltaY;
		// Zmiana wysokoœci jest dyktowana tym, w którym momencie lotu jest gracz.
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

		// Sprawdzenie kolizji cia³a na wysokoœci g³owy z potencjalnie now¹ wartoœci¹ y.
		if (!Collision(x, y + 2.7f + deltaY, z))
			// Przypisanie nowej wartoœci y.
			y += deltaY;

		// Zmniejszenie licznika d³ugoœci skoku.
		jump -= 1;
	}
	// Grawitacja.
	else if (y > 0) {
		
		// Obliczenie potencjalnie nowej wartoœci y.
		float newY = y - fallingSpeed;
		// Sprawdzenie kolizji cia³a na wysokoœci butów z potencjalnie now¹ wartoœci¹ y.
		if (!Collision(x, newY, z)) {
			// Przypisanie nowej wartoœci y.
			y = newY;
			// Zwiêkszenie prêdkoœci spadania.
			fallingSpeed += 0.006f;
		}
		else {
			// Wyrównanie wysokoœci y do liczby ca³kowitej.
			y = (int)(y);
			// Zakoñczenie skoku. Pozwala wykonaæ nowy.
			jump = 0;
			// Zresetowanie prêdkoœci spadania do podstawowej.
			fallingSpeed = 0.1f;
		}
	}

	// Jeœli wykonano ruch w przód/ty³.
	if (deltaMoveStraight) {
		// Obliczenie potencjalnie nowej wartoœci x.
		float newX = x + (deltaMoveStraight * lx);
		// Sprawdzenie kolizji cia³a na wysokoœci butów, pasa i g³owy z potencjalnie now¹ wartoœci¹ x.
		if (!Collision(newX, y, z) && !Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Przypisanie nowej wartoœci do x.
			x = newX;
		// Obliczenie potencjalnie nowej wartoœci z.
		float newZ = z + (deltaMoveStraight * lz);
		// Sprawdzenie kolizji cia³a na wysokoœci butów, pasa i g³owy z potencjalnie now¹ wartoœci¹ z.
		if (!Collision(x, y, newZ) && !Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Przypisanie nowej wartoœci z.
			z = newZ;

	}
	// Jeœli wykonano ruch na bok.
	if (deltaMoveSides) {
		// Obliczenie potencjalnie nowej wartoœci x.
		float newX = x + (deltaMoveSides * -lz);
		// Sprawdzenie kolizji cia³a na wysokoœci butów, pasa i g³owy z potencjalnie now¹ wartoœci¹ x.
		if (!Collision(newX, y, z) && !Collision(newX, y + 1, z) && !Collision(newX, y + 2, z))
			// Przypisanie nowej wartoœci do x.
			x = newX;
		// Obliczenie potencjalnie nowej wartoœci z.
		float newZ = z + (deltaMoveSides * lx);
		// Sprawdzenie kolizji cia³a na wysokoœci butów, pasa i g³owy z potencjalnie now¹ wartoœci¹ z.
		if (!Collision(x, y, newZ) && !Collision(x, y + 1, newZ) && !Collision(x, y + 2, newZ))
			// Przypisanie nowej wartoœci z.
			z = newZ;
	}

	// Obliczenie wektora kamery.
	if (deltaAngleXZ) {
		angleXZ += deltaAngleXZ * 2;
		lx = sin(angleXZ);
		lz = -cos(angleXZ);
	}

	Following();

	// Wywo³ania Timera za 10 milisekund.
	glutTimerFunc(10, Timer, 1);
	// Render.
	glutPostRedisplay();
}

bool Engine::Collision(float x, float y, float z) {
	int x1, x2, y1, z1, z2;
	float space = 0.4;
	x1 = (int)(x + space);
	x2 = (int)(x - space);
	y1 = (int)(y);
	z1 = (int)(z + space);
	z2 = (int)(z - space);
	if (map->get(x1, y1, z1) == 0 && map->get(x2, y1, z1) == 0 && map->get(x1, y1, z2) == 0 && map->get(x2, y1, z2) == 0)
		return false;
	else
		return true;
}

void Engine::Following() {
	float x1 = x, y1 = y + 2.5, z1 = z;
	float x2 = x, y2 = y + 2, z2 = z;
	float lx1 = lx;
	float lz1 = lz;

	float ly1 = ly;
	for (int i = 0;i < 500;i++) {
		x1 += lx1 * 0.01;
		z1 += lz1 * 0.01;
		y1 += ly1 * 0.01;
		x2 = (int)(x1);
		y2 = (int)(y1);
		z2 = (int)(z1);
		if (map->get(x2, y2, z2) != 0) {
			//cout << x << "   " << y << "   " << z << endl;
			//cout << x2 << "   " << y2 << "   " << z2 << endl;
			followedX = x2;
			followedY = y2;
			followedZ = z2;
			Wall(x1,y1,z1);
			return;
		}
	}

	followedX = NULL;
	followedY = NULL;
	followedZ = NULL;
	followedWall = NULL;
	//cout << " Koniec petli: " << x1 << "   " << y1 << "   " << z1 << endl;
}

void Engine::Wall(float x1, float y1, float z1) {
	x1 = x1 - (int)x1 - 0.5;
	y1 = y1 - (int)y1 - 0.5;
	z1 = z1 - (int)z1 - 0.5;

	if (abs(x1)>abs(y1)&& abs(x1) > abs(z1)) {
		if (x1 >= 0)
			followedWall = 0;
		else if (x1 < 0)
			followedWall = 1;
	}
	else if (abs(y1) > abs(x1) && abs(y1) > abs(z1)) {
		if (y1 >= 0)
			followedWall = 2;
		else if (y1 < 0)
			followedWall = 3;
	}
	else if (abs(z1) > abs(x1) && abs(z1) > abs(y1)) {
		if (z1 >= 0)
			followedWall = 4;
		else if (z1 < 0)
			followedWall = 5;
	}
	cout << followedWall << endl;

}