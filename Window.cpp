#include "Window.h"

Window* Window::engine = NULL;
Game* Window::game = new Game();

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

void Window::Init(int argc, char* argv[], int w, int h, bool fullscreen) {

	// Inicjalizacja biblioteki GLUT.
	glutInit(&argc, argv);
	// Inicjalizacja podwójnego bufora ramki i system kolorów RGB.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Rozmiary głównego okna programu.
	glutInitWindowSize(w, h);
	// Utworzenie głównego okna programu.
	glutCreateWindow("Minecraft 14A");
	// Pełna ekran okna programu.
	if (fullscreen)
		glutEnterGameMode();
		//glutFullScreen();

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
	// Ukrycie kursora.
	
	//GameInit();
	game->GameInit();

	// Wywołanie funkcji timera.
	glutTimerFunc(15, Timer, 1);
	// Wprowadzenie programu do obsługi pętli komunikatów.
	glutMainLoop();
}

void Window::Display() {

	//GameDisplay();
	game->GameDisplay();

}

void Window::Reshape(int w, int h) {

	//GameReshape(w, h);
	game->GameReshape(w,h);
}

void Window::PressKey(unsigned char key, int xx, int yy) {

	game->GamePressKey(key, xx, yy);
}

void Window::ReleaseKey(unsigned char key, int x, int y) {

	game->GameReleaseKey(key, x, y);
}

void Window::Mouse(int button, int state, int x, int y) {
	game->GameMouse(button, state, x, y);
}

void Window::MouseMove(int x1, int y1) {

	game->GameMouseMove(x1, y1);
}

void Window::Timer(int parameter)
{
	game->GameTimer();

	glutTimerFunc(15, Timer, 1);

	glutPostRedisplay();
}
