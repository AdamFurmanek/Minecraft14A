#include "Engine.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>

Engine* Engine::engine = NULL;

float Engine::angle = 0.0;
float Engine::lx = 0.0f, Engine::lz = -1.0f, Engine::ly = 0.0f;
float Engine::x = 0.0f, Engine::z = 5.0f, Engine::y = 1.0f;
float Engine::deltaAngle = 0.0, Engine::deltaAngleY = 0.0, Engine::deltaMove = 0.0, Engine::deltaMoveSides = 0.0;
float Engine::jump = 0;

//int* Engine::map = new int[8][64][8];

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

void Engine::init(int argc, char* argv[], Resolution res, bool fullscreen) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	int x, y;
	switch (res) {
	case FULLHD:
		x = 1920;
		y = 1080;
		break;
	case HD:
		x = 1280;
		y = 720;
		break;
	case SVGA:
		x = 800;
		y = 600;
		break;
	case VGA:
	default:
		x = 640;
		y = 480;
		break;
	}
	glutInitWindowSize(x, y);
	glutCreateWindow(argv[0]);
	if (fullscreen)
		glutFullScreen();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMove);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);

	glutSetCursor(GLUT_CURSOR_NONE);

	glutTimerFunc(15, timer, 1);
	glutMainLoop();
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void Engine::display() {

	if (deltaMoveSides) {
		x += deltaMoveSides * -lz * 0.3f;
		z += deltaMoveSides * lx * 0.3f;
	}
	if (deltaMove) {
		x += deltaMove * lx * 0.3f;
		z += deltaMove * lz * 0.3f;
	}


	//cout << "x: " << x << "   " << "z: " << z << endl;
	//cout << "lx: " << lx << "   " << "lz: " << lz << endl;

	if (deltaAngle) {
		angle += deltaAngle*2;
		lx = sin(angle);
		lz = -cos(angle);
	}

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.431f, 0.698f, 0.98f, 1.0);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);

	// Draw ground
	glColor3f(0.431f, 0.698f, 0.098f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

	glutSwapBuffers();

}

void Engine::reshape(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

void Engine::specialKeyboard(int key, int x, int y) {

}

void Engine::pressKey(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'a': deltaMoveSides = -0.5f; break;
	case 'd': deltaMoveSides = 0.5f; break;
	case 'w': deltaMove = 0.5f; break;
	case 's': deltaMove = -0.5f; break;
	case 'q':
		if (deltaMove==0.5f) {
			deltaMove += 1.0f;
		}
		break;
	case ' ':
		if(jump==0)
			jump = 1.5f;
		break;
	case 27:
		exit(0);
		break;
	}
}

void Engine::releaseKey(unsigned char key, int x, int y) {

	switch (key) {
	case 'a':
	case 'd': deltaMoveSides = 0.0f;break;
	case 'w':
	case 's': deltaMove = 0;break;
	}
}

void Engine::mouse(int button, int state, int x, int y) {

}

void Engine::mouseMove(int x, int y) {

		
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
		// update deltaAngle
		deltaAngle = (x-(glutGet(GLUT_WINDOW_WIDTH) / 2)) * 0.001f;
		deltaAngleY = (y - (glutGet(GLUT_WINDOW_HEIGHT) / 2)) * 0.001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
		ly = ly - deltaAngleY;
}

void Engine::timer(int parameter)
{
	//skok w gore
	if (jump > 0) {
		jump -= 0.1f;
		y += 0.1;
	}
	//spadanie
	else if (y > 1) {
		y -= 0.1;
	}
	//jakiœ problem mam z floatami i jump schodzi poni¿ej 0 :)
	if (jump < 0)
		jump = 0;
	glutTimerFunc(10, timer, 1);
}

void Engine::Exception(string Error) {
	/* Tymczasowa obs³uga b³êdów: wypisanie w konsoli. */
	cout << "Error";
	exit(0);
}