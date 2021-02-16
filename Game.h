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
 *  \brief Klasa bêd¹ca rozgrywk¹ gry.
 *
 *  Pozwala graczowi na na grê. Korzysta i steruje klasami odpowiedzialnymi za poszczególne elementy rozgrywki:
 *  rener œwiata, ruch i kolizja gracza, otoczenie itd. Gracz ma do dyspozycji œwiat gry stworzony z szeœciennych voxeli ró¿nego rodzaju.
 *  Mo¿e siê w nim poruszaæ i dzia³a na niego grawitacja oraz kolizja z blokami. Otoczenie mo¿na dowolnie modyfikowaæ. Œwiat jest oteksturowany i oœwietlany.
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
	 *  \brief Destruktor usuwaj¹cy obiekt klasy Game.
	 *
	 *	Zabezpiecza przed du¿ymi wyciekami pamiêci.
	 *  U¿ywa siê go, gdy aplikacja ze stanu 2 przechodzi do stanu 0, usuwaj¹c aktualn¹ rozgrywkê.
	 *  Bez tego ka¿de ponownie wejœcie do rozgrywki rodzi³oby wyciek pamiêci wielkoœci 50Mb.
	 */
	~Game();

	/*! \fn void Game::GameInit()
	 *  \brief Metoda inicjuj¹ca rozgrywkê.
	 *
	 *  Inicjacja nie jest u¿ywana tylko przy uruchomieniu rozgrywki.
	 *  Wykorzystuje siê j¹, gdy z planszy zapisu gry przechodzi siê z powrotem do rozgrywki, aby w³¹czyæ odpowiednie parametry wyœwietlania.
	 *  W³¹cza funkcje odpowiednie dla rozgrywki np. faceculling, tablice wierzcho³ków i wywo³uje reshape.
	 */
	void GameInit();

	/*! \fn void Game::GameDisplay()
	 *  \brief Wyœwietlacz rozgrywki.
	 *
	 *	U¿ywana gdy stan aplikacji to 2.
	 *  U¿ywaj¹c ró¿nych klas i ich metod wykonuje kolejno:
	 *  czyœci bufor, rysuje kolor nieba, rysuje interface (kursor i aktualnie wybrany blok), ustawia kamerê,
	 *  oblicza pozycjê latarki (jeœli w³¹czona), oblicza pozycjê œwiat³a, rysuje s³oñce i ksiê¿yc,
	 *  renderuje œwiat z voxeli, rysuje ramkê œledzonego bloku, kieruje polecenia do wykonania.
	 */
	void GameDisplay();

	/*! \fn void Game::GameReshape(int w, int h)
	 *  \brief Metoda zmieniaj¹ca rozmiar okna.
	 * 	\param w nowa szerokoœæ okna
	 *	\param h nowa wysokoœæ okna
	 *
	 *  U¿ywana gdy stan aplikacji to 2.
	 */
	void GameReshape(int w, int h);

	/*! \fn void Game::GamePressKey(unsigned char key)
	 *  \brief Obs³uga klawiatury (przy naciœniêciu klawisza).
	 *  \param key okreœla u¿yty przycisk
	 *
	 *	Modyfikuje FieldOfView/ViewDistance/mg³ê jeœli gracz za¿¹da to odpowiednim przyciskiem.
	 *  W przeciwnym wypadku oddelegowuje sterowanie do metody PressKey klasy Player.
	 */
	void GamePressKey(unsigned char key);
	
	/*! \fn void Game::GameReleaseKey(unsigned char key)
	 *  \brief Obs³uga klawiatury (przy puszczeniu klawisza).
	 *  \param key okreœla u¿yty przycisk
	 *
	 *  Oddelegowuje sterowanie do metody ReleaseKey klasy Player.
	 */
	void GameReleaseKey(unsigned char key);
	
	/*! \fn void Game::GameMouse(int button, int state, int x, int y)
	 *  \brief Obs³uga myszki (naciœniêtej).
	 *	\param button okreœla u¿yty przycisk
	 *	\param state okreœla rodzaj eventu (keydown/keyup)
	 *  \param x wspó³rzêdna x myszki przy naciœniêciu
	 *  \param y wspó³rzêdna y myszki przy naciœniêciu
	 *
	 *	Oddelegowuje sterowanie do metody Mouse klasy Interaction.
	 */
	void GameMouse(int button, int state, int x, int y);
	
	/*! \fn void Game::GameMouseMove(int x1, int y1)
	 *  \brief Obs³uga myszki (ruszonej).
	 *  \param x1 nowa wspó³rzêdna x myszki
	 *  \param y1 nowa wspó³rzêdna y myszki
	 *
	 *	Oddelegowuje sterowanie do metody Move klasy Camera.
	 */
	void GameMouseMove(int x1, int y1);
	
	/*! \fn void Game::GameTimer()
	 *  \brief Obs³uga Timera.
	 *
	 *	Oddelegowuje steroanie do metod: ComputeAmbient klasy Ambient,
	 *  ComputeFall oraz ComputeMove klasy Player, ComputeTracking klasy Interaction.
	 */
	void GameTimer();
	
	/*! \fn void Game::SaveGame(int id)
	 *  \brief Metoda zapisuj¹ca stan gry do wybranego pliku.
	 * 	\param id wybrany slot zapisu
	 *
	 *	Otwiera odpowiedni plik zapisu (lub tworzy jeœli nie istnieje). Zapisuje mapê i poszczególne elementy aktualnej rozgrywki.
	 */
	void SaveGame(int id);
	
	/*! \fn void Game::LoadGame(int id)
	 *  \brief Metoda wczytuj¹ca stan gry z wybranego pliku.
	 *  \param id wybrany slot zapisu
	 *
	 *	Otwiera odpowiedni plik zapisu. Jeœli plik nie istnieje wywo³uje CreateGame i wychodzi.
	 *  Jeœli istnieje, wczytuje mapê i poszczególne elementy aktualnej rozgrywki.
	 *  Tworzy nowe obiekty wykorzystywane przez Game, daj¹c wczytane parametry do konstruktorów. 
	 */
	void LoadGame(int id);
	
	/*! \fn void Game::CreateGame()
	 *  \brief Metoda tworz¹ca now¹ grê od zera.
	 *
	 *	Tworzy nowe obiekty wykorzystywane przez Game, u¿ywaj¹c parametrów domyœlnych w konstruktorach.
	 */
	void CreateGame();

};

#endif