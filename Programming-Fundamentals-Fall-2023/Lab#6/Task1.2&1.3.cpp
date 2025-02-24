#include <iostream>
using namespace std;
void take_input(int matrix[][5], const int row, const int col)
{
    cout << "Enter matrix elements:" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }
}
void print_matrix(int matrix[][5], const int row, const int col)
{
    cout << "Matrix elements are:" << endl;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}
int main()
{
    const int row = 5;
    const int col = 5;
    int matrix[5][5];
    take_input(matrix, row, col);
    print_matrix(matrix, row, col);
    return 0;
}
