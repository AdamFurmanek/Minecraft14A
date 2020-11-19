#define _CRT_SECURE_NO_WARNINGS
#ifndef Engine_h
#define Engine_h

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Map.h"

using namespace std;

class Engine
{
private:
	static Engine* engine;
	Engine();
	~Engine();

	// K¹t rotacji kierunku kamery.
	static float angleXZ;
	// Wektor reprezentuj¹cy kierunek kamery.
	static float lx, lz, ly;
	// Pozycja œrodka gracza (y to wysokoœæ butów).
	static float x, y, z;
	// Pozycja œledzonego bloku.
	static float followedX, followedY, followedZ;
	// Œciana œledzonego bloku.
	static int followedWall;
	// Zmiany k¹ta XZ oraz Y.
	static float deltaAngleXZ, deltaAngleY;
	// Zmiany przemieszczenia prosto-ty³ i na boki.
	static float deltaMoveStraight, deltaMoveSides;
	// Czas trwania skoku.
	static int jump;
	// Szybkoœæ spadania.
	static float fallingSpeed;
	// Pole widzenia.
	static int viewField;
	// Latarka.
	static bool flashlight;

	static void Display();
	static void Reshape(int w, int h);
	static void Keyboard(unsigned char key, int x, int y);
	static void SpecialKeyboard(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void PressKey(unsigned char key, int xx, int yy);
	static void ReleaseKey(unsigned char key, int x, int y);
	static void MouseMove(int x, int y);
	static void Timer(int parameter);
	// Metoda sprawdza czy cia³o gracza na jego podanej wysokoœci nie styka siê krawêdziami z blokiem.
	static bool Collision(float x, float y, float z);
	static void Following();
	static void Wall(float x1, float y1, float z1);
	static Map* map;

	static void DrawCubeBorder();

public:

	static Engine* getInstance();
	static void init(int argc, char* argv[], int w, int h, bool fullscreen);


};

#endif