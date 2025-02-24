#include <iostream>
using namespace std;

void countCurrency(int amount)
{
    int notes[] = {5000, 1000, 500, 100, 50, 20, 10};
    int noteCounter[7] = {0};

    for (int i = 0; i < 7; i++)
    {
        noteCounter[i] = amount / notes[i];
        amount %= notes[i];
    }

    cout << "Currency Count ->" << endl;
    for (int i = 0; i < 7; i++)
    {
        if (noteCounter[i] != 0)
        {
            cout << notes[i] << ": " << noteCounter[i] << endl;
        }
    }
}

int main()
{
    int amount;
    cout << "Enter the amount: ";
    cin >> amount;

    countCurrency(amount);

    return 0;
}
