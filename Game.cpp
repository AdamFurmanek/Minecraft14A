#include "Game.h"

Game::~Game() {
	delete map;
	delete ambient;
	delete textures;
	delete camera;
	delete player;
	delete interaction;
	delete timer;
}

void Game::GameInit() {

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glutSetCursor(GLUT_CURSOR_NONE);
	GameReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void Game::GameDisplay() {

	timer->Update();

	// Czyszczenie bufora koloru i bufora głębi.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Kolor tła.
	ambient->clearColor();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (glutGet(GLUT_WINDOW_WIDTH) * 1.0 / glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Rysowanie celownika.
	player->DrawCursor();
	// Rysowanie trzymanego bloku.
	textures->DrawSelectedBlock(interaction->getHandID());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(player->getViewField(), (glutGet(GLUT_WINDOW_WIDTH) * 1.0 / glutGet(GLUT_WINDOW_HEIGHT)), 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera->LookAt(player->getX(), player->getY(), player->getZ());

	player->Flashlight(camera->getVector());

	ambient->AmbientDisplay(player->getX(), player->getY(), player->getZ(), textures->getViewDistance());

	textures->TexturesDisplay(player->getX(), player->getY(), player->getZ(), ambient->skyColor, timer->getTimer());

	// Rysowanie ramki śledzonego bloku.
	interaction->DrawCubeBorder();
	// Skierowanie poleceń do wykonania.
	glFlush();

	// Zamiana buforów koloru.
	glutSwapBuffers();

}

void Game::GameReshape(int w, int h) {

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(player->getViewField(), (w * 1.0 / h), 0.01, 1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

void Game::GamePressKey(unsigned char key) {

	if (key == '9') {
		if(player->getViewField()>35)
			player->setViewField(player->getViewField() - 5);
	}
	else if (key == '0') {
		if (player->getViewField() < 100)
			player->setViewField(player->getViewField() + 5);
	}
	else if (key == '-') {
		if (textures->getViewDistance() > 20)
			textures->setViewDistance(textures->getViewDistance()-2);
	}
	else if (key == '=') {
		if (textures->getViewDistance() < 600)
			textures->setViewDistance(textures->getViewDistance() + 2);
	}
	else if (key == 'g') {
		if (glIsEnabled(GL_FOG)) {
			glDisable(GL_FOG);
		}
		else {
			glEnable(GL_FOG);
		}
	}
	else {
		player->PressKey(key);
	}

}

void Game::GameReleaseKey(unsigned char key) {

	player->ReleaseKey(key);
}

void Game::GameMouse(int button, int state, int x, int y) {
	
	interaction->Mouse(button, state, x, y);
}

void Game::GameMouseMove(int x1, int y1) {

	camera->Move(x1, y1);
}

void Game::GameTimer() {
	ambient->ComputeAmbient(textures->getViewDistance());

	player->ComputeFall(timer->getTime());

	player->ComputeMove(camera->getVector()[0], camera->getVector()[2], timer->getTime());

	interaction->ComputeTracking(player->getX(), player->getY(), player->getZ(), camera->getVector());
}

void Game::SaveGame(int id) {
	string name = "save1.sav";
	name[4] = (id + 48);

	ofstream plik(name.c_str(), ios::binary);
	char m;
	for (int i = 0; i < map->getX(); i++) {
		for (int j = 0; j < map->getY(); j++) {
			for (int k = 0;k < map->getZ();k++) {
				m = map->get(i, j, k);
				plik.write((const char*)&m, sizeof(char));
			}
		}
	}
	plik << "\n";
	plik << ambient->getTime() << "\n";
	plik << textures->getViewDistance() << "\n";
	plik << camera->getVector()[0] << "\n" << camera->getVector()[1] << "\n" << camera->getVector()[2] << "\n" << camera->getAngleXZ() << "\n";
	plik << player->getX() << "\n" << player->getY() << "\n" << player->getZ() << "\n" << player->getJump() << "\n" << player->getFallingSpeed() << "\n" << player->getFlashlight() << "\n" << player->getViewField() << "\n";
	plik << interaction->getHandID() << "\n";
	plik.close();

}

void Game::LoadGame(int id) {

	string name = "save1.sav";
	name[4] = (id + 48);

	ifstream plik(name.c_str(), ios::binary);

	if (!plik.is_open()) {
		CreateGame();
		return;
	}
	map = new Map(false);
	char m;
	for (int i = 0; i < map->getX(); i++) {
		for (int j = 0; j < map->getY(); j++) {
			for (int k = 0;k < map->getZ();k++) {
				plik.read((char*)&m, sizeof(char));
				map->simpleSet(m, i, j, k);
			}
		}
	}
	map->checkFullVisibility();
	float time;
	plik >> time;
	ambient = new Ambient(time);
	float viewDistance;
	plik >> viewDistance;
	textures = new Textures(map, viewDistance);
	float x, y, z;
	float angleXZ;
	plik >> x;
	plik >> y;
	plik >> z;
	plik >> angleXZ;
	camera = new Camera(x, y, z, angleXZ);
	int jump;
	float fallingSpeed;
	bool flashlight;
	float viewField;
	plik >> x;
	plik >> y;
	plik >> z;
	plik >> jump;
	plik >> fallingSpeed;
	plik >> flashlight;
	cout << flashlight << endl;
	plik >> viewField;
	player = new Player(map, x, y, z, jump, fallingSpeed, flashlight, viewField);
	int handID;
	plik >> handID;
	interaction = new Interaction(map, player, handID);
	plik.close();
	timer = new Timer();
}

void Game::CreateGame() {
	map = new Map();
	ambient = new Ambient();
	textures = new Textures(map);
	camera = new Camera();
	player = new Player(map);
	player->ResetPosition();
	interaction = new Interaction(map, player);
	timer = new Timer();
	GameInit();
}