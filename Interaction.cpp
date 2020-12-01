#include "Interaction.h"

Map* Interaction::map = NULL;
Player* Interaction::player = NULL;

Interaction::Interaction(Map* map, Player* player, int handID) {
	this->map = map;
	this->player = player;
	followedX = 0;
	followedY = 0;
	followedZ = 0;
	followedWall = 0;
	this->handID = handID;
	handMax = 13;
}

void Interaction::Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		switch (button) {
		case GLUT_LEFT_BUTTON:
			if (followedWall != 0 && followedY > 0)
				map->set(0, followedX, followedY, followedZ);
			break;
		case GLUT_RIGHT_BUTTON:
			if (followedWall != 0) {
				switch (followedWall) {
				case 1:
					followedX += 1;
					break;
				case 2:
					followedX -= 1;
					break;
				case 3:
					followedY += 1;
					break;
				case 4:
					followedY -= 1;
					break;
				case 5:
					followedZ += 1;
					break;
				case 6:
					followedZ -= 1;
					break;

				}
				map->set(handID, followedX, followedY, followedZ);
				// Jeœli dochodzi do kolizji, usuñ postawiony blok.
				if (player->Collision(player->getX(), player->getY(), player->getZ()) || player->Collision(player->getX(), player->getY() + 1, player->getZ()) || player->Collision(player->getX(), player->getY() + 2, player->getZ())) {
					map->set(0, followedX, followedY, followedZ);
				}
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			if (followedWall != 0) {
				handID = map->get(followedX, followedY, followedZ);
				break;
			}
		}
	else if (button == 3) {
		handID++;
		if (handID > handMax)
			handID = 1;
	}
	else if (button == 4) {
		handID--;
		if (handID <= 0)
			handID = handMax;
	}
}

void Interaction::ComputeTracking(float x, float y, float z, float vector[3]) {
	float x1 = x, y1 = y + 2.5, z1 = z;
	float x2 = x, y2 = y + 2, z2 = z;
	float lx1 = vector[0];
	float ly1 = vector[1];
	float lz1 = vector[2];

	for (int i = 0;i < 450;i++) {
		x1 += lx1 * 0.01;
		z1 += lz1 * 0.01;
		y1 += ly1 * 0.01;
		x2 = (int)(x1);
		y2 = (int)(y1);
		z2 = (int)(z1);
		if (y2 > y + 6 || y2 < y - 3 || x2<51 || z2<51 || x2 > map->getX() - 48 || z2 > map->getX() - 48)
			break;
		if (map->get(x2, y2, z2) > 0) {
			//cout << x << "   " << y << "   " << z << endl;
			//cout << x2 << "   " << y2 << "   " << z2 << endl;
			followedX = x2;
			followedY = y2;
			followedZ = z2;
			Wall(x1, y1, z1);
			return;
		}
	}

	followedX = NULL;
	followedY = NULL;
	followedZ = NULL;
	followedWall = NULL;
	//cout << " Koniec petli: " << x1 << "   " << y1 << "   " << z1 << endl;
}

void Interaction::Wall(float x1, float y1, float z1) {
	x1 = x1 - (int)x1 - 0.5;
	y1 = y1 - (int)y1 - 0.5;
	z1 = z1 - (int)z1 - 0.5;

	if (abs(x1) > abs(y1) && abs(x1) > abs(z1)) {
		if (x1 >= 0)
			followedWall = 1;
		else if (x1 < 0)
			followedWall = 2;
	}
	else if (abs(y1) > abs(x1) && abs(y1) > abs(z1)) {
		if (y1 >= 0)
			followedWall = 3;
		else if (y1 < 0)
			followedWall = 4;
	}
	else if (abs(z1) > abs(x1) && abs(z1) > abs(y1)) {
		if (z1 >= 0)
			followedWall = 5;
		else if (z1 < 0)
			followedWall = 6;
	}

}

void Interaction::DrawCubeBorder() {
	// Gruboœæ rysowania linii.
	glLineWidth(3);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glColor3f(10, 10, 10);
	glTranslatef(followedX + 0.5, followedY + 0.5, followedZ + 0.5);
	glutWireCube(1.005);
	glTranslatef(-followedX - 0.5, -followedY - 0.5, -followedZ - 0.5);
}