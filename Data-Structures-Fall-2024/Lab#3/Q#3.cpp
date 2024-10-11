#include "Double_LL.h"

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

int main()
{
    Node<int> *head = nullptr;
    cout << "Inserting at end: " << endl;
    insert_at_end(head, 7);
    insert_at_end(head, 9);
    print_list(head);

    cout << "Inserting at start: " << endl;
    insert_at_start(head, 9);
    insert_at_start(head, 12);
    print_list(head);

    cout << "Inserting at end: " << endl;
    insert_at_end(head, 10);
    insert_at_end(head, 9);
    print_list(head);

    cout << "Inserting in middle: " << endl;
    insert_in_middle(head, 15);
    print_list(head);

    cout << "K_Node Swap Function Test (index 3)" << endl;
    swap_k_nodes(head, 3);
    print_list(head);

    delete_full_list(head);
    return 0;
}