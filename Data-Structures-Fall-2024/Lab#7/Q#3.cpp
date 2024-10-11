#include <iostream>
using namespace std;

void Combination(int data[], int arr_size, int start, int combination_size, int curr[], int curr_index)
{
    if (combination_size == 0)
    {
        for (int i = 0; i < curr_index; i++)
        {
            cout << curr[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = start; i <= arr_size - combination_size; i++)
    {
        curr[curr_index] = data[i];
        Combination(data, arr_size, i + 1, combination_size - 1, curr, curr_index + 1);
    }
}

void print(int data[], int arr_size, int combination_size)
{
    if (combination_size > arr_size)
    {
        cout << "Value cannot be greater than arr_size" << endl;
        return;
    }

    int *curr = new int[combination_size];
    Combination(data, arr_size, 0, combination_size, curr, 0);
    delete[] curr;
}

int main()
{

    const int arr_size = 4;
    int data[arr_size] = {1, 2, 3, 4};

    cout << "Combinations of size 2:" << endl;
    print(data, arr_size, 2);

    cout << "Combinations of size 3:" << endl;
    print(data, arr_size, 3);

    return 0;
}