#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
namespace Listing_6
{
	// ������������ ��������� �� ��������� ���
#define GL_PI 3.1415f
// �������� �����
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// ���������� ��� ��������� �����
	void RenderScene(void)
	{
		GLfloat x, y, z, angle; // ����� �������� ���������� � ����
			// ���� ��������� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_CULL_FACE);

		// ���������� ��������� ������� � ��������� �������
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 40.0f);
		glVertex2f(30.0f, -20.0f);
		glVertex2f(-30.0f, -20.0f);
		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 60.0f);
		glVertex2f(30.0f, -20.0f);
		glVertex2f(0.0f, 40.0f);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 60.0f);
		glVertex2f(0.0f, 40.0f);
		glVertex2f(-30.0f, -20.0f);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 60.0f);
		glVertex2f(-30.0f, -20.0f);
		glVertex2f(30.0f, -20.0f);
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
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 6");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}