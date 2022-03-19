#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
namespace Listing_3
{
	// �������� �����
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// ���������� ��� ��������� �����
	void RenderScene(void)
	{
		// ���������� ���� ��� ��� ���� ���������� ����� 
		GLfloat x, y, z, angle; // ����� �������� ���������� � ����
		GLfloat fSizes[2]; // ������� ��������� ������ �����
		GLfloat fCurrSize; // ������ �������� ���������
		GLfloat blueColor = 1.0f;
		GLfloat colorStep = 0.04f;
		GLint factor = 1; // ��������� ������� 
		GLushort pattern = 0xFF00; // ������ �������
		GLushort patternStep = 1;
		// ������� ���� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes);
		fCurrSize = fSizes[0];
		// �������������� ������� 
		glEnable(GL_LINE_STIPPLE);
		// ��������� ������ ��� � �� 20 ������ �� ���
		for (y = -90.0f; y < 90.0f; y += 10.0f)
		{
			// �������� ������ ����� 
			glLineWidth(fCurrSize);
			glColor3f(1.0f, 0.0f, blueColor);
			// ����������� ��������� ������� � ������ 
			glLineStipple(factor, pattern);
			// �������� ����� 
			glBegin(GL_LINES);
			glVertex2f(-80.0f, y);
			glVertex2f(80.0f, y);
			glEnd();
			// ������������� ������ �����
			fCurrSize += 0.5f;
			pattern += patternStep;
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
		// ������������� ����� ��������� � ������� ���������� 
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
		glutCreateWindow("Listing 3");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}