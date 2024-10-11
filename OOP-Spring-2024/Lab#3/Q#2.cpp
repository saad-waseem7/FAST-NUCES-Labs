#include <iostream>
using namespace std;

void OutputArray(int *myArray, const int &size)
{
    cout << "Entered Array is: ";
    for (int i = 0; i < size; i++)
    {
        cout << *(myArray + i) << " ";
    }
    cout << endl;
}

int main()
{
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int *arr = new int[size];
    cout << "Enter " << size << " integers:\n";
    for (int i = 0; i < size; i++)
    {
        cin >> *(arr + i);
    }
    OutputArray(arr, size);
    delete[] arr;
    return 0;
}