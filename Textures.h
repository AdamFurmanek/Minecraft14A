#ifndef Textures_h
#define Textures_h

#include "Targa.h"
#include "Map.h"

class Textures
{
private:
	static Map* map;
	GLuint TextureID[14];
	int viewDistance;
public:
	Textures(Map* map, float viewDistance = 30);
	void TexturesDisplay(float x, float y, float z);
	int getViewDistance() {
		return viewDistance;
	}
};

#endif
