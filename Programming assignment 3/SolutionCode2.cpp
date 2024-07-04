#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int queue[100000];
int front;
int rear;
int num;

// Function to initialize the queue
void initializeQueue()
{
    num = 0;
    front = 0;
    rear = 0;
}

// Function to enqueue an element
void enqueue(int x)
{
    if (num == 100000)
        return; // Queue full
    queue[rear] = x;
    rear = (rear + 1) % 100000;
    num++;
}

// Function to dequeue an element
int dequeue()
{
    int x = queue[front];
    front = (front + 1) % 100000;
    num--;
    return x;
}

// Function to mark cycle nodes in the graph
void markCycle(int currVertex, int vertex, vector<int>& parent, vector<int>& cycle)
{
    while (currVertex != vertex)
    {
        cycle[currVertex] = 1;
        cycle[vertex] = 1;
        currVertex = parent[currVertex];
        vertex = parent[vertex];
    }
    cycle[currVertex] = 1;
}

// Function to mark cycle nodes in the graph with one step difference in distance
void markCycleWithOneStepDifference(int currVertex, int vertex, vector<int>& parent, vector<int>& cycle)
{
    cycle[currVertex] = 1;
    currVertex = parent[currVertex];
    while (currVertex != vertex)
    {
        cycle[currVertex] = 1;
        cycle[vertex] = 1;
        currVertex = parent[currVertex];
        vertex = parent[vertex];
    }
    cycle[currVertex] = 1;
}

// Function to find cycles in the graph using BFS
void findCycles(vector<vector<int> >& edges, vector<int>& visited, vector<int>& cycle, vector<int>& parent, vector<int>& distance, int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            parent[i] = 1; // Initialize parent of the starting vertex
            distance[i] = 1; // Initialize distance of the starting vertex
            initializeQueue();
            enqueue(i);
            while (num != 0)
            {
                int vertex = dequeue();
                int neighbours = edges[vertex][0];
                for (int j = 1; j <= neighbours; j++)
                {
                    int currVertex = edges[vertex][j];
                    if (!visited[currVertex])
                    {
                        distance[currVertex] = distance[vertex] + 1;
                        visited[currVertex] = 1;
                        parent[currVertex] = vertex;
                        enqueue(currVertex);
                    }
                    else if (visited[currVertex] && parent[vertex] != currVertex)
                    {
                        if (distance[currVertex] == distance[vertex])
                            markCycle(currVertex, vertex, parent, cycle); // Found a cycle of even length
                        else if (distance[currVertex] == distance[vertex] + 1)
                            markCycleWithOneStepDifference(currVertex, vertex, parent, cycle); // Found a cycle of odd length
                    }
                }
            }
        }
    }
    
    // Output the cycle array indicating whether each vertex is part of a cycle
    for (int i = 1; i <= n; i++)
    {
        cout << cycle[i] << " ";
    }
}

int main()
{
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;
    
    // Reading edges from input
    vector<int> edgeStarts;
    vector<int> edgeEnds;
    for (int i = 0; i < numEdges; i++)
    {
        int start, end;
        cin >> start >> end;
        edgeStarts.push_back(start);
        edgeEnds.push_back(end);
    }
    
    // Creating adjacency list representation of the graph
    vector<vector<int> > edges;
    for (int i = 0; i <= numVertices; i++)
    {
        vector<int> temp;
        temp.push_back(0); // Degree of the vertex
        edges.push_back(temp);
    }
    
    for (int i = 0; i < numEdges; i++)
    {
        edges[edgeStarts[i]][0]++;
        edges[edgeStarts[i]].push_back(edgeEnds[i]);
        edges[edgeEnds[i]][0]++;
        edges[edgeEnds[i]].push_back(edgeStarts[i]);
    }
    
    // Arrays to track visited vertices, parent vertices, distances, and cycle status
    vector<int> visited(numVertices + 1, 0);
    vector<int> cycle(numVertices + 1, 0);
    vector<int> parent(numVertices + 1, 0);
    vector<int> distance(numVertices + 1, 0);
    
    // Find cycles in the graph
    findCycles(edges, visited, cycle, parent, distance, numVertices, numEdges);
    
    return 0;
}
