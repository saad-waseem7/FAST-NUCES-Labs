#include <iostream>
using namespace std;

void take_input(char matA[][100], int rows, int columns)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> matA[i][j];
        }
    }
}

void sort_row(char matB[][100], int row, int length) {
    char temp;
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (matB[row][i] > matB[row][j]) {
                temp = matB[row][i];
                matB[row][i] = matB[row][j];
                matB[row][j] = temp;
            }
        }
    }
}

void print_mat(char matC[][100], int rows, int columns)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matC[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char arr[100][100];
    int rows, columns;

    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> columns;
    take_input(arr, rows, columns);

    for (int i = 0; i < rows; i++) {
        sort_row(arr, i, columns);
    }

    cout << "The sorted matrix is:" << endl;
    print_mat(arr, rows, columns);
    return 0;
}
