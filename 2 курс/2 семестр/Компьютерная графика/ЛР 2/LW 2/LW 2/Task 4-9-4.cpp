#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
#include <math.h>
namespace Task_4_9_4
{
	// ������������ ��������� �� ��������� ���
#define GL_PI 3.1415f
// �������� �����
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	bool isPointsVisible = true;
	bool isLinesVisible = true;
	// ���������� ��� ��������� �����
	void RenderScene(void)
	{
		GLfloat x, y, angle; // ����� �������� ���������� � ����
		// ���� ��������� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT);
		// ���������� ��������� ������� � ��������� �������
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		if (isLinesVisible)
		{
			glBegin(GL_LINE_STRIP);
			for (angle = 0.0f; angle <= 2.0f * GL_PI; angle += GL_PI * 0.1f)
			{
				x = 25.0f * (-GL_PI + angle);
				y = 25.0f * sin(angle);
				// ������ ����� � ������� ������� �������� z
				glVertex2f(x, y);
			}
			glEnd();
		}
		if (isPointsVisible)
		{
			glPointSize(5.0f);
			// �������� ���� ��� ��� ���� ���������� �����
			glBegin(GL_POINTS);
			for (angle = 0.0f; angle <= 2.0f * GL_PI; angle += GL_PI * 0.1f)
			{
				x = 25.0f * (-GL_PI + angle);
				y = 25.0f * sin(angle);
				// ������ ����� � ������� ������� �������� z
				glVertex2f(x, y);
			}
			// ������ �����
			glEnd();
		}
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
		// ���� ��������� ���������� ����������
		glColor3f(1.0f, 0.0f, 1.0f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_POINT_SMOOTH);     // ����������� �����
		glEnable(GL_LINE_SMOOTH);     // ����������� �����
		glEnable(GL_POLYGON_SMOOTH); // ����������� ����� ���������������
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
	void processMenuEvents(int option) {

		switch (option) {
		case 1:
			isLinesVisible = !isLinesVisible;
			break;
		case 2:
			isPointsVisible = !isPointsVisible;
			break;
		}

		RenderScene();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 4");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();

		glutCreateMenu(processMenuEvents);
		//�������� ������ � ����� ����
		glutAddMenuEntry("Change lines visibility", 1);
		glutAddMenuEntry("Change points visibility", 2);
		// ���������� ���� ������ ������
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();
		return 0;
	}
}