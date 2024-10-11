#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
using namespace std;

bool compare(string **dynamic, string k, int row)
{
    for (int i = 0; (*(*(dynamic + row)))[i] != '\0'; i++)
    {
        if ((*(*(dynamic + row)))[i] != k[i])
        {
            return false;
        }
    }
    return true;
}

int extract(string **dynamic, int row)
{
    string input1;
    cout << "Enter word to find: " << endl;
    cin >> input1;
    int i;
    for (i = 0; i < row; i++)
    {
        if (compare(dynamic, input1, i))
        {
            return i;
        }
    }
    return -1;
    cout << "\nfound: " << i << endl;
}

string **CreateDynamicArray(char ws[], int &rows)
{
    rows = 1;
    for (int i = 0; ws[i] != '\0'; ++i)
    {
        if (ws[i] == '#')
        {
            ++rows;
        }
    }
    string **dynamicArray = new string *[rows];
    for (int i = 0; i < rows; ++i)
    {
        *(dynamicArray + i) = new string[10];
    }

    int row = 0, col = 0;
    for (int i = 0; ws[i] != '\0'; ++i)
    {
        if (ws[i] == '#')
        {
            ++row;
            col = 0;
        }
        else if (ws[i] == ' ')
        {
            ++col;
        }
        else
        {
            dynamicArray[row][col] += ws[i];
        }
    }
    return dynamicArray;
}

void synonymOutput(string **d, int index)
{
    if (index < 0)
    {
        cout << "invalid input" << endl;
        return;
    }

    int i;
    for (i = 0; !(d[index][i].empty()) && i < 10; i++)
    {
    }
    cout << endl;
    cout << d[index][i - 1] << endl;
}

int main()
{
    int rows;
    cout << "Enter words and their synonyms separated by '#' (e.g., word1 synonym1 synonym2#word2 synonym3):" << endl;
    string userInput;
    getline(cin, userInput);
    char *inputArray = new char[userInput.length() + 1];
    int x;
    for (x = 0; userInput[x] != '\0'; x++)
    {
        *(inputArray + x) = userInput[x];
    }
    *(inputArray + x) = '\0';
    string **dynamicArray = CreateDynamicArray(inputArray, rows);
    for (int i = 0; i < rows; ++i)
    {
        cout << "Ptr" << i << ": ";
        int j = 0;
        while (!(*(*(dynamicArray + i) + j)).empty())
        {
            cout << *(*(dynamicArray + i) + j) << " ";
            ++j;
        }
        cout << endl;
    }
    int index;
    index = extract(dynamicArray, rows);
    synonymOutput(dynamicArray, index);

    for (int i = 0; i < rows; ++i)
    {
        delete[] *(dynamicArray + i);
    }
    delete[] dynamicArray;
    delete[] inputArray;

    system("pause");
    return 0;
}
