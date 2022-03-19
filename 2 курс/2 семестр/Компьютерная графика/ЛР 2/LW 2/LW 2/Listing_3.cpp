#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
namespace Listing_3
{
	// Значения углов
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		// Вызывается один раз для всех оставшихся точек 
		GLfloat x, y, z, angle; // Здесь хранятся координаты и углы
		GLfloat fSizes[2]; // Метрики диапазона ширины линий
		GLfloat fCurrSize; // Запись текущего состояния
		GLfloat blueColor = 1.0f;
		GLfloat colorStep = 0.04f;
		GLint factor = 1; // Множитель фактуры 
		GLushort pattern = 0xFF00; // Шаблон фактуры
		GLushort patternStep = 1;
		// Очищаем окно текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes);
		fCurrSize = fSizes[0];
		// Активизируется фактура 
		glEnable(GL_LINE_STIPPLE);
		// Пошаговый проход оси у по 20 единиц за раз
		for (y = -90.0f; y < 90.0f; y += 10.0f)
		{
			// Задается ширина линии 
			glLineWidth(fCurrSize);
			glColor3f(1.0f, 0.0f, blueColor);
			// Обновляется множитель повтора и шаблон 
			glLineStipple(factor, pattern);
			// Рисуется линия 
			glBegin(GL_LINES);
			glVertex2f(-80.0f, y);
			glVertex2f(80.0f, y);
			glEnd();
			// Увеличивается ширина линии
			fCurrSize += 0.5f;
			pattern += patternStep;
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
		// Устанавливает объем отсечения с помощью отсекающих 
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
		glutCreateWindow("Listing 3");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();
		return 0;
	}
}