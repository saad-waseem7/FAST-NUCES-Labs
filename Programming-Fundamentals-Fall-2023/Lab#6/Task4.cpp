#include <iostream>
using namespace std;
void Upper_half(int A[][10], int N) 
{
    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < N; ++j)
        {
            if (j >= i)
            {
                cout << A[i][j] << "  ";
            }
            else 
            {
                cout << "   ";
            }
        }
        cout << endl;
    }
}
int main() {
    int N;
    int A[10][10];
    cout << "Enter the size of the square matrix: ";
    cin >> N;
    if (N <= 0 || N > 10) {
        cout << "Invalid Entry." << endl;
        return 1;
    }
    cout << "Enter elements for matrix:" << endl;
    for (int i = 0; i < N; ++i) 
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> A[i][j]; 
        }
      
    }
    cout << "Upper half of the matrix:" << endl;
    Upper_half(A, N);
    return 0;
}
