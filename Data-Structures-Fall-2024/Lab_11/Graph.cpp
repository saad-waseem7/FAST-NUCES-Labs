#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class DirectedGraph
{
private:
    int vertices;
    vector<list<int>> adjList;

public:
    DirectedGraph(int v) : vertices(v), adjList(v) {}

    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest);
    }
    void BFS(int start)
    {
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from node " << start << ": ";
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    bool isPath(int src, int dest)
    {
        if (src == dest)
            return true;

        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[src] = true;
        q.push(src);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adjList[node])
            {
                if (neighbor == dest)
                {
                    return true;
                }
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return false;
    }
};

int main()
{
    int vertices = 5;
    DirectedGraph graph(vertices);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);
    graph.addEdge(3, 3);

    graph.BFS(2);

    int src = 1, dest = 3;
    if (graph.isPath(src, dest))
    {
        cout << "There is a path from " << src << " to " << dest << endl;
    }
    else
    {
        cout << "There is no path from " << src << " to " << dest << endl;
    }

    return 0;
}