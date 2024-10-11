// L23-2620 Quiz#1...

#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node(T data);
    ~Node();
};

template <typename T>
Node<T>::Node(T data)
{
    this->data = data;
    this->next = nullptr;
}

template <typename T>
Node<T>::~Node() {}

template <typename T>
void insert_at_end(Node<T> *&head, T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    Node<T> *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
}

template <typename T>
void insert_at_start(Node<T> *&head, T data)
{
    Node<T> *newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
}

template <typename T>
bool is_empty(Node<T> *&head)
{
    return head == nullptr;
}

template <typename T>
void delete_node(Node<T> *&head, int index)
{
    if (index < 0)
    {
        cout << "Invalid index. Index should be non-negative." << endl;
        return;
    }
    if (index == 0)
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node<T> *current = head;
    for (int i = 0; i < index - 1 && current != nullptr; i++)
    {
        current = current->next;
    }
    if (current == nullptr || current->next == nullptr)
    {
        cout << "Invalid index. Index out of range." << endl;
        return;
    }
    Node<T> *temp = current->next;
    current->next = current->next->next;
    delete temp;
}

template <typename T>
void delete_full_list(Node<T> *&head)
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        Node<T> *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    cout << "List deleted successfully." << endl;
}

template <typename T>
bool hasCycle(Node<T> *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return false;
    }

    Node<T> *slow = head;
    Node<T> *fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void print_list(Node<T> *head)
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

int main()
{
    Node<int> *head = nullptr;

    insert_at_start(head, 2);
    insert_at_start(head, 6);
    insert_at_start(head, 7);

    insert_at_end(head, 9);

    insert_at_start(head, 7);
    insert_at_start(head, 8);
    insert_at_start(head, 9);

    cout << "Testing on Straight Single Linked List" << endl;
    if (hasCycle(head) == true)
    {
        cout << "Cycle found in list" << endl;
    }
    else
    {
        cout << "No cycle found in the list." << endl;
    }

    Node<int> *cycle_start = head->next->next;
    while (head->next != nullptr)
    {
        head = head->next;
    }
    head->next = cycle_start;

    cout << "Testing on Linked List with Cycle" << endl;
    if (hasCycle(head) == true)
    {
        cout << "Cycle found in list" << endl;
    }
    else
    {
        cout << "No cycle found in the list." << endl;
    }

    delete_full_list(head);
    return 0;
}
