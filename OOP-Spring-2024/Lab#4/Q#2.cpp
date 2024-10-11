#include <iostream>
using namespace std;
void bubbleSort(int** arr, int rows, int cols) 
{
    int temp = 0;
	for (int i = 0; i < rows; i++) 
	{
        bool swapped = false;
        for (int j = 0; j < cols - 1; j++) 
		{
            if (*(*(arr + i) + j) > *(*(arr + i) + j + 1)) 
			{
				temp = (*(*(arr + i) + j));
				(*(*(arr + i) + j) = *(*(arr + i) + j + 1));
				*(*(arr + i) + j + 1) = temp;
                swapped = true;
            }
        }
        if (!swapped) 
		{
            break;
        }
    }
}
void printArray(int** arr, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{
            cout << *(*(arr + i) + j) << " ";
        }
        cout << endl;
    }
}
int main() {
    int rows, cols;
    cout << "Enter the number of rows: "<< endl;
	cin >> rows;
	cout << "Enter the number of columns: "<< endl;
    cin >> cols;

    int** arr = new int*[rows];
    for (int i = 0; i < rows; i++) 
	{
        arr[i] = new int[cols];
    }
	cout <<"Enter Elements in Matrix: "<<endl;
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{
            cin >> *(*(arr + i) + j);
        }
    }

    cout << "Original array:" << endl;
    printArray(arr, rows, cols);
    bubbleSort(arr, rows, cols);
    cout << "Sorted array:" << endl;
    printArray(arr, rows, cols);

    for (int i = 0; i < rows; i++) 
	{
        delete[] arr[i];
    }
    delete[] arr;
	system("pause");
    return 0;
}