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

/*

>>>Available Functions (Utilized Templates in all)...

insert_at_end(*&head, data):                  ->> Insert at End of List
insert_at_start(*&head, data):                ->> Insert at Start of List
insert_v1_before_v2(*&head, v1, v2):          ->> Insert one value before another value
insert_in_middle(*&head):                     ->> Insert a node before the middle node of list
delete_node(*&head, index):                   ->> Delete the node at given index
delete_at_start(*&head):                      ->> Delete Head
delete_at_end(*&head):                        ->> Delete the last node
removeDuplicates(*&head):                     ->> Delete all duplicate nodes
delete_full_list(*&head):                     ->> Free memory of Whole List
insert_at_position(*&head, position, data):   ->> Insert a new node with the given data at the given position (not developed yet)
reverse_list(*&head):                         ->> Reverses the linked list (by iterating)
find_middle(*head):                           ->> Find and Print the middle node
swap_k_nodes(*&head, k):                      ->> Swap the k-th node from start with end
length_of_list(*&head):                       ->> Return the length of the list (int)
print_list(*head):                            ->> Prints The List

*/

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
void delete_node(Node<T> *&head, int index)
{
    if (head == nullptr)
    {
        cout << "List is already empty." << endl;
        return;
    }
    if (index == 0)
    {
        delete_at_start(head);
        return;
    }
    Node<T> *current = head;
    for (int i = 0; i < index - 1 && current->next != nullptr; i++)
    {
        current = current->next;
    }
    if (current->next == nullptr || current->next->next == nullptr)
    {
        cout << "Index out of range." << endl;
        return;
    }
    Node<T> *temp = current->next;
    current->next = current->next->next;
    current->next->prev = current;
    delete temp;
}
template <typename T>
void swap_k_nodes(Node<T> *&head, int k)
{
    if (head == nullptr || k <= 0)
    {
        return;
    }
    int length = 0;
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        length++;
        temp = temp->next;
    }
    if (k > length)
    {
        cout << "K is out of bounds." << endl;
        return;
    }
    Node<T> *k_from_beginning = head;
    for (int i = 1; i < k; i++)
    {
        k_from_beginning = k_from_beginning->next;
    }
    Node<T> *k_from_end = head;
    for (int i = 1; i < length - k + 1; i++)
    {
        k_from_end = k_from_end->next;
    }
    T temp_data = k_from_beginning->data;
    k_from_beginning->data = k_from_end->data;
    k_from_end->data = temp_data;
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
void find_middle_Node(Node<T> *&head)
{
    if (!head || !head->next)
    {
        cout << "List has less than two Nodes." << endl;
        return;
    }

    Node<T> *slow = head;
    Node<T> *fast = head;
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    cout << "Middle Node: " << slow->data << endl;
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
int length_of_list(Node<T> *head)
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
{
    Node<T> *current = head;
    while (current != nullptr)
    {
        cout << current->data << " <-> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}