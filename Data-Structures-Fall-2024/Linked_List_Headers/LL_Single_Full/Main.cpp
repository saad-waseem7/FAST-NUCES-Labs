#include "Single_LL.h"
using namespace std;
int main()
{
    Node<int> *head = nullptr;

    // Testing insertion functions
    cout << "Inserting elements at start..." << endl;
    insert_at_start(head, 10);
    insert_at_start(head, 20);
    insert_at_start(head, 30);
    insert_at_start(head, 40);
    insert_at_start(head, 50);
    cout << "List after insertions at start: ";
    print_list(head);

    cout << "Inserting element 25 at position 3..." << endl;
    insert_at_position(head, 3, 25);
    cout << "List after insertion at position 3: ";
    print_list(head);

    cout << "Inserting element 60 at end..." << endl;
    insert_at_end(head, 60);
    cout << "List after insertion at end: ";
    print_list(head);

    cout << "Inserting element 5 before 10..." << endl;
    insert_v1_before_v2(head, 5, 10);
    cout << "List after inserting 5 before 10: ";
    print_list(head);

    // Testing search function
    cout << "Searching for element 25: " << (search_node(head, 25) ? "Found" : "Not Found") << endl;
    cout << "Searching for element 99: " << (search_node(head, 99) ? "Found" : "Not Found") << endl;

    // Testing length of list
    cout << "Length of the list: " << length_of_list(head) << endl;

    /*
    // Testing finding middle node
    Node<int> *middle = find_middle(head);
    cout << "Middle element: "
         << (middle != nullptr ? to_string(middle->data) : "List is empty, no middle element.")
         << endl;
    */

    // Testing finding middle node
    Node<int> *middle = find_middle(head);
    if (middle != nullptr)
    {
        cout << "Middle element: " << middle->data << endl;
    }
    else
    {
        cout << "List is empty, no middle element." << endl;
    }

    // Testing reversal of the list
    cout << "Reversing the list..." << endl;
    reverse_by_iteration(head);
    cout << "List after reversal: ";
    print_list(head);

    // Testing deletion functions
    cout << "Deleting element at start..." << endl;
    delete_at_start(head);
    cout << "List after deleting at start: ";
    print_list(head);

    cout << "Deleting element at index 2..." << endl;
    delete_node(head, 2);
    cout << "List after deleting element at index 2: ";
    print_list(head);

    cout << "Deleting all occurrences of 25..." << endl;
    delete_all_occurrence(head, 25);
    cout << "List after deleting all occurrences of 25: ";
    print_list(head);

    // Testing deletion of full list
    cout << "Deleting the entire list..." << endl;
    delete_full_list(head);
    cout << "List after deleting full list: ";
    print_list(head);

    return 0;
}
