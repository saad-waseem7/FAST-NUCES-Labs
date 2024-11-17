#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter the number of terms in the series: ";
    cin >> n;

    int term = 1;
    int sign = 1;
    while (n > 0)
    {
        cout << term;
        if (n > 1)
        {
            if (sign == 1)
            {
                cout << "+";
            }
            else
            {
                cout << "-";
            }
        }
        term++;
        sign = -sign;
        n--;
    }
    cout << endl;
    return 0;
}
