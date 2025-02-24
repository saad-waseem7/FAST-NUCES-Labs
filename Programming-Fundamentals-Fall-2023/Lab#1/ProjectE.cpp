#include <iostream>
using namespace std;

int main() {
    int x;
    cout << "Ente your marks: " << endl;
    cin >> x;

    if (x >= 90 && x <= 100) {
        cout << "Congratulations!! A Grade." << endl;
    }
    else if (x >= 80 && x <= 89) {
        cout << "B Grade." << endl;
    }
    else if (x >= 70 && x <= 79) {
        cout << "C Grade." << endl;
    }
    else if (x >= 60 && x <= 69) {
        cout << "D Grade." << endl;
    }
    else {
        cout << "F Grade." << endl;
    }

    return 0;
}
