#include <iostream>
#include <cstring>

using namespace std;

void encrypt_Substitution(char arr[], int key)
{
    int len = strlen(arr);
    for (int i = 0; i < len; i++)
    {
        // Encrypt only alphabetical characters, leave others unchanged
        if (isalpha(arr[i]))
        {
            char base = islower(arr[i]) ? 'a' : 'A';
            arr[i] = (arr[i] - base + key) % 26 + base;
        }
    }

    cout << "Encrypted string: " << arr << endl;
}

int main()
{
    char arr[] = "Operation Fortune";
    int key;

    cout << "Enter Key for Encryption: ";
    cin >> key;

    encrypt_Substitution(arr, key);

    return 0;
}
