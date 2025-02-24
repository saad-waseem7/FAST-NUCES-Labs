#include<iostream>
using namespace std;
int main() 
{
    int i = 1;
    for (i = 1; i <= 50; i++) 
    {
        cout << "*";
    }
    cout << endl;
    for (i = 1; i <= 9; i++) 
    {
        for (int j = 1; j <= 50; j++) 
        {
            if (j == 1) 
            {
                cout << "=";
            }
            else 
            {
                cout << " ";
            }
            if (j == 50) {
                cout << "=";
            }
        }
        cout << endl;
    }
    for (i = 1; i <= 50; i++) {
        cout << "*";
    }
    cout << endl;
    return 0;
}
