#include<iostream>
using namespace std;
const int rows = 3;
const int cols = 4;

int searchGrid(char grid[rows][cols], char find) {
	int count = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == find) {
				count++;
			}
		}
	}
	return count;
}

int main() {
	char grid[rows][cols] = { 
		{'A', 'B', 'C', 'D'},
	    {'E', 'F', 'G', 'H'},
	    {'I', 'J', 'K', 'L'} 
	};
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << grid[i][j] << '\t';
		}
		cout << endl;
	}
	
	char find;
	cout << "Enter Alphabet to find: ";
	cin >> find;
	int count = searchGrid(grid, find);
	cout << "The character " << find << " appears " << count << " times in the grid." << endl;
	return 0;
}