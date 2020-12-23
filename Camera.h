#ifndef Camera_h
#define Camera_h

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/*! \class Camera Camera.h
 *  \brief Klasa odpowiedzialna za kamerê gracza.
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
	 *  \param vectorX wspó³rzêdna kierunku x
	 *  \param vectorY wspó³rzêdna kierunku y
	 *  \param vectorZ wspó³rzêdna kierunku z
	 *  \param angleXZ k¹t miêdzy x i z
	 *
	 */
	Camera(float vectorX = 1, float vectorY = 0, float vectorZ = 1, float angleXZ = 0);

	/*! \fn void Camera::Move(int x1, int y1)
	 *  \brief Sterowanie kamer¹ za pomoc¹ myszki.
	 *  \param x1 wspó³rzêdna x przesuniêtej myszki
	 *  \param y1 wspó³rzêdna y przesuniêtej myszki
	 *
	 *	Ustawia kursor myszki na niewidoczny i ustawia go na œrodek okna.
	 *  Oblicza róznicê miêdzy œrodkiem okna a nowymy wspó³rzêdnymi myszki
	 *  i na podstawie tej ró¿nicy oblicz przesuniêcie kamery.
	 */
	void Move(int x1, int y1);

	/*! \fn void Camera::LookAt(float x, float y, float z)
	 *  \brief Ustawienie kamery.
	 *  \param x wspó³rzêdna x gracza
	 *  \param y wspó³rzêdna y gracza
	 *  \param z wspó³rzêdna z gracza
	 *
	 *	Ustawia odpowiednio kamerê na podstawie po³o¿enie gracza i kierunku, w którym patrzy.
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
