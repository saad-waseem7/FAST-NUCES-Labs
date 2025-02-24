#include <iostream>
using namespace std;
void moveToEnd(int data[], int size) 
{
    int j = 0;
    for (int i = 0; i < size; i++) 
    {
        if (data[i] != 0) 
        {
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            j++;
        }
    }
}
int main() 
{
    const int size=5;
    int data[size];
    cout << "Enter the elements of the array: " << endl;
    for (int i = 0; i < size; i++) 
    {
        cin >> data[i];
    }
    moveToEnd(data, size);
    cout << "New Array is : ";
    for (int i = 0; i < size; i++) 
    {
        cout << data[i] << " ";
    }
    cout << endl;
    return 0;
}
