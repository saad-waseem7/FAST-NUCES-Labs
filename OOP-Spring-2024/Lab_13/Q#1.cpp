#include <iostream>
using namespace std;

int main()
{
    char choice;
    cout << "Enter 'i' for integer exception" << endl;
    cout << "Enter 'd' for double exception, or any other character for unknown exception: " << endl;
    cin >> choice;

    try
    {
        switch (choice)
        {
        case 'i':
        {
            int value;
            cout << "Enter an integer value: ";
            cin >> value;
            if (cin.fail())
            {
                throw "Invalid input: not an integer.";
            }
            throw value;
        }
        case 'd':
        {
            double value;
            cout << "Enter a double value: ";
            cin >> value;
            if (cin.fail())
            {
                throw "Invalid input: not a double.";
            }
            throw value;
        }
        default:
            throw "Unknown exception.";
        }
    }
    catch (int value)
    {
        cout << "Caught an integer exception. Value: " << value << endl;
    }
    catch (double value)
    {
        cout << "Caught a double exception. Value: " << value << endl;
    }
    catch (...)
    {
        cout << "Caught an unknown exception." << endl;
    }

    return 0;
}
