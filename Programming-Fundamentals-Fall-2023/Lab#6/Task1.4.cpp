#include <iostream>
using namespace std;
void takeTranspose(int matrix[][5], const int rows, const int columns)
{
    int transposeMatrix[5][5];
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            transposeMatrix[i][j] = matrix[j][i];
        }
    }
    cout << "Transpose of the matrix:" << endl;
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            cout << transposeMatrix[i][j] << "  ";
        }
        cout << endl;
    }
}
int main()
{
    const int rows = 5;
    const int columns = 5;
    int arr[rows][columns];
    cout << "Enter elements of matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cin >> arr[i][j];
        }
    }
    cout << "Original Matrix is: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << arr[i][j] << "  ";
            if (j == columns - 1)
                cout << endl;
        }
    }
    takeTranspose(arr, rows, columns);
    return 0;
}
