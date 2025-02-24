#include <iostream>
using namespace std;
int main() {
    int x = 3;
    int product = 1;

    while (x <= 19) {
        product *= x;
        x += 2;
    }
    cout << "The product of the odd integers from 3 to 19 is: " << product << endl;
    return 0;
}
