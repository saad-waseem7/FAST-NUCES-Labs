// The time complexity for the rotation operation O(n).

#include <iostream>
using namespace std;

void reverseArray(int arr[], int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotateArray(int arr[], int n, int position)
{
    position = position % n;
    if (position == 0)
        return;
    reverseArray(arr, 0, n - 1);
    reverseArray(arr, 0, position - 1);
    reverseArray(arr, position, n - 1);
}

void displayArray(const int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    const int n = 7;
    int arr[n] = {1, 2, 3, 4, 5, 6, 7};
    int position = 2;

    cout << "Original array: ";
    displayArray(arr, n);

    rotateArray(arr, n, position);
    cout << "Array after rotation: ";
    displayArray(arr, n);

    return 0;
}
