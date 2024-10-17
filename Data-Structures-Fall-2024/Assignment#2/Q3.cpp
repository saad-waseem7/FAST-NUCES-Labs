#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// Function to sort a queue in ascending order
void sortQueue(queue<int> &q)
{
    if (q.empty())
    {
        cout << "Queue is empty... Nothing to sort!" << endl;
        return;
    }

    // Step 1: Transfer all elements from the queue to a vector
    vector<int> vec;
    while (!q.empty())
    {
        vec.push_back(q.front());
        q.pop();
    }

    // Step 2: Sort the vector
    sort(vec.begin(), vec.end());

    // Step 3: Transfer the sorted elements back to the queue
    for (int num : vec)
    {
        q.push(num);
    }

    cout << "Queue sorted!" << endl;
}

// Function to sort the stack based on the front elements of the queues
void sortStackByQueueFront(stack<queue<int>> &s)
{
    if (s.empty())
    {
        cout << "The stack is empty... Nothing to sort!" << endl;
        return;
    }

    // Temporary stack to hold the queues
    stack<queue<int>> tempStack;

    while (!s.empty())
    {
        queue<int> q = s.top();
        s.pop();

        // Sort the current queue
        sortQueue(q);

        // Insert in sorted order into tempStack
        while (!tempStack.empty() && tempStack.top().front() > q.front())
        {
            s.push(tempStack.top());
            tempStack.pop();
        }
        tempStack.push(q);
    }

    // Restore the sorted queues back to the original stack
    while (!tempStack.empty())
    {
        s.push(tempStack.top());
        tempStack.pop();
    }

    cout << "Stack sorted based on the front elements of queues!" << endl;
}

// Function to sort all queues within a stack
void sortQueuesInStack(stack<queue<int>> &s)
{
    if (s.empty())
    {
        cout << "The stack is empty... Nothing to sort!" << endl;
        return;
    }

    // Temporary stack to hold sorted queues
    stack<queue<int>> tempStack;

    // Pop each queue from the stack, sort it, and push it into the tempStack
    while (!s.empty())
    {
        queue<int> q = s.top();
        s.pop();

        // Sort the queue
        sortQueue(q);

        // Push the sorted queue into the tempStack
        tempStack.push(q);
    }

    // Restore the sorted queues back to the original stack
    while (!tempStack.empty())
    {
        s.push(tempStack.top());
        tempStack.pop();
    }

    cout << "All queues in the stack are sorted!" << endl;
}

// A node that contains a stack of queues
class node
{
public:
    stack<queue<int>> data;
    node *next;
    node() : data(), next(nullptr) {}
};

// Linked list that manages nodes containing stacks of queues
class linkedList
{
    node *head;
    int size;

public:
    linkedList() : head(nullptr), size(0) {}

    // Insert a node containing a stack into the linked list
    void insertNode(stack<queue<int>> s)
    {
        node *newNode = new node();
        newNode->data = s;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
        cout << "Inserted a stack node" << endl;
    }

    // Insert a queue into the stack at a specific node index (1-based)
    void insertToStack(int index, queue<int> q)
    {
        node *targetNode = getNodeAtIndex(index);
        if (targetNode != nullptr)
        {
            targetNode->data.push(q);
            cout << "Inserted queue into stack at node " << index << "." << endl;
        }
    }

