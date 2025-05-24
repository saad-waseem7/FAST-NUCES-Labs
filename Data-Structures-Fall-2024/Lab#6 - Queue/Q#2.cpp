#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    int data;
    Node<T> *next;
    Node(T data)
    {
        this->data = data;
        this->next = NULL;
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

    void special_arrangement()
    {
        int n = size(); // Get the current size of the queue
        if (n % 2 != 0)
        {
            cout << "Queue length is not even." << endl;
            return;
        }

        Queue<T> secondHalf;

        for (int i = 0; i < n / 2; ++i)
        {
            enqueue(dequeue());
        }

        for (int i = 0; i < n / 2; ++i)
        {
            secondHalf.enqueue(dequeue());
        }

        for (int i = 0; i < n / 2; ++i)
        {
            enqueue(dequeue());
            enqueue(secondHalf.dequeue());
        }
    }

    void printQueue()
    {
        int n = size();
        for (int i = 0; i < n; i++)
        {
            T temp = dequeue();
            cout << temp << " ";
            enqueue(temp);
        }
        cout << endl;
    }
};

int main()
{
    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);

    cout << "Original Queue: ";
    q.printQueue();
    q.special_arrangement();
    cout << "Rearranged Queue: ";
    q.printQueue();

    return 0;
}