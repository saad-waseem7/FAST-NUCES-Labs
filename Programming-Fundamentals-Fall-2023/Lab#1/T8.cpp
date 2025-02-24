#include <iostream>
using namespace std;
int main()
{
	int x;
	cout << "Enter Your Age: " << endl;
	cin>>x;
	if (x >= 18 && x <= 21)
		cout << "You can Vote.";
	else if (x >= 21 && x <= 120)
		cout << "You can Vote & Drive.";
	else 
		cout << "Invalid";
	return 0;
}