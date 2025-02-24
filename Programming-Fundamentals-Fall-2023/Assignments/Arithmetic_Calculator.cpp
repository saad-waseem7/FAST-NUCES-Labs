#include <iostream>
using namespace std;

int getValidNumber()
{
    int num;
    while (true)
    {
        cout << "Enter a number between -99 and 999: ";
        cin >> num;
        if (cin.fail() || num < -99 || num > 9999)
        {
            cout << "Invalid input. Please try again." << endl;
            cin.clear();
            cin.ignore();
        }
        else
        {
            break;
        }
    }
    return num;
}

char getValidOperation()
{
    char op;
    cout << "Select an operation (+, -, *, /): ";
    while (true)
    {
        cin >> op;
        if (op == '+' || op == '-' || op == '*' || op == '/')
        {
            break;
        }
        else
        {
            cout << "Invalid operation. Please try again." << endl;
        }
    }
    return op;
}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    if (b == 0)
    {
        cout << "Cannot divide by zero!" << endl;
        return 0;
    }
    return a / b;
}

int main()
{
    int n, k;
    cout << "Enter First Number: " << endl;
    n = getValidNumber();
    cout << "Enter Second Number: " << endl;
    k = getValidNumber();

    char op = getValidOperation();

    if (op == '+')
    {
        cout << "The Sum is: " << add(n, k) << endl;
    }
    else if (op == '-')
    {
        cout << "The Difference is: " << subtract(n, k) << endl;
    }
    else if (op == '*')
    {
        cout << "The Product is: " << multiply(n, k) << endl;
    }
    else if (op == '/')
    {
        cout << "The Division is: " << divide(n, k) << endl;
    }
    else
    {
        cout << "Invalid operation!" << endl;
    }
    return 0;
}