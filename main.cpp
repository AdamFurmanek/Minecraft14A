#include <iostream>
#include "Window.h"

using namespace std;

int main(int argc, char* argv[]) {
	//FreeConsole();
	Window* window = Window::getInstance();
	window->Init(argc, argv);
	return 0;
}