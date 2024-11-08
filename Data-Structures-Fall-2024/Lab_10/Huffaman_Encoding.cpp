#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Node
{
public:
    char data;
    int frequency;
    Node *left;
    Node *right;

    Node(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(Node *a, Node *b)
    {
        return a->frequency > b->frequency;
    }
};

void printHuffmanCodes(Node *node, string code)
{
    if (!node)
        return;

    if (!node->left && !node->right)
    {
        cout << "Character: " << node->data << ", Frequency: " << node->frequency << ", Code: " << code << endl;
    }

    printHuffmanCodes(node->left, code + "0");
    printHuffmanCodes(node->right, code + "1");
}

void buildHuffmanTree(const string &filename)
{

    unordered_map<char, int> frequencyMap;
    ifstream file(filename);
    char ch;
    while (file >> ch)
    {
        frequencyMap[ch]++;
    }
    file.close();

    priority_queue<Node *, vector<Node *>, Compare> minHeap;
    for (auto &pair : frequencyMap)
    {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();

        Node *newNode = new Node('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }
    Node *root = minHeap.top();

    printHuffmanCodes(root, "");
}


int main()
{
    string filename = "Input.txt";
    buildHuffmanTree(filename);
    return 0;
}
