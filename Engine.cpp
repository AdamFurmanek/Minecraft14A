#include "Engine.h"

Engine* Engine::engine = NULL;
Map* Engine::map = new Map();

float Engine::angleXZ = 0.0f;
float Engine::lx = -10.0f, Engine::lz = -1.0f, Engine::ly = -1.0f;
float Engine::x = 5.0f, Engine::z = 5.0f, Engine::y = 60.0f;
float Engine::deltaAngleXZ = 0.0f, Engine::deltaAngleY = 0.0f, Engine::deltaMoveStraight = 0.0f, Engine::deltaMoveSides = 0.0f;
int Engine::jump = 0;
float Engine::fallingSpeed = 0.1f;
int Engine::viewField = 45;

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
	// Do³¹czenie funkcji obs³ugi naciœniêcia klawiszy
	glutKeyboardFunc(PressKey);
	// Do³¹czenie funkcji obs³ugi zwolnienia klawiszy
	glutKeyboardUpFunc(ReleaseKey);
	// Funkcja blokuje wykonywanie powtarzaj¹cyh wciœnieñ.
	glutIgnoreKeyRepeat(1);
	// Ukrycie kursora.
	glutSetCursor(GLUT_CURSOR_NONE);
	// W³¹czenie testu bufora g³êbokoœci.
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	// Wywo³anie funkcji timera.
	glutTimerFunc(15, Timer, 1);
	// Wprowadzenie programu do obs³ugi pêtli komunikatów.
	glutMainLoop();
}

void DrawCube(int x, int y, int z, int id) {



	// Pocz¹tek definicji czworok¹ta.
	glBegin(GL_QUADS);
	// Ustawienie koloru na podstawie id.
	switch (id) {
	case 1:
		// Zielony
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case 2:
		// Czerwony
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	}

	// Góra
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);

	// Dó³
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);

	// Przód
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);

	// Ty³
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);

	// Lewo
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);

	// Prawo
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);

	// Koniec definicji prymitywu.
	glEnd();
}

void Engine::Display() {

	// Czyszczenie bufora koloru i bufora g³êbi.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Kolor t³a.
	glClearColor(0.431f, 0.698f, 0.98f, 1.0);
	// Wybór macierzy modelowania.
	glMatrixMode(GL_MODELVIEW);
	// Macierz jednostkowa.
	glLoadIdentity();
	// Ustawienie kamery.
	gluLookAt(x, y + 2.5, z, x + lx, y + ly + 2.5, z + lz, 0.0f, 1.0f, 0.0f);

	for (int x1 = 0;x1 < map->getX(); x1++) {
		for (int y1 = 0;y1 < map->getY();y1++) {
			for (int z1 = 0;z1 < map->getZ();z1++) {
				if (map->get(x1, y1, z1) != 0) {
					DrawCube(x1, y1, z1, map->get(x1, y1, z1));
				}
			}
		}
	}

	//GLfloat light_position[] = { 0.0, 15.0, 0.0, 1 };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);


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
		ly = ly - deltaAngleY;

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