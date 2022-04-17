#include "glew.h"
#include "glut.h"


namespace Listing_3_2
{
	// Величина поворота
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;
	// Вызывается при изменении размеров окна
	void ChangeSize(GLsizei w, GLsizei h)
	{
		GLfloat nRange = 120.0f;
		// Предотвращает деление на нуль
		if (h == 0)
			h = 1;
		// Устанавливает размеры поля просмотра равны размерам окна
		glViewport(0, 0, w, h);
		// Устанавливаем перспективную систему координат
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// Устанавливает объем отсечения с помощью отсекающих
		// плоскостей (левая, правая, нижняя, верхняя, 
		// ближняя, дальняя) 
		if (w <= h)
			glOrtho(-nRange, nRange, -nRange * h / w,
				nRange * h / w, -nRange * 2.0f, nRange * 2.0f);
		else
			glOrtho(-nRange * w / h, nRange * w / h, -nRange,
				nRange, -nRange * 2.0f, nRange * 2.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	// Эта функция выполняет необходимую инициализацию в контексте
	// визуализации. В данном случае устанавливается 
	// и инициализируется освещение сцены. 
	void SetupRC()
	{
		// Параметры света 
		GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
		GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
		GLfloat lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };
		glEnable(GL_DEPTH_TEST); // Удаление скрытых поверхностей
		glFrontFace(GL_CCW); //Многоугольники с обходом против
							 //часовой стрелки направлены наружу
		glEnable(GL_CULL_FACE); // Расчеты внутри самолета не
		// выполняются
		 // Активизация освещения
		glEnable(GL_LIGHTING);
		// Устанавливается и активизируется источник света 0
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glEnable(GL_LIGHT0);
		// Активизирует согласование цветов
		glEnable(GL_COLOR_MATERIAL);
		// Свойства материалов соответствуют кодам glColor 
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		// Темно-синий фон
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// Реагирует на клавиши со стрелками, двигая систему отсчета камеры
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

		xRot = (GLfloat)((const int)xRot % 360);
		yRot = (GLfloat)((const int)yRot % 360);
		// Обновляем окно
		glutPostRedisplay();
	}

	// Вызывается для рисования сцены 
	void RenderScene(void)
	{
		float fZ, bZ;
		// Очищаем окно текущим цветом очистки
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		fZ = 100.0f;
		bZ = -100.0f;
		// Записываем состояние матрицы и выполняем поворот 
		glPushMatrix();
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(yRot, 0.0f, 1.0f, 0.0f);
		// В качестве текущего цвета рисования задает красный
		glColor3f(1.0f, 0.0f, 1.0f);
		// Лицевая часть 
		///////////////////////////////////
		glBegin(GL_QUADS);
		// прямо вверх оси z
		glNormal3f(0.0f, 0.0f, 1.0f);
		// Левая сторона
		glVertex3f(-50.0f, 50.0f, fZ);
		glVertex3f(-50.0f, -50.0f, fZ);
		glVertex3f(-35.0f, -50.0f, fZ);
		glVertex3f(-35.0f, 50.0f, fZ);
		// Правая сторона
		glVertex3f(50.0f, 50.0f, fZ);
		glVertex3f(35.0f, 50.0f, fZ);
		glVertex3f(35.0f, -50.0f, fZ);
		glVertex3f(50.0f, -50.0f, fZ);

		// Верх
		glVertex3f(-35.0f, 50.0f, fZ);
		glVertex3f(-35.0f, 35.0f, fZ);
		glVertex3f(0.0f, 15.0f, fZ);
		glVertex3f(0.0f, 30.0f, fZ);

		glVertex3f(35.0f, 35.0f, fZ);
		glVertex3f(35.0f, 50.0f, fZ);
		glVertex3f(0.0f, 30.0f, fZ);
		glVertex3f(0.0f, 15.0f, fZ);
		 
		// Низ
		glVertex3f(-35.0f, -35.0f, fZ);
		glVertex3f(-35.0f, -50.0f, fZ);
		glVertex3f(35.0f, -50.0f, fZ);
		glVertex3f(35.0f, -35.0f, fZ);
		// Верхняя длинная часть 
	   ////////////////////////////

		//Все нормали для верхней части вверх оси Y

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-50.0f, 50.0f, fZ);
		glVertex3f(-35.0f, 50.0f, fZ);
		glVertex3f(-35.0f, 50.0f, bZ);
		glVertex3f(-50.0f, 50.0f, bZ);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(35.0f, 50.0f, fZ);
		glVertex3f(50.0f, 50.0f, fZ);
		glVertex3f(50.0f, 50.0f, bZ);
		glVertex3f(35.0f, 50.0f, bZ);

		glNormal3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-35.0f, 50.0f, fZ);
		glVertex3f(0.0f, 30.0f, fZ);
		glVertex3f(0.0f, 30.0f, bZ);
		glVertex3f(-35.0f, 50.0f, bZ);

