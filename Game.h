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
		// Pole widzenia.
		static int viewField;
		static int viewDistance;

		static Map* map;
		static Ambient* ambient;
		static Textures* textures;
		static Camera* camera;
		static Player* player;
		static Interaction* interaction;

	static void GameInit();
	static void GameDisplay();
	static void GameReshape(int w, int h);
	static void GamePressKey(unsigned char key, int xx, int yy);
	static void GameReleaseKey(unsigned char key, int x, int y);
	static void GameMouse(int button, int state, int x, int y);
	static void GameMouseMove(int x1, int y1);

	static void LoadGame();
	static void CreateGame();

	static void DrawCursor();

	static void GameTimer();
};

#endif