#include <iostream>
#include <string>
using namespace std;

const int rows = 9;
const int cols = 4;
const int rows_P = 4;
const int cols_P = 9;

void print_array_body(char data[][cols], int rows, int cols)
{
    cout << "\nSeating Arrangement:\n";
    for (int i = 0; i < rows; ++i)
    {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < cols; ++j)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void print_array_head(char data[][cols_P], int rows_P, int cols_P)
{
    cout << "\nAirplane Head:\n";
    for (int i = 0; i < rows_P; ++i)
    {
        for (int j = 0; j < cols_P; ++j)
        {
            cout << data[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int get_valid_int(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (!cin.fail())
        {
            return value;
        }
        else
        {
            cout << "Invalid input! Please enter a valid number.\n";
            cin.clear();
            cin.ignore();
        }
    }
}

int main()
{
    char airplane_Pattern_head[rows_P][cols_P] = {
        {' ', ' ', ' ', '/', '\\', ' ', ' ', ' '},
        {' ', ' ', '/', ' ', ' ', '\\', ' ', ' '},
        {' ', '/', ' ', '#', '#', ' ', '\\', ' '},
        {'/', ' ', ' ', '#', '#', ' ', ' ', '\\'}};

    char grid[rows][cols] = {
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'},
        {'-', '-', '-', '-'}};

    print_array_head(airplane_Pattern_head, rows_P, cols_P);
    print_array_body(grid, rows, cols);

    cout << "Welcome to the Ticketing Center!\n\n";
    string word;
    while (true)
    {
        cout << "Available Options:\n";
        cout << "1. Reserve a seat in Business Class (Rows 1-3)\n";
        cout << "2. Reserve a seat in Economy Class (Rows 4-9)\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> word;

        if (word == "1" || word == "Business")
        {
            int r1 = get_valid_int("Enter Row (1-3): ");
            int c1 = get_valid_int("Enter Column (1-4): ");

            if (r1 >= 1 && r1 <= 3 && c1 >= 1 && c1 <= 4)
            {
                if (grid[r1 - 1][c1 - 1] == 'Z')
                {
                    cout << "Sorry, seat is already booked!\n";
                }
                else
                {
                    grid[r1 - 1][c1 - 1] = 'Z';
                    cout << "Seat successfully reserved in Business Class!\n";
                }
            }
            else
            {
                cout << "Invalid seat selection! Please choose a valid Business Class seat.\n";
            }
        }
        else if (word == "2" || word == "Economy")
        {
            int r1 = get_valid_int("Enter Row (4-9): ");
            int c1 = get_valid_int("Enter Column (1-4): ");

            if (r1 >= 4 && r1 <= 9 && c1 >= 1 && c1 <= 4)
            {
                if (grid[r1 - 1][c1 - 1] == 'X')
                {
                    cout << "Sorry, seat is already booked!\n";
                }
                else
                {
                    grid[r1 - 1][c1 - 1] = 'X';
                    cout << "Seat successfully reserved in Economy Class!\n";
                }
            }
            else
            {
                cout << "Invalid seat selection! Please choose a valid Economy Class seat.\n";
            }
        }
        else if (word == "3" || word == "Quit")
        {
            cout << "Thank you for using the Ticketing Center! Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice! Please try again.\n";
        }

        // Show updated seating arrangement
        print_array_head(airplane_Pattern_head, rows_P, cols_P);
        print_array_body(grid, rows, cols);
    }

    return 0;
}
