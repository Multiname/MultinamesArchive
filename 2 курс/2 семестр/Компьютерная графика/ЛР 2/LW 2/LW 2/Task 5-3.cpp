#include "glew.h"
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace Task_5_3
{
#pragma warning(disable : 4996)

	// Rotation amounts
	static GLfloat zPos = -60.0f;
	// Texture objects
#define TEXTURE_BRICK 0
#define TEXTURE_FLOOR 1
#define TEXTURE_CEILING 2
#define TEXTURE_COUNT 3
	GLuint textures[TEXTURE_COUNT];
	const char* szTextureFiles[TEXTURE_COUNT] = { "brick.tga", "floor.tga", "ceiling.tga" };
	// Define targa header.
#pragma pack(1)
	typedef struct
	{
		GLbyte identsize; // Size of ID field that follows header(0)
		GLbyte colorMapType; // 0 = None, 1 = paletted
		GLbyte imageType; // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8 = rle
		unsigned short colorMapStart; // First colour map entry
		unsigned short colorMapLength; // Number of colors
		unsigned char colorMapBits; // bits per palette entry
		unsigned short xstart; // image x origin
		unsigned short ystart; // image y origin
		unsigned short width; // width in pixels
		unsigned short height; // height in pixels
		GLbyte bits; // bits per pixel (8 16, 24, 32)
		GLbyte descriptor; // image descriptor
	} TGAHEADER;
#pragma pack(8)
	/////////////////////////////////////////////////////
	///////////////
	// Allocate memory and load targa bits. Returns pointer to new buffer,
	// height, and width of texture, and the OpenGL format of data.
	// Call free() on buffer when finished!
	// This only works on pretty vanilla targas... 8, 24, or 32 bit color
	// only, no palettes, no RLE encoding.
	GLbyte* gltLoadTGA(const char* szFileName, GLint
		* iWidth, GLint* iHeight, GLint* iComponents, GLenum
		* eFormat)
	{
		FILE* pFile; // File pointer
		TGAHEADER tgaHeader; // TGA file header
		unsigned long lImageSize; // Size in bytes of image
		short sDepth; // Pixel depth;
		GLbyte* pBits = NULL; // Pointer to bits

			// Default/Failed values
		*iWidth = 0;
		*iHeight = 0;
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;

		// Attempt to open the fil
		pFile = fopen(szFileName, "rb");
		if (pFile == NULL)
			return NULL;

		// Read in header (binary)
		fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1,
			pFile);

		// Do byte swap for big vs little endian
#ifdef __APPLE__
		BYTE_SWAP(tgaHeader.colorMapStart);
		BYTE_SWAP(tgaHeader.colorMapLength);
		BYTE_SWAP(tgaHeader.xstart);
		BYTE_SWAP(tgaHeader.ystart);
		BYTE_SWAP(tgaHeader.width);
		BYTE_SWAP(tgaHeader.height);
#endif

		// Get width, height, and depth of texture
		* iWidth = tgaHeader.width;
		*iHeight = tgaHeader.height;
		sDepth = tgaHeader.bits / 8;

		// Put some validity checks here. Very simply, I only understand
			// or care about 8, 24, or 32 bit targa's.
		if (tgaHeader.bits != 8 && tgaHeader.bits != 24 &&
			tgaHeader.bits != 32)
			return NULL;
		// Calculate size of image buffer
		lImageSize = tgaHeader.width * tgaHeader.height *
			sDepth;

		// Allocate memory and check for success
		pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
		if (pBits == NULL)
			return NULL;

		// Read in the bits
		// Check for read error. This should catch RLE or other
			// weird formats that I don't want to recognize
		if (fread(pBits, lImageSize, 1, pFile) != 1)
		{
			free(pBits);
			return NULL;
		}

		// Set OpenGL format expected
		switch (sDepth)
		{
		case 3: // Most likely case
			*eFormat = GL_BGR_EXT;
			*iComponents = GL_RGB8;
			break;
		case 4:
			*eFormat = GL_BGRA_EXT;
			*iComponents = GL_RGBA8;
			break;
		case 1:
			*eFormat = GL_LUMINANCE;
			*iComponents = GL_LUMINANCE8;
			break;
		};


		// Done with File
		fclose(pFile);
		// Return pointer to image data
		return pBits;
	}
	/////////////////////////////////////////////////////
	//////////////////////////
	// Change texture filter for each texture object
	void ProcessMenu(int value)
	{
		GLint iLoop;

		for (iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
		{
			glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

			switch (value)
			{
			case 0:
				glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				break;

			case 1:
				glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				break;

			case 2:
				glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				break;

			case 3:
				glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
				break;

			case 4:
				glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				break;

			case 5:
			default:
				glTexParameteri(GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				break;
			}
		}

		// Trigger Redraw
		glutPostRedisplay();
	}
	/////////////////////////////////////////////////////
	/////////////
	// This function does any needed initialization on the rendering
	// context. Here it sets up and initializes the texture objects.
	void SetupRC()
	{
		GLubyte* pBytes;
		GLint iWidth, iHeight, iComponents;
		GLenum eFormat;
		GLint iLoop;

		// Black background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Textures applied as decals, no lighting or coloring effects
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			GL_DECAL);
		// Load textures
		glGenTextures(TEXTURE_COUNT, textures);
		for (iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
		{
			// Bind to next texture object
			glBindTexture(GL_TEXTURE_2D, textures[iLoop]);
			// Load texture, set filter and wrap modes
			pBytes = (GLubyte*)gltLoadTGA(szTextureFiles[iLoop], &iWidth,
				&iHeight, &iComponents, &eFormat);
			gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents,
				iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
			glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			// Don't need original texture data any more
			free(pBytes);
		}
	}
	///////////////////////////////////////////////////
	// Shutdown the rendering context. Just deletes the
	// texture objects
	void ShutdownRC(void)
	{
		glDeleteTextures(TEXTURE_COUNT, textures);
	}

	///////////////////////////////////////////////////
	// Respond to arrow keys, move the viewpoint back
	// and forth
	void SpecialKeys(int key, int x, int y)
	{
		if (key == GLUT_KEY_UP)
			zPos += 1.0f;
		if (key == GLUT_KEY_DOWN)
			zPos -= 1.0f;
		// Refresh the Window
		glutPostRedisplay();
	}
	/////////////////////////////////////////////////////
	////////////////
	// Change viewing volume and viewport. Called when window is resized
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		// Prevent a divide by zero
		if (h == 0)
			h = 1;
		// Set Viewport to window dimensions
		glViewport(0, 0, w, h);
		fAspect = (GLfloat)w / (GLfloat)h;
		// Reset coordinate system
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Produce the perspective projection
		gluPerspective(90.0f, fAspect, 1, 120);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	/////////////////////////////////////////////////////
	//
	// Called to draw scene
	void RenderScene(void)
	{
		GLfloat z;

		// Clear the window with current clearing color
		glClear(GL_COLOR_BUFFER_BIT);
		// Save the matrix state and do the rotations
		glPushMatrix();
		// Move object back and do in place rotation
		glTranslatef(0.0f, 0.0f, zPos);

		for (z = 60.0f; z >= 0.0f; z -= 10)
		{
			// Floor
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FLOOR]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-10.0f, -10.0f, z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(10.0f, -10.0f, z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(10.0f, -10.0f, z -
				10.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-10.0f, -10.0f, z -
				10.0f);
			glEnd();
			// Ceiling
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_CEILING]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-10.0f, 10.0f, z -
				10.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(10.0f, 10.0f, z - 10.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(10.0f, 10.0f, z);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-10.0f, 10.0f, z);
			glEnd();
			// Upper Left Wall
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-20.0f, 0.0f, z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-20.0f, 0.0f, z - 10.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-10.0f, 10.0f, z - 10.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-10.0f, 10.0f, z);
			glEnd();
			// Bottom Left Wall
			glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BRICK]);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-10.0f, -10.0f, z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-10.0f, -10.0f, z - 10.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-20.0f, 0.0f, z - 10.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-20.0f, 0.0f, z);
			glEnd();
			// Upper Right Wall
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(10.0f, 10.0f, z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(10.0f, 10.0f, z - 10.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(20.0f, 0.0f, z - 10.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(20.0f, 0.0f, z);
			glEnd();
			// Bottom Right Wall
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(20.0f, 0.0f, z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(20.0f, 0.0f, z - 10.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(10.0f, -10.0f, z - 10.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(10.0f, -10.0f, z);
			glEnd();
		}
		// Restore the matrix state
		glPopMatrix();
		// Buffer swap
		glutSwapBuffers();
	}
	/////////////////////////////////////////////////////
	// Program entry point
	int main(int argc, char* argv[])
	{
		// Standard initialization stuff
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Tunnel");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);

		// Add menu entries to change filter
		glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("GL_NEAREST", 0);
		glutAddMenuEntry("GL_LINEAR", 1);
		glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST", 2);
		glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", 3);
		glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", 4);
		glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", 5);
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		// Startup, loop, shutdown
		SetupRC();
		glutMainLoop();
		ShutdownRC();

		return 0;
	}
}