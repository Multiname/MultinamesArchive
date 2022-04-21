#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
#include <math.h>
namespace Task_4_9_2
{
	// Значения углов
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		GLfloat x, y, z, angle; // Место хранения координат и углов
		GLfloat sizes[2]; //Запоминаем диапазон размеров поддерживаемых точек
		GLfloat step; // Запоминаем поддерживаемый инкремент размеров точек
		GLfloat curSize; // Записываем размер текущих точек
		GLfloat minSize; // Записываем минимальный размер точки
		GLfloat maxSize; // Записываем максимальный размер точки
		GLfloat blueColor = 1.0f;
		GLfloat colorStep = 0.005f;
		// Очищаем окно текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT);
		// Записывается состояние матрицы и выполняются повороты
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		// Получаем диапазон размеров поддерживаемых точек и размер шага
		glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
		glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
		// Задаем исходный размер точки
		curSize = sizes[0];
		minSize = sizes[0];
		maxSize = sizes[1];
		short multiplier = 3;
		// Задаем начальную координату z
		z = -75.0f;
		// Циклический проход по окружности три раза
		for (angle = 0.0f; angle <= (2.0f * 3.1415f) * 5.0f; angle += 3.1415f * 0.1f)
		{
			// Расчет значений x и у точек окружности
			x = 25.0f * sin(angle);
			y = 25.0f * cos(angle);
			// Задаем размер точки перед указанием примитива
			glPointSize(curSize);
			glColor3f(1.0f, 0.0f, blueColor);
			// Рисуем точку
			glBegin(GL_POINTS);
			glVertex3f(x, y, z);
			glEnd();
			// Увеличиваем значение z и размер точки
			z += 1.5f;
			if (curSize >= maxSize / 5)
				multiplier = -3;
			else if (curSize <= minSize)
				multiplier = 3;
			curSize += multiplier * step;

			blueColor -= colorStep;
		}
		// Восстанавливаем преобразования
		glPopMatrix();
		// Очищаем стек команд рисования
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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_POINT_SMOOTH);     // Сглаживание точек
		glEnable(GL_LINE_SMOOTH);     // Сглаживание линий
		glEnable(GL_POLYGON_SMOOTH); // Сглаживание краев многоугольников
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
		glutCreateWindow("Listing 2");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}