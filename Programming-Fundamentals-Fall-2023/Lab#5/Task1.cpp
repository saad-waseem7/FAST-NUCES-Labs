#include<iostream>
using namespace std;
void concatenateStrings(char con_arrays[], char str1[], char str2[])
{
    int k = 0;
    for (int i = 0; str1[i] != '\0'; i++, k++)
    {
        con_arrays[k] = str1[i];
    }
    con_arrays[k] = ' ';
    k++;
    for (int i = 0; str2[i] != '\0'; i++, k++)
    {
        con_arrays[k] = str2[i];
    }
    con_arrays[k] = '\0';
    cout << "After Concatenation: " << endl << con_arrays << endl;
}
int main()
{
    char a[20], b[5], c[5];
    cout << "Enter First Word: ";
    cin >> b;
    cout << "Enter Second Word: ";
    cin >> c;
    concatenateStrings(a, b, c);
    return 0;
}
