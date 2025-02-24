#pragma once
#include<iostream>
#include<windows.h>

using namespace std;


//Header File (From Dr.Amir Wali) Starts Here.....

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void myLine(int x1, int y1, int x2, int y2, int color) //use three 3 integers if you want colored lines.
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(color, color, color)); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);

}


// This function checks if any of the 4 cursor keys are pressed. 
// If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 4 cursor keys is pressed.
// whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right and 4 for left.
bool isCursorKeyPressed(int& whichKey)   //whichKey passed as reference.... 
{
	char key;
	key = GetAsyncKeyState(37);
	if (key == 1)
	{
		whichKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = GetAsyncKeyState(38);
	if (key == 1)
	{

		whichKey = 2;		// 2 if up key is pressed
		return true;
	}

	key = GetAsyncKeyState(39);
	if (key == 1)
	{

		whichKey = 3; // 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(40);
	if (key == 1)
	{

		whichKey = 4;   // 4 if down key is pressed
		return true;
	}
	return false;
}

void myRectangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0)); //Fill color can also be passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0));  //Fill color is black
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);


}

//Header File Ends Here.....


//Modified Function Copied From Semester Project (and Others)........


void myEllipse1(int x1, int y1, int x2, int y2, int R, int G, int B)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB(from 0 - 255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);

	//Set the brush to NULL to prevent filling
	HBRUSH oldBrush = (HBRUSH)SelectObject(device_context, GetStockObject(NULL_BRUSH));

	Ellipse(device_context, x1, y1, x2, y2);

	//Restore the original brush
	SelectObject(device_context, oldBrush);

	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
}

void myRectangle1(int x1, int y1, int x2, int y2, int R, int G, int B)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    // Change the color by changing the values in RGB (from 0-255)
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(device_context, pen);

    // Set the brush to NULL to prevent filling
    HBRUSH oldBrush = (HBRUSH)SelectObject(device_context, GetStockObject(NULL_BRUSH));

    Rectangle(device_context, x1, y1, x2, y2);

    // Restore the original brush
    SelectObject(device_context, oldBrush);

    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
}


//Ends here......


//My Code Functions Start Here.....

bool intersect(float X1, float Y1, float R1, float X2, float Y2, float R2)
{
	int res = 0;
	res = sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
	if (res <= R1 + R2)
	{
		return res;
	}
}

void most_intersecting(float X[], float Y[], float R[], int N)
{
	int max = 0;
	int max_index = -1;
	for (int i = 0; i < N; ++i)
	{
		int count = 0;
		for (int j = 0; j < N; ++j)
		{
			intersect(X[i], Y[i], R[i], X[j], Y[j], R[j]);
			count++;
		}
		if (max < count)
		{
			max = count;
			max_index = i;
		}
	}
	if (max_index == -1)
	{
		cout << "No circle intersects with any other circle." << endl;
	}
	else
	{
		cout << "Circle with radius " << R[max_index] << " and center " << "(" << X[max_index] << "," << Y[max_index] << ")" << " intersects most circles." << endl;
	}
}