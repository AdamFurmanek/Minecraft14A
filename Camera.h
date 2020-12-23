#ifndef Camera_h
#define Camera_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/*! \class Camera Camera.h
 *  \brief Klasa odpowiedzialna za kamer� gracza.
 *
 *  Steruje kierunkiem kamery.
 */
class Camera
{
private:
	float vector[3];
	float angleXZ;
	float deltaAngleXZ, deltaAngleY;

public:

	/*! \fn Camera::Camera(float vectorX = 1, float vectorY = 0, float vectorZ = 1, float angleXZ = 0)
	 *  \brief Konstruktor.
	 *  \param vectorX wsp�rz�dna kierunku x
	 *  \param vectorY wsp�rz�dna kierunku y
	 *  \param vectorZ wsp�rz�dna kierunku z
	 *  \param angleXZ k�t mi�dzy x i z
	 *
	 */
	Camera(float vectorX = 1, float vectorY = 0, float vectorZ = 1, float angleXZ = 0);

	/*! \fn void Camera::Move(int x1, int y1)
	 *  \brief Sterowanie kamer� za pomoc� myszki.
	 *  \param x1 wsp�rz�dna x przesuni�tej myszki
	 *  \param y1 wsp�rz�dna y przesuni�tej myszki
	 *
	 *	Ustawia kursor myszki na niewidoczny i ustawia go na �rodek okna.
	 *  Oblicza r�znic� mi�dzy �rodkiem okna a nowymy wsp�rz�dnymi myszki
	 *  i na podstawie tej r�nicy oblicz przesuni�cie kamery.
	 */
	void Move(int x1, int y1);

	/*! \fn void Camera::LookAt(float x, float y, float z)
	 *  \brief Ustawienie kamery.
	 *  \param x wsp�rz�dna x gracza
	 *  \param y wsp�rz�dna y gracza
	 *  \param z wsp�rz�dna z gracza
	 *
	 *	Ustawia odpowiednio kamer� na podstawie po�o�enie gracza i kierunku, w kt�rym patrzy.
	 */
	void LookAt(float x, float y, float z);

	float* getVector() {
		return vector;
	}

	float getAngleXZ() {
		return angleXZ;
	}

};

#endif
