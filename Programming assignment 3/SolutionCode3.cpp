#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void DFS(vector<vector<int>>& edges, vector<vector<int>>& sparseTable, vector<int>& visited, vector<int>& depth, int vertex, int parent)
{
    sparseTable[vertex][0] = parent;
    visited[vertex] = 1;
    depth[vertex] = depth[parent] + 1;
    int neighbours = edges[vertex][0];
    for (int i = 1; i <= neighbours; i++)
    {
        int child = edges[vertex][i];
        if (!visited[child])
        {
            DFS(edges, sparseTable, visited, depth, child, vertex);
        }
    }
}

void DFSfinal(vector<vector<int>>& edges, vector<int>& breadcrumbs, vector<int>& visited, int vertex)
{
    visited[vertex] = 1;
    int neighbours = edges[vertex][0];
    int initial = breadcrumbs[vertex];
    for (int i = 1; i <= neighbours; i++)
    {
        int child = edges[vertex][i];
        if (!visited[child])
        {
            DFSfinal(edges, breadcrumbs, visited, child);
            breadcrumbs[vertex] += breadcrumbs[child];
        }
    }
}

void makeSparseTable(vector<vector<int>>& edges, vector<vector<int>>& sparseTable, vector<int>& depth, int n)
{
    for (int i = 1; i < 20; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (sparseTable[j][i - 1] != -1)
            {
                sparseTable[j][i] = sparseTable[sparseTable[j][i - 1]][i - 1];
            }
        }
    }
}

int lowestCommonAncestor(int a, int b, vector<vector<int>>& sparseTable, vector<int>& depth)
{
    int u = (depth[a] >= depth[b]) ? a : b;
    int v = (depth[a] >= depth[b]) ? b : a;
    while (depth[u] != depth[v])
    {
        int depthDiff = depth[u] - depth[v];
        int climb = floor(log2(depthDiff));
        u = sparseTable[u][climb];
    }
    if (u == v)
        return u;
    for (int top = 19; top >= 0; top--)
    {
        if (sparseTable[u][top] != sparseTable[v][top])
        {
            u = sparseTable[u][top];
            v = sparseTable[v][top];
        }
    }

    return sparseTable[u][0];
}

int main()
{
    int n, k;
    cin >> n >> k;

    // Reading edges
    vector<int> startNodes;
    vector<int> endNodes;
    for (int i = 0; i < n - 1; i++)
    {
        int temp;
        cin >> temp;
        startNodes.push_back(temp);
    }
    for (int i = 0; i < n - 1; i++)
    {
        int temp;
        cin >> temp;
        endNodes.push_back(temp);
    }

    // Constructing adjacency list
    vector<vector<int>> edges(n + 1, vector<int>());
    for (int i = 0; i < n - 1; i++)
    {
        edges[startNodes[i]].push_back(endNodes[i]);
        edges[endNodes[i]].push_back(startNodes[i]);
    }

    // Initializing arrays
    vector<int> visited(n + 1, 0);
    vector<int> depth(n + 1, 0);
    vector<vector<int>> sparseTable(n + 1, vector<int>(20, -1));
    depth[0] = 0;
    visited[0] = 1;

    // Performing DFS and building sparse table
    DFS(edges, sparseTable, visited, depth, 1, 0);
    makeSparseTable(edges, sparseTable, depth, n);

    vector<int> breadcrumbs(n + 1, 0);
    vector<int> ancestorArray(n + 1, 0);

    // Processing queries
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        int ancestor = lowestCommonAncestor(u, v, sparseTable, depth);
        breadcrumbs[u]++;
        breadcrumbs[v]++;
        breadcrumbs[ancestor] -= 2;
        ancestorArray[ancestor]++;
    }

    // Final DFS to compute results
    DFSfinal(edges, breadcrumbs, visited, 1);

    // Outputting the result
    for (int i = 1; i <= n; i++)
    {
        cout << ancestorArray[i] + breadcrumbs[i] << " ";
    }
    cout << endl;

    return 0;
}
