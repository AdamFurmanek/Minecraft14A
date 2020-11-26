#ifndef Game_h
#define Game_h
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Map.h"
#include "Targa.h"

using namespace std;

class Game
{
	// K�t rotacji kierunku kamery.
	static float angleXZ;
	// Wektor reprezentuj�cy kierunek kamery.
	static float lx, lz, ly;
	// Pozycja �rodka gracza (y to wysoko�� but�w).
	static float x, y, z;
	// Pozycja �ledzonego bloku.
	static float followedX, followedY, followedZ;
	// �ciana �ledzonego bloku.
	static int followedWall;
	// Zmiany k�ta XZ oraz Y.
	static float deltaAngleXZ, deltaAngleY;
	// Zmiany przemieszczenia prosto-ty� i na boki.
	static float deltaMoveStraight, deltaMoveSides;
	// Czas trwania skoku.
	static int jump;
	// Szybko�� spadania.
	static float fallingSpeed;
	// Pole widzenia.
	static int viewField;
	static int viewDistance;
	// Latarka.
	static bool flashlight;

	static Map* map;

	public:

	static void GameInit();
	static void GameDisplay();
	static void GameReshape(int w, int h);
	static void GamePressKey(unsigned char key, int xx, int yy);
	static void GameReleaseKey(unsigned char key, int x, int y);
	static void GameMouse(int button, int state, int x, int y);
	static void GameMouseMove(int x1, int y1);

	static void LoadGame();
	static void CreateGame();

	static void ComputeSun();
	static void ComputeFall();
	static void ComputeMove();
	static void ComputeTracking();
	static bool Collision(float x, float y, float z);
	static void Wall(float x1, float y1, float z1);
	static void DrawCubeBorder();
	static void DrawCursor();
};

#endif