#ifndef Textures_h
#define Textures_h

#include "Targa.h"
#include "Map.h"

class Textures
{
private:
	static Map* map;
	GLuint TextureID[14];
public:
	void TexturesDisplay(float x, float y, float z);
	Textures(Map* map);
};

#endif
