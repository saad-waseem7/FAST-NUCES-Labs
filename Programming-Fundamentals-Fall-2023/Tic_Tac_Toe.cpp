#include <iostream>
#include <cstdlib>
using namespace std;

void printBoard(const int board[3][3])
{
	cout << "-------------" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << "| ";
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
			{
				cout << " " << " | ";
			}
			else if (board[i][j] == 1)
			{
				cout << "X" << " | ";
			}
			else
			{
				cout << "O" << " | ";
			}
		}
		cout << endl
			 << "-------------" << endl;
	}
}

bool checkWinner(const int b[3][3], int &who)
{
	for (int i = 0; i < 3; i++)
	{
		if (b[i][0] == b[i][1] && b[i][0] == b[i][2] && b[i][0] != 0)
		{
			who = b[i][0];
			return true;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (b[0][i] == b[1][i] && b[0][i] == b[2][i] && b[0][i] != 0)
		{
			who = b[0][i];
			return true;
		}
	}
	if (b[0][0] == b[1][1] && b[0][0] == b[2][2] && b[0][0] != 0)
	{
		who = b[0][0];
		return true;
	}
	if (b[2][0] == b[1][1] && b[2][0] == b[0][2] && b[2][0] != 0)
	{
		who = b[2][0];
		return true;
	}
	else
	{
		return false;
	}
}

bool checkDraw(const int b[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (b[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	int board[3][3] = {0};
	int player = 1;
	int row, col;
	bool winner = false;
	int who;
	char playAgain = 'n';

	cout << "Welcome to Tic-Tac-Toe!" << endl;

	do
	{
		do
		{
			printBoard(board);
			cout << "Player " << player << "'s turn. Enter row and column (1-3): " << endl;

			cout << "Enter Row: ";
			while (!(cin >> row) || row < 1 || row > 3)
			{
				cout << "Invalid input. Please enter a number between 1 and 3 for row: ";
				cin.clear();
				cin.ignore();
			}

			cout << "Enter Column: ";
			while (!(cin >> col) || col < 1 || col > 3 || board[row - 1][col - 1] != 0)
			{
				if (board[row - 1][col - 1] != 0)
				{
					cout << "This cell is already occupied. Please enter a number between 1 and 3 for row:" << endl;
				}
				else
				{
					cout << "Invalid input. Please enter a number between 1 and 3 for column: ";
				}
				cin.clear();
				cin.ignore();
			}

			board[row - 1][col - 1] = player;

			system("cls");

			winner = checkWinner(board, who);
			if (winner)
			{
				break;
			}

			if (player == 1)
			{
				player = 2;
			}
			else
			{
				player = 1;
			}
		} while (!winner && !checkDraw(board));

		printBoard(board);

		if (winner)
		{
			cout << "Player " << who << " wins!" << endl;
		}
		else if (checkDraw(board))
		{
			cout << "It's a draw!" << endl;
		}

		cout << "Do you want to play again? (y/n): ";
		cin >> playAgain;
		while (playAgain != 'y' && playAgain != 'n' && playAgain != 'Y' && playAgain != 'N')
		{
			cout << "Invalid input. Please enter 'y' or 'n': ";
			cin >> playAgain;
		}

		if (playAgain == 'y' || playAgain == 'Y')
		{
			system("cls");
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					board[i][j] = 0;
				}
			}
			winner = false;
			player = 1;
		}
		else if (playAgain == 'n' || playAgain == 'N')
		{
			cout << "Exiting..." << endl;
		}

	} while (playAgain == 'y' || playAgain == 'Y');

	return 0;
}
