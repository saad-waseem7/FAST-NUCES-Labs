#include <iostream>
using namespace std;
int main()
{
    const int size = 5;
    int arr[size] = {5, 8, 3, 9, 2};
    // cout << arr << endl;
    for (int *ptr = arr; ptr < arr + 5; ++ptr)
    {
        cout << *ptr << " ";
    }
    return 0;
}