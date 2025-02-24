#include <iostream>
using namespace std;
int main() {
    int n = 7;
    int data[7] = { 4, 7, 8, 5, 3, 6, 4 };
    int temp;
    char prnt;
   
    for (int i = 0; i < n / 2; i++) 
    {
        temp = data[i];
        data[i] = data[n - i - 1];
        data[n - i - 1] = temp;
    }

    cout << "Array has been stored in reverse." << endl;
    cout << "Press 'R' to show the reversed array: ";
    cin >> prnt;

    if (prnt == 'r' || prnt == 'R') 
    {
        for (int i = 0; i < n; i++) 
        {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    else 
    {
        cout << "Invalid input. Please press 'R' to show the reversed array." << endl;
    }

    return 0;
}
