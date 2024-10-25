#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int x) : data(x), next(nullptr) {}
};

Node *remove_zero_sum_node(Node *head)
{

    Node *temp = new Node(0);
    temp->next = head;
    Node *start = temp;
    while (start)
    {
        int sum = 0;
        Node *end = start->next;
        while (end)
        {
            sum += end->data;
            if (sum == 0)
            {
                start->next = end->next;
            }
            end = end->next;
        }
        start = start->next;
    }

    Node *new_node = temp->next;
    delete temp;
    return new_node;
}

void display(Node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    Node *head = new Node(3);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(-3);
    head->next->next->next->next = new Node(4);

    cout << "Original list: ";
    display(head);

    head = remove_zero_sum_node(head);
    cout << "Modified list: ";
    display(head);

    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
