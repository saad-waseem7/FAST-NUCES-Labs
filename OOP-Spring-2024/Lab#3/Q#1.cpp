#include <iostream>
using namespace std;

void PrintArray(int *arr, int size)
{
    cout << "Array: ";
    for (int i = 0; i < size; i++)
    {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int *InputArray(int &size)
{
    cout << "Enter the size of the array: ";
    cin >> size;
    int *arr = new int[size];
    cout << "Enter " << size << " integers:\n";
    for (int i = 0; i < size; i++)
    {
        cin >> *(arr + i);
    }
    return arr;
}

int main()
{
    int size;
    int *arr = InputArray(size);
    PrintArray(arr, size);
    delete[] arr;
    return 0;
}