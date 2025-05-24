#include <iostream>
using namespace std;
void printArray(int **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << *(*(arr + i) + j) << " ";
        }
        cout << endl;
    }
}
int sumOfArray(int **arr, int rows, int cols)
{
    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum = sum + *(*(arr + i) + j);
        }
    }
    return sum;
}
int main()
{
    int rows, cols;
    cout << "Enter the number of rows: " << endl;
    cin >> rows;
    cout << "Enter the number of columns: " << endl;
    cin >> cols;

    int **arr = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        arr[i] = new int[cols];
    }

    cout << "Enter the values in the array:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> *(*(arr + i) + j);
        }
    }
    cout << "The array is: " << endl;
    printArray(arr, rows, cols);

    int sum = sumOfArray(arr, rows, cols);
    cout << "The sum of all the elements in the array is: ";
    cout << sum << endl;

    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    system("pause");
    return 0;
}