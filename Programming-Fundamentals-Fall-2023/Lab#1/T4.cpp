#include <iostream>
using namespace std;
int main()
{
	int x;
	cout << "Enter Number: " << endl;
	cin >> x;
	if (x % 2 == 0)
		cout << "The Number is Even";
	else if (x % 2 != 0)
		cout << "The number is Odd";
	else cout << "Invalid";
	return 0;

}