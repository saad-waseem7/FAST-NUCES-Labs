#include <iostream>
using namespace std;
const int max_index= 10;
void matrixMultiplication(int A[][max_index], int B[][max_index], int result[][max_index], int N, int L, int M) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < L; k++)
                result[i][j] += A[i][k] * B[k][j];
}
void displayMatrix(int matrix[][max_index], int rows, int columns) 
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}
int main() 
{
    int A[max_index][max_index] = { 0 };
    int B[max_index][max_index] = { 0 };
    int result[max_index][max_index] = { 0 };
    int N, L, M;
    cout << "Enter dimensions for matrix A: " << endl;
    cin >> N;
    cout << "X" << endl;
    cin >> L;
    if (L <= 0 || N <= 0 || L > max_index) {
        cout << "Invalid entry for matrix multiplication." << endl;
        return 1;
    }
    cout << "Enter dimensions for matrix B: " << endl;
    cin >> L;
    cout << "X" << endl;
    cin >> M;
    if (M <= 0 || M > max_index) {
        cout << "Invalid entry for matrix multiplication." << endl;
        return 1;
    }
    cout << "Enter elements for matrix A:" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < L; j++)
            cin >> A[i][j];
    cout << "Enter elements for matrix B:" << endl;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < M; j++)
            cin >> B[i][j];

    matrixMultiplication(A, B, result, N, L, M);
    cout << "Matrix A:" << endl;
    displayMatrix(A, N, L);
    cout << "Matrix B:" << endl;
    displayMatrix(B, L, M);
    cout << "Result of Matrix Multiplication (A x B) is:" << endl;
    displayMatrix(result, N, M);
    return 0;
}
