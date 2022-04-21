#include "glew.h"
#include "glut.h"
#include <math.h>

namespace Listing_3_1
{
	// Величина поворота 
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		// Угол поворота вокруг ядра
		static GLfloat fElect1 = 0.0f;
		// Очищаем окно текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Обновляем матрицу наблюдения модели
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//Транслируем всю сцену в поле зрения
		//Это исходное преобразование наблюдения
		glTranslatef(0.0f, 0.0f, -100.0f);
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		// Красное ядро
		glColor3ub(255, 0, 0);
		glutSolidTeapot(10.0f);

		// Желтые электроны
		glColor3ub(255, 255, 0);
		// Орбита первого электрона
		// Записываем преобразование наблюдения
		glPushMatrix();
		// Поворачиваем на угол поворота
		glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
		// Трансляция элемента от начала координат на орбиту
		glTranslatef(90.0f, 0.0f, 0.0f);
		// Рисуем электрон
		glutSolidSphere(6.0f, 15, 15);

		glTranslatef(-180.0f, 0.0f, 0.0f);
		glColor3ub(255, 0, 255);
		glutSolidSphere(6.0f, 15, 15);
		glColor3ub(255, 255, 0);

		// Восстанавливаем преобразование наблюдения
		glPopMatrix();

		//Орбита второго электрона
		glPushMatrix();
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
		glTranslatef(-70.0f, 0.0f, 0.0f);
		glutSolidSphere(6.0f, 15, 15);

		glTranslatef(140.0f, 0.0f, 0.0f);
		glColor3ub(255, 0, 255);
		glutSolidSphere(6.0f, 15, 15);
		glColor3ub(255, 255, 0);

		glPopMatrix();

		// Орбита третьего электрона
		glPushMatrix();
		glRotatef(360.0f - 45.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 60.0f);
		glutSolidSphere(6.0f, 15, 15);

		glTranslatef(0.0f, 0.0f, -120.0f);
		glColor3ub(255, 0, 255);
		glutSolidSphere(6.0f, 15, 15);

		glPopMatrix();

		// Увеличиваем угол поворота
		fElect1 += 5.0f;
		if (fElect1 > 360.0f)
			fElect1 = 0.0f;
		// Показываем построенное изображение
		glutSwapBuffers();
	}
	// Функция выполняет необходимую инициализацию 
	// в контексте визуализации 
	void SetupRC()
	{
		glEnable(GL_DEPTH_TEST); // Удаление скрытых поверхностей
		glFrontFace(GL_CCW); // Полигоны с обходом против
		//часовой стрелки направлены наружу
		glEnable(GL_CULL_FACE); //Внутри пирамиды расчеты не //производятся
		// Черный фон
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

		if (xRot > 356.0f)
			xRot = 0.0f;
		if (xRot < -1.0f)
			xRot = 355.0f;
		if (yRot > 356.0f)
			yRot = 0.0f;
		if (yRot < -1.0f)
			yRot = 355.0f;
		// Перерисовывает сцену с новыми координатами
		//glutPostRedisplay();
	}
	void TimerFunc(int value)
	{
		glutPostRedisplay();
		glutTimerFunc(10, TimerFunc, 1);
	}
	void ChangeSize(int w, int h)
	{
		GLfloat nRange = 100.0f;
		// Предотвращение деления на ноль
		if (h == 0)
			h = 1;
		// Устанавливает поле просмотра по размерам окна 
		glViewport(0, 0, w, h);
		// Обновляет стек матрицы проектирования
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Устанавливает объем отсечения с помощью отсекающих
			// плоскостей (левая, правая, нижняя, верхняя, 
			// ближняя, дальняя) 
		if (w <= h)
			glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange * 2.0f, nRange * 2.0f);
		else
			glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange * 2.0f, nRange * 2.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
			GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("OpenGL Atom");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		glutTimerFunc(500, TimerFunc, 1);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}