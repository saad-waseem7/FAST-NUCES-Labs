#include <iostream>
#include <string>
using namespace std;
int main()
{
	string name;
	cout << "Enter a Number: ";
	cin >> name;
	int flag = 0;
	for (char i : name) 
	{
		if (!(i >= '0' && i <= '9'))
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		cout << "Wrong Format to enter number" << endl;
	}
	else {
		for (char i : name)
		{
			cout << i << endl;
		}
	}
}