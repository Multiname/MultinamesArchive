#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
#include <math.h>
namespace Task_4_9_2
{
	// �������� �����
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// ���������� ��� ��������� �����
	void RenderScene(void)
	{
		GLfloat x, y, z, angle; // ����� �������� ��������� � �����
		GLfloat sizes[2]; //���������� �������� �������� �������������� �����
		GLfloat step; // ���������� �������������� ��������� �������� �����
		GLfloat curSize; // ���������� ������ ������� �����
		GLfloat minSize; // ���������� ����������� ������ �����
		GLfloat maxSize; // ���������� ������������ ������ �����
		GLfloat blueColor = 1.0f;
		GLfloat colorStep = 0.005f;
		// ������� ���� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT);
		// ������������ ��������� ������� � ����������� ��������
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		// �������� �������� �������� �������������� ����� � ������ ����
		glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
		glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
		// ������ �������� ������ �����
		curSize = sizes[0];
		minSize = sizes[0];
		maxSize = sizes[1];
		short multiplier = 3;
		// ������ ��������� ���������� z
		z = -75.0f;
		// ����������� ������ �� ���������� ��� ����
		for (angle = 0.0f; angle <= (2.0f * 3.1415f) * 5.0f; angle += 3.1415f * 0.1f)
		{
			// ������ �������� x � � ����� ����������
			x = 25.0f * sin(angle);
			y = 25.0f * cos(angle);
			// ������ ������ ����� ����� ��������� ���������
			glPointSize(curSize);
			glColor3f(1.0f, 0.0f, blueColor);
			// ������ �����
			glBegin(GL_POINTS);
			glVertex3f(x, y, z);
			glEnd();
			// ����������� �������� z � ������ �����
			z += 1.5f;
			if (curSize >= maxSize / 5)
				multiplier = -3;
			else if (curSize <= minSize)
				multiplier = 3;
			curSize += multiplier * step;

			blueColor -= colorStep;
		}
		// ��������������� ��������������
		glPopMatrix();
		// ������� ���� ������ ���������
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
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 2");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}