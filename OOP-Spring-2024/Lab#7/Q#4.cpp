#include <iostream>
using namespace std;

class Matrix
{
private:
    int rows;
    int cols;
    int **data;

public:
    Matrix(int r, int c);
    ~Matrix();
    int &operator()(int row, int col);
    Matrix operator*(Matrix &temp);
    int getRows();
    int getCols();
};

Matrix::Matrix(int r, int c)
{
    rows = r;
    cols = c;
    data = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        *(data + i) = new int[cols]();
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] *(data + i);
    }
    delete[] data;
}

int &Matrix::operator()(int row, int col)
{
    return *(*(data + row) + col);
}

Matrix Matrix::operator*(Matrix &temp)
{
    Matrix result(rows, temp.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < temp.cols; j++)
        {
            int sum = 0;
            for (int k = 0; k < cols; k++)
            {
                sum += (*this)(i, k) * temp.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

int Matrix::getRows()
{
    return rows;
}

int Matrix::getCols()
{
    return cols;
}

int main()
{
    Matrix A(2, 3);
    Matrix B(3, 2);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            A(i, j) = i + j;
        }
    }
    cout << endl;
    cout << "Matrix A: " << endl;
    for (int i = 0; i < A.getRows(); i++)
    {
        for (int j = 0; j < A.getCols(); j++)
        {
            cout << A(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            B(i, j) = i * j;
        }
    }
    cout << endl;
    cout << "Matrix B: " << endl;
    for (int i = 0; i < B.getRows(); i++)
    {
        for (int j = 0; j < B.getCols(); j++)
        {
            cout << B(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "After Multiplication: " << endl;
    Matrix C = A * B;

    for (int i = 0; i < C.getRows(); i++)
    {
        for (int j = 0; j < C.getCols(); j++)
        {
            cout << C(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}