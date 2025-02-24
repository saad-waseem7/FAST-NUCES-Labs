#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int x = 1;
    while (x <= 25) {
        cout << "Square root of " << x << " is: " << sqrt(x) << endl;
        x += 2;
    }
    return 0;
}
