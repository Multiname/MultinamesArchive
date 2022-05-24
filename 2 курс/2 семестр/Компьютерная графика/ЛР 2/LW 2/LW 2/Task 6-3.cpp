#include "glew.h"
#include "glut.h"
#include <cstddef>
#include <stdlib.h>

#include "misc.h"

namespace Task_6_3
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
		pImage = (GLubyte*)ConvertTgaToBitmap("Park.tga",
			&iWidth, &iHeight, &iComponents, &eFormat);
		glRasterPos2i(0, 0);
		glPixelTransferf(GL_RED_SCALE, 1.0f);
		glPixelTransferf(GL_GREEN_SCALE, 1.0f);
		glPixelTransferf(GL_BLUE_SCALE, 1.0f);
		if (pImage != NULL)
		{
			GLbyte* pModifiedBytes;
			glDrawPixels(iWidth, iHeight, eFormat,
				GL_UNSIGNED_BYTE, pImage);
			switch (renderMode)
			{
			case 2:
				pModifiedBytes = (GLbyte*)malloc(iWidth *
					iHeight);
				glPixelTransferf(GL_RED_SCALE, 0.3f);
				glPixelTransferf(GL_GREEN_SCALE, 0.59f);
				glPixelTransferf(GL_BLUE_SCALE, 0.11f);
				glReadPixels(0, 0, iWidth, iHeight, GL_LUMINANCE,
					GL_UNSIGNED_BYTE, pModifiedBytes);
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 1.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
				glDrawPixels(iWidth, iHeight, GL_LUMINANCE,
					GL_UNSIGNED_BYTE, pModifiedBytes);
				break;
			case 3:
				pModifiedBytes = (GLbyte*)malloc(iWidth *
					iHeight);
				glPixelTransferf(GL_RED_SCALE, 0.33f);
				glPixelTransferf(GL_GREEN_SCALE, 0.34f);
				glPixelTransferf(GL_BLUE_SCALE, 0.33f);
				glReadPixels(0, 0, iWidth, iHeight, GL_LUMINANCE,
					GL_UNSIGNED_BYTE, pModifiedBytes);
				glPixelTransferf(GL_RED_SCALE, 1.0f);
				glPixelTransferf(GL_GREEN_SCALE, 1.0f);
				glPixelTransferf(GL_BLUE_SCALE, 1.0f);
				glDrawPixels(iWidth, iHeight, GL_LUMINANCE,
					GL_UNSIGNED_BYTE, pModifiedBytes);
				break;
			case 4:
				pModifiedBytes = (GLbyte*)malloc(iWidth *
					iHeight);
				glReadPixels(0, 0, iWidth, iHeight, GL_LUMINANCE,
					GL_UNSIGNED_BYTE, pModifiedBytes);
				glDrawPixels(iWidth, iHeight, GL_LUMINANCE,
					GL_UNSIGNED_BYTE, pModifiedBytes);
				break;
			}

			free(pImage);
		}

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
		glutCreateWindow("Black and white");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		glutCreateMenu(ProcessMenu);
		glutAddMenuEntry("Save", 0);
		glutAddMenuEntry("Full color", 1);
		glutAddMenuEntry("NTSC", 2);
		glutAddMenuEntry("Thirds", 3);
		glutAddMenuEntry("Without pixel transfer", 4);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}

int main(int argc, char* argv[]) { return Task_6_3::main(argc, argv); }