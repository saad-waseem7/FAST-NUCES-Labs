#include<iostream>
#include<string>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include"Visual.h"

using namespace std;

int main()
{
	const int N = 4;
	float X[N] = { 105, 150, 80, 180 };
	float Y[N] = { 250, 310, 270, 260 };
	float R[N] = { 55, 30, 28, 40 };
	 
	int colors[N][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0} };
	for (int i = 0; i < N; ++i)
	{
		myEllipse1(X[i], Y[i], X[i] + 2 * R[i], Y[i] + 2 * R[i], colors[i][0], colors[i][1], colors[i][2]);
		//Modeified Function Call here...
		Sleep(500);
	}
	cout << "Intersecting circles:" << endl;
	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			if (intersect(X[i], Y[i], R[i], X[j], Y[j], R[j]))
			{
				cout << "Circle " << i + 1 << " and Circle " << j + 1 << " intersect." << endl;
			}
		}
	}
	most_intersecting(X, Y, R, N);
	char wait;
	cin >> wait;
	return 0;
}
