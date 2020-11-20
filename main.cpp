#include <iostream>
#include "Window.h"

using namespace std;

int main(int argc, char* argv[]) {
	Window* window = Window::getInstance();
	window->Init(argc, argv, 1280, 720, false);
	return 0;
}