#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "glew.h"
#include "glut.h"
#include <stdio.h>
#include <stdlib.h>

#define GLT_PI 3.14159265358979323846

typedef struct
{
	char identSize;
	char colorMapType;
	char imageType;
	short int colorMapStart;
	short int colorMapLength;
	char colorMapBits;
	char xStart;
	char yStart;
	short width;
	short height;
	char bits;
	char descriptor;
} TGA_HEADER;

typedef GLint GLTVector4i[4];
typedef GLint GLTVector2i[2];

typedef GLfloat GLTMatrix[16];

GLbyte* ConvertTgaToBitmap(const char* fileName, GLint
	* width, GLint* height, GLint* components,
	GLenum* format);

GLint WriteTga(const char* szFileName);