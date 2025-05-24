#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    float *arr = new float[size];

    cout << "Enter Elements in Array: " << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << "Enter element " << i + 1 << " : ";
        cin >> *(arr + i);
    }

    float max = arr[0], secondMax = arr[0];
    int maxIndex = 0, secondMaxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            secondMax = max;
            secondMaxIndex = maxIndex;
            max = arr[i];
            maxIndex = i;
        }
        else if (arr[i] > secondMax && arr[i] != max)
        {
            secondMax = arr[i];
            secondMaxIndex = i;
        }
    }

    cout << "Index of the second largest element: ";
    cout << secondMaxIndex + 1 << endl;
    cout << "Value of the second largest element: ";
    cout << secondMax << endl;

    delete[] arr;

    return 0;
}