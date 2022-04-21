#include "ObjLoader.h"
#include <fstream>
#include <string>
#include <sstream>

ObjLoader::ObjLoader(string filename)
{
	ifstream file(filename);
	string line;
	while (getline(file, line))
	{
		if (line.substr(0, 1) == "v")
		{
			vector<GLfloat> Point;
			GLfloat x, y, z;
			istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;
			Point.push_back(x);
			Point.push_back(y);
			Point.push_back(z);
			v.push_back(Point);

		}
		else if (line.substr(0, 1) == "f")
		{
			vector<GLint> vIndexSets;
			GLint u, v, w;
			istringstream vtns(line.substr(2));
			vtns >> u; vtns >> v; vtns >> w;
			vIndexSets.push_back(u - 1);
			vIndexSets.push_back(v - 1);
			vIndexSets.push_back(w - 1);
			f.push_back(vIndexSets);
		}
	}
	file.close();
}

void ObjLoader::Draw()
{
	glBegin(GL_TRIANGLES);//Начать рисовать
	for (int i = 0; i < f.size(); i++) {
		GLfloat VN[3];//Нормальный
		// Три вершины
		vertex a, b, c, normal;

		if ((f[i]).size() != 3) {
			cout << "ERROR::THE SIZE OF f IS NOT 3!" << endl;
		}
		else {
			GLint firstVertexIndex = (f[i])[0];// Удалить индекс вершины
			GLint secondVertexIndex = (f[i])[1];
			GLint thirdVertexIndex = (f[i])[2];

			a.x = (v[firstVertexIndex])[0];// Первая вершина
			a.y = (v[firstVertexIndex])[1];
			a.z = (v[firstVertexIndex])[2];

			b.x = (v[secondVertexIndex])[0]; // Вторая вершина
			b.y = (v[secondVertexIndex])[1];
			b.z = (v[secondVertexIndex])[2];

			c.x = (v[thirdVertexIndex])[0]; // Третья вершина
			c.y = (v[thirdVertexIndex])[1];
			c.z = (v[thirdVertexIndex])[2];

			GLfloat vec1[3], vec2[3], vec3[3];// Рассчитать нормальный вектор
			//(x2-x1,y2-y1,z2-z1)
			vec1[0] = a.x - b.x;
			vec1[1] = a.y - b.y;
			vec1[2] = a.z - b.z;

			//(x3-x2,y3-y2,z3-z2)
			vec2[0] = a.x - c.x;
			vec2[1] = a.y - c.y;
			vec2[2] = a.z - c.z;

			//(x3-x1,y3-y1,z3-z1)
			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;

			glNormal3f(VN[0], VN[1], VN[2]);// Рисуем нормальный вектор

			glVertex3f(a.x, a.y, a.z);// Рисуем треугольник
			glVertex3f(b.x, b.y, b.z);
			glVertex3f(c.x, c.y, c.z);
		}
	}
	glEnd();
}