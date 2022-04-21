#include "glew.h"
#include "glut.h"
#include <windows.h>
#include <math.h>
#include <stdio.h>

namespace Task_4_7
{
#define GLT_PI 3.14159265358979323846
#define GLT_PI_DIV_180 0.017453292519943296
#define GLT_INV_PI_DIV_180 57.2957795130823229
	// Данные о свете и материале
	GLfloat fLightPos[4] = { -100.0f, 100.0f, 50.0f,
	1.0f }; // Point source
	GLfloat fLightPosMirror[4] = { -100.0f, -100.0f,
	50.0f, 1.0f };
	GLfloat fNoLight[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat fLowLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat fBrightLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat yRot = 0.0f;//Угол поворота, задействованный в анимации
	typedef GLfloat GLTVector3[3]; // Трехомпонентный вектор с плавающей запятой
		// Для достижения наилучших результатов, поместим его в списке отображения
		// Рисуем тор (бублик) при z = fZVal... в плоскости XY
		// Скалярное масштабирование вектора

	typedef struct { // Рамка для контейнера ссылок
		float x;
		float y;
		float z;
	} Position;
	Position spheres[50];

	void gltScaleVector(GLTVector3 vVector, const GLfloat
		fScale)
	{
		vVector[0] *= fScale; vVector[1] *= fScale;
		vVector[2] *= fScale;
	}
	// Возвращает длину вектора в квадрате
	GLfloat gltGetVectorLengthSqrd(const GLTVector3
		vVector)
	{
		return (vVector[0] * vVector[0]) +
			(vVector[1] * vVector[1]) + (vVector[2] * vVector[2]);
	}
	// Возвращает длину вектора 
	GLfloat gltGetVectorLength(const GLTVector3 vVector)
	{
		return
			(GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
	}
	// Масштабирование вектора по длине - создание единичсного вектора 
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
				// Первая точка
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
	// Эта функция выполняет необходимую инициализацию в контексте
		// визуализации 
	void SetupRC()
	{
		// Серый фон
		glClearColor(fLowLight[0], fLowLight[1],
			fLowLight[2], fLowLight[3]);

		// Задние части многоугольников отбрасываются
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// Устанавливаются параметры источника света: 
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fNoLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, fLowLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, fBrightLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, fBrightLight);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		// Преимущественно используется согласование свойств материала glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT,
			GL_AMBIENT_AND_DIFFUSE);
		glMateriali(GL_FRONT, GL_SHININESS, 128);

		for (int i = 0; i < 50; i++)
		{
			spheres[i].x = (float)((rand() % 400) - 200) * 0.1f;
			spheres[i].y = 1.0f;
			spheres[i].z = (float)((rand() % 400) - 200) * 0.1f;
		}
	}
	/////////////////////////////////////////////////////
	//////
	// Рисуем землю как стороны треугольников. Модели затенения и цветные модели // установлены так, что мы в конечном итоге получим черно - белую шахматную
		// доску.
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
	// Рисуем случайных обитателей и вращающихся тор / сферу
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
	// Вызывается для рисования сцены 
	void RenderScene(void)
	{
		// Очищаем окно текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		// Источник света помещается под полом и освещает 
		// "отраженный" мир
		glLightfv(GL_LIGHT0, GL_POSITION,
			fLightPosMirror);
		glPushMatrix();
		glFrontFace(GL_CW); // Зеркально отображается геометрия, 
	   // инвертируется ориентация
		glScalef(1.0f, -1.0f, 1.0f);
		DrawWorld();
		glFrontFace(GL_CCW);
		glPopMatrix();

		// Над "отраженными" объектами рисуется 
		// прозрачная земля 
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,
			GL_ONE_MINUS_SRC_ALPHA);
		DrawGround();
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);

		// Восстанавливается правильное освещение и 
		// правильно рисуется мир
		glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
		DrawWorld();
		glPopMatrix();

		// Переключение буферов
		glutSwapBuffers();
	}
	/////////////////////////////////////////////////////
	//////
	//Вызывается библиотекой GLUT в холостом состоянии (окно не меняет //размера и не перемещается) 
	void TimerFunction(int value)
	{
		yRot += 1.0f; // Обновление коэффициента поворота

		// Перерисовка сцены
		glutPostRedisplay();

		// Сброс таймера
		glutTimerFunc(10, TimerFunction, 1);
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
		// Система координат обновляется перед
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Генерируется перспективная проекция
		gluPerspective(35.0f, fAspect, 1.0f, 50.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, -3.0f, -4.0f);
	}
	/////////////////////////////////////////////////////
	////////
	// Точка входа программы
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

		SetupRC();
		glutMainLoop();
		return 0;
	}
}