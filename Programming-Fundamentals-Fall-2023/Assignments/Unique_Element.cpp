#include <iostream>
using namespace std;

int main()
{
    int size = 10;
    int *data = new int[size];

    cout << "Enter 10 elements of the array: " << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << "Enter " << i + 1 << " Number: ";
        cin >> data[i];
    }

    int flag = 0;
    for (int i = 0; i < size - 1; ++i)
    {
        flag = 0;
        for (int j = i + 1; j < size; ++j)
        {
            if (data[i] == data[j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
    if (flag == 0)
    {
        cout << "The array has unique elements.";
    }
    else
    {
        cout << "The array does not have unique elements.";
    }

    delete[] data;
    return 0;
}