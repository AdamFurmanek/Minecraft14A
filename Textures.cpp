#include "Textures.h"
#include "WaterShader.h"


WaterShader* waterShader;

const float cube_vert[] = {
1.001f, 1.001f, -0.001f,
-0.001f, 1.001f, -0.001f,
1.001f, 1.001f, 1.001f,
-0.001f, 1.001f, 1.001f,

1.001f, -0.001f, 1.001f,
-0.001f, -0.001f, 1.001f,
1.001f, -0.001f, -0.001f,
-0.001f, -0.001f, -0.001f,

-0.001f, 1.001f, 1.001f,
-0.001f, -0.001f, 1.001f,
1.001f, 1.001f, 1.001f,
1.001f, -0.001f, 1.001f,

1.001f, -0.001f, -0.001f,
-0.001f, -0.001f, -0.001f,
1.001f, 1.001f, -0.001f,
-0.001f, 1.001f, -0.001f,

-0.001f, 1.001f, -0.001f,
-0.001f, -0.001f, -0.001f,
-0.001f, 1.001f, 1.001f,
-0.001f, -0.001f, 1.001f,

1.001f, 1.001f, -0.001f,
1.001f, 1.001f, 1.001f,
1.001f, -0.001f, -0.001f,
1.001f, -0.001f, 1.001f

};

const float cube_norm[] = {
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,

0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,

0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,

0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,

-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,

1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
};

const unsigned char wallTop[] = {
0, 1, 2,// strona 1
1, 3, 2
};

const unsigned char wallBottom[] = {
4, 5, 6, // strona 2
5, 7, 6
};

const unsigned char wallZp[] = {
8, 9, 10, // strona 3
9, 11, 10
};

const unsigned char wallZm[] = {
12, 13, 14, // strona 4
13, 15, 14
};

const unsigned char wallXm[] = {
16, 17, 18, // strona 5
17, 19, 18
};

const unsigned char wallXp[] = {
20, 21, 22, // strona 6
21, 23, 22
};

const float cube_texc[] = {
	0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 1.0f,
	1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f,
	1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f,
	0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 1.0f,
	1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f,
	0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 1.0f
};

Map* Textures::map = NULL;

