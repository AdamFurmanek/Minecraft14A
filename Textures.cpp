#include "Textures.h"

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

	// Włączenie tabel i zdefiniowanie buforów:
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cube_vert);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, cube_norm);

	// Wygenerowanie 14 identyfikatorów dla tekstur:
	glGenTextures(14, TextureID);
	// Aktywacja trzech tekstur i ³adowanie ich z plików TGA:
	glBindTexture(GL_TEXTURE_2D, TextureID[0]);
	LoadTGAMipmap(_strdup("nic"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[1]);
	LoadTGAMipmap(_strdup("Textures//bedrock.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[2]);
	LoadTGAMipmap(_strdup("Textures//stone.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[3]);
	LoadTGAMipmap(_strdup("Textures//dirt.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[4]);
	LoadTGAMipmap(_strdup("Textures//grass.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[5]);
	LoadTGAMipmap(_strdup("Textures//sand.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[6]);
	LoadTGAMipmap(_strdup("Textures//sandstone.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[7]);
	LoadTGAMipmap(_strdup("Textures//tree.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[8]);
	LoadTGAMipmap(_strdup("Textures//leaves.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[9]);
	LoadTGAMipmap(_strdup("Textures//obsidian.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[10]);
	LoadTGAMipmap(_strdup("Textures//smooth_stone.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[11]);
	LoadTGAMipmap(_strdup("Textures//stone_bricks.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[12]);
	LoadTGAMipmap(_strdup("Textures//purple_plate.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBindTexture(GL_TEXTURE_2D, TextureID[13]);
	LoadTGAMipmap(_strdup("Textures//red_plate.tga"));
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	// Przygotowanie szeœcianu:
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	// Tabela z punktami:
	glVertexPointer(3, GL_FLOAT, 0, cube_vert);
	// Tabela ze wspó³rzêdnymi tekstur (2 wspó³rzêdne):
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texc);
	// Face culling.
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	// Włączenie testu bufora głębokości.
	glEnable(GL_DEPTH_TEST);
}

void Textures::TexturesDisplay(float x, float y, float z) {
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	int x1, y1, z1;
	char v;
	for (x1 = x - viewDistance;x1 < x + viewDistance; x1++) {
		for (y1 = 0;y1 < map->getY();y1++) {
			for (z1 = z - viewDistance;z1 < z + viewDistance;z1++) {
				if (map->get(x1, y1, z1) > 0 && (v = map->getV(x1, y1, z1)) != 63) {
					glTranslatef(x1, y1, z1);
					glBindTexture(GL_TEXTURE_2D, TextureID[map->get(x1, y1, z1)]);

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

					glTranslatef(-x1, -y1, -z1);
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
	glScalef(0.05, 0.05, 0.05);
	glTranslatef(w*0.005, -h*0.005, -12);
		glBindTexture(GL_TEXTURE_2D, TextureID[id]);
		glDrawElements(GL_TRIANGLES, sizeof(wallZp), GL_UNSIGNED_BYTE, wallZp);

	glTranslatef(-w*0.005, h*0.005, 12);
	glScalef(20, 20, 20);
}