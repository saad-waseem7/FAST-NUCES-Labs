#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void constructGraph(const vector<vector<int>> &connections, unordered_map<int, vector<int>> &adjacencyList)
{
    for (const auto &link : connections)
    {
        int nodeA = link[0];
        int nodeB = link[1];
        adjacencyList[nodeA].push_back(nodeB);
        adjacencyList[nodeB].push_back(nodeA);
    }
}

int depthFirstSearch(int currentNode, int parentNode, unordered_map<int, vector<int>> &adjacencyList,
                     const vector<int> &hasCoin, int &travelCost)
{
    bool containsCoin = (hasCoin[currentNode] == 1);

    for (int adjacentNode : adjacencyList[currentNode])
    {
        if (adjacentNode != parentNode)
        {
            int childContainsCoin = depthFirstSearch(adjacentNode, currentNode, adjacencyList, hasCoin, travelCost);
            if (childContainsCoin)
            {
                travelCost += 2;
                containsCoin = true;
            }
        }
    }

    return containsCoin;
}

int findMinTravelCost(int totalNodes, vector<vector<int>> &connections, vector<int> &hasCoin)
{
    unordered_map<int, vector<int>> adjacencyList;
    constructGraph(connections, adjacencyList);

    int travelCost = 0;
    depthFirstSearch(0, -1, adjacencyList, hasCoin, travelCost);
    return travelCost;
}

int main()
{
    vector<int> hasCoin = {1, 0, 0, 0, 0, 1};
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};

    int totalNodes = hasCoin.size();
    cout << "Minimum Cost to Collect All Coins: " << findMinTravelCost(totalNodes, connections, hasCoin) << endl;

    return 0;
}
