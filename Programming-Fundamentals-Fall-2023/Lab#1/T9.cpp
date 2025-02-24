#include<iostream>
using namespace std;
int main()
{
	int x;
	cout << "Enter Your Speed: " << endl;
	cin >> x;
	if (x >= 45 && x <= 70)
		cout << "Your Speed is Safe." << endl;
	else
		cout << "Your Speed is Unsafe." << endl;
	return 0;
}