#include <stdio.h>
#include <stdlib.h>

int** Creategraph(int **, int);
void DFS(int **, int *, int, int);

struct Graph    // List of vertices
{
    int data;
    struct Graph *next;
};

void FillingGraph(struct Graph *, int **, int, int);

int size;

int main()
{
    int i, j, v;
    int **graph = NULL, *visited = NULL, *List = NULL;
    struct Graph *pointer;

    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices: ");
    scanf("%d", &size);

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

    printf("Enter the number of start vertex: ");
    scanf("%d", &v);

    // <---------- ! ---------->
    DFS(graph, visited, size, v);
    // <---------- ! ---------->
    printf("\n\n");

    struct Graph *array;
    array = (struct Graph *)(malloc(sizeof(struct Graph *) * size));

    FillingGraph(array, graph, size, 0);

    for(i = 0; i < size; i++)
    {
        printf("%d:  ", i);
        pointer = (array + i);
        while(pointer -> next != NULL)
        {
            printf("%d ", pointer -> data);
            pointer = pointer -> next;
        }
        printf("\n");
    }
        //printf("%d %d\n", i, array[i].data);

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

void FillingGraph(struct Graph *array, int **graph, int size, int v)
{
    struct Graph *pointer = NULL;
    int i = v;
    pointer = (array + i);

    for(int j = 0; j < size; j++)
    {
        if(graph[i][j] == 1)
        {
            pointer -> data = j;

            pointer -> next = malloc(sizeof(struct Graph));
            pointer = pointer -> next;
            pointer -> next = NULL;
        }
    }

    i++;

    if(i < size) FillingGraph(array, graph, size, i);
}


