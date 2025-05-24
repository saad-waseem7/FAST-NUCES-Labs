#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node
{
    int data;
    Node *up;
    Node *down;
    Node *left;
    Node *right;

    Node(int value) : data(value), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}
};

struct VisitedNode
{
    Node *node;
    VisitedNode *next;

    VisitedNode(Node *n) : node(n), next(nullptr) {}
};

int sumOfDigits(int num)
{
    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int numOfDigits(int num)
{
    int digits = 0;
    while (num != 0)
    {
        digits++;
        num /= 10;
    }
    return digits;
}

class Maze
{
private:
    Node *head;
    int rows, cols;

public:
    Maze() : head(nullptr), rows(0), cols(0) {}

    void Read(const string &filename)
    {
        ifstream file(filename);
        string line;
        Node *previousRowStart = nullptr;
        Node *currentRowStart = nullptr;
        Node *lastNode = nullptr;

        while (getline(file, line))
        {
            istringstream ss(line);
            string token;
            Node *currentRow = nullptr;

            while (getline(ss, token, ','))
            {
                int value = stoi(token);
                Node *newNode = new Node(value);

                if (!head)
                {
                    head = newNode;
                }

                if (lastNode)
                {
                    lastNode->right = newNode;
                    newNode->left = lastNode;
                }

                if (previousRowStart)
                {
                    previousRowStart->down = newNode;
                    newNode->up = previousRowStart;
                    previousRowStart = previousRowStart->right;
                }

                lastNode = newNode;

                if (!currentRowStart)
                {
                    currentRowStart = newNode;
                }
            }

            previousRowStart = currentRowStart;
            lastNode = nullptr;
            rows++;
        }

        if (!line.empty())
        {
            stringstream ss(line);
            string temp;
            cols = 0;
            while (getline(ss, temp, ','))
            {
                cols++;
            }
        }
    }

    void Print()
    {
        Node *row = head;
        while (row)
        {
            Node *col = row;
            while (col)
            {
                cout << col->data << " ";
                col = col->right;
            }
            cout << endl;
            row = row->down;
        }
    }

    int ClueRow(int data)
    {
        return (sumOfDigits(data) % rows) + 1;
    }

    int ClueColumn(int data)
    {
        return numOfDigits(data);
    }

    bool isVisited(Node *current, VisitedNode *visitedList)
    {
        VisitedNode *temp = visitedList;
        while (temp != nullptr)
        {
            if (temp->node == current)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void addToVisited(Node *current, VisitedNode *&visitedList)
    {
        VisitedNode *newVisitedNode = new VisitedNode(current);
        newVisitedNode->next = visitedList;
        visitedList = newVisitedNode;
    }

    void Traverse()
    {
        VisitedNode *visitedList = nullptr;
        Node *current = head;

        while (current)
        {
            cout << "Visiting Node: " << current->data << endl;

            if (isVisited(current, visitedList))
            {
                cout << "Node " << current->data << " has been visited again. Stopping." << endl;
                return;
            }

            addToVisited(current, visitedList);

            int nextRow = ClueRow(current->data);
            int nextCol = ClueColumn(current->data);
            cout << "Next Row: " << nextRow << ", Next Column: " << nextCol << endl;

            Node *nextNode = findNode(nextRow, nextCol);

            if (!nextNode)
            {
                cout << "Reached a dead end." << endl;
                return;
            }

            if (nextNode == current)
            {
                cout << "Elite Node found: " << nextNode->data << endl;
                return;
            }

            current = nextNode;
        }
    }

    Node *findNode(int row, int col)
    {
        Node *temp = head;
        for (int i = 1; i < row && temp; i++)
        {
            temp = temp->down;
        }
        for (int j = 1; j < col && temp; j++)
        {
            temp = temp->right;
        }
        return temp;
    }
    ~Maze()
    {
        Node *currentRow = head;
        while (currentRow)
        {
            Node *currentNode = currentRow;
            currentRow = currentRow->down;
            while (currentNode)
            {
                Node *nextNode = currentNode->right;
                delete currentNode;
                currentNode = nextNode;
            }
        }
    }
};

int main()
{
    Maze maze;
    maze.Read("Maze.txt");
    cout << "Maze structure:" << endl;
    maze.Print();
    maze.Traverse();
    return 0;
}
