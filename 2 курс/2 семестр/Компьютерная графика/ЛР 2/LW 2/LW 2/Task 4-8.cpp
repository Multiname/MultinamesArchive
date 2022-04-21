#include "glew.h"
#include "glut.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

namespace Task_4_8
{
#define GLT_PI 3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229
	// ������ � ����� � ���������
	GLfloat fLightPos[4] = { -100.0f, 100.0f, 50.0f,
	1.0f }; // Point source
	GLfloat fLightPosMirror[4] = { -100.0f, -100.0f,
	50.0f, 1.0f };
	GLfloat fNoLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat fLowLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat fBrightLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat redLight[] = { 1.0f, 0.25f, 0.25f, 1.0f };
	static GLfloat yRot = 0.0f;//���� ��������, ��������������� � ��������
	typedef GLfloat GLTVector3[3]; // ��������������� ������ � ��������� �������
		// ��� ���������� ��������� �����������, �������� ��� � ������ �����������
		// ������ ��� (������) ��� z = fZVal... � ��������� XY
		// ��������� ��������������� �������

	typedef struct { // ����� ��� ���������� ������
		float x;
		float y;
		float z;
	} Position;
	Position spheres[50];

	bool greyColorEnabled = true;

	void gltScaleVector(GLTVector3 vVector, const GLfloat
		fScale)
	{
		vVector[0] *= fScale; vVector[1] *= fScale;
		vVector[2] *= fScale;
	}
	// ���������� ����� ������� � ��������
	GLfloat gltGetVectorLengthSqrd(const GLTVector3
		vVector)
	{
		return (vVector[0] * vVector[0]) +
			(vVector[1] * vVector[1]) + (vVector[2] * vVector[2]);
	}
	// ���������� ����� ������� 
	GLfloat gltGetVectorLength(const GLTVector3 vVector)
	{
		return
			(GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
	}
	// ��������������� ������� �� ����� - �������� ����������� ������� 
	void gltNormalizeVector(GLTVector3 vNormal)
	{
		GLfloat fLength = 1.0f /
			gltGetVectorLength(vNormal);
		gltScaleVector(vNormal, fLength);
	}
	void gltDrawTorus(GLfloat majorRadius, GLfloat
		minorRadius, GLint numMajor, GLint numMinor)
	{
		GLTVector3 vNormal;
		double majorStep = 2.0f * GLT_PI / numMajor;
		double minorStep = 2.0f * GLT_PI / numMinor;
		int i, j;
		for (i = 0; i < numMajor; ++i)
		{
			double a0 = i * majorStep;
			double a1 = a0 + majorStep;
			GLfloat x0 = (GLfloat)cos(a0);
			GLfloat y0 = (GLfloat)sin(a0);
			GLfloat x1 = (GLfloat)cos(a1);
			GLfloat y1 = (GLfloat)sin(a1);
			glBegin(GL_TRIANGLE_STRIP);
			for (j = 0; j <= numMinor; ++j)
			{
				double b = j * minorStep;
				GLfloat c = (GLfloat)cos(b);
				GLfloat r = minorRadius * c +
					majorRadius;
				GLfloat z = minorRadius *
					(GLfloat)sin(b);
				// ������ �����
				glTexCoord2f((float)(i) / (float)(numMajor),
					(float)(j) / (float)(numMinor));
				vNormal[0] = x0 * c;
				vNormal[1] = y0 * c;
				vNormal[2] = z / minorRadius;
				gltNormalizeVector(vNormal);
				glNormal3fv(vNormal);
				glVertex3f(x0 * r, y0 * r, z);

				glTexCoord2f((float)(i + 1) / (float)(numMajor),
					(float)(j) / (float)(numMinor));
				vNormal[0] = x1 * c;
				vNormal[1] = y1 * c;
				vNormal[2] = z / minorRadius;
				glNormal3fv(vNormal);
				glVertex3f(x1 * r, y1 * r, z);
			}
			glEnd();
		}
	}

	/////////////////////////////////////////////////////
	/////////////
	// ��� ������� ��������� ����������� ������������� � ���������
		// ������������ 
	void SetupRC()
	{
		// ����� ���
		glClearColor(fLowLight[0], fLowLight[1],
			fLowLight[2], fLowLight[3]);

		// ������ ����� ��������������� �������������
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// ��������������� ��������� ��������� �����: 
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fNoLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, fLowLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, fBrightLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, fBrightLight);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		// ��������������� ������������ ������������ ������� ��������� glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,
			GL_AMBIENT_AND_DIFFUSE);
		glMateriali(GL_FRONT, GL_SHININESS, 128);

		for (int i = 0; i < 50; i++)
		{
			spheres[i].x = (float)((rand() % 400) - 200) * 0.1f;
			spheres[i].y = 1.0f;
			spheres[i].z = (float)((rand() % 400) - 200) * 0.1f;
		}

