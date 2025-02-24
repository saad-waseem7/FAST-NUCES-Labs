#include <iostream>
using namespace std;
int main()
{
	int x;
	cout << "Enter a number: ";
	cin >> x;
	if (x >= 10 && x <= 50)
		cout << "It is in range.";
	else
		cout << "It is not in range.";
	return 0;
}