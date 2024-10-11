#include <iostream>
#include <string>
using namespace std;

void input_scores(int **&scores, int d1, int d2, string *country)
{
    scores = new int *[d1];
    for (int i = 0; i < d1; i++)
    {
        *(scores + i) = new int[d2];
        cout << "Enter name of country " << i + 1 << ": ";
        cin >> country[i];
        cout << "Enter scores for country " << country[i] << ": ";
        for (int j = 0; j < d2; j++)
        {
            cin >> *(*(scores + i) + j);
        }
    }
}

void find_achievers(int **scores, int d1, int d2, int **&achievers)
{
    achievers = new int *[d1];
    for (int i = 0; i < d1; i++)
    {
        int count = 0;
        for (int j = 0; j < d2; j++)
        {
            if (*(*(scores + i) + j) > 300)
            {
                count++;
            }
        }
        *(achievers + i) = new int[count + 1];
        int index = 0;
        for (int j = 0; j < d2; j++)
        {
            if (*(*(scores + i) + j) > 300)
            {
                achievers[i][index++] = *(*(scores + i) + j);
            }
        }
        achievers[i][count] = -1;
    }
}

void display_achievers(int **achievers, int n, string *country)
{
    cout << "Achievers:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << country[i] << ": ";
        for (int j = 0; *(*(achievers + i) + j) != -1; j++)
        {
            cout << *(*(achievers + i) + j) << " ";
        }
        cout << -1 << endl;
    }
}

void deallocate_memory(int **&scores, int **&achievers, int row)
{
    for (int i = 0; i < row; i++)
    {
        delete[] *(scores + i);
        delete[] *(achievers + i);
    }
    delete[] scores;
    delete[] achievers;
}

int main()
{
    int **scores;
    int **achievers;
    int num1, num2;
    cout << "Enter number of countries: ";
    cin >> num1;
    cout << "Enter number of players per country: ";
    cin >> num2;

    string *country = new string[num1];

    input_scores(scores, num1, num2, country);
    find_achievers(scores, num1, num2, achievers);
    display_achievers(achievers, num1, country);
    deallocate_memory(scores, achievers, num1);
    delete[] country;

    return 0;
}
