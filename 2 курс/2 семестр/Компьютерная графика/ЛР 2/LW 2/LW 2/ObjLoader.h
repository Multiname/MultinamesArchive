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
	ObjLoader(string filename);// ������ �������
	void Draw();// ������� ���������
private:
	vector<vector<GLfloat>> v;// ��������� ���������� ������� (x, y, z)
	vector<vector<GLint>> f;// ��������� ��� ��������� ������� ����
};