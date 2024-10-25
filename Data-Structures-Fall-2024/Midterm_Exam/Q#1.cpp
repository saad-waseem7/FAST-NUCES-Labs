#include <iostream>
#include <cstring>
using namespace std;

// Made a single class to Implement Cstring Linked List

class Node
{
public:
    char data;
    Node *next;
    Node *prev;

    Node()
    {
        data = '\0';
        next = prev = nullptr;
    }
    Node(Node &other)
    {
        data = other.data;
        next = prev = nullptr;
    }

    ~Node()
    {
        clear();
    }

    void assign(char *source)
    {
        Node *temp = this;
        while (temp->next != NULL)
            temp = temp->next;

        while (*source != '\0')
        {
            temp->next = new Node;
            temp->next->prev = temp;
            temp = temp->next;
            temp->data = *source;
            source++;
        }
        temp->next = NULL;
        temp->prev = NULL;
    }

    bool is_palindrome()
    {
        Node *left = next;
        Node *tail = next;

        while (tail && tail->next)
        {
            tail = tail->next;
        }
        while (left != NULL && tail != NULL && left != tail && left->prev != tail)
        {
            if (left->data != tail->data)
                return false;
            left = left->next;
            tail = tail->prev;
        }
        return true;
    }

    void copy(char *destination)
    {
        Node *current = next;
        while (current)
        {
            *destination++ = current->data;
            current = current->next;
        }
        *destination = '\0';
    }

    void removeAll(Node &node)
    {
        Node *current = next;
        while (current != NULL)
        {
            Node *nextNode = current->next;
            if (node.contains(current->data))
            {
                remove_node(current);
            }
            current = nextNode;
        }
    }

    void display()
    {
        Node *temp = this;
        while (temp != NULL)
        {
            cout << temp->data << "";
            temp = temp->next;
        }
    }

    bool contains(char k)
    {
        Node *current = next;
        while (current)
        {
            if (current->data == k)
                return true;
            current = current->next;
        }
        return false;
    }

    void remove_node(Node *node)
    {
        if (!node)
            return;
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        delete node;
    }

    void clear()
    {
        Node *current = next;
        while (current != NULL)
        {
            Node *next_node = current->next;
            delete current;
            current = next_node;
        }
        next = prev = nullptr;
    }
};

int main()
{
    Node *head = new Node;
    head->assign("Hello World!");
    head->display();

    Node *palindrome = new Node;
    cout << endl;
    palindrome->assign("racecar");
    palindrome->display();

    cout << endl;

    if (palindrome->is_palindrome())
    {
        palindrome->display();
        cout << " is Palindrome" << endl;
    }
    else
    {
        cout << "Not Palindrome" << endl;
    }

    char temp[50];
    palindrome->copy(temp);
    cout << "Copied string: " << temp << endl;

    Node *head2 = new Node;
    head2->assign("Pakistan");
    Node *to_remove = new Node;
    to_remove->assign("ntias");
    head2->removeAll(*to_remove);
    head2->display();

    return 0;
}
