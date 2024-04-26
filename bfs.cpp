#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;
// Graph representation using adjacency list
class Graph
{
public:
    int vertices;
    vector<vector<int>> adjList;
    Graph(int V) : vertices(V), adjList(V) {}
    // Function to add an edge to the graph
    void addEdge(int v, int w)
    {
        adjList[v].push_back(w);
        adjList[w].push_back(v);
    }
};
// Parallel Breadth First Search
void parallelBFS(const Graph &graph, int source)
{
    vector<bool> visited(graph.vertices, false);
    queue<int> bfsQueue;
    bfsQueue.push(source);
    visited[source] = true;
    while (!bfsQueue.empty())
    {
        int currentVertex = bfsQueue.front();
        cout << currentVertex << " ";
#pragma omp parallel for
        for (int i = 0; i < graph.adjList[currentVertex].size(); i++)
        {
            int neighbor = graph.adjList[currentVertex][i];
            if (!visited[neighbor])
            {
#pragma omp critical
                {
                    bfsQueue.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        bfsQueue.pop();
    }
}
int main()
{
    // Example usage
    Graph graph(6);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    cout << "Parallel BFS starting from vertex 0: ";
    parallelBFS(graph, 0);
    cout << endl;
    return 0;
}

/*
openMP execution
g++ -fopenmp programName.cpp -o programName
./programName
*/