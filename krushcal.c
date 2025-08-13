#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge {
    int u, v, w;
};

// Comparator for qsort
int comparator(const void *p1, const void *p2) {
    struct Edge *e1 = (struct Edge *)p1;
    struct Edge *e2 = (struct Edge *)p2;
    return e1->w - e2->w;
}

// Initialize parent[] and rank[]
void makeSet(int parent[], int rank[], int vertices) {
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find parent with path compression
int findParent(int parent[], int node) {
    if (parent[node] != node)
        parent[node] = findParent(parent, parent[node]);
    return parent[node];
}

// Union by rank
void unionSet(int u, int v, int parent[], int rank[]) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (u != v) {
        if (rank[u] < rank[v]) {
            parent[u] = v;
        } else if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[v] = u;
            rank[u]++;
        }
    }
}

// Kruskal's Algorithm
int kruskalAlgo(struct Edge edges[], int vertices, int edgesCount) {
    // Sort edges by weight
    qsort(edges, edgesCount, sizeof(struct Edge), comparator);

    int parent[vertices], rank[vertices];
    makeSet(parent, rank, vertices);

    int minCost = 0;
    printf("Edges in MST:\n");
    for (int i = 0; i < edgesCount; i++) {
        int uParent = findParent(parent, edges[i].u);
        int vParent = findParent(parent, edges[i].v);

        if (uParent != vParent) {
            printf("%d -- %d == %d\n", edges[i].u, edges[i].v, edges[i].w);
            minCost += edges[i].w;
            unionSet(uParent, vParent, parent, rank);
        }
    }
    return minCost;
}

// Driver code
int main() {
    int vertices = 9;
    int edgesCount = 10;

   /* struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };*/
struct Edge edges[] = {
    {0, 1, 4},
    {0, 7, 8},
    {1, 2, 8},
    {1, 7, 11},
    {2, 3, 7},
    {2, 8, 2},
    {2, 5, 4},
    {3, 4, 9},
    {3, 5, 14},
    {4, 5, 10},
    {5, 6, 2},
    {6, 7, 1},
    {6, 8, 6},
    {7, 8, 7}
};


    int totalCost = kruskalAlgo(edges, vertices, edgesCount);
    printf("Total cost of MST: %d\n", totalCost);

    return 0;
}
