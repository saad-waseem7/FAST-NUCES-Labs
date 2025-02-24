#include <iostream>
using namespace std;

int main() {
    char choice;

    do {
        int number;
        int factorial = 1;

        cout << "Enter a number to calculate its factorial: ";
        cin >> number;

        for (int x = 1; x <= number; x++) {
            factorial *= x;
        }

        cout << "The factorial of " << number << " is: " << factorial << '\n';
        cout << "Do you want to calculate another factorial? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    return 0;
}
