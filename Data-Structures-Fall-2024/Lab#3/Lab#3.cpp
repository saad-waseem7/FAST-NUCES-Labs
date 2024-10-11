#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node *prev;
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
    ~Node()
    {
    }
};

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
void swap_k_nodes(Node<T> *&head, int k)
{
    if (!head || k <= 0)
    {
        return;
    }

    Node<T> *k_from_start = head;
    Node<T> *k_from_end = head;
    Node<T> *temp = head;

    int count = 1;
    while (temp != nullptr)
    {

        if (count < k)
        {
            k_from_start = k_from_start->next;
        }

        if (count > k)
        {
            k_from_end = k_from_end->next;
        }

        temp = temp->next;
        count++;
    }

    if (count - 1 < k)
    {
        cout << "K is out of bounds." << endl;
        return;
    }

    if (k_from_start != k_from_end)
    {
        T temp_data = k_from_start->data;
        k_from_start->data = k_from_end->data;
        k_from_end->data = temp_data;
    }
}

template <typename T>
Node<T> *removeDuplicates(Node<T> *head)
{
    if (!head)
        return nullptr;

    Node<T> *current = head;

    while (current != nullptr)
    {
        Node<T> *runner = current->next;
        Node<T> *prev = current;

        while (runner != nullptr)
        {
            if (runner->data == current->data)
            {
                prev->next = runner->next;
                if (runner->next != nullptr)
                {
                    runner->next->prev = prev;
                }
                Node<T> *temp = runner;
                runner = runner->next;
                delete temp;
            }
            else
            {
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return head;
}

template <typename T>
void print_list(Node<T> *head)
{
    Node<T> *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main()
{
    Node<int> *head = new Node<int>(1);
    insert_at_end(head, 2);
    insert_at_end(head, 3);
    insert_at_end(head, 4);
    insert_at_end(head, 5);
    insert_at_end(head, 2);
    insert_at_end(head, 3);

    cout << "Original List: ";
    print_list(head);
    head = removeDuplicates(head);
    cout << "After Removing Duplicates: ";
    print_list(head);

    cout << "After Swapping 1st and Last K Nodes: ";
    swap_k_nodes(head, 2);
    print_list(head);

    cout << "After Deleting Entire List: ";
    delete_full_list(head);

    return 0;
}