Textures::Textures(Map* map, float viewDistance) {

	this->map = map;
	this->viewDistance = viewDistance;

	// Wygenerowanie 14 identyfikatorów dla tekstur:
	glGenTextures(14, TextureID);
	// Aktywacja trzech tekstur i ³adowanie ich z plików TGA:
	glBindTexture(GL_TEXTURE_2D, TextureID[0]);
	LoadTGAMipmap(_strdup("nic"));
	glBindTexture(GL_TEXTURE_2D, TextureID[1]);
	LoadTGAMipmap(_strdup("Textures//bedrock.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
	LoadTGAMipmap(_strdup("Textures//stone.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[3]);
	LoadTGAMipmap(_strdup("Textures//dirt.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[4]);
	LoadTGAMipmap(_strdup("Textures//grass.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[5]);
	LoadTGAMipmap(_strdup("Textures//sand.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[6]);
	LoadTGAMipmap(_strdup("Textures//sandstone.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[7]);
	LoadTGAMipmap(_strdup("Textures//tree.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[8]);
	LoadTGAMipmap(_strdup("Textures//leaves.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[9]);
	LoadTGAMipmap(_strdup("Textures//obsidian.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[10]);
	LoadTGAMipmap(_strdup("Textures//smooth_stone.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[11]);
	LoadTGAMipmap(_strdup("Textures//stone_bricks.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[12]);
	LoadTGAMipmap(_strdup("Textures//purple_plate.tga"));
	glBindTexture(GL_TEXTURE_2D, TextureID[13]);
	LoadTGAMipmap(_strdup("Textures//red_plate.tga"));

	glVertexPointer(3, GL_FLOAT, 0, cube_vert);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texc);
	glNormalPointer(GL_FLOAT, 0, cube_norm);

	waterShader = new WaterShader();

	(*waterNoise1).SetFrequency(5);
	(*waterNoise1).SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
}

void Textures::TexturesDisplay(float x, float y, float z, GLfloat skyColor[3], float timer) {

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble windowX, windowY, windowZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	int x1, y1, z1;
	char v;
	for (y1 = 0;y1 < map->getY();y1++) {
		for (x1 = x - viewDistance;x1 < x + viewDistance; x1++) {
			for (z1 = z - viewDistance;z1 < z + viewDistance;z1++) {
				if (map->get(x1, y1, z1) > 0 && (v = map->getV(x1, y1, z1)) != 63) {
					gluProject(x1 + 0.5, y1, z1 + 0.5, modelview, projection, viewport, &windowX, &windowY, &windowZ);
					if ((y1 > y - 3 && y1 < y + 3 && x1 > x - 3 && x1 < x + 3 && z1 > z - 3 && y1 < z + 3) || (windowX<2400 && windowX>-500 && windowY > -700 && windowY < 1200 && windowZ < 1)) { //jeśli odległość mała
						
						glPushMatrix();

						glTranslatef(x1, y1, z1);

						glBindTexture(GL_TEXTURE_2D, TextureID[map->get(x1, y1, z1)]);

						//Shader wody.
						if (map->get(x1, y1, z1) == 100) {
							glDisable(GL_TEXTURE_2D);
							glColor3f(skyColor[0] * 0.8, skyColor[1] * 0.8, skyColor[2] * 0.8);

							float height = timer - (int)timer;
							
							height += abs((*waterNoise1).GetNoise((float)z1, (float)x1) * 10);
							while (height > 1)
								height -= 1;
							if (height > 0.5)
								height = 1 - height;
							waterShader->Enable(height, 0);
						}

						if (((v >> 0) & 1UL) == 0 && y + 2.5 > y1)
							glDrawElements(GL_TRIANGLES, sizeof(wallTop), GL_UNSIGNED_BYTE, wallTop);
						if (((v >> 1) & 1UL) == 0 && y + 2.5 < y1)
							glDrawElements(GL_TRIANGLES, sizeof(wallBottom), GL_UNSIGNED_BYTE, wallBottom);
						if (((v >> 2) & 1UL) == 0 && z > z1)
							glDrawElements(GL_TRIANGLES, sizeof(wallZp), GL_UNSIGNED_BYTE, wallZp);
						if (((v >> 3) & 1UL) == 0 && z < z1)
							glDrawElements(GL_TRIANGLES, sizeof(wallZm), GL_UNSIGNED_BYTE, wallZm);
						if (((v >> 4) & 1UL) == 0 && x < x1)
							glDrawElements(GL_TRIANGLES, sizeof(wallXm), GL_UNSIGNED_BYTE, wallXm);
						if (((v >> 5) & 1UL) == 0 && x > x1)
							glDrawElements(GL_TRIANGLES, sizeof(wallXp), GL_UNSIGNED_BYTE, wallXp);

						if (map->get(x1, y1, z1) == 100) {
							waterShader->Disable();
							glEnable(GL_TEXTURE_2D);
						}

						glPopMatrix();

					}
				}
			}
		}
	}
}


void Textures::DrawSelectedBlock(int id) {

	double w = glutGet(GLUT_SCREEN_WIDTH);
	double h = glutGet(GLUT_SCREEN_HEIGHT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glScalef(0.005, 0.005, 0.005);
	glTranslatef(w*0.005, -h*0.005, -12);
		glBindTexture(GL_TEXTURE_2D, TextureID[id]);
		glDrawElements(GL_TRIANGLES, sizeof(wallZp), GL_UNSIGNED_BYTE, wallZp);

	glTranslatef(-w*0.005, h*0.005, 12);
	glScalef(200, 200, 200);
}