#ifndef Game_h
#define Game_h
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Map.h"
#include "Targa.h"
#include "Ambient.h"
#include "Textures.h"
#include "Camera.h"
#include "Player.h"
#include "Interaction.h"

using namespace std;

class Game
{
	public:

		Map* map;
		Ambient* ambient;
		Textures* textures;
		Camera* camera;
		Player* player;
		Interaction* interaction;

		~Game();
		void GameInit();
		void GameDisplay();
		void GameReshape(int w, int h);
		void GamePressKey(unsigned char key, int xx, int yy);
		void GameReleaseKey(unsigned char key, int x, int y);
		void GameMouse(int button, int state, int x, int y);
		void GameMouseMove(int x1, int y1);
		void GameTimer();
		void SaveGame(int id);
		void LoadGame(int id);
		void CreateGame();

};

#endif