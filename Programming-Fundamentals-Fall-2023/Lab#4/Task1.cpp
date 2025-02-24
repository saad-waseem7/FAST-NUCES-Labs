#include<iostream>
using namespace std;
void printASCII(char c) 
{
    for (int i = 0; i < 5; i++) 
    {
        cout << int(c + i) << endl;
    }
}
int main() 
{
    char c;
    cout << "Enter a character: ";
    cin >> c;
    printASCII(c);
    return 0;
}
