#include "Window.h"

Window* Window::engine = NULL;
Game* Window::game = new Game();
Menu* Window::menu = new Menu();
int Window::state = 0;

Window::Window()
{

}

Window::~Window() {

}

Window* Window::getInstance() {
	if (Window::engine == NULL)
		Window::engine = new Window();
	return Window::engine;
}

void Window::Init(int argc, char* argv[]) {

	// Inicjalizacja biblioteki GLUT.
	glutInit(&argc, argv);
	// Inicjalizacja podwójnego bufora ramki i system kolorów RGB.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Rozmiary głównego okna programu.
	glutInitWindowSize(1280, 720);
	// Utworzenie głównego okna programu.
	glutCreateWindow("Minecraft 14A");
	// Wyśrodkowanie okna.
	glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH) / 2 - 640, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 360);
	// Dołączenie funkcji generującej scenę 3D.
	glutDisplayFunc(Display);
	// Dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// Dołączenie funkcji obsługi myszy.
	glutMouseFunc(Mouse);
	// Dołączenie funkcji obsługi ruchu myszy.
	glutPassiveMotionFunc(MouseMove);
	glutMotionFunc(MouseMove);
	// Dołączenie funkcji obsługi naciśnięcia klawiszy
	glutKeyboardFunc(PressKey);
	// Dołączenie funkcji obsługi zwolnienia klawiszy
	glutKeyboardUpFunc(ReleaseKey);
	// Funkcja blokuje wykonywanie powtarzającyh wciśnień.
	glutIgnoreKeyRepeat(1);
	// Wywołanie funkcji timera.
	glutTimerFunc(15, Timer, 1);
	// Wprowadzenie programu do obsługi pętli komunikatów.
	glutMainLoop();
}

void Window::Display() {

	if (state == 0)
		menu->MenuDisplay();
	else if(state == 1)
		game->GameDisplay();

}

void Window::Reshape(int w, int h) {
	if (state == 0)
		menu->MenuReshape(w,h);
	else if (state == 1)
		game->GameReshape(w,h);
}

void Window::PressKey(unsigned char key, int xx, int yy) {
	if (key == '1') {
		glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH) / 2 - 640, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 360);
		glutReshapeWindow(1280, 720);
	}
	
	else if (key == '2') {
		glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH) / 2 - 800, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 450);
		glutReshapeWindow(1600, 900);
	}

	else if (key == '3') {
		glutFullScreen();
	}

	else if (state == 1) {
		game->GamePressKey(key, xx, yy);
	}
}

void Window::ReleaseKey(unsigned char key, int x, int y) {
	if (state == 1)
		game->GameReleaseKey(key, x, y);
}

void Window::Mouse(int button, int state1, int x, int y) {
	
	if (state == 0) {
		if (menu->MenuMouse(button, state1, x, y) == 1) {
			glutSetCursor(GLUT_CURSOR_WAIT);
			state = 1;
			game->CreateGame();
			game->GameReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
		else if (menu->MenuMouse(button, state1, x, y) == 2) {
			glutSetCursor(GLUT_CURSOR_WAIT);
			state = 1;
			game->LoadGame();
			game->GameReshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		}
	}
	if (state == 1)
		game->GameMouse(button, state1, x, y);
}

void Window::MouseMove(int x1, int y1) {
	if (state == 0)
		menu->MenuMouseMove(x1, y1);
	else if (state == 1)
		game->GameMouseMove(x1, y1);
}

void Window::Timer(int parameter)
{
	if (state == 0)
		menu->MenuTimer();
	else if (state == 1)
		game->GameTimer();

	glutTimerFunc(15, Timer, 1);

	glutPostRedisplay();
}
