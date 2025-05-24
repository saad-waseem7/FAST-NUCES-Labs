#include <iostream>
using namespace std;
int main()
{
    int num;
    cout << "Enter a Number: ";
    cin >> num;

    int *ptr = &num;
    // cout << *ptr << endl;
    cout << "Square of Number: " << (*ptr) * (*ptr) << endl;
    cout << "Cube of Number: " << (*ptr) * (*ptr) * (*ptr) << endl;
    cout << "Half of Number: " << (*ptr) / 2 << endl;

    return 0;
}