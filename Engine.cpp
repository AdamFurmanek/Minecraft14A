#include "Engine.h"

Engine* Engine::engine = NULL;
Map* Engine::map = new Map();

float Engine::angle = 0.0;
float Engine::lx = 0.0f, Engine::lz = -1.0f, Engine::ly = 0.0f;
float Engine::x = 5.0f, Engine::z = 5.0f, Engine::y = 4.0f;
float Engine::deltaAngle = 0.0, Engine::deltaAngleY = 0.0, Engine::deltaMove = 0.0, Engine::deltaMoveSides = 0.0;
float Engine::jump = 0;

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
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(15, timer, 1);
	glutMainLoop();
}

void drawCube(int x, int y, int z, int id) {
	glBegin(GL_QUADS);
	float r, g, b;
	switch (id) {
	case 1:
		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		break;
	case 2:
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		break;
	}

	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);

	// Bottom face (y = -1.0f)
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);

	// Front face  (z = 1.0f)
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);

	// Back face (z = -1.0f)
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);

	// Left face (x = -1.0f)
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 0.0f, z + 1.0f);

	// Right face (x = 1.0f)
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 0.0f, z + 0.0f);
	glEnd();  // End of drawing color-cube
}

void Engine::display() {

	if (deltaMoveSides) {

		float space = (deltaMoveSides >= 0) ? (0.3) : (-0.3);

		float x1, x2, y1, z1, z2;
		x1 = (int)(x + space + (deltaMoveSides * -lz * 0.3f));
		x2 = (int)(x - space + (deltaMoveSides * -lz * 0.3f));
		y1 = (int)(y - 1);
		z1 = (int)(z);
		if (lz <0 && map->get(x1, y1, z1) == 0 && map->get(x1, y1 - 1, z1) == 0 && map->get(x1, y1 + 1, z1) == 0)
			x += deltaMoveSides * -lz * 0.3f;
		else if(lz >0 && map->get(x2, y1 - 1, z1) == 0 && map->get(x2, y1 - 1, z1) == 0 && map->get(x2, y1 + 1, z1) == 0)
			x += deltaMoveSides * -lz * 0.3f;
		x1 = (int)(x);
		z1 = (int)(z + space + (deltaMoveSides * lx * 0.3f));
		z2 = (int)(z - space + (deltaMoveSides * lx * 0.3f));
		if (lx>0 && map->get(x1, y1, z1) == 0 && map->get(x1, y1 - 1, z1) == 0 && map->get(x1, y1 + 1, z1) == 0)
			z += deltaMoveSides * lx * 0.3f;
		else if(lx<0 && map->get(x1, y1, z2) == 0 && map->get(x1, y1 - 1, z2) == 0 && map->get(x1, y1 + 1, z2) == 0)
			z += deltaMoveSides * lx * 0.3f;
	}
	if (deltaMove) {

		float space = (deltaMove >= 0) ? (0.3) : (-0.3);

		float x1, x2, y1, z1, z2;
		x1 = (int)(x + space + (deltaMove * lx * 0.3f));
		x2 = (int)(x - space + (deltaMove * lx * 0.3f));
		y1 = (int)(y - 1);
		z1 = (int)(z);
		if (lx > 0 && map->get(x1, y1, z1) == 0 && map->get(x1, y1 - 1, z1) == 0&& map->get(x1, y1 + 1, z1) == 0) {
			x += deltaMove * lx * 0.3f;
		}
		else if (lx < 0 && map->get(x2, y1, z1) == 0 && map->get(x2, y1 - 1, z1) == 0 && map->get(x2, y1 + 1, z1) == 0) {
			x += deltaMove * lx * 0.3f;
		}
		x1 = (int)(x);
		z1 = (int)(z + space + (deltaMove * lz * 0.3f));
		z2 = (int)(z - space + (deltaMove * lz * 0.3f));
		if (lz > 0 && map->get(x1,y1,z1) == 0 && map->get(x1, y1-1, z1) == 0 && map->get(x1, y1 + 1, z1) == 0)
			z += deltaMove * lz * 0.3f;
		if( lz<0 && map->get(x1, y1, z2) == 0 && map->get(x1, y1 - 1, z2) == 0 && map->get(x1, y1 + 1, z2) == 0)
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
	cout << y << endl;
	gluLookAt(x, y-0.5, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);

	for (int x = 0;x < map->getX(); x++) {
		for (int y = 0;y < map->getY();y++) {
			for (int z = 0;z < map->getZ();z++) {
				if (map->get(x, y, z) != 0) {
					drawCube(x, y, z, map->get(x, y, z));
				}
			}
		}
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
		float x1, x2, y1, z1, z2;
		x1 = (int)(x + 0.3);
		x2 = (int)(x - 0.3);
		y1 = (int)(y );
		z1 = (int)(z + 0.3);
		z2 = (int)(z - 0.3);
		if (map->get(x1, y1, z1) == 0 && map->get(x2, y1, z2) == 0 && map->get(x1, y1, z2) == 0 && map->get(x2, y1, z1) == 0)
			y += 0.1;
	}
	//spadanie
	else if (y > 2) {
		float x1, x2, y1, z1, z2;
		x1 = (int)(x + 0.3);
		x2 = (int)(x - 0.3);
		y1 = (int)(y - 1);
		z1 = (int)(z + 0.3);
		z2 = (int)(z - 0.3);
		if (map->get(x1, y1 - 2, z1) == 0 && map->get(x2, y1 - 2, z2) == 0 && map->get(x1, y1 - 2, z2) == 0 && map->get(x2, y1 - 2, z1) == 0)
			y -= 0.1;
		else
			jump = 0;
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