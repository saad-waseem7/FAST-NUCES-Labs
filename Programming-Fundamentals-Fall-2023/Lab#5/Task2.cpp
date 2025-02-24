#include<iostream>
#include<cstring>
using namespace std;
int lexicographical_comparison(char str1[], char str2[])
{
    return strcmp(str1, str2);
}
int main()
{
    char a[10], b[10];
    cout << "Enter First Word: ";
    cin >> a;
    cout << "Enter Second Word: ";
    cin >> b;
    int result = lexicographical_comparison(a, b);
    if (result == 0) 
    {
        cout << "Strings are equal." << endl;
    }     
    else if (result < 0)
    {
        cout << "String 1 " << a << " comes before String 2 " << b << endl;
    }
    else
    {
        cout << "String 2 " << b << " comes before String 1 " << a << endl;
    }
    return 0;
}
