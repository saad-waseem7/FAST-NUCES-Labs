#include <iostream>
#include <fstream>
using namespace std;
const int rows = 4;
const int cols = 4;

void printMatrix(int matrix[rows][cols], const char* label) {
    cout << label << " Matrix:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int originalMatrix[rows][cols];
    ifstream inputFile("Data.txt");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inputFile >> originalMatrix[i][j];
        }
    }
    inputFile.close();
    printMatrix(originalMatrix, "Original");
    int transposedMatrix[cols][rows];
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            transposedMatrix[i][j] = originalMatrix[j][i];
        }
    }
    ofstream outputFile("Data.txt");
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            outputFile << transposedMatrix[i][j] << ' ';
        }
        outputFile << endl;
    }
    outputFile.close();
    printMatrix(transposedMatrix, "Transposed");

    return 0;
}
