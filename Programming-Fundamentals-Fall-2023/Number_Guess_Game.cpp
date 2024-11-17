#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(nullptr));

    char playAgain;
    do
    {
        // Generate a random number between 1 and 100
        int secretNumber = rand() % 100 + 1;
        int guess;
        int attempts = 0;
        bool validInput;

        cout << "Welcome to the Guess the Number game!\n";
        cout << "I have selected a number between 1 and 100. Can you guess it?\n";

        do
        {
            validInput = false;
            cout << "Enter your guess: ";
            if (!(cin >> guess))
            {
                cout << "Invalid input! Please enter a valid integer.\n";
                cin.clear();
                cin.ignore();
            }
            else
            {
                validInput = true;
                attempts++;

                if (guess < secretNumber)
                {
                    cout << "Too low! Try again.\n";
                }
                else if (guess > secretNumber)
                {
                    cout << "Too high! Try again.\n";
                }
                else
                {
                    cout << "Congratulations! You guessed the number " << secretNumber << " correctly!\n";
                    cout << "It took you " << attempts << " attempts.\n";
                }
            }
        } while (guess != secretNumber || !validInput);

        do
        {
            cout << "Do you want to play again? (y/n): ";
            cin >> playAgain;
            if (playAgain != 'y' && playAgain != 'n')
            {
                cout << "Invalid response! Please enter 'y' or 'n'.\n";
            }
        } while (playAgain != 'y' && playAgain != 'n');
    } while (playAgain == 'y');

    cout << "Thanks for playing! Goodbye.\n";
    return 0;
}