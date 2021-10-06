#include <iostream>
using namespace std;

const int MAXLEN = 255;

float square(float Ax, float Ay, float Bx, 
	float By, float Cx, float Cy);

void main()
{
	setlocale(LC_ALL, "Russian");

	cout << "¬ведите вол-во точек: ";
	int nop{};
	cin >> nop;
	cout << "¬ведите координаты многоугоольника: " << endl;
	float Points[MAXLEN][2]{};
	for (int i = 0; i < nop; i++)
	{
		cin >> Points[i][0];
		cin >> Points[i][1];
	}

	float sq = 0;
	for (int j = 0; j < nop - 2; j++)
	{
		sq += square(Points[0][0], Points[0][1],
			Points[j + 1][0], Points[j + 1][1],
			Points[j + 2][0], Points[j + 2][1]);
	}

	cout << "ѕлощадь фигуры: " << sq << endl;
}

float square(float Ax, float Ay, float Bx,
	float By, float Cx, float Cy)
{
	float ABx = Bx - Ax;
	float ABy = By - Ay;
	float ACx = Cx - Ax;
	float ACy = Cy - Ay;
	return 0.5 * abs(ABx * ACy - (ABy * ACx));
}