#include "glew.h"
#include "glut.h"
#include <math.h>

namespace Listing_3_4
{
	// Параметры освещения
	GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		// Угол поворота системы Земля/Луна
		static float fMoonRot = 0.0f;
		static float fEarthRot = 0.0f;
		static float fSatelliteRot = 0.0f;
		// Очищаем окно текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT);
		// Save the matrix state and do the rotations
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		// Транслируем всю сцену в поле зрения
		glTranslatef(0.0f, 0.0f, -300.0f);
		// Устанавливаем цвет материала красным
		// Солнце
		glDisable(GL_LIGHTING);
		glColor3ub(255, 255, 0);
		glutSolidSphere(15.0f, 30, 17);
		glEnable(GL_LIGHTING);
		// Движение источника света, после прорисовки солнца!
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		// Поворот системы координат
		glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
		// Прорисовка Земли
		glColor3ub(0, 0, 255);
		glTranslatef(105.0f, 0.0f, 0.0f);
		glutSolidSphere(15.0f, 30, 17);
		
		glPushMatrix();

		// Поворот в системе координат, связанной с Землей
			// и изображение Луны
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

		// Восстанавливается состояние матрицы
		glPopMatrix(); // Матрица наблюдения модели
		// Шаг по орбите Земли равен пяти градусам
		fEarthRot += 1.0f;
		if (fEarthRot > 360.0f)
			fEarthRot = 0.0f;
		// Показывается построенное изображение
		glutSwapBuffers();
	}
	// Функция выполняет всю необходимую инициализацию в контексте
	//визуализации
	void SetupRC()
	{
		// Параметры света и координаты
		glEnable(GL_DEPTH_TEST); // Удаление скрытых поверхностей
		glFrontFace(GL_CCW); //Многоугольники с обходом против
		//часовой стрелки направлены наружу
		glEnable(GL_CULL_FACE); //Расчеты внутри самолета не выполняются
		// Активация освещения
		glEnable(GL_LIGHTING);
		// Устанавливается и активизируется источник света 0
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);
		// Активизирует согласование цветов
		glEnable(GL_COLOR_MATERIAL);
		// Свойства материалов соответствуют кодам glColor
		glColorMaterial(GL_FRONT,
			GL_AMBIENT_AND_DIFFUSE);
		// Темно-синий фон
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
		// Предотвращает деление на ноль
		if (h == 0)
			h = 1;
		// Размер поля просмотра устанавливается равным размеру окна
		glViewport(0, 0, w, h);
		// Расчет соотношения сторон окна
		fAspect = (GLfloat)w / (GLfloat)h;
		// Устанавливаем перспективную систему координат
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Поле обзора равно 45 градусов, ближняя и дальняя плоскости
			// проходят через 1 и 425
		gluPerspective(45.0f, fAspect, 1.0, 425.0);
		// Обновляем матрицу наблюдения модели
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