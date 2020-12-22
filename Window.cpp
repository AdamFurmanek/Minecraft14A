#include "Window.h"

Window* Window::engine = NULL;
Game* Window::game = NULL;
Menu* Window::menu = new Menu();
int Window::state = 0;

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
	// Inicjacja parametrów obiektu menu.
	menu->InitMenu();
	// Wywołanie funkcji timera.
	glutTimerFunc(15, Timer, 1);
	// Wprowadzenie programu do obsługi pętli komunikatów.
	glutMainLoop();
}

void Window::Display() {

	if (state == 0)
		menu->MenuDisplay();
	else if (state == 1)
		menu->SavingMenuDisplay();
	else if(state == 2)
		game->GameDisplay();
	else if(state == 3)
		menu->SavingMenuDisplay();

	glutPostRedisplay();
}

void Window::Reshape(int w, int h) {
	if (state == 0)
		menu->MenuReshape(w,h);
	else if (state == 1)
		menu->MenuReshape(w, h);
	else if (state == 2)
		game->GameReshape(w,h);
	else if (state == 3)
		menu->MenuReshape(w, h);
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
	else if (state == 0) {
		if (key == 27)
			exit(0);
	}
	else if (state == 1) {
		if (key == 27)
			state = 0;
	}
	else if (state == 2) {
		if (key == 27) {
			menu->InitMenu();
			state = 0;
			delete game;
		}
		else if (key == 'v') {
			menu->InitMenu();
			state = 3;
		}
		else {
			game->GamePressKey(key, xx, yy);
		}
	}
	else if (state == 3) {
		if (key == 27) {
			game->GameInit();
			state = 2;
		}
	}
}

void Window::ReleaseKey(unsigned char key, int x, int y) {
	if (state == 2)
		game->GameReleaseKey(key, x, y);
}

void Window::Mouse(int button, int state1, int x, int y) {
		if (state == 0 && state1 == GLUT_DOWN) {
			if (menu->MenuMouse(x, y) == 1) {
				glutSetCursor(GLUT_CURSOR_WAIT);
				game = new Game();
				game->CreateGame();
				game->GameInit();
				state = 2;
			}
			else if (menu->MenuMouse(x, y) == 2) {
				state = 1;
			}
		}
		else if (state == 1 && state1 == GLUT_DOWN) {
			int id = menu->SavingMenuMouseChecked(x, y);
			if (id != 0) {
				glutSetCursor(GLUT_CURSOR_WAIT);
				game = new Game();
				game->LoadGame(id);
				game->GameInit();
				state = 2;
			}
		}
		else if (state == 2) {
			game->GameMouse(button, state1, x, y);
		}
		else if (state == 3 && state1 == GLUT_DOWN) {
			int id = menu->SavingMenuMouse(x, y);
			if (id != 0) {
				glutSetCursor(GLUT_CURSOR_WAIT);
				game->SaveGame(id);
				game->GameInit();
				state = 2;
			}
		}
}

void Window::MouseMove(int x1, int y1) {
	if (state == 0)
		menu->MenuMouseMove(x1, y1);
	else if (state == 1)
		menu->SavingMenuMouseMove(x1, y1);
	else if (state == 2)
		game->GameMouseMove(x1, y1);
	else if (state == 3)
		menu->SavingMenuMouseMove(x1, y1);
}

void Window::Timer(int parameter)
{
	if (state == 2)
		game->GameTimer();

	glutTimerFunc(15, Timer, 1);
}
