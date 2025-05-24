#include "Double_LL.h"

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

    cout << "Deleting all Duplicates: " << endl;
    head = removeDuplicates(head);
    print_list(head);

    cout << "Inserting a value before other: " << endl;
    insert_v1_before_v2(head, 6, 15);
    print_list(head);

    cout << "Reversing List: " << endl;
    reverse_list(head);
    print_list(head);

    delete_full_list(head);
    print_list(head);

    return 0;
}