    // Insert an element into a specific queue in a stack
    void insertToSpecificQueue(int nodeIndex, int queueIndex, int value)
    {
        node *targetNode = getNodeAtIndex(nodeIndex);
        if (targetNode != nullptr)
        {
            stack<queue<int>> tempStack;
            int currentQueueIndex = 1;

            // Traverse through the stack
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

            // Restore the stack back to the node
            while (!tempStack.empty())
            {
                targetNode->data.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    // Delete a queue from the stack at a specific node index (1-based)
    void deleteFromStack(int index)
    {
        node *targetNode = getNodeAtIndex(index);
        if (targetNode != nullptr && !targetNode->data.empty())
        {
            targetNode->data.pop();
            cout << "Deleted top queue from stack at node " << index << "." << endl;
        }
    }

    // Delete an element from a specific queue in a stack
    void deleteFromSpecificQueue(int nodeIndex, int queueIndex)
    {
        node *targetNode = getNodeAtIndex(nodeIndex);
        if (targetNode != nullptr)
        {
            stack<queue<int>> tempStack;
            int currentQueueIndex = 1;

            // Traverse through the stack
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

            // Restore the stack back to the node
            while (!tempStack.empty())
            {
                targetNode->data.push(tempStack.top());
                tempStack.pop();
            }
        }
    }

    // Delete a node from the linked list at a specific index (1-based)
    void deleteNodeAtIndex(int index)
    {
        if (head == nullptr)
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

        node *prev = nullptr;
        int currentIndex = 1;
        while (temp != nullptr && currentIndex < index)
        {
            prev = temp;
            temp = temp->next;
            currentIndex++;
        }

        if (temp == nullptr)
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

    // Sort nodes based on the front element of the top queue in the stack
    void sortNodesByStackTop()
    {
        if (head == nullptr || head->next == nullptr)
        {
            cout << "List is empty or has only one node, no need to sort!" << endl;
            return;
        }

        bool swapped;
        node *temp;
        do
        {
            swapped = false;
            temp = head;

            while (temp->next != nullptr)
            {
                int currentFront = (temp->data).top().front();
                int nextFront = (temp->next->data).top().front();

                if (currentFront > nextFront)
                {
                    swap(temp->data, temp->next->data);
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);

        cout << "Linked list nodes sorted by top element of stack!" << endl;
    }

    // Display the entire linked list with stacks and queues
    void displayLinkedList()
    {
        node *temp = head;
        int nodeIndex = 1;

        while (temp != nullptr)
        {
            cout << "Node " << nodeIndex << ":\n";
            displayStack(temp->data); // Display the stack of queues
            temp = temp->next;
            nodeIndex++;
        }
    }

    // Sort all queues in ascending order within each node's stack
    void sortQueuesInNodes()
    {
        node *temp = head;
        while (temp != nullptr)
        {
            sortQueuesInStack(temp->data); // Sort queues within the stack
            temp = temp->next;
        }
    }

    // Sort all stacks in ascending order within each node based on queue fronts
    void sortStacksInNodes()
    {
        node *temp = head;
        while (temp != nullptr)
        {
            sortStackByQueueFront(temp->data); // Sort stack based on queue fronts
            temp = temp->next;
        }
    }

private:
    // Get node at a specific index (1-based)
    node *getNodeAtIndex(int index)
    {
        if (head == nullptr)
        {
            cout << "List is empty!" << endl;
            return nullptr;
        }

        node *temp = head;
        int currentIndex = 1;

        while (temp != nullptr)
        {
            if (currentIndex == index)
            {
                return temp;
            }
            temp = temp->next;
            currentIndex++;
        }

        cout << "Index out of range!" << endl;
        return nullptr;
    }

    // Display a stack of queues
    void displayStack(stack<queue<int>> st)
    {
        stack<queue<int>> tempStack = st;
        int stackIndex = 1;
        while (!tempStack.empty())
        {
            queue<int> q = tempStack.top();
            tempStack.pop();
            cout << "  Queue " << stackIndex << " elements: ";
            displayQueue(q);
            stackIndex++;
        }
    }

    // Display a queue
    void displayQueue(queue<int> q)
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
        cout << "\nMenu: \n";
        cout << "1. Insert a new node\n";
        cout << "2. Insert a queue into a node's stack\n";
        cout << "3. Insert an element into a specific queue\n";
        cout << "4. Delete a node\n";
        cout << "5. Delete a queue from a node's stack\n";
        cout << "6. Delete an element from a specific queue\n";
        cout << "7. Sort nodes by stack's top element\n";
        cout << "8. Sort all queues in each node\n";
        cout << "9. Display the linked list\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Insert a node with a stack of 2 queues as an example
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
            ll.insertNode(s);
            break;
        }

        case 2:
        {
            // Insert a queue into a specific node
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
            ll.insertToStack(nodeIndex, newQueue);
            break;
        }

        case 3:
        {
            // Insert an element into a specific queue in a stack
            cout << "Enter node index: ";
            cin >> nodeIndex;
            cout << "Enter queue index: ";
            cin >> queueIndex;
            cout << "Enter value to insert: ";
            cin >> value;
            ll.insertToSpecificQueue(nodeIndex, queueIndex, value);
            break;
        }

        case 4:
        {
            // Delete a node
            cout << "Enter node index to delete: ";
            cin >> nodeIndex;
            ll.deleteNodeAtIndex(nodeIndex);
            break;
        }

        case 5:
        {
            // Delete a queue from a specific node's stack
            cout << "Enter node index: ";
            cin >> nodeIndex;
            ll.deleteFromStack(nodeIndex);
            break;
        }

        case 6:
        {
            // Delete an element from a specific queue in a stack
            cout << "Enter node index: ";
            cin >> nodeIndex;
            cout << "Enter queue index: ";
            cin >> queueIndex;
            ll.deleteFromSpecificQueue(nodeIndex, queueIndex);
            break;
        }

        case 7:
        {
            // Sort nodes by top element of the stack
            ll.sortNodesByStackTop();
            break;
        }

        case 8:
        {
            // Sort all queues in each node
            ll.sortQueuesInNodes();
            break;
        }

        case 9:
        {
            // Display the linked list
            ll.displayLinkedList();
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
