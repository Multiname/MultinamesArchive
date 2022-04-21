#include "glew.h"
#include "glut.h" 
#include <math.h>
#include "ObjLoader.h"

namespace Task_4_6
{
	typedef GLfloat GLTVector3[3];
	typedef GLfloat GLTVector4[4];//Четырехкомпонентный вектор с плавающей //запятой
	typedef GLfloat GLTMatrix[16];// Основноц столбец матрицы 4х4 с плавающей //запятой

	ObjLoader* loader;

	bool light_0IsEnabled = true;
	bool light_1IsEnabled = true;
	// Величина поворота 
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	GLTMatrix shadowMat_0;
	GLTMatrix shadowMat_1;
	GLfloat lightPos_0[] = { -50.f, 150.0f, 100.0f, 1.0f };
	GLfloat lightPos_1[] = { 50.f, 150.0f, 100.0f, 1.0f };

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

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos_0);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos_1);

		glBegin(GL_QUADS);
		glColor3ub(128, 128, 0);
		glVertex3f(200.0f, 0.0f, -200.0f);
		glVertex3f(-200.0f, 0.0f, -200.0f);
		glColor3ub(0, 255, 0);
		glVertex3f(-200.0f, 0.0f, 200.0f);
		glVertex3f(200.0f, 0.0f, 200.0f);
		glEnd();

		// Восстановление состояния матрицы
		glPopMatrix();

		if (light_0IsEnabled) {
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glPushMatrix();

			// Текущая матрица множится на матрицу проекции тени
			// Самолетик поворачивается в новом плоском пространстве
			glRotatef(xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(yRot, 0.0f, 1.0f, 0.0f);
			glMultMatrixf((GLfloat*)shadowMat_0);

			glColor3ub(16, 16, 16);
			loader->Draw();

			// Восстанавливается нормальная проекция 
			glPopMatrix();
			// Восстанавливаются переменные состояния освещения 
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
		}

		if (light_1IsEnabled) {
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
			glPushMatrix();

			// Текущая матрица множится на матрицу проекции тени
			// Самолетик поворачивается в новом плоском пространстве
			glRotatef(xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(yRot, 0.0f, 1.0f, 0.0f);
			glMultMatrixf((GLfloat*)shadowMat_1);

			glColor3ub(16, 16, 16);
			loader->Draw();

			// Восстанавливается нормальная проекция 
			glPopMatrix();
			// Восстанавливаются переменные состояния освещения 
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
		}

		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glColor3ub(128, 0, 128);
		loader->Draw();
		glPopMatrix();

		// Отобразить результаты
		glutSwapBuffers();
	}

	// Полученные три коэффициента уравнения плоскости дают три точки на поверхности
	void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane)
	{
		// Получение нормали из трех точек. Нормаль – первые три коэффициента
		// уравнения плоскости
		gltGetNormalVector(vPoint1, vPoint2, vPoint3, vPlane);

		// Итоговый коэффициент находится обратной подстановкой
		vPlane[3] = -(vPlane[0] * vPoint3[0] + vPlane[1] * vPoint3[1] + vPlane[2] * vPoint3[2]);
	}

	//По коэффициентам уравнения плоскости и положению источника света 
// создается матрица отбрасывания тени. Полученное 
// значение сохраняется в destMat
	void gltMakeShadowMatrix(GLTVector3 vPoints[3], GLTVector4 vLightPos, GLTMatrix destMat)
	{
		GLTVector4 vPlaneEquation;
		GLfloat dot;
		gltGetPlaneEquation(vPoints[0], vPoints[1], vPoints[2], vPlaneEquation);
		// Скалярное произведение направляющего вектора 
		// плоскости и положения источника света
		dot = vPlaneEquation[0] * vLightPos[0] +
			vPlaneEquation[1] * vLightPos[1] +
			vPlaneEquation[2] * vLightPos[2] +
			vPlaneEquation[3] * vLightPos[3];
		// Выполняется проектирование 
		// Первый столбец
		destMat[0] = dot - vLightPos[0] * vPlaneEquation[0];
		destMat[4] = 0.0f - vLightPos[0] * vPlaneEquation[1];
		destMat[8] = 0.0f - vLightPos[0] * vPlaneEquation[2];
		destMat[12] = 0.0f - vLightPos[0] * vPlaneEquation[3];
		// Второй столбец
		destMat[1] = 0.0f - vLightPos[1] * vPlaneEquation[0];
		destMat[5] = dot - vLightPos[1] * vPlaneEquation[1];
		destMat[9] = 0.0f - vLightPos[1] * vPlaneEquation[2];
		destMat[13] = 0.0f - vLightPos[1] * vPlaneEquation[3];
		// Третий столбец
		destMat[2] = 0.0f - vLightPos[2] * vPlaneEquation[0];
		destMat[6] = 0.0f - vLightPos[2] * vPlaneEquation[1];
		destMat[10] = dot - vLightPos[2] * vPlaneEquation[2];
		destMat[14] = 0.0f - vLightPos[2] * vPlaneEquation[3];
		// Четвертый столбец
		destMat[3] = 0.0f - vLightPos[3] * vPlaneEquation[0];
		destMat[7] = 0.0f - vLightPos[3] * vPlaneEquation[1];
		destMat[11] = 0.0f - vLightPos[3] * vPlaneEquation[2];
		destMat[15] = dot - vLightPos[3] * vPlaneEquation[3];
	}

	// Эта функция выполняет необходимую инициализацию в контексте
	// визуализации. 
	void SetupRC()
	{
		GLTVector3 points[3] = {
			{ 1.0f, 0.0f, -1.0f },
			{ -1.0f, 0.0f, -1.0f },
			{ -1.0f, 0.0f, 1.0f } };

		GLfloat diffuseLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };

		glEnable(GL_DEPTH_TEST);// Удалить скрытых поверхностей
		glFrontFace(GL_CCW);// Многоугольники с обходом против часовой стрелки
			// направлены вперед
		glEnable(GL_CULL_FACE);// Внутри самолета расчеты не производятся

		// Активизируется освещение
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);

		glClearColor(0.5f, 1.0f, 0.5f, 1.0f);

		glEnable(GL_LIGHTING);
		GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white);

		glColor3ub(128, 0, 128);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		// Активизирует согласование цветов
		glEnable(GL_COLOR_MATERIAL);

		gltMakeShadowMatrix(points, lightPos_0, shadowMat_0);
		gltMakeShadowMatrix(points, lightPos_1, shadowMat_1);

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
		gluPerspective(45.0f, fAspect, 1.0f, 500.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0f, -30.0f, -150.0f);
	}

	void processMenuEvents(int option) {
		switch (option) {
		case 1:
			if (light_0IsEnabled)
				glDisable(GL_LIGHT0);
			else
				glEnable(GL_LIGHT0);
			light_0IsEnabled = !light_0IsEnabled;
			break;
		case 2:
			if (light_1IsEnabled)
				glDisable(GL_LIGHT1);
			else
				glEnable(GL_LIGHT1);
			light_1IsEnabled = !light_1IsEnabled;
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
		glutAddMenuEntry("Switch light 0", 1);
		glutAddMenuEntry("Switch light 1", 2);
		// прикрепить меню правой кнопки
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();
		return 0;
	}
}