#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void buildTree(unordered_map<int, int> &parent)
{
    cout << "Enter parent-child pairs (enter -1 to stop):\n";
    int parentNode, childNode;
    while (true)
    {
        cin >> parentNode;
        if (parentNode == -1)
            break;
        cin >> childNode;
        parent[childNode] = parentNode;
    }
}

int getKthAncestor(int node, int k, unordered_map<int, int> &parent)
{
    while (k > 0 && parent.find(node) != parent.end())
    {
        node = parent[node];
        k--;
    }
    return k == 0 ? node : -1;
}

int main()
{
    unordered_map<int, int> parent;
    buildTree(parent);

    int node, k;
    cout << "Enter the node and k to find the k-th ancestor:\n";
    cin >> node >> k;

    int result = getKthAncestor(node, k, parent);
    if (result != -1)
        cout << "The " << k << "-th ancestor of node " << node << " is: " << result << endl;
    else
        cout << "The " << k << "-th ancestor of node " << node << " does not exist.\n";

    return 0;
}
