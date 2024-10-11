#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node(T value)
    {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class Queue
{
private:
    Node<T> *head;
    Node<T> *tail;
    int count;

public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty!" << endl;
            return T();
        }
        Node<T> *temp = head;
        T data = head->data;
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        delete temp;
        count--;
        return data;
    }

    T front()
    {
        if (!isEmpty())
        {
            return head->data;
        }
        return T();
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    int size()
    {
        return count;
    }
};

template <typename T>
void sortQueueAscending(Queue<T> &q)
{
    if (q.isEmpty())
        return;

    int n = q.size();
    for (int i = 0; i < n; i++)
    {
        T minElement = q.dequeue();
        for (int j = 1; j < n; j++)
        {
            T currElement = q.dequeue();
            if (currElement < minElement)
            {
                q.enqueue(minElement);
                minElement = currElement;
            }
            else
            {
                q.enqueue(currElement);
            }
        }
        q.enqueue(minElement);
    }
}

template <typename T>
Queue<T> mergeTwoQueues(Queue<T> &q1, Queue<T> &q2)
{
    Queue<T> resultQueue;

    while (!q1.isEmpty() && !q2.isEmpty())
    {
        if (q1.front() <= q2.front())
        {
            resultQueue.enqueue(q1.dequeue());
        }
        else
        {
            resultQueue.enqueue(q2.dequeue());
        }
    }

    while (!q1.isEmpty())
    {
        resultQueue.enqueue(q1.dequeue());
    }

    while (!q2.isEmpty())
    {
        resultQueue.enqueue(q2.dequeue());
    }

    return resultQueue;
}

template <typename T>
Queue<T> mergeKQueues(Queue<T> queues[], int K)
{
    if (K == 0)
        return Queue<T>();

    Queue<T> mergedQueue = queues[0];
    for (int i = 1; i < K; i++)
    {
        mergedQueue = mergeTwoQueues(mergedQueue, queues[i]);
    }
    sortQueueAscending(mergedQueue);
    return mergedQueue;
}

template <typename T>
void printQueue(Queue<T> &q)
{
    while (!q.isEmpty())
    {
        cout << q.dequeue() << " ";
    }
    cout << endl;
}

int main()
{
    const int K = 3;
    Queue<int> queues[K];

    queues[0].enqueue(10);
    queues[0].enqueue(4);
    queues[0].enqueue(7);
    queues[0].enqueue(1);

    queues[1].enqueue(2);
    queues[1].enqueue(8);
    queues[1].enqueue(5);
    queues[1].enqueue(11);

    queues[2].enqueue(9);
    queues[2].enqueue(6);
    queues[2].enqueue(3);
    queues[2].enqueue(12);

    Queue<int> result = mergeKQueues(queues, K);

    cout << "Merged Sorted Queue: ";
    printQueue(result);

    return 0;
}