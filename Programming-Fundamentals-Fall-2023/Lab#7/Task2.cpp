#include <iostream>
using namespace std;
int main() {
	char strings[3][100] = { "Hello", "Gun", "Tom" };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 100; j++) {
			cout << strings[i][j];
		}
		cout << endl;
	}
	int srcindex, destindex;
	cout << "Enter the number of the string to copy (0-2): ";
	cin >> srcindex;
	cout << "Enter the index of the string to overwrite (0-2): ";
	cin >> destindex;
	char selectedString[100];
	strcpy(selectedString, strings[srcindex]);
	strcpy(strings[destindex], selectedString);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 100; j++) {
			cout << strings[i][j];
		}
		cout << endl;
	}
	return 0;
}