		// ��������� ���������� ������
		glEnable(GL_FOG); // ���������� �����
		glFogfv(GL_FOG_COLOR, fLowLight);
		// ���� ������ ������������� ����
		glFogf(GL_FOG_START, 1.0f); // ��������� ������
		// ���������� �����
		glFogf(GL_FOG_END, 25.0f); // ��������� ������
		// ������������� �����
		glFogf(GL_FOG_DENSITY, 0.1f);
		glFogi(GL_FOG_MODE, GL_LINEAR); // ����� ���������
			// ������ ������������
	}
	/////////////////////////////////////////////////////
	//////
	// ������ ����� ��� ������� �������������. ������ ��������� � ������� ������ // ����������� ���, ��� �� � �������� ����� ������� ����� - ����� ���������
		// �����.
	void DrawGround(void)
	{
		GLfloat fExtent = 20.0f;
		GLfloat fStep = 0.5f;
		GLfloat y = 0.0f;
		GLfloat fColor;
		GLfloat iStrip, iRun;
		GLint iBounce = 0;

		glShadeModel(GL_FLAT);
		for (iStrip = -fExtent; iStrip <= fExtent; iStrip
			+= fStep)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for (iRun = fExtent; iRun >= -fExtent;
				iRun -= fStep)
			{
				if ((iBounce % 2) == 0)
					fColor = 1.0f;
				else
					fColor = 0.0f;
				glColor4f(fColor, fColor, fColor,
					0.5f);
				glVertex3f(iStrip, y, iRun);
				glVertex3f(iStrip + fStep, y, iRun);
				iBounce++;
			}
			glEnd();
		}
		glShadeModel(GL_SMOOTH);
	}
	/////////////////////////////////////////////////////
	//////////////////
	// ������ ��������� ���������� � ����������� ��� / �����
	void DrawWorld(void)
	{
		glColor3f(1.0f, 0.0f, 0.0f);

		for (int i = 0; i < 50; i++)
		{
			glPushMatrix();
			glTranslatef(spheres[i].x, spheres[i].y, spheres[i].z);
			glutSolidSphere(0.1f, 13, 26);
			glPopMatrix();
		}

		glPushMatrix();
		glTranslatef(0.0f, 1.3f, -3.5f);

		glPushMatrix();
		glRotatef(-yRot * 2.0f, 0.0f, 1.0f, 0.0f);
		glTranslatef(1.0f, 0.0f, 0.0f);
		glutSolidSphere(0.1f, 13, 26);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-yRot * 2.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 1.0f, 0.0f);
		glutSolidSphere(0.1f, 13, 26);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-yRot * 2.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-1.0f, 0.0f, 0.0f);
		glutSolidSphere(0.1f, 13, 26);
		glPopMatrix();

		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		gltDrawTorus(0.35, 0.15, 61, 37);

		glPopMatrix();
	}
	/////////////////////////////////////////////////////
	////////////////// 
	// ���������� ��� ��������� ����� 
	void RenderScene(void)
	{
		// ������� ���� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA);
		DrawGround();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
		DrawWorld();
		glPopMatrix();

		// ������������ �������
		glutSwapBuffers();
	}
	/////////////////////////////////////////////////////
	//////
	//���������� ����������� GLUT � �������� ��������� (���� �� ������ //������� � �� ������������) 
	void TimerFunction(int value)
	{
		yRot += 1.0f; // ���������� ������������ ��������

		// ����������� �����
		glutPostRedisplay();

		// ����� �������
		glutTimerFunc(10, TimerFunction, 1);
	}
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		// ������������� ������� �� ����, ����� ���� ������� ���������
			// (������ ������� ���� ������� ������). 
		if (h == 0)
			h = 1;
		glViewport(0, 0, w, h);
		fAspect = (GLfloat)w / (GLfloat)h;
		// ������� ��������� ����������� �����
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// ������������ ������������� ��������
		gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -3.0f, -4.0f);
	}

	void processMenuEvents(int option) {
		switch (option) {
		case 1:
			if (greyColorEnabled)
				glFogfv(GL_FOG_COLOR, redLight);
			else
				glFogfv(GL_FOG_COLOR, fLowLight);
			greyColorEnabled = !greyColorEnabled;
			break;
		case 2:
			glFogi(GL_FOG_MODE, GL_LINEAR);
			break;
		case 3:
			glFogi(GL_FOG_MODE, GL_EXP);
			break;
		case 4:
			glFogi(GL_FOG_MODE, GL_EXP2);
			break;
		}

		RenderScene();
	}

	/////////////////////////////////////////////////////
	////////
	// ����� ����� ���������
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
			GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("OpenGL Blending and Transparency");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		glutTimerFunc(50, TimerFunction, 1);

		glutCreateMenu(processMenuEvents);
		//�������� ������ � ����� ����
		glutAddMenuEntry("Switch color", 1);
		glutAddMenuEntry("Linear mode", 2);
		glutAddMenuEntry("Exp mode", 3);
		glutAddMenuEntry("Exp2 mode", 4);
		// ���������� ���� ������ ������
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		SetupRC();
		glutMainLoop();
		return 0;
	}
}