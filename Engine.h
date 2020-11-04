#ifndef Engine_h
#define Engine_h

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "Map.h"

using namespace std;

class Engine
{
private:
	static Engine* engine;
	Engine();
	~Engine();

	// K�t rotacji kierunku kamery.
	static float angleXZ;
	// Wektor reprezentuj�cy kierunek kamery.
	static float lx, lz, ly;
	// Pozycja �rodka gracza (y to wysoko�� but�w)
	static float x, y, z;
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

	static void Display();
	static void Reshape(int w, int h);
	static void Keyboard(unsigned char key, int x, int y);
	static void SpecialKeyboard(int key, int x, int y);
	static void Mouse(int button, int state, int x, int y);
	static void PressKey(unsigned char key, int xx, int yy);
	static void ReleaseKey(unsigned char key, int x, int y);
	static void MouseMove(int x, int y);
	static void Timer(int parameter);
	// Metoda sprawdza czy cia�o gracza na jego podanej wysoko�ci nie styka si� kraw�dziami z blokiem.
	static bool Collision(float x, float y, float z);
	static Map* map;

public:

	static Engine* getInstance();
	static void init(int argc, char* argv[], int w, int h, bool fullscreen);


};

#endif