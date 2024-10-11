#include <iostream>
#include <cstring>
using namespace std;

void reverse_string(char **data, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        int start = 0;
        int end = strlen(*(data + i)) - 1;
        while (start < end)
        {
            char temp = data[i][start];
            data[i][start] = data[i][end];
            data[i][end] = temp;
            start++;
            end--;
        }
    }
}

void print_array(char **data, int rows)
{
    cout << "Reversed Strings:" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << *(data + i) << endl;
    }
}

int main()
{
    int n;
    cout << "Enter the number of strings: ";
    cin >> n;

    char **data = new char *[n];
    for (int i = 0; i < n; i++)
    {
        *(data + i) = new char[100];
        cout << "Enter String " << i + 1 << ": ";
        cin >> *(data + i);
    }

    reverse_string(data, n);
    print_array(data, n);

    for (int i = 0; i < n; i++)
    {
        delete[] *(data + i);
    }
    delete[] data;
    return 0;
}