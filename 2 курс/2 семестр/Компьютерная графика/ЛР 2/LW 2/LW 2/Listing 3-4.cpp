#include "glew.h"
#include "glut.h"
#include <math.h>

namespace Listing_3_4
{
	// ��������� ���������
	GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	// ���������� ��� ��������� �����
	void RenderScene(void)
	{
		// ���� �������� ������� �����/����
		static float fMoonRot = 0.0f;
		static float fEarthRot = 0.0f;
		static float fSatelliteRot = 0.0f;
		// ������� ���� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);
		// Save the matrix state and do the rotations
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		// ����������� ��� ����� � ���� ������
		glTranslatef(0.0f, 0.0f, -300.0f);
		// ������������� ���� ��������� �������
		// ������
		glDisable(GL_LIGHTING);
		glColor3ub(255, 255, 0);
		glutSolidSphere(15.0f, 30, 17);
		glEnable(GL_LIGHTING);
		// �������� ��������� �����, ����� ���������� ������!
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		// ������� ������� ���������
		glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
		// ���������� �����
		glColor3ub(0, 0, 255);
		glTranslatef(105.0f, 0.0f, 0.0f);
		glutSolidSphere(15.0f, 30, 17);
		
		glPushMatrix();

		// ������� � ������� ���������, ��������� � ������
			// � ����������� ����
		glColor3ub(200, 200, 200);
		glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
		glTranslatef(30.0f, 0.0f, 0.0f);
		fMoonRot += 3.0f;
		if (fMoonRot > 360.0f)
			fMoonRot -= 360.0f;
		glutSolidSphere(6.0f, 30, 17);

		glPopMatrix();

		glColor3ub(225, 150, 100);
		glRotatef(fSatelliteRot, 0.0f, 1.0f, 0.0f);
		glTranslatef(45.0f, 0.0f, 0.0f);
		fSatelliteRot -= 5.0f;
		if (fSatelliteRot < 0.0f)
			fSatelliteRot += 360.0f;
		glutSolidSphere(4.0f, 30, 17);

		// ����������������� ��������� �������
		glPopMatrix(); // ������� ���������� ������
		// ��� �� ������ ����� ����� ���� ��������
		fEarthRot += 1.0f;
		if (fEarthRot > 360.0f)
			fEarthRot = 0.0f;
		// ������������ ����������� �����������
		glutSwapBuffers();
	}
	// ������� ��������� ��� ����������� ������������� � ���������
	//������������
	void SetupRC()
	{
		// ��������� ����� � ����������
		glEnable(GL_DEPTH_TEST); // �������� ������� ������������
		glFrontFace(GL_CCW); //�������������� � ������� ������
		//������� ������� ���������� ������
		glEnable(GL_CULL_FACE); //������� ������ �������� �� �����������
		// ��������� ���������
		glEnable(GL_LIGHTING);
		// ��������������� � �������������� �������� ����� 0
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);
		// ������������ ������������ ������
		glEnable(GL_COLOR_MATERIAL);
		// �������� ���������� ������������� ����� glColor
		glColorMaterial(GL_FRONT,
			GL_AMBIENT_AND_DIFFUSE);
		// �����-����� ���
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	void TimerFunc(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(10, TimerFunc, 1);
	}
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		// ������������� ������� �� ����
		if (h == 0)
			h = 1;
		// ������ ���� ��������� ��������������� ������ ������� ����
		glViewport(0, 0, w, h);
		// ������ ����������� ������ ����
		fAspect = (GLfloat)w / (GLfloat)h;
		// ������������� ������������� ������� ���������
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ���� ������ ����� 45 ��������, ������� � ������� ���������
			// �������� ����� 1 � 425
		gluPerspective(45.0f, fAspect, 1.0, 425.0);
		// ��������� ������� ���������� ������
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
			GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Earth/Moon/Sun System");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		glutTimerFunc(250, TimerFunc, 1);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}