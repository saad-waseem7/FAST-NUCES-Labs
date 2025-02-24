#include <iostream>
using namespace std;
int main()
{
    // Initialize the deck of cards with values.
    int deck[52] = {1, 2, 3, 4, 5, 6, 0, 8, 9, 10, 0, 10, 10, 1, 2, 3, 4, 5, 6, 0, 8, 9, 10, 0, 10, 10, 1, 2, 3, 4, 5, 6, 0, 8, 9, 10, 0, 10, 10, 1, 2, 3, 4, 5, 6, 0, 8, 9, 10, 0, 10, 10};

    // Initialize four players and a variable to store the open card.
    int p1[5], p2[5], p3[5], p4[5], index = 0, open, player = 1;
    int max, max_index = 0;

    // Give 5 cards to each player and set the open card.
    for (int i = 0; i < 5; i++)
    {
        p1[i] = deck[index++];
        p2[i] = deck[index++];
        p3[i] = deck[index++];
        p4[i] = deck[index++];
    }
    open = deck[index++];

    // Main game loop start
    while (index < 52)
    {
        // Determine the current player's turn
        if (player == 1)
        {
            // Find the highest card in player 1's hand
            max = p1[0];
            max_index = 0;
            for (int i = 1; i < 5; i++)
            {
                if (max < p1[i])
                {
                    max = p1[i];
                    max_index = i;
                }
            }

            // Check if the highest card is lower than the open card
            if (max < open)
            {
                // Swap the open card with the highest card in player 1's hand
                swap(p1[max_index], open);
            }
            else
            {
                // If player 1's highest card is higher than the open card, draw a new open card
                open = deck[index++];

                // If player 1's highest card is still higher, swap it with the open card
                if (max < open)
                {
                    swap(p1[max_index], open);
                }
            }

            // Move to the next player
            player = 2;
        }
        else if (player == 2)
        {
            // Find the highest card in player 2's hand
            max = p2[0];
            max_index = 0;
            for (int i = 1; i < 5; i++)
            {
                if (max < p2[i])
                {
                    max = p2[i];
                    max_index = i;
                }
            }

            // Check if the highest card is lower than the open card
            if (max < open)
            {
                // Swap the open card with the highest card in player 2's hand
                swap(p2[max_index], open);
            }
            else
            {
                // If player 2's highest card is higher than the open card, draw a new open card
                open = deck[index++];

                // If player 2's highest card is still higher, swap it with the open card
                if (max < open)
                {
                    swap(p2[max_index], open);
                }
            }

            // Move to the next player
            player = 3;
        }
        else if (player == 3)
        {
            // Find the highest card in player 3's hand
            max = p3[0];
            max_index = 0;
            for (int i = 1; i < 5; i++)
            {
                if (max < p3[i])
                {
                    max = p3[i];
                    max_index = i;
                }
            }

            // Check if the highest card is lower than the open card
            if (max < open)
            {
                // Swap the open card with the highest card in player 3's hand
                swap(p3[max_index], open);
            }
            else
            {
                // If player 3's highest card is higher than the open card, draw a new open card
                open = deck[index++];

                // If player 3's highest card is still higher, swap it with the open card
                if (max < open)
                {
                    swap(p3[max_index], open);
                }
            }

            // Move to the next player
            player = 4;
        }
        else
        {
            // Find the highest card in player 4's hand
            max = p4[0];
            max_index = 0;
            for (int i = 1; i < 5; i++)
            {
                if (max < p4[i])
                {
                    max = p4[i];
                    max_index = i;
                }
            }

            // Check if the highest card is lower than the open card
            if (max < open)
            {
                // Swap the open card with the highest card in player 4's hand
                swap(p4[max_index], open);
            }
            else
            {
                // If player 4's highest card is higher than the open card, draw a new open card
                open = deck[index++];

                // If player 4's highest card is still higher, swap it with the open card
                if (max < open)
                {
                    swap(p4[max_index], open);
                }
            }

            // Move back to player 1 after player 4's turn
            player = 1;
        }

        // Break the loop if there are no cards left
        if (index >= 52)
        {
            break;
        }
    } // End of the game loop

    // Print the final cards of all players
    for (int j = 0; j < 5; j++)
    {
        cout << p1[j] << endl;
        cout << p2[j] << endl;
        cout << p3[j] << endl;
        cout << p4[j] << endl;
    }

    return 0;
}
