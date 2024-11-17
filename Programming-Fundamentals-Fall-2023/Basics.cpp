#include <iostream>
#include <cstring>
using namespace std;

// This file contains some basic functions...

/*

//Array Sort and Insertion of One Entry (Basic Way: can overwrite last entry)

void sort_array(int arr[],int size=5)
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4 - j; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
            }
        }
    }
}
void print_array(int arr[],int size=5)
{
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main()
{
    int data[5] = {3, 2, 1, 5, 7};
    cout << "\nOriginal Array: ";
    print_array(data);
    sort_array(data);
    cout << "Sorted Array (Ascending Order): ";
    print_array(data);
    cout<<"Enter a Number to Enter in Array"<<endl;
    int num = 0;
    cin >> num;
    data[4] = num;
    //print_array(data);
    sort_array(data);
    print_array(data);
    return 0;
}

*/

/*

//Array Reversal

void reverseArray(int arr[], int size)
{
    for (int i = 0; i < size / 2; ++i)
    {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

int main()
{
    const int size = 5;
    int myArray[size] = {1, 2, 3, 4, 5};

    cout << "Original Array: ";
    for (int i = 0; i < size; ++i)
    {
        cout << myArray[i] << " ";
    }
    reverseArray(myArray, size);
    cout << "\nReversed Array: ";
    for (int i = 0; i < size; ++i)
    {
        cout << myArray[i] << " ";
    }

    return 0;
}

*/

/*

//Prime Number Checker

bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i <= num / 2; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int main() {
    int num;
    cout << "Enter a number: ";
    cin >> num;

    if (isPrime(num))
    {
        cout << num << " is a prime number.\n";
    }
    else
    {
        cout << num << " is not a prime number.\n";
    }
    return 0;
}

*/

/*

//Factorial Calculation

int factorial(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int main()
{
    int num;
    cout << "Enter a number: ";
    cin >> num;
    cout << "Factorial of " << num << " is: " << factorial(num) << "\n";
    return 0;
}

*/

/*

//String Reversal

void reverseString(char str[])
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; ++i)
    {
        swap(str[i], str[length - i - 1]);
    }
}

int main()
{
    char myString[] = "Hello, World!";
    cout << "Original String: " << myString << "\n";
    reverseString(myString);
    cout << "Reversed String: " << myString << "\n";
    return 0;
}

*/

/*

//Fibonacci Series

int fibonacci(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main()
{
    int terms;
    cout << "Enter the number of terms for Fibonacci series: ";
    cin >> terms;
    cout << "Fibonacci Series:\n";
    for (int i = 0; i < terms; ++i)
    {
        cout << fibonacci(i) << " ";
    }
    return 0;
}

*/

/*

//Palindrome Checker

bool isPalindrome(const char str[])
{
    int length = strlen(str);
    for (int i = 0; i < length / 2; ++i)
    {
        if (str[i] != str[length - i - 1])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    char myString[] = "level";
    cout << "Original String: " << myString << "\n";
    if (isPalindrome(myString))
    {
        cout << "The string is a palindrome.\n";
    }
    else
    {
        cout << "The string is not a palindrome.\n";
    }
    return 0;
}

*/

/*

//Sorting Algorithm (Bubble Sort)

void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    const int size = 5;
    int myArray[size] = {64, 34, 25, 12, 22};
    cout << "Original Array: ";
    for (int i = 0; i < size; ++i)
    {
        cout << myArray[i] << " ";
    }
    bubbleSort(myArray, size);
    cout << "\nSorted Array: ";
    for (int i = 0; i < size; ++i)
    {
        cout << myArray[i] << " ";
    }
    return 0;
}
*/

/*

//Prime Factors

void primeFactors(int num)
{
    for (int i = 2; i <= num; ++i)
    {
        while (num % i == 0)
        {
            cout << i << " ";
            num /= i;
        }
    }
}

int main()
{
    int num;
    cout << "Enter a number: ";
    cin >> num;
    cout << "Prime Factors: ";
    primeFactors(num);
    return 0;
}

*/