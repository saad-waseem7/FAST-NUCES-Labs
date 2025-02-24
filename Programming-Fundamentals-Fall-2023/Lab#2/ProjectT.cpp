#include <iostream>
using namespace std;

int main() {
    int num1, num2;

    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;
    num1 = abs(num1);
    num2 = abs(num2);
    int gcd = 1;
    int divisor = 2;
    while (divisor <= num1 && divisor <= num2) {
        if (num1 % divisor == 0 && num2 % divisor == 0) {
            gcd = divisor;
        }
        divisor++;
    }
    cout << "The GCD (HCF) of " << num1 << " and " << num2 << " is: " << gcd << endl;
    return 0;
}
