#include <iostream>
#include <stack>
using namespace std;

template <typename k, typename v>
class TNode
{
public:
    k key;
    v value;
    TNode<k, v> *leftChild;
    TNode<k, v> *rightChild;
    TNode(k key, v value)
    {
        this->key = key;
        this->value = value;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
    ~TNode() {}
};

template <typename k, typename v>
class BST
{
public:
    TNode<k, v> *root;

    BST()
    {
        this->root = nullptr;
    }

    BST(TNode<k, v> *root)
    {
        this->root = root;
    }

    void insert_by_Recursion(k const key, v const value)
    {
        root = insert_by_recursion(root, key, value);
    }

    TNode<k, v> *insert_by_recursion(TNode<k, v> *node, k const key, v const value)
    {
        if (node == nullptr)
            return new TNode<k, v>(key, value);
        if (key < node->key)
            node->leftChild = insert_by_recursion(node->leftChild, key, value);
        else if (key > node->key)
            node->rightChild = insert_by_recursion(node->rightChild, key, value);
        return node;
    }

    void insert_by_iteration(k const key, v const value)
    {
        TNode<k, v> *newNode = new TNode<k, v>(key, value);
        if (root == nullptr)
            root = newNode;
        else
        {
            TNode<k, v> *current = root;
            while (true)
            {
                if (key < current->key)
                {
                    if (current->leftChild == nullptr)
                    {
                        current->leftChild = newNode;
                        break;
                    }
                    current = current->leftChild;
                }
                else if (key > current->key)
                {
                    if (current->rightChild == nullptr)
                    {
                        current->rightChild = newNode;
                        break;
                    }
                    current = current->rightChild;
                }
                else
                {
                    cout << "Key already exists in the BST." << endl;
                    delete newNode;
                    break;
                }
            }
        }
    }

    v *search_by_recursion(k key)
    {
        return search_by_recursion(root, key);
    }

    v *search_by_recursion(TNode<k, v> *node, k key)
    {
        if (node == nullptr)
            return nullptr;
        if (node->key == key)
            return &node->value;
        if (key < node->key)
            return search_by_recursion(node->leftChild, key);
        else
            return search_by_recursion(node->rightChild, key);
    }

    void inorder_print_keys_by_recursion() const
    {
        inorder_print_keys_by_recursion(root);
    }

    void inorder_print_keys_by_recursion(TNode<k, v> *node) const
    {
        if (node == nullptr)
            return;
        inorder_print_keys_by_recursion(node->leftChild);
        cout << node->key << " ";
        inorder_print_keys_by_recursion(node->rightChild);
    }

    void inorder_print_keys_by_iteration() const
    {
        stack<TNode<k, v> *> s;
        TNode<k, v> *current = root;
        while (!s.empty() || current != nullptr)
        {
            while (current != nullptr)
            {
                s.push(current);
                current = current->leftChild;
            }
            if (!s.empty())
            {
                current = s.top();
                s.pop();
                cout << current->key << " ";
                current = current->rightChild;
            }
        }
        cout << endl;
    }

    int length() const
    {
        return length(root);
    }

    int length(TNode<k, v> *node) const
    {
        if (node == nullptr)
            return 0;
        return 1 + length(node->leftChild) + length(node->rightChild);
    }

    bool print_all_ancestors(TNode<k, v> *node, k key)
    {
        if (node == nullptr)
            return false;
        if (node->key == key)
            return true;
        if (print_all_ancestors(node->leftChild, key) || print_all_ancestors(node->rightChild, key))
        {
            cout << node->key << " ";
            return true;
        }
        return false;
    }

    void print_all_ancestors(k const key)
    {
        print_all_ancestors(root, key);
        cout << endl;
    }
};

int main()
{
    BST<int, int> tree;
    tree.insert_by_iteration(500, 500);
    tree.insert_by_Recursion(1000, 1000);
    tree.insert_by_iteration(1, 1);
    tree.insert_by_iteration(600, 600);
    tree.insert_by_Recursion(700, 700);
    tree.insert_by_iteration(10, 10);
    tree.insert_by_iteration(30, 30);
    tree.insert_by_Recursion(9000, 9000);
    tree.insert_by_iteration(50000, 50000);
    tree.insert_by_Recursion(20, 20);

    cout << "Printing keys using iterative inorder traversal: ";
    tree.inorder_print_keys_by_iteration();

    cout << endl
         << "Printing keys using recursive inorder traversal: ";
    tree.inorder_print_keys_by_recursion();

    cout << endl
         << "Tree Length: " << tree.length() << endl;

    int *val = tree.search_by_recursion(1);
    if (val != nullptr)
    {
        cout << "1 found" << endl;
    }
    else
    {
        cout << "1 not found" << endl;
    }

    val = tree.search_by_recursion(123);
    if (val == nullptr)
    {
        cout << "123 not found" << endl;
    }

    cout << endl
         << "Printing the keys of ancestor nodes of 20: ";
    tree.print_all_ancestors(20);

    return 0;
}
