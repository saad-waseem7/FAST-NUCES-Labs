#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Class for Book Records
class BookRecord
{
public:
    string ISSN;
    string title;
    vector<string> authors;
    int reference_copies;
    int issuable_copies;
    BookRecord *next;
    BookRecord *previous;

    BookRecord(string ISSN, string title, vector<string> authors, int reference_copies, int issuable_copies)
    {
        this->ISSN = ISSN;
        this->title = title;
        this->authors = authors;
        this->reference_copies = reference_copies;
        this->issuable_copies = issuable_copies;
        this->next = nullptr;
        this->previous = nullptr;
    }
};

// Class for AVL Tree Nodes
class AVL_Node
{
public:
    string ISSN;
    BookRecord *bookRecord;
    AVL_Node *left;
    AVL_Node *right;
    int height;

    AVL_Node(string ISSN, BookRecord *record)
    {
        this->ISSN = ISSN;
        this->bookRecord = record;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

// Helper functions for AVL Tree
int get_Height(AVL_Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->height;
}

int get_Balance(AVL_Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return get_Height(root->left) - get_Height(root->right);
}

AVL_Node *Right_Rotate(AVL_Node *node)
{
    AVL_Node *child_ptr = node->left; // Temporary child node pointer
    AVL_Node *T = child_ptr->right;   // Another temporary node pointer for right node of temporary child (pointer)
    child_ptr->right = node;          // right child of temporary child becomes root of the left subtree
    node->left = T;                   // left child of root becomes right child of temporary child
    node->height = max(get_Height(node->left), get_Height(node->right)) + 1;
    child_ptr->height = max(get_Height(child_ptr->left), get_Height(child_ptr->right)) + 1;
    return child_ptr;
}

AVL_Node *Left_Rotate(AVL_Node *node) // reverse of above...
{
    AVL_Node *child_ptr = node->right;
    AVL_Node *T = child_ptr->left;
    child_ptr->left = node;
    node->right = T;
    node->height = max(get_Height(node->left), get_Height(node->right)) + 1;
    child_ptr->height = max(get_Height(child_ptr->left), get_Height(child_ptr->right)) + 1;
    return child_ptr;
}

AVL_Node *insert_AVL(AVL_Node *node, string ISSN, BookRecord *bookRecord)
{
    if (!node)
        return new AVL_Node(ISSN, bookRecord);

    if (ISSN < node->ISSN)
        node->left = insert_AVL(node->left, ISSN, bookRecord);
    else if (ISSN > node->ISSN)
        node->right = insert_AVL(node->right, ISSN, bookRecord);
    else
        return node;

    node->height = max(get_Height(node->left), get_Height(node->right)) + 1;
    int balance = get_Balance(node);

    if (balance > 1 && ISSN < node->left->ISSN)
        return Right_Rotate(node);

    else if (balance < -1 && ISSN > node->right->ISSN)
        return Left_Rotate(node);

    else if (balance > 1 && ISSN > node->left->ISSN)
    {
        node->left = Left_Rotate(node->left);
        return Right_Rotate(node);
    }
    else if (balance < -1 && ISSN < node->right->ISSN)
    {
        node->right = Right_Rotate(node->right);
        return Left_Rotate(node);
    }
    else
        return node;
}

AVL_Node *min_Node(AVL_Node *node)
{
    AVL_Node *temp = node;
    while (temp->left)
    {
        temp = temp->left;
    }
    return temp;
}

AVL_Node *delete_AVL(AVL_Node *root, string ISSN)
{
    if (!root)
        return root;

    if (ISSN < root->ISSN)
        root->left = delete_AVL(root->left, ISSN);

    else if (ISSN > root->ISSN)
        root->right = delete_AVL(root->right, ISSN);

    else
    {
        if (!root->left || !root->right)
        {
            AVL_Node *temp = root->left ? root->left : root->right;
            if (!temp)
                return nullptr;
            else
                *root = *temp;
            delete temp;
        }
        else
        {
            AVL_Node *temp = min_Node(root->right);
            root->ISSN = temp->ISSN;
            root->bookRecord = temp->bookRecord;
            root->right = delete_AVL(root->right, temp->ISSN);
        }
    }

    root->height = max(get_Height(root->left), get_Height(root->right)) + 1;
    int balance = get_Balance(root);

    if (balance > 1 && get_Balance(root->left) >= 0)
        return Right_Rotate(root);

    else if (balance < -1 && get_Balance(root->right) <= 0)
        return Left_Rotate(root);

    else if (balance > 1 && get_Balance(root->left) < 0)
    {
        root->left = Left_Rotate(root->left);
        return Right_Rotate(root);
    }
    else if (balance < -1 && get_Balance(root->right) > 0)
    {
        root->right = Right_Rotate(root->right);
        return Left_Rotate(root);
    }
    else
        return root;
}

// Doubly Linked List functions
void insert_Double_LL(BookRecord *&head, BookRecord *&tail, BookRecord *new_Rec)
{
    if (!head)
    {
        head = tail = new_Rec;
        return;
    }

    BookRecord *current = head;
    while (current && current->ISSN < new_Rec->ISSN)
        current = current->next;

    if (!current)
    {
        tail->next = new_Rec;
        new_Rec->previous = tail;
        tail = new_Rec;
    }
    else
    {
        new_Rec->next = current;
        new_Rec->previous = current->previous;
        if (current->previous)
            current->previous->next = new_Rec;
        else
            head = new_Rec;
        current->previous = new_Rec;
    }
}

void delete_Double_LL(BookRecord *&head, BookRecord *&tail, string ISSN)
{
    BookRecord *current = head;
    while (current && current->ISSN != ISSN)
        current = current->next;

    if (!current)
        return;

    if (current->previous)
        current->previous->next = current->next;
    else
        head = current->next;

    if (current->next)
        current->next->previous = current->previous;
    else
        tail = current->previous;

    delete current;
}