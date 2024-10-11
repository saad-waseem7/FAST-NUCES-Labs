#include "Double_LL.h"

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

int main()
{
    Node<int> *head = nullptr;
    cout << "Inserting at end: " << endl;
    insert_at_end(head, 7);
    insert_at_end(head, 9);
    print_list(head);

    cout << "Inserting at start: " << endl;
    insert_at_start(head, 9);
    print_list(head);

    cout << "Inserting at end: " << endl;
    insert_at_end(head, 10);
    insert_at_end(head, 9);
    print_list(head);

    cout << "Inserting in middle: " << endl;
    insert_in_middle(head, 15);
    print_list(head);

    cout << "Finding Middle Node: " << endl;
    find_middle_Node(head);

    delete_full_list(head);

    return 0;
}