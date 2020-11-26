#include "Game.h"

Map* Game::map = NULL;
Ambient* Game::ambient = NULL;
Textures* Game::textures = NULL;
Camera* Game::camera = NULL;
Player* Game::player = NULL;
Interaction* Game::interaction = NULL;

int Game::viewField = 60;
int Game::viewDistance = 40;

int frame;
long time, timebase;
char s[50];

void Game::GameInit() {

	map = new Map();
	ambient = new Ambient();
	textures = new Textures(map);
	camera = new Camera();
	player = new Player(map);
	interaction = new Interaction(map, player);

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

	camera->LookAt(player->getX(), player->getY(), player->getZ());

	player->Flashlight(camera->getVector());

	ambient->AmbientDisplay(player->getX(), player->getY(), player->getZ());

	textures->TexturesDisplay(player->getX(), player->getY(), player->getZ());

	// Rysowanie ramki śledzonego bloku.
	interaction->DrawCubeBorder();
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

	player->PressKey(key, xx, yy);
}

void Game::GameReleaseKey(unsigned char key, int x, int y) {

	player->ReleaseKey(key, x, y);
}

void Game::GameMouse(int button, int state, int x, int y) {
	
	interaction->Mouse(button, state, x, y);
}

void Game::GameMouseMove(int x1, int y1) {

	camera->Move(x1, y1);

}

void Game::GameTimer() {
	ambient->ComputeSun();

	player->ComputeFall();

	player->ComputeMove(camera->getVector()[0], camera->getVector()[2]);

	interaction->ComputeTracking(player->getX(), player->getY(), player->getZ(), camera->getVector());
}

void Game::DrawCursor() {
	// Grubość rysowania linii.
	glLineWidth(3);
	glDisable(GL_LIGHTING);
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3f(-0.002, 0, -0.1);
	glVertex3f(0.002, 0, -0.1);
	glVertex3f(0, -0.002, -0.1);
	glVertex3f(0, 0.002, -0.1);
	glEnd();
}
