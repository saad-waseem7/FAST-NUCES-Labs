#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int dfs(TreeNode *root, int &cameraCount)
{
    if (!root)
        return 1;

    int left = dfs(root->left, cameraCount);
    int right = dfs(root->right, cameraCount);

    if (left == 0 || right == 0)
    {
        cameraCount++;
        return 2;
    }
    if (left == 2 || right == 2)
    {
        return 1;
    }
    return 0;
}

int minCameraCover(TreeNode *root)
{
    int cameraCount = 0;
    if (dfs(root, cameraCount) == 0)
    {
        cameraCount++;
    }
    return cameraCount;
}

TreeNode *buildTree()
{
    cout << "Enter tree nodes level-wise (-1 for NULL):\n";
    vector<TreeNode *> nodes;
    int val;
    cin >> val;
    if (val == -1)
        return NULL;

    TreeNode *root = new TreeNode(val);
    nodes.push_back(root);

    int index = 0;
    while (index < nodes.size())
    {
        TreeNode *current = nodes[index++];
        if (!current)
            continue;

        cin >> val;
        current->left = (val == -1) ? NULL : new TreeNode(val);
        nodes.push_back(current->left);

        cin >> val;
        current->right = (val == -1) ? NULL : new TreeNode(val);
        nodes.push_back(current->right);
    }
    return root;
}

int main()
{
    TreeNode *root = buildTree();
    cout << "Minimum cameras needed: " << minCameraCover(root) << endl;
    return 0;
}
