#include "glew.h"
#include "glut.h"

namespace Task_6_1
{
	GLubyte one[40] =
	{
		0xFF, 0xFF,
		0xFF, 0xFF,
		0xFF, 0xFF,
		0xFF, 0xFF,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0x03, 0xC0,
		0xFF, 0xFF,
		0xFF, 0xFF,
		0xFF, 0xFF,
		0xFF, 0xFF
	};

	GLubyte two[20] = {
		0xFF, 0xFF,
		0xFF, 0xFF,
		0x33, 0x00,
		0x33, 0x00,
		0x33, 0x00,
		0x33, 0x00,
		0x33, 0x00,
		0x33, 0x00,
		0xFF, 0xFF,
		0xFF, 0xFF
	};

	bool Positions[10][10]
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },
		{ 0, 1, 0, 1, 1, 1, 1, 0, 1, 0 },
		{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
	};

	void SetupRC()
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void ChangeSize(int w, int h)
	{
		if (h == 0)
			h = 1;
		glViewport(0, 0, w, h);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, (GLfloat)w, 0.0f, (GLfloat)h);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void RenderScene(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for (int y = 0; y < 10; y++)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			for (int x = 0; x < 10; x++)
			{
				if (Positions[9 - y][x])
				{
					glRasterPos2i(96 + 32 * x, 56 + 20 * (y + 10));
					glBitmap(16, 20, 0.0, 0.0, 0.0, 0.0, one);
					glBitmap(16, 20, -16.0, 0.0, 0.0, 0.0, one);
				}
			}
			glColor3f(1.0f, 0.0f, 1.0f);
			for (int x = 0; x < 10; x++)
			{
				if (Positions[y][x])
				{
					glRasterPos2i(96 + 32 * x, 56 + 20 * y);
					glBitmap(10, 10, 0.0, 0.0, 0.0, 0.0, two);
					glBitmap(10, 10, -11.0, 0.0, 0.0, 0.0, two);
					glBitmap(10, 10, -22.0, 0.0, 0.0, 0.0, two);
					glBitmap(10, 10, 0.0, -10.0, 0.0, 0.0, two);
					glBitmap(10, 10, -11.0, -10.0, 0.0, 0.0, two);
					glBitmap(10, 10, -22.0, -10.0, 0.0, 0.0, two);
				}
			}
		}

		glutSwapBuffers();
	}

	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(512, 512);
		glutCreateWindow("OpenGL Bitmaps");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);

		SetupRC();
		glutMainLoop();
		return 0;
	}
}