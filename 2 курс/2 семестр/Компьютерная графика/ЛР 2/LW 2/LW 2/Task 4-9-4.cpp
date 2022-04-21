#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
#include <math.h>
namespace Task_4_9_4
{
	// Определяется константа со значением “пи”
#define GL_PI 3.1415f
// Значения углов
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	bool isPointsVisible = true;
	bool isLinesVisible = true;
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		GLfloat x, y, angle; // Здесь хранятся координаты и углы
		// Окно очищается текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT);
		// Записываем состояние матрицы и выполняем поворот
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		if (isLinesVisible)
		{
			glBegin(GL_LINE_STRIP);
			for (angle = 0.0f; angle <= 2.0f * GL_PI; angle += GL_PI * 0.1f)
			{
				x = 25.0f * (-GL_PI + angle);
				y = 25.0f * sin(angle);
				// Задаем точку и немного смещаем значение z
				glVertex2f(x, y);
			}
			glEnd();
		}
		if (isPointsVisible)
		{
			glPointSize(5.0f);
			// Вызываем один раз для всех оставшихся точек
			glBegin(GL_POINTS);
			for (angle = 0.0f; angle <= 2.0f * GL_PI; angle += GL_PI * 0.1f)
			{
				x = 25.0f * (-GL_PI + angle);
				y = 25.0f * sin(angle);
				// Задаем точку и немного смещаем значение z
				glVertex2f(x, y);
			}
			// Рисуем точки
			glEnd();
		}
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
	void processMenuEvents(int option) {

		switch (option) {
		case 1:
			isLinesVisible = !isLinesVisible;
			break;
		case 2:
			isPointsVisible = !isPointsVisible;
			break;
		}

		RenderScene();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 4");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();

		glutCreateMenu(processMenuEvents);
		//добавить записи в нашем меню
		glutAddMenuEntry("Change lines visibility", 1);
		glutAddMenuEntry("Change points visibility", 2);
		// прикрепить меню правой кнопки
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();
		return 0;
	}
}