#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** Creategraph(int **, int);
void DFS(int **, int *, int, int);

int size;

// <---------- Список смежности ---------->
struct node
{
    int vertex;
    struct node* next;
};
struct node* createNode(int);
struct Graph
{
    int numVertices;
    struct node** adjLists;
};
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
// <---------- ! ---------->

void ListDFS(struct Graph*, int *, int);

int main()
{
    int i, j, v, num;
    int **graph = NULL, *visited = NULL, *List = NULL;

    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);
    num = size - 1;

    // Creating the graph
    graph = Creategraph(graph, size);
    visited = (int *)(malloc(sizeof(int *) * size));  // Array for visited vertices
    List = (int *)(malloc(sizeof(int *) * size));

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    printf("Enter the number of start vertex (positive integer [0; %d]): ", num);
    scanf("%d", &v);

    // <---------- ! ---------->
    DFS(graph, visited, size, v);
    // <---------- ! ---------->
    printf("\n\n");



// <---------- Список смежности ---------->
    struct Graph* graf = createGraph(size);

    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {
            if(graph[i][j] == 1)
            {
                addEdge(graf, i, j);
            }
        }
    }

    printf("\n# Adjacency list #\n");
    printGraph(graf);
// <---------- ! ---------->

    for(i = 0; i < size; i++)
        visited[i] = 0;

    printf("\nEnter the number of start vertex (positive integer[0; %d]): ", num);
    scanf("%d", &v);
    ListDFS(graf, visited, v);

    free(graph);
    free(visited);

    return 0;
}


void DFS(int **graph, int *visited, int size, int v)
{
    int i;
    visited[v] = 1;
    printf("%d ", v);

    for(i = 0; i < size; i++)
    {
        if((graph[v][i] == 1) && (visited[i] == 0)) DFS(graph, visited, size, i);
    }
}



int** Creategraph(int **graph, int size)
{
    srand(time(NULL));

    int i = 0, j = 0;

    // Memory allocation
    graph = (int **)(malloc(sizeof(int *) * size));
    for(i = 0; i < size; i++)
        graph[i] = (int *)(malloc(sizeof(int *) * size));

    // Filling the matrix
    for(i = 0; i < size; i++)
        for(j = i; j < size; j++)
        {
            graph[i][j] = rand() % 2;
            graph[j][i] = graph[i][j];
            if(i == j) graph[i][j] = 0;
            if(graph[i][j] == 1);
        }

    return graph;
}


// <---------- Список смежности ---------->
struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("%d:  ", v);
        while (temp)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void ListDFS(struct Graph* graph, int *visited, int v)
{
    visited[v] = 1;
    printf("%d ", v);
    struct node* temp = graph->adjLists[v];
    while (temp)
        {
            if(visited[temp->vertex] == 0)
            {
                ListDFS(graph, visited, temp->vertex);
            }
            else
            {
                temp = temp -> next;
            }
        }
}
