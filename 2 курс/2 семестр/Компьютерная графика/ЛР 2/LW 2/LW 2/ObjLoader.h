#pragma once
#include <vector>
#include <iostream>
#include "glut.h"

using namespace std;

class ObjLoader
{
public:
	struct vertex
	{
		float x;
		float y;
		float z;
	};
	ObjLoader(string filename);// Чтение функции
	void Draw();// Функция рисования
private:
	vector<vector<GLfloat>> v;// Сохраняем координаты вершины (x, y, z)
	vector<vector<GLint>> f;// Сохраняем три вершинных индекса лица
};