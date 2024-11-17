#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    srand(time(0));
    const int totalPlayers = 4;
    int currentPlayer = 0;
    char roll;
    int players[totalPlayers] = {0};
    int gameStarted[totalPlayers] = {0};

    while (true)
    {
        cout << "Player " << currentPlayer + 1 << ", Press 'R' to roll the dice: ";
        cin >> roll;
        if (!gameStarted[currentPlayer] && (roll == 'R' || roll == 'r'))
        {
            int diceRoll = rand() % 6 + 1;
            cout << "Player " << currentPlayer + 1 << " rolled a " << diceRoll << endl;
            if (diceRoll == 6)
            {
                cout << "Game started! Your value is now 0." << endl;
                gameStarted[currentPlayer] = 1;
            }
            else
            {
                cout << "You need to roll a 6 to start the game." << endl;
                currentPlayer = (currentPlayer + 1) % totalPlayers;
                continue;
            }
        }
        else if (gameStarted[currentPlayer] && (roll == 'R' || roll == 'r'))
        {
            int diceRoll = rand() % 6 + 1;
            cout << "Player " << currentPlayer + 1 << " rolled a " << diceRoll << endl;

            if (diceRoll == 6)
            {
                cout << "You rolled a 6! You get another turn." << endl;
                continue;
            }
            players[currentPlayer] += diceRoll;
            if (players[currentPlayer] == 56)
            {
                cout << "Player " << currentPlayer + 1 << " wins!" << endl;
                break;
            }
            else if (players[currentPlayer] > 56)
            {
                cout << "Oops! So close but Your turn is skipped." << endl;
                players[currentPlayer] -= diceRoll;
            }
        }
        else
        {
            cout << "Invalid input. Press 'R' to roll the dice." << endl;
            continue;
        }
        currentPlayer = (currentPlayer + 1) % totalPlayers;
    }
    cout << "Thanks For Playing.Goodbye!";
    return 0;
}