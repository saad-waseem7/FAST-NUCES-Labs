#include<iostream>
#include<string> 
#include<cstring>
using namespace std;

class StringHolder 
{
private:
	char* str;
	int len;

public:

	StringHolder(char* input) 
	{
		
		for (len = 0; input[len] != '\0'; len++)
		{
		}

		str = new char[len + 1];
		for (int i = 0; i <= len; i++) 
		{
			str[i] = input[i];
		}
	}

	~StringHolder() 
	{
		delete[] str;
	}

	void display() 
	{
		cout << "Entered string: " << str << endl;
		cout << "length of the string: " << len << endl;
	}
};

int main() 
{
	string input;
	cout << "Enter String: " << endl;
	getline(cin, input);
	char *inputArray = new char[input.length() + 1];
	int x;
	for (x = 0; input[x] != '\0'; x++)
	{
		*(inputArray + x) = input[x];
	}
	*(inputArray + x) = '\0';
	StringHolder holder(inputArray);
	holder.display();
	system("pause");
	return 0;
}