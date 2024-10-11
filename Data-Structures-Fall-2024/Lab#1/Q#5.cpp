/*
The overall time complexity of the is_prime function is O(√n).
This is because the function performs a constant-time check for cases and then iterates up to the square root of the input number to check for factors.
*/

#include <iostream>
using namespace std;

bool is_prime(int num)
{
    if (num <= 1)
        return false;
    if (num == 2)
        return true;
    if (num % 2 == 0)
        return false;

    for (int i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

int largest_prime(int data[], int size)
{
    int max = -1;
    for (int i = 0; i < size; i++)
    {
        if (is_prime(data[i]) && data[i] > max)
        {
            max = data[i];
        }
    }
    return max;
}

int main()
{
    int data[] = {6, 8, 13, 15, 17, 3, 21};
    int size = sizeof(data) / sizeof(data[0]);
    int result = largest_prime(data, size);
    if (result == -1)
    {
        cout << "No prime numbers found in the array." << endl;
    }
    else
    {
        cout << "Largest prime number in the array: " << result << endl;
    }

    return 0;
}
