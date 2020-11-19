#include <iostream>
#include "Engine.h"

using namespace std;

int main(int argc, char* argv[]) {
	Engine* engine = Engine::getInstance();
	engine->init(argc, argv, 1280, 720, true);
	return 0;
}