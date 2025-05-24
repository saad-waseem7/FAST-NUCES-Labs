#include <iostream>
#include <cstring>

using namespace std;

void calculate_length(char **data, int len)
{
    for (int i = 0; i < len; i++)
    {
        int length = strlen(*(data + i));
        cout << "Length of String " << i + 1 << " : " << length << endl;
    }
}

int main()
{
    int n;
    cout << "Enter number of strings: ";
    cin >> n;
    char **data = new char *[n];
    for (int i = 0; i < n; i++)
    {
        *(data + i) = new char[100];
        cout << "Enter String " << i + 1 << " : ";
        cin >> *(data + i);
    }
    calculate_length(data, n);

    for (int i = 0; i < n; i++)
    {
        delete[] *(data + i);
    }
    delete[] data;
    return 0;
}