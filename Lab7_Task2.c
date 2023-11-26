#include <stdio.h>
#include <stdlib.h>

struct Stack   // Структура, отвечающая за элементы стека
{
    int data;
    struct Stack *next;
};
struct Stack *init(int);    // Инициализация стека
void Push(struct Stack **, int);    // Добавление элемента в стек
int Pop(struct Stack *);   // Чтение элемента из стека с последующим удалением


int** Creategraph(int **, int);
void DFS(int **, int *, int, int);
int *dfs(struct Stack *, int **, int, int);

int size, count = 0;

int main()
{
    int i, j, v;
    int **graph = NULL, *visited = NULL, *List = NULL;

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

    for(i = 0; i < size; i++)
    {
        visited[i] = 0;
    }

    printf("\n\n");
    struct Stack *list = NULL;
    // <---------- ! ---------->
    int *res = dfs(list, graph, size, v);
    // <---------- ! ---------->

    for(i = 0; i < count; i++)
    {
        printf("%d ", res[i]);
    }

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

// <--------------- Нерекурсивный обход графа в глубину --------------->
int *dfs(struct Stack *list, int **graph, int size, int v)
{
    int i = 0, j = 0, currentVertex = 0;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(graph[i][j] == 1)
            {
                count++;
                break;
            }
        }
    }

    int *visited = malloc(sizeof(int) * size);

    for(i = 0; i < size; i++)
        visited[i] = 0;

    int *result = malloc(sizeof(int) * count);
    int currentIndex = 0;

    list = init(v);
    //Push(&list, v);

    do
    {
        currentVertex = Pop(list);

        if(visited[currentVertex] == 0)
        {
            visited[currentVertex] = 1;
            result[currentIndex++] = currentVertex;

            for(i = size - 1; i >= 0; i--)
            {
                if((graph[currentVertex][i] == 1) && (visited[i] == 0))
                {
                    Push(&list, i);
                }
            }
        }
    } while(list -> next != NULL);
    //printf("\b");

    return result;
}
// <------------------------------------------------------------------------->


struct Stack *init(int element)
{
    struct Stack *p = NULL; // Создание указателя на структуру

    if((p = malloc(sizeof(struct Stack))) == NULL)  // Выделение памяти под структуру
    {
        printf("Unable to allocate memory: ");
        exit(1);
    }

    p -> data = element;    // Присваивание введённого значения полю данных
    p -> next = NULL;   // Установка на нулевой указатель

    return p;
}

void Push(struct Stack **list ,int element)
{
    struct Stack *new_element = init(element);  // Создание нового элемента

    struct Stack *tmp = *list;  // Сохранение оригинального указателя на голову

    while(tmp -> next != NULL)
    {
        tmp = tmp -> next;
    }

    tmp -> next = new_element;
}

int Pop(struct Stack *list)
{
    int res = 0;    // Результат извлеения из очереди
    int i = 0, j;   // Переменные счётчики числа элементов стека
    struct Stack *tmp = list, *p = list;   // Сохранение указателя на вершину стека

    while(list -> next != NULL) // Обход списка
    {
        list = list -> next;
        i++;
    }
    i--;

    res = list -> data; // Получение элемента стека

    struct Stack *to_delete = list; // Переназначение указателя на последний элемент

    for(j = 0; j < i; j++)
    {
    tmp = tmp -> next;    // Очередной обход списка до предпоследнего элемента
    }

    tmp -> next = NULL; // Присвоение предпоследнему элементу нулевого указателя

    // Сохранение первого листа списка
    if(p -> next != NULL) free(to_delete);    // Очистка памяти по последнему указателю

    return res;    // Возвращение значения
}
