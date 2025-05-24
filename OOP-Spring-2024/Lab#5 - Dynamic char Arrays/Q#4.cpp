#include <iostream>
#include <cstring>
#include <string>
using namespace std;

char *concatenate_array(char *data1, char *data2)
{
    int len1 = strlen(data1);
    int len2 = strlen(data2);
    int totalLen = len1 + len2 + 2;
    char *result = new char[totalLen];

    strcpy(result, data1);
    strcat(result, "_");
    strcat(result, data2);

    return result;
}

char *add_delimiter(string &input)
{
    int length = 0;
    while (input[length] != '\0')
    {
        length++;
    }

    char *modified = new char[length * 2 + 1];
    int index = 0;

    for (int i = 0; i < length; i++)
    {
        if (input[i] == ' ')
        {
            modified[index++] = '_';
        }
        else
        {
            modified[index++] = input[i];
        }
    }
    modified[index] = '\0';
    return modified;
}

int main()
{
    char *data1;
    char *data2;

    cout << "Enter first array:" << endl;
    string temp1;
    getline(cin, temp1);
    data1 = add_delimiter(temp1);

    cout << "Enter second array:" << endl;
    string temp2;
    getline(cin, temp2);
    data2 = add_delimiter(temp2);

    char *concatenated = concatenate_array(data1, data2);

    cout << "Concatenated String:" << endl;
    cout << concatenated << endl;

    delete[] concatenated;
    delete[] data1;
    delete[] data2;

    return 0;
}