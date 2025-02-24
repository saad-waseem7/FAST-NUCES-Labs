#include<iostream>
using namespace std;
int main()
{
	int arr[5][5];
    int val = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            arr[i][j] = val++;
        }
    }
    cout << "Initialized 2D array is:" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << arr[i][j] << "  ";
        }
        cout << endl;
    }
    return 0;
}