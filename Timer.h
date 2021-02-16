#include <ctime>
#ifndef Timer_h
#define Timer_h

class Timer
{
private:
	long int milliseconds;
	clock_t lastTime;

public:
	Timer() {
		milliseconds = 10;
		lastTime = clock();
	}

	void Update() {
		milliseconds = clock() - lastTime;
		lastTime = clock();
	}

	long int getTime() {
		return milliseconds;
	}

};

#endif