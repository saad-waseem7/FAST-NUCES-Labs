#include <iostream>
using namespace std;
void countFrequency(char str[], int frequency[]) {
    for (int i = 0; str[i]; ++i)
        if (isalpha(str[i])) frequency[toupper(str[i]) - 'A']++;
}
void reorderString(char str[], int frequency[]) {
    for (int i = 0; str[i]; ++i)
        for (int j = 0; str[j + 1]; ++j)
            if (frequency[toupper(str[j]) - 'A'] < frequency[toupper(str[j + 1]) - 'A'] ||
                (frequency[toupper(str[j]) - 'A'] == frequency[toupper(str[j + 1]) - 'A'] && str[j] < str[j + 1]))
                swap(str[j], str[j + 1]);
}
int main() {
    int frequency[26] = { 0 };
    char input[100];
    cout << "Enter a string: ";
    cin >> input;
    countFrequency(input, frequency);
    cout << input << endl;
    for (char c = 'A'; c <= 'Z'; ++c)
        if (frequency[c - 'A']) cout << c << ": " << frequency[c - 'A'] << " times" << endl;

    reorderString(input, frequency);
    cout << input;
    return 0;
}
