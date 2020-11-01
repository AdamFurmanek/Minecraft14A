#include <iostream>
#include "Engine.h"


using namespace std;

int main(int argc, char* argv[]) {
	Engine* engine = Engine::getInstance();
	engine->init(argc, argv, HD, false);
	return 0;
}