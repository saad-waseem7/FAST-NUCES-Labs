#include <iostream>
using namespace std;
int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;
    while (number > 0) {
        int digit = number % 10;
        cout << digit << endl;
        number = number / 10;
    }
    return 0;
}
