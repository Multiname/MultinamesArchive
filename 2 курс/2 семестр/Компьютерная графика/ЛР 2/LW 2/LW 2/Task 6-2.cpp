#include "glew.h"
#include "glut.h"
#include <cstddef>
#include <stdlib.h>

#include "misc.h"

namespace Task_6_2
{
	const int WINDOW_HEIGHT = 512;
	const int WINDOW_WIDTH = 512;
	GLint renderMode = 1;

	void SetupRC()
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
		GLubyte* pImage = NULL;
		GLint iWidth, iHeight, iComponents;
		GLenum eFormat;
		glClear(GL_COLOR_BUFFER_BIT);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		pImage = (GLubyte*)ConvertTgaToBitmap("Ruins.tga",
			&iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		if (pImage != NULL)
		{
			glDrawPixels(iWidth, iHeight * renderMode / 5, eFormat,
				GL_UNSIGNED_BYTE, pImage);
		}
		free(pImage);
		glutSwapBuffers();
	}

	void ProcessMenu(int value)
	{
		if (value == 0)
			WriteTga("result.tga");
		else
			renderMode = value;

		glutPostRedisplay();
	}


	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutCreateWindow("OpenGL Bitmaps");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("Save", 0);
		glutAddMenuEntry("100%", 5);
		glutAddMenuEntry("80%", 4);
		glutAddMenuEntry("60%", 3);
		glutAddMenuEntry("40%", 2);
		glutAddMenuEntry("20%", 1);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}