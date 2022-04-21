#include "glew.h"
#include "glut.h" 
#include <math.h>
#include "ObjLoader.h"

namespace Task_4_1
{
	ObjLoader* loader;

	// �������� �������� 
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	typedef GLfloat GLTVector3[3];
	// �������� ���������� �������
	void gltScaleVector(GLTVector3 vVector, const GLfloat
		fScale)
	{
		vVector[0] *= fScale; vVector[1] *= fScale;
		vVector[2] *= fScale;
	}
	// �������� ������� ����� �������
	GLfloat gltGetVectorLengthSqrd(const GLTVector3
		vVector)
	{
		return (vVector[0] * vVector[0]) +
			(vVector[1] * vVector[1]) + (vVector[2] * vVector[2]);
	}

	// �������� ����� �������
	GLfloat gltGetVectorLength(const GLTVector3 vVector)
	{
		return
			(GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
	}
	// ����������� ������ ��������� �����
	void gltNormalizeVector(GLTVector3 vNormal)
	{
		GLfloat fLength = 1.0f /
			gltGetVectorLength(vNormal);
		gltScaleVector(vNormal, fLength);
	}
	// ��������� ��������� ������������ ���� ��������
	void gltVectorCrossProduct(const GLTVector3 vU, const
		GLTVector3 vV, GLTVector3 vResult)
	{
		vResult[0] = vU[1] * vV[2] - vV[1] * vU[2];
		vResult[1] = -vU[0] * vV[2] + vV[0] * vU[2];
		vResult[2] = vU[0] * vV[1] - vV[0] * vU[1];
	}
	// ������� ���� ������ �� �������
	void gltSubtractVectors(const GLTVector3 vFirst,
		const GLTVector3 vSecond, GLTVector3 vResult)
	{
		vResult[0] = vFirst[0] - vSecond[0];
		vResult[1] = vFirst[1] - vSecond[1];
		vResult[2] = vFirst[2] - vSecond[2];
	}
	// ���� ��� ����� �� ��������� ���������� ������ ������� �������, ��������� // �������
	void gltGetNormalVector(const GLTVector3 vP1, const
		GLTVector3 vP2, const GLTVector3 vP3, GLTVector3
		vNormal)
	{
		GLTVector3 vV1, vV2;

		gltSubtractVectors(vP2, vP1, vV1);
		gltSubtractVectors(vP3, vP1, vV2);

		gltVectorCrossProduct(vV1, vV2, vNormal);
		gltNormalizeVector(vNormal);
	}
	// ���������� ��� ��������� ����� 
	void RenderScene(void)
	{
		GLTVector3 vNormal; // ������ ��� ���������� ������� � �����������
		// ������� ���� ������� ������ �������
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);
		// ���������� ��������� ������� � ��������� �������
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		// ������� ����� - ����� ����
		 // ��������������� ���� ���������
		glColor3ub(128, 0, 128);

		loader->Draw();

		// �������������� ��������� �������
		glPopMatrix();
		// ���������� ����������
		glutSwapBuffers();
	}
	// ��� ������� ��������� ����������� ������������� � ���������
	// ������������. 
	void SetupRC()
	{
		// ���������� 
		GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f,
	   1.0f };
		GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f,
	   1.0f };
		glEnable(GL_DEPTH_TEST);// ������� ������� ������������
		glFrontFace(GL_CCW);// �������������� � ������� ������ ������� �������
			// ���������� ������
		glEnable(GL_CULL_FACE);// ������ �������� ������� �� ������������
		// �������������� ���������
		glEnable(GL_LIGHTING);
		// ��������������� � �������������� �������� ����� 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glEnable(GL_LIGHT0);
		// ������������ ������������ ������
		glEnable(GL_COLOR_MATERIAL);
		// �������� ���������� ������������� ����� glColor
		glColorMaterial(GL_FRONT,
			GL_AMBIENT_AND_DIFFUSE);
		glClearColor(0.5f, 1.0f, 0.5f, 1.0f);

		loader = new ObjLoader("parallelepiped.obj");
	}
	/////////////////////////////////////////////////////
	// ���������� ���������
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

		if (xRot > 356.0f)
			xRot = 0.0f;
		if (xRot < -1.0f)
			xRot = 355.0f;
		if (yRot > 356.0f)
			yRot = 0.0f;
		if (yRot < -1.0f)
			yRot = 355.0f;
		// ���������� ����
		glutPostRedisplay();
	}
	/////////////////////////////////////////////////////
	/////
	// ����������� �������� � ��������� ��������� �����
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f
		};
		// ������������� ������� �� ����
		if (h == 0)
			h = 1;
		// ������ ���� ��������� ��������������� ������ ������� ���� glViewport(0, 0, w, h);
		// ����������� ������� ���������
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		fAspect = (GLfloat)w / (GLfloat)h;
		gluPerspective(45.0f, fAspect, 1.0f, 225.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glTranslatef(0.0f, 0.0f, -150.0f);
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
			GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Parallelepiped");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}