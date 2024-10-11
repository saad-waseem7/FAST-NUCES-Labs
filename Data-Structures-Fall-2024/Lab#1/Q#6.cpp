/*
Each operation (creation, insertion, transpose, addition, and print) operates with a complexity of O(r * c),
where r is the number of rows and c is the number of columns.
The overall time complexity is O(r * c), where r is the number of rows and c is the number of columns.
*/

#include <iostream>
using namespace std;

template <typename T>
class Matrix
{
private:
    T **matrix;
    int rows, columns;

    void allocateMemory()
    {
        matrix = new T *[rows];
        for (int i = 0; i < rows; ++i)
        {
            matrix[i] = new T[columns]();
        }
    }

    void deallocateMemory()
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

public:
    Matrix(int r, int c) : rows(r), columns(c)
    {
        allocateMemory();
    }

    Matrix(const Matrix &k) : rows(k.rows), columns(k.columns)
    {
        allocateMemory();
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                matrix[i][j] = k.matrix[i][j];
            }
        }
    }

    ~Matrix()
    {
        deallocateMemory();
    }

    void insertElement(T element, int rowNo, int colNo)
    {
        if (rowNo >= 0 && rowNo < rows && colNo >= 0 && colNo < columns)
        {
            matrix[rowNo][colNo] = element;
        }
        else
        {
            cout << "Index out of bounds." << endl;
        }
    }

    Matrix operator+(const Matrix &k)
    {
        if (rows != k.rows || columns != k.columns)
        {
            cout << "Error: Matrices dimensions mismatch." << endl;
            return Matrix(0, 0);
        }

        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                result.matrix[i][j] = matrix[i][j] + k.matrix[i][j];
            }
        }
        return result;
    }

    void print() const
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void transpose()
    {
        T **transposed = new T *[columns];
        for (int i = 0; i < columns; ++i)
        {
            transposed[i] = new T[rows];
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                transposed[j][i] = matrix[i][j];
            }
        }

        deallocateMemory();
        swap(rows, columns);
        matrix = transposed;
    }
};

int main()
{
    Matrix<int> m1(2, 3);
    m1.insertElement(1, 0, 0);
    m1.insertElement(1, 0, 1);
    m1.insertElement(1, 0, 2);
    m1.insertElement(0, 1, 0);
    m1.insertElement(0, 1, 1);
    m1.insertElement(0, 1, 2);
    cout << "Matrix m1:" << endl;
    m1.print();

    m1.transpose();
    cout << "Transposed m1:" << endl;
    m1.print();

    Matrix<int> m2(2, 3);
    m2.insertElement(-1, 0, 0);
    m2.insertElement(-1, 0, 1);
    m2.insertElement(-1, 0, 2);
    m2.insertElement(10, 1, 0);
    m2.insertElement(5, 1, 1);
    m2.insertElement(1, 1, 2);
    cout << "Matrix m2:" << endl;
    m2.print();

    m2.transpose();
    cout << "Transposed m2:" << endl;
    m2.print();

    Matrix<int> m3(m2);

    Matrix<int> m4 = m1 + m3;
    cout << "Matrix m4 (m1 + m3):" << endl;
    m4.print();

    m4.transpose();
    cout << "Transposed m4:" << endl;
    m4.print();

    return 0;
}
