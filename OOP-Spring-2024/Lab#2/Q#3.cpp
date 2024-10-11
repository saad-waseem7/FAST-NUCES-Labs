#include <iostream>
using namespace std;

void take_input_array(int data[], int size = 5)
{
    cout << "Enter Elements in Array: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Enter element " << i + 1 << " : ";
        cin >> data[i];
    }
}

int large(const int *arr, int size)
{
    int largest = *arr;
    for (const int *ptr = arr + 1; ptr < arr + size; ++ptr)
    {
        if (*ptr > largest)
        {
            largest = *ptr;
        }
    }
    return largest;
}

int main()
{
    const int size = 5;
    int arr[size] = {};
    take_input_array(arr);
    int largest = large(arr, size);
    cout << "The largest number in the array is: " << largest << endl;
    return 0;
}