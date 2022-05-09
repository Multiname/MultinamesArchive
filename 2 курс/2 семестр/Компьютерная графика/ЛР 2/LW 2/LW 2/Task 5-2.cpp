#include "glew.h"
#include "glut.h"
#include <math.h>

namespace Task_5_2
{
	// Rotation angle
	static GLfloat yRot = 0.0f;

#define GLT_PI 3.14159265358979323846
	///////////////////////////////////////////////////////
	// Some data types
	typedef GLfloat GLTVector2[2]; // Two component floating point vector
	typedef GLfloat GLTVector3[3]; // Three component floating point vector
	typedef GLfloat GLTVector4[4]; // Four component floating point vector
	typedef GLfloat GLTMatrix[16]; // A column major 4x4 matrix of type GLfloat
	// Adds two vectors together
	void gltAddVectors(const GLTVector3 vFirst, const
		GLTVector3 vSecond, GLTVector3 vResult) {
		vResult[0] = vFirst[0] + vSecond[0];
		vResult[1] = vFirst[1] + vSecond[1];
		vResult[2] = vFirst[2] + vSecond[2];
	}
	// Subtract one vector from another
	void gltSubtractVectors(const GLTVector3 vFirst,
		const GLTVector3 vSecond, GLTVector3 vResult)
	{
		vResult[0] = vFirst[0] - vSecond[0];
		vResult[1] = vFirst[1] - vSecond[1];
		vResult[2] = vFirst[2] - vSecond[2];
	}
	// Scales a vector by a scalar
	void gltScaleVector(GLTVector3 vVector, const GLfloat fScale)
	{
		vVector[0] *= fScale; vVector[1] *= fScale; vVector[2] *= fScale;
	}
	// Gets the length of a vector squared
	GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector)
	{
		return (vVector[0] * vVector[0]) + (vVector[1] * vVector[1]) + (vVector[2] * vVector[2]);
	}

	// Gets the length of a vector
	GLfloat gltGetVectorLength(const GLTVector3 vVector)
	{
		return (GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
	}

	// Scales a vector by it's length - creates a unit vector
	void gltNormalizeVector(GLTVector3 vNormal)
	{
		GLfloat fLength = 1.0f / gltGetVectorLength(vNormal);
		gltScaleVector(vNormal, fLength);
	}
	// Transform a point by a 4x4 matrix
	void gltTransformPoint(const GLTVector3 vSrcVector,
		const GLTMatrix mMatrix, GLTVector3 vOut)
	{
		vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4]
			* vSrcVector[1] + mMatrix[8] * vSrcVector[2] + mMatrix[12];
		vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5]
			* vSrcVector[1] + mMatrix[9] * vSrcVector[2] + mMatrix[13];
		vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6]
			* vSrcVector[1] + mMatrix[10] * vSrcVector[2] + mMatrix[14];
	}
	// Rotates a vector using a 4x4 matrix. Translation column is ignored
	void gltRotateVector(const GLTVector3 vSrcVector,
		const GLTMatrix mMatrix, GLTVector3 vOut)
	{
		vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4]
			* vSrcVector[1] + mMatrix[8] * vSrcVector[2];
		vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5]
			* vSrcVector[1] + mMatrix[9] * vSrcVector[2];
		vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6]
			* vSrcVector[1] + mMatrix[10] * vSrcVector[2];
	}
	// Get the dot product between two vectors
	GLfloat gltVectorDotProduct(const GLTVector3 vU,
		const GLTVector3 vV)
	{
		return vU[0] * vV[0] + vU[1] * vV[1] + vU[2] * vV[2];
	}

	void toonDramCylinder(GLfloat radius, int edgeNum, GLTVector3 vLightDir)
	{
		GLTMatrix mModelViewMatrix;
		GLTVector3 vNormal, vTransformedNormal;
		double step = 2.0f * GLT_PI / edgeNum;

		// Get the modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewMatrix);

		// Normalize the light vector
		gltNormalizeVector(vLightDir);

		for (int i = 0; i < edgeNum; ++i)
		{
			GLfloat vx = cos((i + 0.5) * step);
			GLfloat vz = sin((i + 0.5) * step);
			GLfloat vy = 0.0f;
			GLTVector3 norm = { vx, vy, vz };

			GLfloat x0 =  radius * cos(i * step);
			GLfloat z0 = -radius * sin(i * step);
			GLfloat y0 = 2.0f;

			GLfloat x1 = radius * cos((i + 1) * step);
			GLfloat z1 = -radius * sin((i + 1) * step);
			GLfloat y1 = -2.0f;

			glBegin(GL_TRIANGLE_STRIP);
			glTexCoord1f(gltVectorDotProduct(vLightDir, norm));
			glVertex3f(x0, y0, z0);
			glVertex3f(x0, y1, z0);
			glVertex3f(x1, y0, z1);
			glVertex3f(x1, y1, z1);
			glEnd();
		}

		GLTVector3 n0 = { 0.0f, -1.0f, 0.0f };
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord1f(gltVectorDotProduct(vLightDir, n0));
		glVertex3f(0.0f, 2.0f, 0.0f);
		for (int i = 0; i < edgeNum + 1; ++i)
		{
			GLfloat x = radius * cos(i * step);
			GLfloat z = -radius * sin(i * step);
			GLfloat y = 2.0f;
			glVertex3f(x, y, z);
		}
		glEnd();

		GLTVector3 n1 = { 0.0f, 1.0f, 0.0f };
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord1f(gltVectorDotProduct(vLightDir, n1));
		glVertex3f(0.0f, -2.0f, 0.0f);
		for (int i = 0; i < edgeNum + 1; ++i)
		{
			GLfloat x = radius * cos(-i * step);
			GLfloat z = -radius * sin(-i * step);
			GLfloat y = -2.0f;
			glVertex3f(x, y, z);
		}
		glEnd();
	}

	// Draw a torus (doughnut), using the current 1D texture for light shading
	void toonDrawTorus(GLfloat majorRadius, GLfloat minorRadius,
		int numMajor, int numMinor, GLTVector3 vLightDir)
	{
		GLTMatrix mModelViewMatrix;
		GLTVector3 vNormal, vTransformedNormal;
		double majorStep = 2.0f * GLT_PI / numMajor;
		double minorStep = 2.0f * GLT_PI / numMinor;
		int i, j;

		// Get the modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, mModelViewMatrix);

		// Normalize the light vector
		gltNormalizeVector(vLightDir);

		// Draw torus as a series of triangle strips
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
				GLfloat r = minorRadius * c + majorRadius;
				GLfloat z = minorRadius * (GLfloat)sin(b);
				// First point
				vNormal[0] = x0 * c;
				vNormal[1] = y0 * c;
				vNormal[2] = z / minorRadius;
				gltNormalizeVector(vNormal);
				gltRotateVector(vNormal, mModelViewMatrix, vTransformedNormal);

				// Texture coordinate is set by intensity of light
				glTexCoord1f(gltVectorDotProduct(vLightDir, vTransformedNormal));
				glVertex3f(x0 * r, y0 * r, z);
				// Second point
				vNormal[0] = x1 * c;
				vNormal[1] = y1 * c;
				vNormal[2] = z / minorRadius;
				gltNormalizeVector(vNormal);
				gltRotateVector(vNormal, mModelViewMatrix, vTransformedNormal);

				// Texture coordinate is set by intensity of light
				glTexCoord1f(gltVectorDotProduct(vLightDir, vTransformedNormal));
				glVertex3f(x1 * r, y1 * r, z);
			}
			glEnd();
		}
	}
	// Called to draw scene
	void RenderScene(void)
	{
		// Where is the light coming from
		GLTVector3 vLightDir0 = { cos(yRot * GLT_PI / 180), 0.0f, -sin(yRot * GLT_PI / 180) };
		GLTVector3 vLightDir1 = { 0.0f, cos(yRot * GLT_PI / 180), -sin(yRot * GLT_PI / 180) };

		// Clear the window with current clearing color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -15.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		glTranslatef(2.0f, 0.0f, 0.0f);
		toonDramCylinder(1.0f, 50, vLightDir0);

		glTranslatef(-4.0f, 0.0f, 0.0f);
		toonDramCylinder(1.0f, 50, vLightDir0);

		glTranslatef(2.0f, 3.0f, 0.0f);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		toonDramCylinder(1.0f, 50, vLightDir1);

		glPopMatrix();
		// Do the buffer Swap
		glutSwapBuffers();

		// Rotate 1/2 degree more each frame
		yRot += 1.0f;
	}
	// This function does any needed initialization on the rendering
	// context. 
	void SetupRC()
	{
		// Load a 1D texture with toon shaded values
		// Green, greener...
		GLbyte toonTable[12][3] = {
			{ 0, 16, 0 },
			{ 0, 32, 0 },
			{ 0, 48, 0 },
			{ 0, 64, 0 },
			{ 0, 80, 0 },
			{ 0, 96, 0 },
			{ 0, 112, 0 },
			{ 0, 128, 0 },
			{ 0, 144, 0 },
			{ 0, 160, 0 },
			{ 0, 176, 0 },
			{ 0, 192, 0 },
		};
		// Bluish background
		glClearColor(0.0f, 0.0f, .50f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 12, 0, GL_RGB, GL_UNSIGNED_BYTE, toonTable);

		glEnable(GL_TEXTURE_1D);
	}
	///////////////////////////////////////////////////////////
	// Called by GLUT library when idle (window not being
	// resized or moved)
	void TimerFunction(int value)
	{
		// Redraw the scene with new coordinates
		glutPostRedisplay();
		glutTimerFunc(33, TimerFunction, 1);
	}
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		// Prevent a divide by zero, when window is too short
		// (you cant make a window of zero width).
		if (h == 0)
			h = 1;
		glViewport(0, 0, w, h);

		fAspect = (GLfloat)w / (GLfloat)h;
		// Reset the coordinate system before modifying
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Set the clipping volume
		gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	///////////////////////////////////////////////////
	// Program entry point
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Toon/Cell Shading Demo");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		glutTimerFunc(33, TimerFunction, 1);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}