#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
#include <math.h>
namespace Listing_1
{
	// Определяется константа со значением “пи”
	#define GL_PI 3.1415f
	// Значения углов
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		GLfloat x, y, z, angle; // Здесь хранятся координаты и углы
		// Окно очищается текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT);
		// Записываем состояние матрицы и выполняем поворот
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		// Вызываем один раз для всех оставшихся точек
		glBegin(GL_POINTS);
		z = -75.0f;
		for (angle = 0.0f; angle <= (2.0f * GL_PI) * 10.0f; angle += 0.1f)
		{
			x = 25.0f * sin(angle);
			y = 25.0f * cos(angle);
			// Задаем точку и немного смещаем значение z
			glVertex3f(x, y, z);
			z += 0.25f;
		}
		// Рисуем точки
		glEnd();
		// Восстанавливаем преобразования
		glPopMatrix();
		// Очищаем стек команд преобразования
		glutSwapBuffers();
	}
	// Функция выполняет необходимую инициализацию 
	// в контексте визуализации 
	void SetupRC()
	{
		// Черный фон
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		// Цвет рисования выбирается фиолетовым
		glColor3f(1.0f, 0.0f, 1.0f);
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
		if (key > 356.0f)
			xRot = 0.0f;
		if (key < -1.0f)
			xRot = 355.0f;
		if (key > 356.0f)
			yRot = 0.0f;
		if (key < -1.0f)
			yRot = 355.0f;
		// Обновляем окно
		glutPostRedisplay();
	}
	void ChangeSize(int w, int h)
	{
		GLfloat nRange = 100.0f;
		// Предотвращает деление на нуль
		if (h == 0)
			h = 1;
		// Устанавливаем размеры поля просмотра равными размерам окна
		glViewport(0, 0, w, h);
		// Устанавливаем перспективную систему координат
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Устанавливает объем отсечения с помощью отсекающих 
		// плоскостей (левая, правая, нижняя, верхняя, ближняя, дальняя)
		if (w <= h)
			glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
		else
			glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
		// Обновляется стек матриц проекции модели
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 1");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}