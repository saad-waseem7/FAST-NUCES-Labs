#include <iostream>
#include <list>
#include <vector>
#include <stack>
using namespace std;

class DirectedGraph
{
private:
    int numVertices;
    vector<list<int>> adjList;

public:
    DirectedGraph(int v) : numVertices(v), adjList(v) {}

    void addEdge(int from, int to)
    {
        adjList[from].push_back(to);
    }

    void dfsRecursiveHelper(int current, vector<bool> &visited)
    {
        visited[current] = true;
        cout << current << " ";
        for (int neighbor : adjList[current])
        {
            if (!visited[neighbor])
            {
                dfsRecursiveHelper(neighbor, visited);
            }
        }
    }

    void depthFirstSearch(int start)
    {
        vector<bool> visited(numVertices, false);
        dfsRecursiveHelper(start, visited);
        cout << endl;
    }

    bool checkPath(int start, int end)
    {
        vector<bool> visited(numVertices, false);
        stack<int> stack;
        stack.push(start);

        while (!stack.empty())
        {
            int node = stack.top();
            stack.pop();

            if (node == end)
                return true;

            if (!visited[node])
            {
                visited[node] = true;
                for (int neighbor : adjList[node])
                {
                    if (!visited[neighbor])
                    {
                        stack.push(neighbor);
                    }
                }
            }
        }

        return false;
    }

    void printReversedGraph()
    {
        vector<list<int>> reversedList(numVertices);
        for (int i = 0; i < numVertices; i++)
        {
            for (int neighbor : adjList[i])
            {
                reversedList[neighbor].push_back(i);
            }
        }

        for (int i = 0; i < numVertices; i++)
        {
            cout << i << ": ";
            for (int neighbor : reversedList[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void iterativeDFS(int start)
    {
        vector<bool> visited(numVertices, false);
        stack<int> stack;
        stack.push(start);

        while (!stack.empty())
        {
            int node = stack.top();
            stack.pop();

            if (!visited[node])
            {
                cout << node << " ";
                visited[node] = true;
            }

            for (auto it = adjList[node].rbegin(); it != adjList[node].rend(); ++it)
            {
                if (!visited[*it])
                {
                    stack.push(*it);
                }
            }
        }
        cout << endl;
    }
};

int main()
{
    DirectedGraph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    cout << "DFS Traversal starting from node 0: ";
    graph.depthFirstSearch(0);

    cout << "Is there a path from node 0 to node 4? "
         << (graph.checkPath(0, 4) ? "Yes" : "No") << endl;

    cout << "Is there a path from node 3 to node 0? "
         << (graph.checkPath(3, 0) ? "Yes" : "No") << endl;

    cout << "Reversed Graph Representation:" << endl;
    graph.printReversedGraph();

    cout << "Iterative DFS Traversal starting from node 0: ";
    graph.iterativeDFS(0);

    return 0;
}
