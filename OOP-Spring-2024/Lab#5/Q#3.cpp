#include <iostream>
#include <cstring>

using namespace std;

void capitalize_words(char **data, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        bool word = true;

        for (int j = 0; *(*(data + i) + j) != '\0'; j++)
        {
            if (word && (*(*(data + i) + j) >= 'a' && *(*(data + i) + j) <= 'z'))
            {
                *(*(data + i) + j) -= 32;
                word = false;
            }
            else
            {
                word = false;
            }
        }
    }
}

void print_array(char **data, int rows)
{
    cout << "Modified Strings:" << endl;
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
    cin.ignore();
    char **data = new char *[n];
    for (int i = 0; i < n; i++)
    {
        *(data + i) = new char[100];
        cout << "Enter String " << i + 1 << ": ";
        cin.getline(*(data + i), 100);
    }

    capitalize_words(data, n);
    print_array(data, n);

    for (int i = 0; i < n; i++)
    {
        delete[] *(data + i);
    }
    delete[] data;

    return 0;
}