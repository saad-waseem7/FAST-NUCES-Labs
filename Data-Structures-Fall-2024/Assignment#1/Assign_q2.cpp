#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList
{
private:
    Node *head;
    int length;

public:
    LinkedList() : head(nullptr), length(0) {}

    void append(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        length++;
    }

    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data;
            if (temp->next)
                cout << "->";
            temp = temp->next;
        }
        cout << endl;
    }

    Node *getPrevNode(int index)
    {
        if (index <= 0 || index >= length)
            return nullptr;
        Node *temp = head;
        for (int i = 0; i < index - 1; i++)
        {
            temp = temp->next;
        }
        return temp;
    }

    void swapNodes(int index1, int index2)
    {
        if (index1 == index2)
            return;

        if (index1 > index2)
            swap(index1, index2);

        Node *prev1 = nullptr, *prev2 = nullptr;
        Node *node1 = head, *node2 = head;

        if (index1 != 0)
        {
            prev1 = getPrevNode(index1);
            node1 = prev1->next;
        }
        if (index2 != 0)
        {
            prev2 = getPrevNode(index2);
            node2 = prev2->next;
        }

        if (index1 == 0)
            node1 = head;

        if (!node1 || !node2)
            return;

        if (index1 == 0)
        {
            head = node2;
        }
        else
        {
            prev1->next = node2;
        }

        if (index2 == 0)
        {
            head = node1;
        }
        else
        {
            prev2->next = node1;
        }

        Node *temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }

    void rearrangeByIndices()
    {
        int index, count = 0;
        const int MAX_INDICES = 100;
        int indices[MAX_INDICES];

        cout << "Enter indices to rearrange the linked list in descending order (-1 to stop):" << endl;

        while (true)
        {
            cin >> index;
            if (index == -1)
                break;

            if (index < 0 || index >= length)
            {
                cout << "Invalid index: " << index << endl;
            }
            else
            {
                indices[count++] = index;
            }
        }

        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count - i - 1; j++)
            {
                if (indices[j] < indices[j + 1])
                {
                    int temp = indices[j];
                    indices[j] = indices[j + 1];
                    indices[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < count - 1; i++)
        {
            swapNodes(indices[i], indices[i + 1]);
        }
    }
};

int main()
{
    LinkedList list;

    list.append(16);
    list.append(45);
    list.append(34);
    list.append(22);
    list.append(73);
    list.append(91);

    cout << "Initial linked list: ";
    list.display();

    list.rearrangeByIndices();

    cout << "Rearranged linked list: ";
    list.display();

    return 0;
}
