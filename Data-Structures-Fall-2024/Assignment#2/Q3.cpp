#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

void sortQueue(queue<int> &q)
{
    if (q.empty())
    {
        cout << "Queue is empty..." << endl;
        return;
    }

    vector<int> vec;
    while (!q.empty())
    {
        vec.push_back(q.front());
        q.pop();
    }

    sort(vec.begin(), vec.end());

    for (int num : vec)
    {
        q.push(num);
    }

    cout << "Queue sorted!" << endl;
}

void sort_stack_based_on_queue_fronts(stack<queue<int>> &s)
{
    if (s.empty())
    {
        cout << "The stack is empty..." << endl;
        return;
    }

    stack<queue<int>> tempStack;

    while (!s.empty())
    {
        queue<int> q = s.top();
        s.pop();

        sortQueue(q);

        while (!tempStack.empty() && tempStack.top().front() > q.front())
        {
            s.push(tempStack.top());
            tempStack.pop();
        }
        tempStack.push(q);
    }

    while (!tempStack.empty())
    {
        s.push(tempStack.top());
        tempStack.pop();
    }

    cout << "Stack sorted based on the front elements of queues!" << endl;
}

void queues_in_stack_sort(stack<queue<int>> &s)
{
    if (s.empty())
    {
        cout << "The stack is empty..." << endl;
        return;
    }

    stack<queue<int>> tempStack;

    while (!s.empty())
    {
        queue<int> q = s.top();
        s.pop();

        sortQueue(q);

        tempStack.push(q);
    }

    while (!tempStack.empty())
    {
        s.push(tempStack.top());
        tempStack.pop();
    }

    cout << "All queues in the stack are sorted!" << endl;
}

class node
{
public:
    stack<queue<int>> data;
    node *next;
    node() : data(), next(NULL) {}
};

class linkedList
{
    node *head;
    int size;

public:
    linkedList() : head(NULL), size(0) {}

    void insert_node(stack<queue<int>> s)
    {
        node *newNode = new node();
        newNode->data = s;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
        }
        else
        {
            node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
        cout << "Inserted a stack node" << endl;
    }

    void insert_in_specific_stack(int index, queue<int> q)
    {
        node *targetNode = get_node_by_index(index);
        if (targetNode != NULL)
        {
            targetNode->data.push(q);
            cout << "Inserted queue into stack at node " << index << "." << endl;
        }
    }

