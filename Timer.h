#include <ctime>
#ifndef Timer_h
#define Timer_h

class Timer
{
private:
	//Czas okreœlaj¹cy ile minê³o od ostatniej klatki.
	long int milliseconds;
	clock_t lastTime;

	//Licznik id¹cy od 0 do 1.
	float timer;

public:
	Timer() {
		milliseconds = 10;
		lastTime = clock();
		timer = 0;
	}

	void Update() {
		milliseconds = clock() - lastTime;
		lastTime = clock();
		timer += (float)milliseconds/6000;
		if (timer > 1)
			timer -= 1;
	}

	long int getTime() {
		return milliseconds;
	}

	float getTimer() {
		return timer;
	}

};

#endif