#include <iostream>
using namespace std;
int main()
{
	int x;
	cout << "Enter Your Age: " << endl;
	cin >> x;
	if (x >= 13 && x <= 19)
		cout << "You are a teenager." << endl;
	else
		cout << "You are Not a teenager." << endl;
	return 0;
}