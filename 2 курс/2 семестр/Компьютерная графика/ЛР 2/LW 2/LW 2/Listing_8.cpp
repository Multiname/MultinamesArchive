#include "glew.h" // System and OpenGL Stuff
#include "glut.h"
namespace Listing_8
{
	// Определяется константа со значением “пи”
#define GL_PI 3.1415f
// Значения углов
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	bool flatMode = false;
	// Вызывается для рисования сцены
	void RenderScene(void)
	{
		GLfloat x, y, z, angle; // Здесь хранятся координаты и углы
			// Окно очищается текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT);

		// Записываем состояние матрицы и выполняем поворот
		glPushMatrix();

		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);

		glEnable(GL_CULL_FACE);

		glBegin(GL_TRIANGLE_STRIP);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2f(40.0f, 40.0f);

		glVertex2f(40.0f, -40.0f);

		glVertex2f(-40.0f, 40.0f);

		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(-40.0f, -40.0f);

		glEnd();


		glBegin(GL_TRIANGLE_FAN);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 40.0f);

		glVertex2f(40.0f, -40.0f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(40.0f, 40.0f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-40.0f, 40.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-40.0f, -40.0f);

		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(40.0f, -40.0f);

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
	void processMenuEvents(int option)
	{
		if (flatMode)
			glShadeModel(GL_SMOOTH);
		else
			glShadeModel(GL_FLAT);
		flatMode = !flatMode;
		RenderScene();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("Listing 8");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();

		glutCreateMenu(processMenuEvents);
		//добавить записи в нашем меню
		glutAddMenuEntry("Change shade model", 1);
		// прикрепить меню правой кнопки
		glutAttachMenu(GLUT_RIGHT_BUTTON);

		glutMainLoop();
		return 0;
	}
}