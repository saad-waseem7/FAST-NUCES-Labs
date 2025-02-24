#include <iostream>
using namespace std;

void findPairsWithSum(int data[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n-1; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (data[i] + data[j] == data[k])
                {
                    cout << data[i] << " + " << data[j] << " = " << data[k] << endl;
                }
            }
        }
    }
}

int main()
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int n = sizeof(data) / sizeof(data[0]);
    findPairsWithSum(data, n);
    return 0;
}
