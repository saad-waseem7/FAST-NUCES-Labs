#include <iostream>
using namespace std;

const int max_strings = 100;
const int max_length = 100;

int find_length(char array[][max_length], int rows) {
    int length = 0;
    while (array[rows][length] != '\0') {
        length++;
    }
    return length;
}

void rotate_string(char array[][max_length], int rows) {
    int length = find_length(array, rows);

    char temp = array[rows][length - 1];
    for (int j = length - 1; j > 0; j--) {
        array[rows][j] = array[rows][j - 1];
    }
    array[rows][0] = temp;
}

void print_array(char array[][max_length]) {

    for (int i = 0; array[i][0] != '\0'; i++) {
        cout << array[i] << endl;
    }
}

int main() {

    char data[max_strings][max_length] = { "Hello", "World", "Code" };

    cout << "Original Array: " << endl;
    print_array(data);

    for (int i = 0; data[i][0] != '\0'; i++) {
        rotate_string(data, i);
    }

    cout << "Rotated Array: " << endl;
    print_array(data);

    return 0;
}
