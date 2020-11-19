/* Klasa Ładująca textury z plików. Źródło: Kurs "Grafika komputerowa" Doktora Grzegorza Łukawskiego na platformie Moodle. */
#ifndef Targa_h
#define Targa_h

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>

typedef struct {
	GLuint bpp;		// ilość bitów na piksel
	GLuint width;	// rozmiary w pikselach
	GLuint height;
} TARGAINFO;

// Funkcje
GLubyte* LoadTGAImage(char* filename, TARGAINFO* info);
bool LoadTGATexture(char* filename);
bool LoadTGAMipmap(char* filename);

#endif