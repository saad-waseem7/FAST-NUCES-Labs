#include <iostream>
using namespace std;
int main()
{
    int a, b;
    int sum = 0;

    cout << "Enter First Number: ";
    cin >> a;
    cout << "Enter Second Number: ";
    cin >> b;
    int *ptr_a = &a;
    int *ptr_b = &b;

    cout << "Values using dereference operator: " << endl;
    cout << *ptr_a << endl;
    cout << *ptr_b << endl;
    cout << "Addresses using address-of operator: " << endl
         << ptr_a << endl
         << ptr_b << endl;
    sum = *ptr_a + *ptr_b;

    cout << "Sum is: " << sum << endl;

    return 0;
}