#include<iostream>
using namespace std;
int sum_before(int data[], int index) 
{
    int sum = 0;
    for (int i = 0; i < index; i++) 
    {
        sum += data[i];
    }
    return sum;
}
int sum_after(int data[], int index, int size) 
{
    int sum = 0;
    for (int i = index + 1; i < size; i++) 
    {
        sum += data[i];
    }
    return sum;
}
int equilibrium_index(int data[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        int sum1, sum2;       
        sum1 = sum_before(data, i);
        sum2 = sum_after(data, i, size);
        if (sum1 == sum2)
        {
            return i;
        }
    }
    return 0;
}
int main() 
{
    int result = 0;
    const int size = 7;
    int data[size];
    cout << "Enter Data of Array: " << endl;
    for (int k = 0; k < size; k++) 
    {
        cout << "Enter Number: ";
        cin >> data[k];
    }
    result = equilibrium_index(data, size);
    if (result == 0) 
    {
        cout << "No Equilibrium Index Found" << endl;
    }
    else 
    {
        cout << "Equilibrium Index is: " << result << endl;
    }
    return 0;
}