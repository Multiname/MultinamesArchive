#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
namespace Listing_9
{
	// ������������ ��������� �� ��������� ���
#define GL_PI 3.1415f
// �������� �����
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	bool depthCheck = false;
	bool culling = false;
	bool showBottom = true;
	// ���������� ��� ��������� �����
	void RenderScene(void)
	{
		GLfloat x, y, z, angle; // ����� �������� ���������� � ����
			// ���� ��������� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ���������� ��������� ������� � ��������� �������
		glPushMatrix();

		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		if (showBottom)
		{
			glBegin(GL_TRIANGLE_STRIP);

			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex2f(40.0f, 40.0f);

			glVertex2f(40.0f, -40.0f);

			glVertex2f(-40.0f, 40.0f);

			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex2f(-40.0f, -40.0f);

			glEnd();
		}

		glBegin(GL_TRIANGLE_FAN);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 40.0f);

		glVertex2f(40.0f, -40.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(40.0f, 40.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-40.0f, 40.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-40.0f, -40.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(40.0f, -40.0f);

		glEnd();

		// ��������������� ��������������
		glPopMatrix();
		// ������� ���� ������ ��������������
		glutSwapBuffers();
	}
	// ������� ��������� ����������� ������������� 
	// � ��������� ������������ 
	void SetupRC()
	{
		// ������ ���
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void SpecialKeys(int key, int x, int y)
	{
		if (key == GLUT_KEY_UP)
			xRot -= 5.0f;
		if (key == GLUT_KEY_DOWN)
			xRot += 5.0f;
		if (key == GLUT_KEY_LEFT)
			yRot -= 5.0f;
		if (key == GLUT_KEY_RIGHT)
			yRot += 5.0f;
		if (key > 356.0f)
			xRot = 0.0f;
		if (key < -1.0f)
			xRot = 355.0f;
		if (key > 356.0f)
			yRot = 0.0f;
		if (key < -1.0f)
			yRot = 355.0f;
		// ��������� ����
		glutPostRedisplay();
	}
	void ChangeSize(int w, int h)
	{
		GLfloat nRange = 100.0f;
		// ������������� ������� �� ����
		if (h == 0)
			h = 1;
		// ������������� ������� ���� ��������� ������� �������� ����
		glViewport(0, 0, w, h);
		// ������������� ������������� ������� ���������
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������������� ����� ��������� � ������� ���������� 
		// ���������� (�����, ������, ������, �������, �������, �������)
		if (w <= h)
			glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
		else
			glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
		// ����������� ���� ������ �������� ������
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	void processMenuEvents(int option)
	{
		switch (option) {
		case 1:
			if (depthCheck)
				glDisable(GL_DEPTH_TEST);
			else
				glEnable(GL_DEPTH_TEST);
			depthCheck = !depthCheck;
			break;
		case 2:
			if (culling)
				glDisable(GL_CULL_FACE);
			else
				glEnable(GL_CULL_FACE);
			culling = !culling;
			break;
		case 3:
			showBottom = !showBottom;
			break;
		}

		RenderScene();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 9");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();

		glutCreateMenu(processMenuEvents);
		//�������� ������ � ����� ����
		glutAddMenuEntry("Change depth checking mode", 1);
		glutAddMenuEntry("Change culling mode", 2);
		glutAddMenuEntry("Change bottom visibility", 3);
		// ���������� ���� ������ ������
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();
		return 0;
	}
}
int main(int argc, char* argv[])
{
	Listing_9::main(argc, argv);
	return 0;
}