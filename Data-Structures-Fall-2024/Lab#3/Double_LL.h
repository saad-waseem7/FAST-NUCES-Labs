#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node *prev;
    Node(T data);
    ~Node();
};

template <typename T>
Node<T>::Node(T data)
{
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
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
    newNode->prev = current;
}

template <typename T>
void insert_at_start(Node<T> *&head, T data)
{
    Node<T> *newNode = new Node<T>(data);
    newNode->next = head;
    if (head != nullptr)
    {
        head->prev = newNode;
    }
    head = newNode;
}

template <typename T>
void insert_in_middle(Node<T> *&head, T data)
{
    if (head == nullptr)
    {
        insert_at_start(head, data);
        return;
    }

    Node<T> *newNode = new Node<T>(data);
    Node<T> *slow = head;
    Node<T> *fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    newNode->next = slow->next;
    newNode->prev = slow;
    slow->next->prev = newNode;
    slow->next = newNode;
}
template <typename T>
void insert_v1_before_v2(Node<T> *&head, T v1, T v2)
{
    if (head == nullptr || head->next == nullptr)
    {
        cout << "List has less than two nodes." << endl;
        return;
    }
    if (head->data == v2)
    {
        insert_at_start(head, v1);
        return;
    }
    Node<T> *current = head;
    while (current->next != nullptr && current->next->data != v2)
    {
        current = current->next;
    }
    if (current->next == nullptr)
    {
        cout << "Node with value " << v2 << " not found in the list." << endl;
        return;
    }
    Node<T> *newNode = new Node<T>(v1);
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
}

template <typename T>
void delete_at_start(Node<T> *&head)
{
    if (head == nullptr)
    {
        cout << "List is already empty." << endl;
        return;
    }
    Node<T> *temp = head;
    head = head->next;
    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    delete temp;
}

template <typename T>
void delete_at_end(Node<T> *&head)
{
    if (head == nullptr)
    {
        cout << "List is already empty." << endl;
        return;
    }
    Node<T> *current = head;
    while (current->next->next != nullptr)
    {
        current = current->next;
    }
    Node<T> *temp = current->next;
    current->next = nullptr;
    delete temp;
}

template <typename T>
Node<T> *removeDuplicates(Node<T> *head)
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        Node<T> *temp = current;
        while (temp->next != nullptr)
        {
            if (temp->next->data == current->data)
            {

                Node<T> *duplicate = temp->next;
                temp->next = temp->next->next;

                if (temp->next != nullptr)
                    temp->next->prev = temp;
                delete duplicate;
            }
            else
            {
                temp = temp->next;
            }
        }
        current = current->next;
    }
    return head;
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
void reverse_list(Node<T> *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }
    Node<T> *current = head;
    Node<T> *prev = nullptr;
    Node<T> *next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    head = prev;
}

template <typename T>
void print_list(Node<T> *head)
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        cout << current->data << " <-> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}