/*
Implementation of Singly Linked List with Functions & Time Complexities...
Time Complexities of all functions are written with them...
*/

#include <iostream>
#include <string>
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

/*

>>>Available Functions (Utilized Templates in all)...

insert_at_end(*&head, data):                  ->> Insert at End of List
insert_at_start(*&head, data):                ->> Insert at Start of List
insert_v1_before_v2(*&head, v1, v2):          ->> Insert one value before another value
search_node(*&head, data):                    ->> bool check for presence of element
is_empty(*&head):  (Under Development)        ->> bool check for empty list
delete_node(*&head, index):                   ->> Delete the node at given index
delete_at_start(*&head):                      ->> Delete Head
delete_all_occurrence(*&head, data):          ->> Delete all occurrences of given data
delete_full_list(*&head):                     ->> Free memory of Whole List
insert_at_position(*&head, position, data):   ->> Insert a new node with the given data at the given position
reverse_by_iteration(*&head):                 ->> Reverses the linked list (by iterating)
*find_middle(*head):                          ->> Find and Return the middle node (Node *)
length_of_list(*&head):                       ->> Return the length of the list (int)
print_list(*head):                            ->> Prints The List

*/

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
void insert_at_position(Node<T> *&head, int position, T data)
// Time Complexity: O(n), Inserts a new node with the given data at the given position in the linked list.
{
    if (position <= 0)
    {
        cout << "Invalid position. Position must be greater than 0." << endl;
        return;
    }
    if (position == 1)
    {
        insert_at_start(head, data);
        return;
    }
    Node<T> *newNode = new Node<T>(data);
    Node<T> *current = head;
    for (int i = 1; i < position - 1 && current != nullptr; i++)
    {
        current = current->next;
    }
    if (current == nullptr)
    {
        cout << "Invalid position. Position exceeds the length of the list." << endl;
        delete newNode;
        return;
    }
    newNode->next = current->next;
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
void reverse_by_iteration(Node<T> *&head)
// Time Complexity: O(n), Reverses the linked list using iteration.
{
    if (head == nullptr || head->next == nullptr)
    {
        // List is already empty or has only one node
        return;
    }

    Node<T> *previous_ptr = nullptr;
    Node<T> *current_ptr = head;
    Node<T> *next_ptr = nullptr;

    while (current_ptr != nullptr)
    {
        next_ptr = current_ptr->next;     // Store next node
        current_ptr->next = previous_ptr; // Reverse the link
        previous_ptr = current_ptr;       // Move previous_ptr one step ahead
        current_ptr = next_ptr;           // Move current_ptr one step ahead
    }

    head = previous_ptr; // Update head to the new head of the reversed list
}

// Function for Middle node finding...

template <typename T>
Node<T> *find_middle(Node<T> *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head; // If the list has less than two nodes, return the head itself
    }
    Node<T> *slow_ptr = head;
    Node<T> *fast_ptr = head;
    while (fast_ptr != nullptr && fast_ptr->next != nullptr)
    {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
    }
    return slow_ptr; // Return the middle node
    // Note: This solution assumes that the linked list has at least one node
}

template <typename T>
int length_of_list(Node<T> *&head)
// Time Complexity: O(n), Returns the number of nodes in the linked list.
{
    int count = 0;
    Node<T> *current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
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
