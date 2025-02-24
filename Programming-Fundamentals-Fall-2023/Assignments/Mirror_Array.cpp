#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Enter Size of an Array: " << endl;
    cin >> size;
    int *data = new int[size];
    cout << "Enter " << size << " elements of the array: " << endl;
    for (int i = 0; i < size; ++i)
    {
        cin >> data[i];
    }
    int start = 0;
    int end = size - 1;
    int mirror = 1;

    while (start < end)
    {
        if (data[start] != data[end])
        {
            mirror = 0;
            break;
        }
        start++;
        end--;
    }

    if (mirror == 1)
    {
        cout << "Mirror Array";
    }
    else
    {
        if (size % 2 == 1 && start == end)
        {
            cout << "Mirror Array";
        }
        else
        {
            cout << "It is Not Mirror Array";
        }
    }
    delete[] data;
    return 0;
}