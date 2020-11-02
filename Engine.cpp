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



	//ŒWIAT£O
// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_NORMALIZE);
	//// Set lighting intensity and color
	//GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	//GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	//GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	//GLfloat qaLightPosition[] = { 0.5, 0.5, 0.5, 1.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);


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

	//glNormal3f(x + 1.0f, y + 2.0f, z + 0.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 0.0f);
	glVertex3f(x + 0.0f, y + 1.0f, z + 1.0f);
	glVertex3f(x + 1.0f, y + 1.0f, z + 1.0f);


	// Bottom face (y = -1.0f)
	glNormal3f(x + 1.0f, y + 0.0f, z + 0.0f);
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

	glTranslatef(20.0f, 4.0f, 20.0f);

	glutSolidTeapot(1);

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

	//glFrustum(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	//gluPerspective(45, w/h, 1.5, 100);
	// Set the correct perspective.
	gluPerspective(45, ratio, 0.01, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

void Engine::specialKeyboard(int key, int x, int y) {

}

void Engine::pressKey(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'a': deltaMoveSides = -0.4f; break;
	case 'd': deltaMoveSides = 0.4f; break;
	case 'w': deltaMove = 0.4f; break;
	case 's': deltaMove = -0.4f; break;
	case 'q':
		if (deltaMove==0.4f) {
			deltaMove += 0.6f;
		}
		break;
	case ' ':
		if(jump==0)
			jump = 2.0f;
		break;
	case 27:
		exit(0);
		break;
	}
}

void Engine::releaseKey(unsigned char key, int x, int y) {

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
		if (deltaMove > 0)
			deltaMove = 0.0f;
		break;
	case 's':
		if (deltaMove < 0)
			deltaMove = 0.0f;
		break;
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
	cout << y;
	//skok w gore
	if (jump > 0) {
		jump -= 0.1f;
		float x1, x2, y1, z1, z2;
		x1 = (int)(x + 0.3);
		x2 = (int)(x - 0.3);
		y1 = (int)(y );
		z1 = (int)(z + 0.3);
		z2 = (int)(z - 0.3);
		if (map->get(x1, y1, z1) == 0 && map->get(x2, y1, z2) == 0 && map->get(x1, y1, z2) == 0 && map->get(x2, y1, z1) == 0) {
			if(jump>0.5)
				y += 0.1;
			if (jump == 0.5)
				y += 0.05;
			if (jump == 0)
				y -= 0.05;

		}

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
			y -= 0.12;
		else
			jump = 0;
	}
	glutTimerFunc(10, timer, 1);
}

void Engine::Exception(string Error) {
	/* Tymczasowa obs³uga b³êdów: wypisanie w konsoli. */
	cout << "Error";
	exit(0);
}