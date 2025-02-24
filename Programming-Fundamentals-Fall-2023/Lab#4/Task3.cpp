#include <iostream>
using namespace std;
void oddsum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 2 != 0) {
            sum += i;
        }
    }
    cout << "The Sum of odd Natural Numbers: " << sum << endl;
}
int main() {
    int n;
    cout << "Enter number of terms: ";
    cin >> n;
    oddsum(n);
    return 0;
}
