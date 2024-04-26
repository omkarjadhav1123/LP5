#include <iostream>
#include <vector>
#include <stack>
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

// Recursive Depth First Search function
void dfs(const Graph &graph, int v, vector<bool> &visited)
{
    // Mark the current node as visited
    visited[v] = true;
    cout << v << " ";

    // Recur for all vertices adjacent to this vertex
    for (int neighbor : graph.adjList[v])
    {
        if (!visited[neighbor])
        {
            dfs(graph, neighbor, visited);
        }
    }
}

// Parallel Depth First Search
void parallelDFS(const Graph &graph, int source)
{
    vector<bool> visited(graph.vertices, false);

    // Execute DFS from the source vertex in parallel
#pragma omp parallel
    {
#pragma omp single
        {
            dfs(graph, source, visited); // Start DFS from the source vertex
        }
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

    cout << "Parallel DFS starting from vertex 0: ";
    parallelDFS(graph, 0);
    cout << endl;

    return 0;
}

/*
openMP execution
g++ -fopenmp programName.cpp -o programName
./programName
*/