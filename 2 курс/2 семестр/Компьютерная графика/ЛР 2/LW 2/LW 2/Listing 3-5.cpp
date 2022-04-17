#include "glew.h"
#include "glut.h"
#include <windows.h>
#include <math.h>
#include <random>
#include <time.h>

namespace Listing_3_5
{
	// Используемые константы
#define GLT_PI 3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229
#define gltDegToRad(x) ((x)*GLT_PI_DIV_180)
// Некоторые типы данных
	typedef GLfloat GLTVector2[2];//Двукомпонентный вектор с плавающей запятой
	typedef GLfloat GLTVector3[3];//Трехомпонентный вектор с плавающей запятой
	typedef GLfloat GLTVector4[4];//Четырехкомпонентный вектор с плавающей //запятой
	typedef GLfloat GLTMatrix[16];// Основноц столбец матрицы 4х4 с плавающей //запятой
	void gltLoadIdentityMatrix(GLTMatrix m)
	{
		static GLTMatrix identity = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f };
		memcpy(m, identity, sizeof(GLTMatrix));
	};
	void gltTransformPoint(const GLTVector3 vSrcVector,
		const GLTMatrix mMatrix, GLTVector3 vOut)
	{
		vOut[0] = mMatrix[0] * vSrcVector[0] + mMatrix[4] *
			vSrcVector[1] + mMatrix[8] * vSrcVector[2] + mMatrix[12];
		vOut[1] = mMatrix[1] * vSrcVector[0] + mMatrix[5] *
			vSrcVector[1] + mMatrix[9] * vSrcVector[2] + mMatrix[13];
		vOut[2] = mMatrix[2] * vSrcVector[0] + mMatrix[6] *
			vSrcVector[1] + mMatrix[10] * vSrcVector[2] + mMatrix[14];
	};
	void gltRotationMatrix(float angle, float x, float y,
		float z, GLTMatrix mMatrix)
	{
		float vecLength, sinSave, cosSave, oneMinusCos;
		float xx, yy, zz, xy, yz, zx, xs, ys, zs;
		// Если нулевой вектор проходит, то …
		if (x == 0.0f && y == 0.0f && z == 0.0f)
		{
			gltLoadIdentityMatrix(mMatrix);
			return;
		}
		// Вектор масштабирования
		vecLength = (float)sqrt(x * x + y * y + z * z);
		// Нормализованная матрица вращения
		x /= vecLength;
		y /= vecLength;
		z /= vecLength;

		sinSave = (float)sin(angle);
		cosSave = (float)cos(angle);
		oneMinusCos = 1.0f - cosSave;
		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinSave;
		ys = y * sinSave;
		zs = z * sinSave;
		mMatrix[0] = (oneMinusCos * xx) + cosSave;
		mMatrix[4] = (oneMinusCos * xy) - zs;
		mMatrix[8] = (oneMinusCos * zx) + ys;
		mMatrix[12] = 0.0f;
		mMatrix[1] = (oneMinusCos * xy) + zs;
		mMatrix[5] = (oneMinusCos * yy) + cosSave;
		mMatrix[9] = (oneMinusCos * yz) - xs;
		mMatrix[13] = 0.0f;
		mMatrix[2] = (oneMinusCos * zx) - ys;
		mMatrix[6] = (oneMinusCos * yz) + xs;
		mMatrix[10] = (oneMinusCos * zz) + cosSave;
		mMatrix[14] = 0.0f;
		mMatrix[3] = 0.0f;
		mMatrix[7] = 0.0f;
		mMatrix[11] = 0.0f;
		mMatrix[15] = 1.0f;
	};
	typedef struct { // Контейнер системы отсчета
		GLTVector3 vLocation;
		GLTVector3 vUp;
		GLTVector3 vForward;
	} GLTFrame;
	// Прорисовка тора(бублика), с использованием текущей структуры 1D для легкого затемнения света
	void DrawTorus(GLTMatrix mTransform)
	{
		GLfloat majorRadius = 0.35f;
		GLfloat minorRadius = 0.15f;
		GLint numMajor = 40;
		GLint numMinor = 20;
		GLTVector3 objectVertex; // Вершина, находящаяся в поле зрения
		GLTVector3 transformedVertex; // Новая измененная вершина
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
				GLfloat r = minorRadius * c + majorRadius;
				GLfloat z = minorRadius * (GLfloat)sin(b);
				// Первая точка
				objectVertex[0] = x0 * r;
				objectVertex[1] = y0 * r;
				objectVertex[2] = z;
				gltTransformPoint(objectVertex, mTransform,
					transformedVertex);
				glVertex3fv(transformedVertex);
				// Вторая точка
				objectVertex[0] = x1 * r;
				objectVertex[1] = y1 * r;
				objectVertex[2] = z;
				gltTransformPoint(objectVertex, mTransform,
					transformedVertex);
				glVertex3fv(transformedVertex);
			}
			glEnd();
		}
	}

	// Вызывается для рисования сцены 
	void RenderScene(void)
	{
		GLTMatrix transformationMatrix; // Матрица поворота
		static GLfloat yRot = 0.0f; // Угол поворота, задействованный
									//в
									//анимации
		static GLfloat delta = 5.0f;
		yRot += delta;
		delta += 1 + rand() % (2 - 1 + 1);
		delta *= pow(-1, rand());
		if (delta < 0)
			delta = 1.0f;

		// Очистка окна ткущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Строим матрицу поворота
		gltRotationMatrix(gltDegToRad(yRot), 0.0f, 1.0f, 0.0f, transformationMatrix);
		transformationMatrix[12] = 0.0f;
		transformationMatrix[13] = 0.0f;
		transformationMatrix[14] = -2.5f;

		DrawTorus(transformationMatrix);
		// Буфер обмена
		glutSwapBuffers();
	}
	// Функция выполняет всю необходимую инициализацию в контексте
	// визуализации
	void SetupRC()
	{
		// Голубой фон
		glClearColor(0.0f, 0.0f, .50f, 1.0f);

		// Все рисуется в каркасном виде
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	///////////////////////////////////////////////////////
	////
	// Вызывается библиотекой GLUT в холостом состоянии 
	//(окно не меняет размера и не перемещается) 
	void TimerFunction(int value)
	{
		// Перерисовывает сцену с новыми координатами 
		glutPostRedisplay();
		glutTimerFunc(33, TimerFunction, 1);
	}
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		// Предотвращает деление на нуль, когда окно слишком маленькое
			// (нельзя сделать окно нулевой ширины). 
		if (h == 0)
			h = 1;
		glViewport(0, 0, w, h);

		fAspect = (GLfloat)w / (GLfloat)h;
		// Система координат обновляется перед модификацией
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Генерируется перспективная проекция
		gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	int main(int argc, char* argv[])
	{
		srand(time(NULL));

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
			GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Manual Transformations Demo");
		glutReshapeFunc(ChangeSize);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutTimerFunc(33, TimerFunction, 1);
		glutMainLoop();
		return 0;
	}
}