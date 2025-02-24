#include <iostream>
#include <fstream>
using namespace std;
void compareAndWriteUnique(const char* file1, const char* file2) {
    const int rows = 6;
    const int cols = 6;
    char arryR1[rows][cols];
    char arryR2[rows][cols];

    ifstream input1(file1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            input1 >> arryR1[i][j];
        }
    }

    input1.close();

    ifstream input2(file2);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            input2 >> arryR2[i][j];
        }
    }

    input2.close();

    ofstream output("Output.txt");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (arryR1[i][j] != arryR2[i][j]) {
                output << arryR1[i][j] << ' ';
                output << arryR2[i][j] << ' ';
            }
        }
    }

    output << endl;
    output.close();
}

int main() {
    compareAndWriteUnique("record1.txt", "record2.txt");

    return 0;
}
