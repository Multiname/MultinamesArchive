#include <iostream>
using namespace std;

const int MAXLEN = 255;

float perimeter(float Ax, float Ay, float Bx, float By, 
	float Cx, float Cy);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Введите кол-во точек: ";
	int numofpoints{};
	cin >> numofpoints;
	cout << "Введите координаты точек:" << endl;
	float Points[MAXLEN][2]{};
	for (int i = 0; i < numofpoints; i++)
	{
		cin >> Points[i][0];
		cin >> Points[i][1];
	}

	int p1 = 0;
	int p2 = 1;
	int p3 = 2;
	int maxper = 0;
	for (int a = 0; a < numofpoints - 2; a++)
	{
		for (int b = a + 1; b < numofpoints - 1; b++)
		{
			for (int c = b + 1; c < numofpoints; c++)
			{
				float per = perimeter(Points[a][0], 
					Points[a][1], Points[b][0],
					Points[b][1], Points[c][0],
					Points[c][1]);
				if (per > maxper)
				{
					maxper = per;
					p1 = a;
					p2 = b;
					p3 = c;
				}
			}
		}
	}

	cout << "Точки, образующие треугольник с наибольшим периметром: " << endl
		<< Points[p1][0] << " " << Points[p1][1] << endl
		<< Points[p2][0] << " " << Points[p2][1] << endl
		<< Points[p3][0] << " " << Points[p3][1] << endl;
}

float perimeter(float Ax, float Ay, float Bx, float By, float Cx, float Cy)
{
	return sqrt(pow(Bx - Ax, 2) + pow(By - Ay, 2))
		+ sqrt(pow(Cx - Bx, 2) + pow(Cy - By, 2))
		+ sqrt(pow(Ax - Cx, 2) + pow(Ay - Cy, 2));
}