#include <iostream>
#include <string>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

template <typename T>
class Queue
{
private:
    Node<T> *head;
    Node<T> *tail;

public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }

    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    T dequeue()
    {
        if (head == nullptr)
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        T tempData = head->data;
        Node<T> *temp = head;
        head = head->next;

        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete temp;
        return tempData;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    bool isFull()
    {
        return false;
    }

    int size()
    {
        int count = 0;
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    T front()
    {
        if (head == nullptr)
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        return head->data;
    }

    T rear()
    {
        if (tail == nullptr)
        {
            cout << "Queue is empty." << endl;
            return T();
        }
        return tail->data;
    }
};

int main()
{
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front element: " << q.front() << endl;
    cout << "Rear element: " << q.rear() << endl;
    cout << "Queue size: " << q.size() << endl;

    cout << "Dequeued: " << q.dequeue() << endl;
    cout << "Queue size after dequeue: " << q.size() << endl;

    cout << "Front element: " << q.front() << endl;
    cout << "Rear element: " << q.rear() << endl;

    cout << (q.isEmpty() ? "Queue is empty." : "Queue is not empty.") << endl;

    return 0;
}