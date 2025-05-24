/*
Implementation of Singly Linked List with Functions & Time Complexities...
Time Complexities of all functions are written with them & at the end of program too...
*/

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
// Time Complexity: O(n), Inserts a new node with the given data at the end of the linked list.
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
// Time Complexity: O(1), Inserts a new node with the given data at the start of the linked list.
{
    Node<T> *newNode = new Node<T>(data);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void insert_v1_before_v2(Node<T> *&head, T v1, T v2)
// Time Complexity: O(n), Inserts a new node with value v1 before the node with value v2 in the linked list.
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
    current->next = newNode;
}

template <typename T>
bool search_node(Node<T> *&head, T data)
// Time Complexity: O(n), Searches for a node with the given data in the linked list and returns true if found, else false.
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        if (current->data == data)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename T>
bool is_empty(Node<T> *&head)
//  Time Complexity: O(1), Checks if the linked list is empty and returns true if it is, else false.
{
    return head == nullptr;
}

template <typename T>
void delete_node(Node<T> *&head, int index)
// Time Complexity: O(n), Deletes the node at the given index in the linked list.
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
void delete_at_start(Node<T> *&head)
// Time Complexity: O(1), Deletes the node at the start of the linked list.
{
    if (head == nullptr)
    {
        cout << "List is already empty." << endl;
        return;
    }
    Node<T> *temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
void delete_all_occurrence(Node<T> *&head, T data)
// Time Complexity: O(n), Deletes all occurrences of nodes with the given data in the linked list.
{
    if (head == nullptr)
    {
        cout << "List is empty." << endl;
        return;
    }

    while (head != nullptr && head->data == data)
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    Node<T> *current = head;
    while (current != nullptr && current->next != nullptr)
    {
        if (current->next->data == data)
        {
            Node<T> *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else
        {
            current = current->next;
        }
    }
}
template <typename T>
void delete_full_list(Node<T> *&head)
// Time Complexity: O(n), Deletes the entire linked list.
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
void print_list(Node<T> *head)
// Time Complexity: O(n), Prints the elements of the linked list.
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

    cout << "Original list: ";    
    print_list(head);

    delete_all_occurrence(head, 7);

    print_list(head);

    cout << "Search for 2: " << (search_node(head, 2) ? "Found" : "Not Found") << endl;
    cout << "Search for 9: " << (search_node(head, 9) ? "Found" : "Not Found") << endl;
    cout << "Search for 10: " << (search_node(head, 10) ? "Found" : "Not Found") << endl;

    delete_at_start(head);
    print_list(head);

    delete_full_list(head);
    return 0;
}

/*
insert_at_end(Node<T> *&head, T data):            O(n)
insert_at_start(Node<T> *&head, T data):          O(1)
insert_v1_before_v2(Node<T> *&head, T v1, T v2):  O(n)
search_node(Node<T> *&head, T data):              O(n)
is_empty(Node<T> *&head):                         O(1)
delete_node(Node<T> *&head, int index):           O(n)
delete_at_start(Node<T> *&head):                  O(1)
delete_all_occurrence(Node<T> *&head, T data):    O(n)
delete_full_list(Node<T> *&head):                 O(n)
print_list(Node<T> *head):                        O(n)
Note: n is the number of nodes in the linked list.
*/