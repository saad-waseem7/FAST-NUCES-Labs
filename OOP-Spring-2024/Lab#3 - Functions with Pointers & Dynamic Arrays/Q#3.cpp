#include <iostream>
using namespace std;

void OutputArray_reverse(int *myArray, const int &size)
{
    cout << "Entered Array is: ";
    for (int i = size; i > 0; i--)
    {
        cout << myArray[i] << " ";
    }
    cout << endl;
}
int *AllocateAndCopyArray(int *p, int &size)
{
    size *= 2;
    int *temp = new int[size];
    for (int i = 0; i < size - 2; i++)
    {
        temp[i] = p[i];
    }
    delete[] p;
    p = nullptr;
    return temp;
}
int main()
{
    int size = 4;
    int *arr = new int[size];
    int index = 0;
    int value;
    cout << "Input number: ";
    cin >> value;
    while (value != -1)
    {
        if (index < size)
        {
            *(arr + index) = value;
            index++;
        }
        else
        {
            cout << "Growing " << endl;
            arr = AllocateAndCopyArray(arr, size);
            arr[index] = value;
            index++;
        }
        cout << "Input number: ";
        cin >> value;
    }
    OutputArray_reverse(arr, size);
    delete[] arr;
    arr = nullptr;
}