#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <cmath>
using namespace std;

// Define a structure to represent a person (gender and facing direction)
struct person
{
    char gender;   // 'M' for Male, 'F' for Female
    string facing; // Facing direction: "left", "right", "front", "back"
};

// Function to check if placing a person at (i, j) is valid
bool isValid(person **matrix, int rows, int cols, int i, int j, const person &p)
{
    // Check adjacent cells (up, down, left, right) for uniqueness in gender and facing direction
    if (i > 0 && (matrix[i - 1][j].gender == p.gender || matrix[i - 1][j].facing == p.facing))
        return false; // Check above
    if (i < rows - 1 && (matrix[i + 1][j].gender == p.gender || matrix[i + 1][j].facing == p.facing))
        return false; // Check below
    if (j > 0 && (matrix[i][j - 1].gender == p.gender || matrix[i][j - 1].facing == p.facing))
        return false; // Check left
    if (j < cols - 1 && (matrix[i][j + 1].gender == p.gender || matrix[i][j + 1].facing == p.facing))
        return false; // Check right
    return true;
}

// Recursive backtracking function to arrange people in the matrix
bool arrangePeople(person **matrix, int rows, int cols, queue<person> &remainingPeople, int index)
{
    if (index == rows * cols)
    {
        return true; // Successfully arranged all people
    }

    int row = index / cols; // Calculate the row index
    int col = index % cols; // Calculate the column index

    if (remainingPeople.empty())
        return false; // Exit if no people are left to place

    int size = remainingPeople.size();
    while (size--)
    {
        person p = remainingPeople.front(); // Get the next person from the queue
        remainingPeople.pop();              // Remove person from queue

        if (isValid(matrix, rows, cols, row, col, p))
        {
            matrix[row][col] = p; // Place person in the matrix

            // Recursively try to place the next person
            if (arrangePeople(matrix, rows, cols, remainingPeople, index + 1))
            {
                return true;
            }

            // Backtrack if placing the person leads to an invalid arrangement
            matrix[row][col].gender = '\0'; // Reset the cell
            matrix[row][col].facing = "";
        }

        remainingPeople.push(p); // Put the person back in the queue for the next try
    }

    return false; // No valid arrangement found
}

// Function to print the matrix with each person's gender and facing direction
void printMatrix(person **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j].gender != '\0')
            {
                cout << "Gender: " << matrix[i][j].gender << ", Facing: " << matrix[i][j].facing << " | ";
            }
            else
            {
                cout << "Empty | ";
            }
        }
        cout << endl;
    }
}

// Function to dynamically allocate the matrix
person **allocateMatrix(int rows, int cols)
{
    person **matrix = new person *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new person[cols];
        // Initialize the matrix with default values
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j].gender = '\0'; // Empty cell
            matrix[i][j].facing = "";
        }
    }
    return matrix;
}

// Function to deallocate the matrix memory
void deallocateMatrix(person **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Function to read people from a file and place them directly into the matrix
void readPeopleFromFile(const string &filename, person ***matrix, int &totalPeople, int &rows, int &cols)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Read the entire line from the file
    stringstream ss(line);
    string gender;

    // Facing directions in a fixed cyclic order
    string orientations[] = {"left", "right", "front", "back"};
    int facingIndex = 0;

    // Count total people and read them into the matrix
    totalPeople = 0;
    while (getline(ss, gender, ','))
    {
        totalPeople++;
    }

    // Calculate matrix dimensions (rows x cols) based on total people
    rows = static_cast<int>(sqrt(totalPeople));
    cols = (totalPeople + rows - 1) / rows;

    // Allocate the matrix
    *matrix = allocateMatrix(rows, cols);

    // Reset file pointer to the beginning to read again
    file.clear();
    file.seekg(0, ios::beg);

    // Place each person directly into the matrix
    int index = 0;
    while (getline(file, line) && index < rows * cols)
    {
        stringstream ss(line);
        while (getline(ss, gender, ',') && index < rows * cols)
        {
            person p;
            p.gender = gender[0];                     // Set gender (M/F)
            p.facing = orientations[facingIndex % 4]; // Assign facing direction cyclically
            facingIndex++;
            (*matrix)[index / cols][index % cols] = p; // Place person in the matrix
            index++;
        }
    }

    // Close the file after reading
    file.close();
}

// Main function
int main()
{
    person **matrix = nullptr;
    int totalPeople = 0;
    int rows = 0, cols = 0;

    // Read people from the file
    readPeopleFromFile("People.txt", &matrix, totalPeople, rows, cols);

    if (totalPeople == 0)
    {
        cout << "No people found in the file." << endl;
        return 1;
    }

    cout << "Total People: " << totalPeople << endl;
    cout << "Matrix Dimensions: " << rows << "x" << cols << endl;

    // Print the populated matrix
    printMatrix(matrix, rows, cols);

    // Try to arrange the people in the matrix
    queue<person> peopleQueue;
    for (int i = 0; i < totalPeople; i++)
    {
        peopleQueue.push(matrix[i / cols][i % cols]); // Push all people to the queue for arranging
    }

    if (arrangePeople(matrix, rows, cols, peopleQueue, 0))
    {
        cout << "A valid arrangement was found:\n";
        printMatrix(matrix, rows, cols);
    }
    else
    {
        cout << "No valid arrangement was found. Please check the constraints and input file." << endl;
    }

    // Deallocate the dynamically allocated matrix
    deallocateMatrix(matrix, rows);

    return 0;
}
