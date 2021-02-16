#ifndef Game_h
#define Game_h

#include <GL/glut.h>
#include <fstream>
#include "Map.h"
#include "Targa.h"
#include "Ambient.h"
#include "Textures.h"
#include "Camera.h"
#include "Player.h"
#include "Interaction.h"
#include "Timer.h"

/*! \class Game Game.h
 *  \brief Klasa b�d�ca rozgrywk� gry.
 *
 *  Pozwala graczowi na na gr�. Korzysta i steruje klasami odpowiedzialnymi za poszczeg�lne elementy rozgrywki:
 *  rener �wiata, ruch i kolizja gracza, otoczenie itd. Gracz ma do dyspozycji �wiat gry stworzony z sze�ciennych voxeli r�nego rodzaju.
 *  Mo�e si� w nim porusza� i dzia�a na niego grawitacja oraz kolizja z blokami. Otoczenie mo�na dowolnie modyfikowa�. �wiat jest oteksturowany i o�wietlany.
 */
class Game
{
public:

	Map* map;
	Ambient* ambient;
	Textures* textures;
	Camera* camera;
	Player* player;
	Interaction* interaction;
	Timer* timer;

	/*! \fn Game::~Game()
	 *  \brief Destruktor usuwaj�cy obiekt klasy Game.
	 *
	 *	Zabezpiecza przed du�ymi wyciekami pami�ci.
	 *  U�ywa si� go, gdy aplikacja ze stanu 2 przechodzi do stanu 0, usuwaj�c aktualn� rozgrywk�.
	 *  Bez tego ka�de ponownie wej�cie do rozgrywki rodzi�oby wyciek pami�ci wielko�ci 50Mb.
	 */
	~Game();

	/*! \fn void Game::GameInit()
	 *  \brief Metoda inicjuj�ca rozgrywk�.
	 *
	 *  Inicjacja nie jest u�ywana tylko przy uruchomieniu rozgrywki.
	 *  Wykorzystuje si� j�, gdy z planszy zapisu gry przechodzi si� z powrotem do rozgrywki, aby w��czy� odpowiednie parametry wy�wietlania.
	 *  W��cza funkcje odpowiednie dla rozgrywki np. faceculling, tablice wierzcho�k�w i wywo�uje reshape.
	 */
	void GameInit();

	/*! \fn void Game::GameDisplay()
	 *  \brief Wy�wietlacz rozgrywki.
	 *
	 *	U�ywana gdy stan aplikacji to 2.
	 *  U�ywaj�c r�nych klas i ich metod wykonuje kolejno:
	 *  czy�ci bufor, rysuje kolor nieba, rysuje interface (kursor i aktualnie wybrany blok), ustawia kamer�,
	 *  oblicza pozycj� latarki (je�li w��czona), oblicza pozycj� �wiat�a, rysuje s�o�ce i ksi�yc,
	 *  renderuje �wiat z voxeli, rysuje ramk� �ledzonego bloku, kieruje polecenia do wykonania.
	 */
	void GameDisplay();

	/*! \fn void Game::GameReshape(int w, int h)
	 *  \brief Metoda zmieniaj�ca rozmiar okna.
	 * 	\param w nowa szeroko�� okna
	 *	\param h nowa wysoko�� okna
	 *
	 *  U�ywana gdy stan aplikacji to 2.
	 */
	void GameReshape(int w, int h);

	/*! \fn void Game::GamePressKey(unsigned char key)
	 *  \brief Obs�uga klawiatury (przy naci�ni�ciu klawisza).
	 *  \param key okre�la u�yty przycisk
	 *
	 *	Modyfikuje FieldOfView/ViewDistance/mg�� je�li gracz za��da to odpowiednim przyciskiem.
	 *  W przeciwnym wypadku oddelegowuje sterowanie do metody PressKey klasy Player.
	 */
	void GamePressKey(unsigned char key);
	
	/*! \fn void Game::GameReleaseKey(unsigned char key)
	 *  \brief Obs�uga klawiatury (przy puszczeniu klawisza).
	 *  \param key okre�la u�yty przycisk
	 *
	 *  Oddelegowuje sterowanie do metody ReleaseKey klasy Player.
	 */
	void GameReleaseKey(unsigned char key);
	
	/*! \fn void Game::GameMouse(int button, int state, int x, int y)
	 *  \brief Obs�uga myszki (naci�ni�tej).
	 *	\param button okre�la u�yty przycisk
	 *	\param state okre�la rodzaj eventu (keydown/keyup)
	 *  \param x wsp�rz�dna x myszki przy naci�ni�ciu
	 *  \param y wsp�rz�dna y myszki przy naci�ni�ciu
	 *
	 *	Oddelegowuje sterowanie do metody Mouse klasy Interaction.
	 */
	void GameMouse(int button, int state, int x, int y);
	
	/*! \fn void Game::GameMouseMove(int x1, int y1)
	 *  \brief Obs�uga myszki (ruszonej).
	 *  \param x1 nowa wsp�rz�dna x myszki
	 *  \param y1 nowa wsp�rz�dna y myszki
	 *
	 *	Oddelegowuje sterowanie do metody Move klasy Camera.
	 */
	void GameMouseMove(int x1, int y1);
	
	/*! \fn void Game::GameTimer()
	 *  \brief Obs�uga Timera.
	 *
	 *	Oddelegowuje steroanie do metod: ComputeAmbient klasy Ambient,
	 *  ComputeFall oraz ComputeMove klasy Player, ComputeTracking klasy Interaction.
	 */
	void GameTimer();
	
	/*! \fn void Game::SaveGame(int id)
	 *  \brief Metoda zapisuj�ca stan gry do wybranego pliku.
	 * 	\param id wybrany slot zapisu
	 *
	 *	Otwiera odpowiedni plik zapisu (lub tworzy je�li nie istnieje). Zapisuje map� i poszczeg�lne elementy aktualnej rozgrywki.
	 */
	void SaveGame(int id);
	
	/*! \fn void Game::LoadGame(int id)
	 *  \brief Metoda wczytuj�ca stan gry z wybranego pliku.
	 *  \param id wybrany slot zapisu
	 *
	 *	Otwiera odpowiedni plik zapisu. Je�li plik nie istnieje wywo�uje CreateGame i wychodzi.
	 *  Je�li istnieje, wczytuje map� i poszczeg�lne elementy aktualnej rozgrywki.
	 *  Tworzy nowe obiekty wykorzystywane przez Game, daj�c wczytane parametry do konstruktor�w. 
	 */
	void LoadGame(int id);
	
	/*! \fn void Game::CreateGame()
	 *  \brief Metoda tworz�ca now� gr� od zera.
	 *
	 *	Tworzy nowe obiekty wykorzystywane przez Game, u�ywaj�c parametr�w domy�lnych w konstruktorach.
	 */
	void CreateGame();

};

#endif