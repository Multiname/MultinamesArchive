#include "glew.h"
#include "glut.h" 
#include <math.h>
#include "ObjLoader.h"

namespace Task_4_3
{
	ObjLoader* loader;

	bool redIsEnabled = true;
	bool greenIsEnabled = true;
	bool blueIsEnabled = true;
	// Величина поворота 
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	typedef GLfloat GLTVector3[3];
	// Значение скалярного вектора
	void gltScaleVector(GLTVector3 vVector, const GLfloat
		fScale)
	{
		vVector[0] *= fScale; vVector[1] *= fScale;
		vVector[2] *= fScale;
	}
	// Получает квадрат длины вектора
	GLfloat gltGetVectorLengthSqrd(const GLTVector3
		vVector)
	{
		return (vVector[0] * vVector[0]) +
			(vVector[1] * vVector[1]) + (vVector[2] * vVector[2]);
	}

	// Получает длину вектора
	GLfloat gltGetVectorLength(const GLTVector3 vVector)
	{
		return
			(GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
	}
	// Нормируется вектор источника света
	void gltNormalizeVector(GLTVector3 vNormal)
	{
		GLfloat fLength = 1.0f /
			gltGetVectorLength(vNormal);
		gltScaleVector(vNormal, fLength);
	}
	// Вычислить векторное произведение двух векторов
	void gltVectorCrossProduct(const GLTVector3 vU, const
		GLTVector3 vV, GLTVector3 vResult)
	{
		vResult[0] = vU[1] * vV[2] - vV[1] * vU[2];
		vResult[1] = -vU[0] * vV[2] + vV[0] * vU[2];
		vResult[2] = vU[0] * vV[1] - vV[0] * vU[1];
	}
	// Вычесть один вектор из другого
	void gltSubtractVectors(const GLTVector3 vFirst,
		const GLTVector3 vSecond, GLTVector3 vResult)
	{
		vResult[0] = vFirst[0] - vSecond[0];
		vResult[1] = vFirst[1] - vSecond[1];
		vResult[2] = vFirst[2] - vSecond[2];
	}
	// Даны три точки на плоскости направлены против часовой стрелки, вычислить // нормаль
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

	// Вызывается для рисования сцены 
	void RenderScene(void)
	{
		GLTVector3 vNormal; // Память для вычисления нормали к поверхности
		// Очистка окна текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Записываем состояние матрицы и выполняем поворот
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		GLfloat lightPos_1[] = { 0.0f, 0.0f, 100.0f, 1.0f };
		GLfloat lightPos_2[] = { 0.0f, 0.0f, -100.0f, 1.0f };
		GLfloat lightPos_3[] = { 100.0f, 0.0f, 0.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos_1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos_2);
		glLightfv(GL_LIGHT2, GL_POSITION, lightPos_3);

		loader->Draw();

		// Восстановление состояния матрицы
		glPopMatrix();
		// Отобразить результаты
		glutSwapBuffers();
	}

	// Эта функция выполняет необходимую инициализацию в контексте
	// визуализации. 
	void SetupRC()
	{
		GLfloat diffuseLight_1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		GLfloat diffuseLight_2[] = { 0.0f, 1.0f, 0.0f, 1.0f };
		GLfloat diffuseLight_3[] = { 0.0f, 0.0f, 1.0f, 1.0f };

		glEnable(GL_DEPTH_TEST);// Удалить скрытых поверхностей
		glFrontFace(GL_CCW);// Многоугольники с обходом против часовой стрелки
			// направлены вперед
		glEnable(GL_CULL_FACE);// Внутри самолета расчеты не производятся

		glEnable(GL_LIGHTING);

		// Активизируется освещение
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight_1);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight_2);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight_3);
		glEnable(GL_LIGHT2);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

		glColor3ub(128, 128, 128);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		// Активизирует согласование цветов
		glEnable(GL_COLOR_MATERIAL);

		loader = new ObjLoader("tricycle.obj");
	}
	/////////////////////////////////////////////////////
	// Упарвление стрелками
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
		// Обновление окна
		RenderScene();
	}
	/////////////////////////////////////////////////////
	/////
	// Обновляется проекция и положение источника света
	void ChangeSize(int w, int h)
	{
		GLfloat fAspect;
		// Предотвращает деление на нуль
		if (h == 0)
			h = 1;
		// Размер поля просмотра устанавливается равным размеру окна glViewport(0, 0, w, h);
		// Обновляется система координат
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		fAspect = (GLfloat)w / (GLfloat)h;
		gluPerspective(45.0f, fAspect, 1.0f, 225.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0f, -30.0f, -150.0f);
	}

	void processMenuEvents(int option) {
		switch (option) {
		case 1:
			if (redIsEnabled)
				glDisable(GL_LIGHT0);
			else
				glEnable(GL_LIGHT0);
			redIsEnabled = !redIsEnabled;
			break;
		case 2:
			if (greenIsEnabled)
				glDisable(GL_LIGHT1);
			else
				glEnable(GL_LIGHT1);
			greenIsEnabled = !greenIsEnabled;
			break;
		case 3:
			if (blueIsEnabled)
				glDisable(GL_LIGHT2);
			else
				glEnable(GL_LIGHT2);
			blueIsEnabled = !blueIsEnabled;
			break;
		}

		RenderScene();
	}

	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
			GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Tricycle");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();

		glutCreateMenu(processMenuEvents);
		//добавить записи в нашем меню
		glutAddMenuEntry("Switch red light", 1);
		glutAddMenuEntry("Switch green light", 2);
		glutAddMenuEntry("Switch blue light", 3);
		// прикрепить меню правой кнопки
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();
		return 0;
	}
}