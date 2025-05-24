#include <iostream>
using namespace std;

const int Modulo = 1e9 + 7;

long Good_Digit(int n, int k)
{
    if (n == 0)
    {
        return 1;
    }
    if (k % 2 == 0)
    {
        return (5 * Good_Digit(n - 1, k + 1)) % Modulo;
    }
    else
    {
        return (4 * Good_Digit(n - 1, k + 1)) % Modulo;
    }
}
long Final_Func(int n)
{
    return Good_Digit(n, 0);
}

int main()
{

    cout << Final_Func(1) << endl;
    cout << Final_Func(4) << endl;
    cout << Final_Func(50) << endl;

    return 0;
}