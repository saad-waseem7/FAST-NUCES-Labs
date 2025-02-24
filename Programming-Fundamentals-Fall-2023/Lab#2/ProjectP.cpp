#include <iostream>
using namespace std;
int main() {
    int x = 2;
    int sum = 0;

    while (x <= 30) {
        if (x % 2 == 0) {
            sum += x;
        }
        x++;
    }
    cout << "The sum of the even integers from 2 to 30 is: " << sum << endl;
    return 0;
}
