#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>

const int width = 20;
const int height = 20;

struct Snake {
    int x, y;
};

enum Direction {
    Up,
    Down,
    Left,
    Right
};

int main() {
    // Initialization
    std::vector<Snake> snake = { {10, 10} };
    Direction dir = Right;
    Snake food = { 5, 5 };
    bool game_over = false;

    // Game loop
    while (!game_over) {
        // Check for user input
        if (_kbhit()) {
            switch (_getch()) {
            case 'w': dir = Up; break;
            case 's': dir = Down; break;
            case 'a': dir = Left; break;
            case 'd': dir = Right; break;
            }
        }

        // Move the snake
        Snake head = { snake[0].x, snake[0].y };
        switch (dir) {
        case Up: head.y--; break;
        case Down: head.y++; break;
        case Left: head.x--; break;
        case Right: head.x++; break;
        }

        // Check for collisions with the walls
        if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
            game_over = true;
        }

        // Check for collisions with the food
        if (head.x == food.x && head.y == food.y) {
            // Regenerate the food
            food.x = rand() % width;
            food.y = rand() % height;
        }
        else {
            // Move the tail forward
            snake.pop_back();
        }

        // Move the head forward
        snake.insert(snake.begin(), head);

        // Print the game board
        system("cls");
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == food.x && y == food.y) {
                    std::cout << "*";
                }
                else if (snake[0].x == x && snake[0].y == y) {
                    std::cout << "o";
                }
                else {
                    bool found = false;
                    for (int i = 1; i < snake.size(); i++) {
                        if (snake[i].x == x && snake[i].y == y) {
                            std::cout << "o";
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        std::cout << " ";
                    }
                }
            }
            std::cout << std::endl;
        }

        // Pause the game
        Sleep(100);
    }

    // Print the game over message
    std::cout << "Game Over!" << std::endl;

    return 0;
}