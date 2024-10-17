#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct person
{
    char gender;
    string facing_side;
};

bool valid_check(person **matrix, int rows, int cols, int i, int j, const person &p)
{
    if (i > 0 && (matrix[i - 1][j].gender == p.gender || matrix[i - 1][j].facing_side == p.facing_side))
        return false;
    if (i < rows - 1 && (matrix[i + 1][j].gender == p.gender || matrix[i + 1][j].facing_side == p.facing_side))
        return false;
    if (j > 0 && (matrix[i][j - 1].gender == p.gender || matrix[i][j - 1].facing_side == p.facing_side))
        return false;
    if (j < cols - 1 && (matrix[i][j + 1].gender == p.gender || matrix[i][j + 1].facing_side == p.facing_side))
        return false;
    return true;
}

void people_arrangement(person **matrix, int rows, int cols, queue<person> &people_remain, int index)
{
    if (index == rows * cols)
    {
        return; 
    }

    int temp_row = index / cols;
    int temp_col = index % cols;

    if (people_remain.empty())
        return;

    int size = people_remain.size();
    while (size--)
    {
        person p = people_remain.front();
        people_remain.pop();

        if (valid_check(matrix, rows, cols, temp_row, temp_col, p))
        {
            matrix[temp_row][temp_col] = p;

            people_arrangement(matrix, rows, cols, people_remain, index + 1);
            if (matrix[temp_row][temp_col].gender != '\0') 
                return; 
        }

        matrix[temp_row][temp_col].gender = '\0';
        matrix[temp_row][temp_col].facing_side = "";

        people_remain.push(p);
    }
}

void display_details(person **matrix, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (matrix[i][j].gender != '\0')
            {
                cout << matrix[i][j].gender << " (" << matrix[i][j].facing_side << ") " << " | ";
            }
            else
            {
                cout << "Empty | ";
            }
        }
        cout << endl;
    }
}

person **new_matrix(int rows, int cols)
{
    person **matrix = new person *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new person[cols];
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j].gender = '\0';
            matrix[i][j].facing_side = "";
        }
    }
    return matrix;
}

void delete_matrix(person **matrix, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void load_data_from_file(const string &filename, person ***matrix, int &total_people_count, int &rows, int &cols)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);
    stringstream ss(line);
    string gender;

    string options[] = {"left", "right", "front", "back"};
    int face_index = 0;

    total_people_count = 0;
    while (getline(ss, gender, ','))
    {
        total_people_count++;
    }

    rows = static_cast<int>(sqrt(total_people_count));
    cols = (total_people_count + rows - 1) / rows;

    *matrix = new_matrix(rows, cols);

    file.clear();
    file.seekg(0, ios::beg);

    int index = 0;
    while (getline(file, line) && index < rows * cols)
    {
        stringstream ss(line);
        while (getline(ss, gender, ',') && index < rows * cols)
        {
            person p;
            p.gender = gender[0];
            p.facing_side = options[face_index % 4];
            face_index++;
            (*matrix)[index / cols][index % cols] = p;
            index++;
        }
    }

    file.close();
}

int main()
{
    person **matrix = nullptr;
    int total_people_count = 0;
    int rows = 0, cols = 0;

    load_data_from_file("People.txt", &matrix, total_people_count, rows, cols);

    cout << "Before Arrangement of people: " << endl;
    display_details(matrix, rows, cols);

    if (total_people_count == 0)
    {
        cout << "No people found in the file." << endl;
        return 1;
    }

    queue<person> peopleQueue;
    for (int i = 0; i < total_people_count; i++)
    {
        peopleQueue.push(matrix[i / cols][i % cols]);
    }

    people_arrangement(matrix, rows, cols, peopleQueue, 0);

    cout << "After Arrangement of people: " << endl;
    display_details(matrix, rows, cols);

    if (matrix[0][0].gender == '\0')
    {
        cout << "No valid arrangement was found. Please check the constraints and input file." << endl;
    }

    delete_matrix(matrix, rows);

    return 0;
}