		glNormal3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 30.0f, fZ);
		glVertex3f(35.0f, 50.0f, fZ);
		glVertex3f(35.0f, 50.0f, bZ);
		glVertex3f(0.0f, 30.0f, bZ);

		// Нижняя секция
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, fZ);
		glVertex3f(-50.0f, -50.0f, bZ);
		glVertex3f(50.0f, -50.0f, bZ);
		glVertex3f(50.0f, -50.0f, fZ);
		// Левая секция
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, fZ);
		glVertex3f(50.0f, -50.0f, fZ);
		glVertex3f(50.0f, -50.0f, bZ);
		glVertex3f(50.0f, 50.0f, bZ);
		// Правая секция
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f, 50.0f, fZ);
		glVertex3f(-50.0f, 50.0f, bZ);
		glVertex3f(-50.0f, -50.0f, bZ);
		glVertex3f(-50.0f, -50.0f, fZ);
		glEnd();
		glFrontFace(GL_CW); // элементы с обходом по часовой стрелке
							// смотрят наружу 
		glBegin(GL_QUADS);
		// Задняя часть
		// Параллельно оси z
		glNormal3f(0.0f, 0.0f, -1.0f);
		// Левая сторона
		glVertex3f(-50.0f, 50.0f, bZ);
		glVertex3f(-50.0f, -50.0f, bZ);
		glVertex3f(-35.0f, -50.0f, bZ);
		glVertex3f(-35.0f, 50.0f, bZ);
		// Правая сторона
		glVertex3f(50.0f, 50.0f, bZ);
		glVertex3f(35.0f, 50.0f, bZ);
		glVertex3f(35.0f, -50.0f, bZ);
		glVertex3f(50.0f, -50.0f, bZ);

		// Верх
		glVertex3f(-35.0f, 50.0f, bZ);
		glVertex3f(-35.0f, 35.0f, bZ);
		glVertex3f(0.0f, 15.0f, bZ);
		glVertex3f(0.0f, 30.0f, bZ);

		glVertex3f(35.0f, 35.0f, bZ);
		glVertex3f(35.0f, 50.0f, bZ);
		glVertex3f(0.0f, 30.0f, bZ);
		glVertex3f(0.0f, 15.0f, bZ);

		// Низ
		glVertex3f(-35.0f, -35.0f, bZ);
		glVertex3f(-35.0f, -50.0f, bZ);
		glVertex3f(35.0f, -50.0f, bZ);
		glVertex3f(35.0f, -35.0f, bZ);

		// Внутрення часть 
	   /////////////////////////////
		glColor3f(0.0f, 1.0f, 0.0f);
		// Нормаль указывает на ось Y
		 
		glNormal3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-35.0f, 35.0f, fZ);
		glVertex3f(0.0f, 15.0f, fZ);
		glVertex3f(0.0f, 15.0f, bZ);
		glVertex3f(-35.0f, 35.0f, bZ);

		glNormal3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 15.0f, fZ);
		glVertex3f(35.0f, 35.0f, fZ);
		glVertex3f(35.0f, 35.0f, bZ);
		glVertex3f(0.0f, 15.0f, bZ);
		 
		// Нижняя часть
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-35.0f, -35.0f, fZ);
		glVertex3f(-35.0f, -35.0f, bZ);
		glVertex3f(35.0f, -35.0f, bZ);
		glVertex3f(35.0f, -35.0f, fZ);
		// Левая часть
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-35.0f, 35.0f, fZ);
		glVertex3f(-35.0f, 35.0f, bZ);
		glVertex3f(-35.0f, -35.0f, bZ);
		glVertex3f(-35.0f, -35.0f, fZ);
		// Правая часть
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(35.0f, 35.0f, fZ);
		glVertex3f(35.0f, -35.0f, fZ);
		glVertex3f(35.0f, -35.0f, bZ);
		glVertex3f(35.0f, 35.0f, bZ);
		glEnd();
		glFrontFace(GL_CCW); // полигоны с обходом против часовой стрелки направлены наружу

		// Восстанавливается состояние матрицы
		glPopMatrix();
		// Буфер-обмена
		glutSwapBuffers();
	}
	int main(int argc, char* argv[])
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(800, 600);
		glutCreateWindow("Orthographic Projection");
		glutReshapeFunc(ChangeSize);
		glutSpecialFunc(SpecialKeys);
		glutDisplayFunc(RenderScene);
		SetupRC();
		glutMainLoop();

		return 0;
	}
}