    void insert_in_specific_queue(int nodeIndex, int queueIndex, int value)
    {
        node *targetNode = get_node_by_index(nodeIndex);
        if (targetNode != NULL)
        {
            stack<queue<int>> tempStack;
            int currentQueueIndex = 1;

            while (!targetNode->data.empty())
            {
                queue<int> q = targetNode->data.top();
                targetNode->data.pop();
                if (currentQueueIndex == queueIndex)
                {
                    q.push(value);
                    cout << "Inserted value " << value << " into queue " << queueIndex << " at node " << nodeIndex << "." << endl;
                }
                tempStack.push(q);
                currentQueueIndex++;
            }

            while (!tempStack.empty())
            {
                targetNode->data.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    void deletion_from_stack_by_index(int index)
    {
        node *targetNode = get_node_by_index(index);
        if (targetNode != NULL && !targetNode->data.empty())
        {
            targetNode->data.pop();
            cout << "Deleted top queue from stack at node " << index << "." << endl;
        }
    }

    void delete_from_specific_queue(int nodeIndex, int queueIndex)
    {
        node *targetNode = get_node_by_index(nodeIndex);
        if (targetNode != NULL)
        {
            stack<queue<int>> tempStack;
            int currentQueueIndex = 1;

            while (!targetNode->data.empty())
            {
                queue<int> q = targetNode->data.top();
                targetNode->data.pop();
                if (currentQueueIndex == queueIndex)
                {
                    if (!q.empty())
                    {
                        q.pop();
                        cout << "Deleted front element from queue " << queueIndex << " at node " << nodeIndex << "." << endl;
                    }
                    else
                    {
                        cout << "Queue is already empty!" << endl;
                    }
                }
                tempStack.push(q);
                currentQueueIndex++;
            }

            while (!tempStack.empty())
            {
                targetNode->data.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    void delete_node_by_index(int index)
    {
        if (head == NULL)
        {
            cout << "List is empty!" << endl;
            return;
        }

        node *temp = head;

        if (index == 1)
        {
            head = head->next;
            delete temp;
            size--;
            cout << "Deleted node at index 1." << endl;
            return;
        }

        node *prev = NULL;
        int currentIndex = 1;
        while (temp != NULL && currentIndex < index)
        {
            prev = temp;
            temp = temp->next;
            currentIndex++;
        }

        if (temp == NULL)
        {
            cout << "Index out of range!" << endl;
        }
        else
        {
            prev->next = temp->next;
            delete temp;
            size--;
            cout << "Deleted node at index " << index << "." << endl;
        }
    }

    void sorting_nodes_Stack_top_based()
    {
        if (head == NULL || head->next == NULL)
        {
            cout << "List is empty or has only one node, no need to sort!" << endl;
            return;
        }

        bool sort;
        node *temp;
        do
        {
            sort = false;
            temp = head;

            while (temp->next != NULL)
            {
                int currentFront = (temp->data).top().front();
                int nextFront = (temp->next->data).top().front();

                if (currentFront > nextFront)
                {
                    swap(temp->data, temp->next->data);
                    sort = true;
                }
                temp = temp->next;
            }
        } while (sort);

        cout << "Linked list nodes sorted by top element of stack!" << endl;
    }

    void print_LL()
    {
        node *temp = head;
        int nodeIndex = 1;

        while (temp != NULL)
        {
            cout << "Node " << nodeIndex << ":\n";
            print_stack(temp->data);
            temp = temp->next;
            nodeIndex++;
        }
    }

    void queue_in_node_sort()
    {
        node *temp = head;
        while (temp != NULL)
        {
            queues_in_stack_sort(temp->data);
            temp = temp->next;
        }
    }

    void stack_in_node_sort()
    {
        node *temp = head;
        while (temp != NULL)
        {
            sort_stack_based_on_queue_fronts(temp->data);
            temp = temp->next;
        }
    }

private:
    node *get_node_by_index(int index)
    {
        if (head == NULL)
        {
            cout << "List is empty!" << endl;
            return NULL;
        }

        node *temp = head;
        int currentIndex = 1;

        while (temp != NULL)
        {
            if (currentIndex == index)
            {
                return temp;
            }
            temp = temp->next;
            currentIndex++;
        }

        cout << "Index out of range!" << endl;
        return NULL;
    }

    void print_stack(stack<queue<int>> st)
    {
        stack<queue<int>> tempStack = st;
        int s_index = 1;
        while (!tempStack.empty())
        {
            queue<int> q = tempStack.top();
            tempStack.pop();
            cout << "  Queue " << s_index << " elements: ";
            print_queue(q);
            s_index++;
        }
    }

    void print_queue(queue<int> q)
    {
        while (!q.empty())
        {
            cout << q.front() << " ";
            q.pop();
        }
        cout << endl;
    }
};

int main()
{
    linkedList ll;
    int choice, nodeIndex, queueIndex, value;

    while (true)
    {
        cout << "\nOptions: \n"
             << "1. Insert a new node\n"
             << "2. Insert a queue into a node's stack\n"
             << "3. Insert an element into a specific queue\n"
             << "4. Delete a node\n"
             << "5. Delete a queue from a node's stack\n"
             << "6. Delete an element from a specific queue\n"
             << "7. Sort nodes by stack's top element\n"
             << "8. Sort all queues in each node\n"
             << "9. Display the linked list\n"
             << "10. End Program\n"
             << "\n>>>Enter Option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            stack<queue<int>> s;
            queue<int> q1, q2;
            q1.push(10);
            q1.push(30);
            q1.push(20);
            q2.push(15);
            q2.push(25);
            q2.push(35);
            s.push(q1);
            s.push(q2);
            ll.insert_node(s);
            break;
        }

        case 2:
        {
            cout << "Enter node index to insert the queue: ";
            cin >> nodeIndex;
            queue<int> newQueue;
            cout << "Enter elements for the new queue (-1 to stop): ";
            while (true)
            {
                cin >> value;
                if (value == -1)
                    break;
                newQueue.push(value);
            }
            ll.insert_in_specific_stack(nodeIndex, newQueue);
            break;
        }

        case 3:
        {
            cout << "Enter node index: ";
            cin >> nodeIndex;
            cout << "Enter queue index: ";
            cin >> queueIndex;
            cout << "Enter value to insert: ";
            cin >> value;
            ll.insert_in_specific_queue(nodeIndex, queueIndex, value);
            break;
        }

        case 4:
        {
            cout << "Enter node index to delete: ";
            cin >> nodeIndex;
            ll.delete_node_by_index(nodeIndex);
            break;
        }

        case 5:
        {
            cout << "Enter node index: ";
            cin >> nodeIndex;
            ll.deletion_from_stack_by_index(nodeIndex);
            break;
        }

        case 6:
        {
            cout << "Enter node index: ";
            cin >> nodeIndex;
            cout << "Enter queue index: ";
            cin >> queueIndex;
            ll.delete_from_specific_queue(nodeIndex, queueIndex);
            break;
        }

        case 7:
        {
            ll.sorting_nodes_Stack_top_based();
            break;
        }

        case 8:
        {
            ll.queue_in_node_sort();
            break;
        }

        case 9:
        {
            ll.print_LL();
            break;
        }

        case 10:
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
