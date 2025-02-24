#include <iostream>
using namespace std;

int main() {
    int data[5], max, min, second_largest;
    for (int i = 0; i < 5; i++) 
    {
        cout << "Enter Number: ";
        cin >> data[i];
    }

    max = data[0];
    min = data[0];
    second_largest = data[1];

    for (int i = 1; i < 5; i++) 
    {
        if (data[i] > max) 
        {
            second_largest = max;
            max = data[i];
        }
        else if (data[i] > second_largest && data[i] != max) 
        {
            second_largest = data[i];
        }

        if (data[i] < min) {
            min = data[i];
        }
    }

    cout << "Max is: " << max << endl;
    cout << "Min is: " << min << endl;
    cout << "Second largest is: " << second_largest << endl;

    // Checking for ascending, descending, or random sequence
    bool ascending = true, descending = true;
    for (int i = 0; i < 4; i++) {
        if (data[i] > data[i + 1]) 
        {
            ascending = false;
        }
        if (data[i] < data[i + 1]) {
            descending = false;
        }
    }

    if (ascending) 
    {
        cout << "Ascending" << endl;
    }
    else if (descending) 
    {
        cout << "Descending" << endl;
    }
    else 
    {
        cout << "Random Numbers" << endl;
    }

    return 0;
}
