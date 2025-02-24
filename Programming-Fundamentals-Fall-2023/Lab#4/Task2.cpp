#include<iostream>
using namespace std;
int sumdiff(int a, int b)
{
	int res = 0;
	if ((a % 3 == 0) && (a % 5 == 0) && (a % 7 == 0))
	{
		if ((b % 3 == 0) && (b % 5 == 0) && (b % 7 == 0)) 
		{
			res = a + b;
		}
	}
	else
	{
		res = a - b;
	}
	return res;
}
int main()
{
	int x, y, result = 0;
	cout << "Enter First Number: ";
	cin >> x;
	cout << "Enter Second Number: ";
	cin >> y;
	result = sumdiff(x, y);
	cout << result;
	return 0;
}