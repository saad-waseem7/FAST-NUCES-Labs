#include <iostream>
using namespace std;
int main() {
    int number, originalNumber, remainder, sum = 0;
    cout << "Enter a number: ";
    cin >> number;
    originalNumber = number;
    while (number > 0) {
        remainder = number % 10;
        sum += remainder * remainder * remainder;
        number = number / 10;
    }
    if (sum == originalNumber) {
        cout << "The number " << originalNumber << " is an Armstrong number." << endl;
    }
    else {
        cout << "The number " << originalNumber << " is not an Armstrong number." << endl;
    }
    return 0;
}
