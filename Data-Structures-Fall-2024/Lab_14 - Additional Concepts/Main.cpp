#include <iostream>
using namespace std;

class Node
{
public:
    int value;
    Node *next;

    Node(int value)
    {
        this->value = value;
        this->next = nullptr;
    }
};

class Linked_List
{
private:
    Node *head;

public:
    Linked_List() : head(nullptr) {}

    void append(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    Node *getHead() const
    {
        return head;
    }

    Node *getReversedHead() const
    {
        Node *prev = nullptr;
        Node *current = head;
        while (current)
        {
            Node *nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        return prev;
    }

    Node *find(int value) const
    {
        Node *current = head;
        while (current)
        {
            if (current->value == value)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

class Iterator
{
private:
    Node *current;

public:
    Iterator(Node *start) : current(start) {}

    int operator*() const
    {
        return current->value;
    }

    Iterator &operator++()
    {
        if (current)
            current = current->next;
        return *this;
    }

    bool operator!=(const Iterator &other) const
    {
        return current != other.current;
    }
};

Iterator begin(const Linked_List &list)
{
    return Iterator(list.getHead());
}

Iterator end(const Linked_List &list)
{
    return Iterator(nullptr);
}

class Reverse_Iterator
{
private:
    Node *current;

public:
    Reverse_Iterator(Node *start) : current(start) {}

    int operator*() const
    {
        return current->value;
    }

    Reverse_Iterator &operator++()
    {
        if (current)
            current = current->next;
        return *this;
    }

    bool operator!=(const Reverse_Iterator &other) const
    {
        return current != other.current;
    }
};

Reverse_Iterator rbegin(const Linked_List &list)
{
    return Reverse_Iterator(list.getReversedHead());
}

Reverse_Iterator rend(const Linked_List &list)
{
    return Reverse_Iterator(nullptr);
}

int main()
{
    Linked_List list;

    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    cout << "Linked List elements (forward): ";
    for (auto it = begin(list); it != end(list); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Linked List elements (reverse): ";
    for (auto it = rbegin(list); it != rend(list); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    int searchValue = 30;
    Node *foundNode = list.find(searchValue);
    if (foundNode)
    {
        cout << "Value " << searchValue << " found in the list." << endl;
    }
    else
    {
        cout << "Value " << searchValue << " not found in the list." << endl;
    }

    return 0;
}
