#include <iostream>
using namespace std;

void fibonacci(int *arr, int n)
{
    arr[0] = 1;
    arr[1] = 1;
    for (int i = 2; i < n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
}

int main()
{
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    int *fib_arr = new int[n];
    fibonacci(fib_arr, n);

    cout << "Fibonacci Sequence numbers: ";
    for (int i = 0; i < n; ++i)
    {
        cout << fib_arr[i] << " ";
    }
    cout << endl;
    delete[] fib_arr;

    return 0;
}