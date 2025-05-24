#include <iostream>
using namespace std;
int main()
{

    int num1 = 5, num2 = 7, sum = 0;
    int *xPtr = nullptr, *yPtr = nullptr, *sumPtr = nullptr;

    cout << "Num1 = " << num1 << endl;
    cout << "Num2 = " << num2 << endl;

    cout << "Address of Num1 = " << &num1 << endl;
    cout << "Address of Num2 = " << &num2 << endl;
    xPtr = &num1;
    yPtr = &num2;

    cout << "*xPtr = " << *xPtr << endl;
    cout << "*yPtr = " << *yPtr << endl;

    sumPtr = &sum;
    cout << "*sumPtr = " << *sumPtr << endl;
    *sumPtr = *xPtr + *yPtr;
    cout << "*sumPtr = " << *sumPtr << endl;

    cout << "xPtr = " << xPtr << endl;
    cout << "yPtr = " << yPtr << endl;

    return 0;
}