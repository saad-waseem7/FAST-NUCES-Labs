#include <iostream>
using namespace std;

int main() {
    int day, time;
    cout << "Choose the day of the Week: " << endl;
    cout << '\n';
    cout << "1.Monday" << endl;
    cout << "2.Tuesday" << endl;
    cout << "3.Wednesday" << endl;
    cout << "4.Thursday" << endl;
    cout << "5.Friday" << endl;
    cout << "6.Saturday" << endl;
    cout << "7.Sunday" << endl;
    cout << '\n';
    cout << "Enter Number Corresponding To Selected Day: " << endl;
    cin >> day;

    cout << "Enter the time in 24-hour format: ";
    cin >> time;

    if (day >= 1 && day <= 5 && time >= 9 && time < 21) {
        cout << "The store is open." << endl;
    }
    else {
        cout << "The store is closed." << endl;
    }

    return 0;
}
