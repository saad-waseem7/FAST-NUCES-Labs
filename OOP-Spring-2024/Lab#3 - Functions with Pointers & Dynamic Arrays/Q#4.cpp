#include <iostream>
using namespace std;

int sumArray(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += *(arr + i);
    }
    return sum;
}
int main()
{
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int *arr = new int[size];
    cout << "Enter " << size << " elements: " << endl;
    for (int i = 0; i < size; ++i)
    {
        cin >> *(arr + i);
    }
    int sum = sumArray(arr, size);
    cout << "Sum of array elements: " << endl;
    cout << sum;
    delete[] arr;
    return 0;
}