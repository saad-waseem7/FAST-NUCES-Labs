// L23-2620 Quiz#1..

#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
};

template <typename T>
class Stack
{
private:
    Node<T> *topNode;
    int count;

public:
    Stack()
    {
        topNode = nullptr;
        count = 0;
    }

    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return topNode == nullptr;
    }

    bool top(T &value)
    {
        if (isEmpty())
        {
            return false;
        }
        value = topNode->data;
        return true;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty! Cannot pop." << endl;
            return;
        }
        Node<T> *temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    void push(T const &data)
    {
        Node<T> *newNode = new Node<T>;
        newNode->data = data;
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    T getMin()
    {
        if (isEmpty())
        {
            cout << "Stack is empty! Cannot find minimum." << endl;
            return -1;
        }
        int minValue = topNode->data;
        Node<T> *current = topNode->next;
        while (current != nullptr)
        {
            if (current->data < minValue)
            {
                minValue = current->data;
            }
            current = current->next;
        }
        return minValue;
    }

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
        cout << "Stack destroyed." << endl;
    }
};

int main()
{
    Stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    int topValue;
    if (s.top(topValue))
    {
        cout << "Top element: " << topValue << endl;
    }

    cout << "Stack size: " << s.size() << endl;

    s.pop();
    cout << "After pop, stack size: " << s.size() << endl;

    cout << "Minimum value in the stack: " << s.getMin() << endl;

    return 0;
}