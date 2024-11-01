#include <iostream>
#include <algorithm>
using namespace std;

template <typename k, typename v>
class TNode
{
public:
    k key;
    v value;
    int height;
    TNode<k, v> *leftChild;
    TNode<k, v> *rightChild;

    TNode(k key, v value)
    {
        this->key = key;
        this->value = value;
        this->height = 1;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
};

template <typename k, typename v>
class BST
{
public:
    TNode<k, v> *root;

    BST() { this->root = nullptr; }

    virtual void insert_by_Recursion(k const key, v const value)
    {
        root = insert_by_recursion(root, key, value);
    }

    virtual TNode<k, v> *insert_by_recursion(TNode<k, v> *node, k const key, v const value)
    {
        if (node == nullptr)
            return new TNode<k, v>(key, value);
        if (key < node->key)
            node->leftChild = insert_by_recursion(node->leftChild, key, value);
        else if (key > node->key)
            node->rightChild = insert_by_recursion(node->rightChild, key, value);
        return node;
    }

protected:
    v *search_recursive(TNode<k, v> *node, k key)
    {
        if (node == nullptr)
            return nullptr;
        if (node->key == key)
            return &node->value;
        if (key < node->key)
            return search_recursive(node->leftChild, key);
        else
            return search_recursive(node->rightChild, key);
    }
};

template <typename k, typename v>
class AVL : public BST<k, v>
{
public:
    AVL() : BST<k, v>() {}

    void insert(k const key, v const value)
    {
        this->root = insert_by_recursion(this->root, key, value);
    }

    TNode<k, v> *insert_by_recursion(TNode<k, v> *node, k const key, v const value) override
    {
        if (node == nullptr)
            return new TNode<k, v>(key, value);

        if (key < node->key)
            node->leftChild = insert_by_recursion(node->leftChild, key, value);
        else if (key > node->key)
            node->rightChild = insert_by_recursion(node->rightChild, key, value);
        else
            return node;

        node->height = 1 + max(height(node->leftChild), height(node->rightChild));
        int balance = get_balance(node);

        if (balance > 1 && key < node->leftChild->key)
            return right_rotate(node);
        if (balance < -1 && key > node->rightChild->key)
            return left_rotate(node);
        if (balance > 1 && key > node->leftChild->key)
        {
            node->leftChild = left_rotate(node->leftChild);
            return right_rotate(node);
        }
        if (balance < -1 && key < node->rightChild->key)
        {
            node->rightChild = right_rotate(node->rightChild);
            return left_rotate(node);
        }

        return node;
    }

    void delete_node(k key)
    {
        this->root = delete_node(this->root, key);
    }

    TNode<k, v> *delete_node(TNode<k, v> *node, k key)
    {
        if (node == nullptr)
            return node;

        if (key < node->key)
            node->leftChild = delete_node(node->leftChild, key);
        else if (key > node->key)
            node->rightChild = delete_node(node->rightChild, key);
        else
        {
            if (node->leftChild == nullptr || node->rightChild == nullptr)
            {
                TNode<k, v> *temp = node->leftChild ? node->leftChild : node->rightChild;
                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else
            {
                TNode<k, v> *temp = min_value_node(node->rightChild);
                node->key = temp->key;
                node->value = temp->value;
                node->rightChild = delete_node(node->rightChild, temp->key);
            }
        }

        if (node == nullptr)
            return node;

        node->height = 1 + max(height(node->leftChild), height(node->rightChild));
        int balance = get_balance(node);

        if (balance > 1 && get_balance(node->leftChild) >= 0)
            return right_rotate(node);
        if (balance > 1 && get_balance(node->leftChild) < 0)
        {
            node->leftChild = left_rotate(node->leftChild);
            return right_rotate(node);
        }
        if (balance < -1 && get_balance(node->rightChild) <= 0)
            return left_rotate(node);
        if (balance < -1 && get_balance(node->rightChild) > 0)
        {
            node->rightChild = right_rotate(node->rightChild);
            return left_rotate(node);
        }

        return node;
    }

    TNode<k, v> *min_value_node(TNode<k, v> *node)
    {
        TNode<k, v> *current = node;
        while (current->leftChild != nullptr)
            current = current->leftChild;
        return current;
    }

    int height(TNode<k, v> *node) const
    {
        return node == nullptr ? 0 : node->height;
    }

    int height() const
    {
        return height(this->root);
    }

    int get_balance(TNode<k, v> *node) const
    {
        return node == nullptr ? 0 : height(node->leftChild) - height(node->rightChild);
    }

    TNode<k, v> *right_rotate(TNode<k, v> *y)
    {
        TNode<k, v> *x = y->leftChild;
        TNode<k, v> *T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        y->height = max(height(y->leftChild), height(y->rightChild)) + 1;
        x->height = max(height(x->leftChild), height(x->rightChild)) + 1;

        return x;
    }

    TNode<k, v> *left_rotate(TNode<k, v> *x)
    {
        TNode<k, v> *y = x->rightChild;
        TNode<k, v> *T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        x->height = max(height(x->leftChild), height(x->rightChild)) + 1;
        y->height = max(height(y->leftChild), height(y->rightChild)) + 1;

        return y;
    }

    void inorderPrintKeys() const
    {
        inorderPrintKeys(this->root);
        cout << endl;
    }

    void inorderPrintKeys(TNode<k, v> *node) const
    {
        if (node != nullptr)
        {
            inorderPrintKeys(node->leftChild);
            cout << node->key << " ";
            inorderPrintKeys(node->rightChild);
        }
    }

    v *search(k key)
    {
        return this->search_recursive(this->root, key);
    }
};

int main()
{
    AVL<int, int> tree;
    for (int i = 1; i <= 100; i++)
        tree.insert(i, i);
    for (int i = -1; i >= -100; i--)
        tree.insert(i, i);
    for (int i = 150; i > 100; i--)
        tree.insert(i, i);
    for (int i = -150; i < -100; i++)
        tree.insert(i, i);
    for (int i = 150; i > 100; i--)
        tree.delete_node(i);

    tree.inorderPrintKeys();
    cout << endl
         << endl;
    cout << "Tree Height: " << tree.height() << endl;

    int *val = tree.search(-100);
    if (val != nullptr)
    {
        cout << "Key= -100 found" << endl;
    }
    val = tree.search(-151);
    if (val == nullptr)
    {
        cout << "Key= -151 not found" << endl;
    }

    return 0;
}
