#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_VERTEX 6

struct Vertex {
    char name;
    int mark;
    struct Node* list;
};
struct Node {
    struct Vertex* vertex;
    struct Node* next;
};
struct Vertex* new_vertex(char name) {
    struct Vertex* vertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    vertex->name = name;
    vertex->list = 0;
    return vertex;
}
void connect(struct Vertex* a, struct Vertex* b) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->vertex = b;
    node->next = a->list;
    a->list = node;
}
void visit(struct Vertex* vertex) {
    printf (" %c", vertex->name);
}
void do_dfs(struct Vertex *vertex, int* count) {
    struct Node* p = vertex->list;
    vertex->mark = ++(*count);
    visit (vertex);
    while (p != 0) {
        if (!p->vertex->mark) 
            do_dfs (p->vertex, count);
        p = p->next;
    }
}
void dfs(struct Vertex *graph[]) {
    int i;
    int count = 0;
    for (i = 0; i < NUM_OF_VERTEX; i ++) 
        graph[i]->mark = 0;
    
    for (i = 0; i < NUM_OF_VERTEX; i ++) 
        if (graph[i]->mark == 0) 
            do_dfs (graph[i], &count);
}
void do_bfs(struct Vertex *vertex, int* count) {
    struct Node *iqueue, *front, *rear, *p, *temp;
    struct Vertex *w;
    vertex->mark = ++(*count);
    visit (vertex);
    iqueue = (struct Node*)malloc(sizeof(struct Node));
    iqueue->vertex = vertex;
    iqueue->next = 0;
    front = iqueue;
    rear  = iqueue;
    while (front != 0) {
        p = front->vertex->list;
        while (p != 0) {
            w = p->vertex;
            if (w->mark == 0) {
                struct Node* nqueue;
                w->mark = ++(*count);
                visit (w);
                nqueue = (struct Node*)malloc(sizeof(struct Node));
                nqueue->vertex = w;
                nqueue->next = 0;
                rear->next = nqueue;
                rear = nqueue;
            }
            p = p->next;
        }
        temp = front;
        front = front->next;
        free (temp);
    }
}
void bfs(struct Vertex *graph[]) {
    int i;
    int count = 0;
    for (i = 0; i < NUM_OF_VERTEX; i ++) 
        graph[i]->mark = 0;
    
    for (i = 0; i < NUM_OF_VERTEX; i ++) 
        if (graph[i]->mark == 0) 
            do_bfs (graph[i], &count);
}
int main() 
{
    struct Vertex *graph[NUM_OF_VERTEX] = {
        new_vertex('A'), //[0]
        new_vertex('B'), //[1]
        new_vertex('C'), //[2]
        new_vertex('D'), //[3]
        new_vertex('E'), //[4]
        new_vertex('F'), //[5]
    };    

    connect(graph[0],graph[4]);connect(graph[0],graph[3]);connect(graph[0],graph[1]);connect(graph[1],graph[3]);connect(graph[2],graph[1]);
    connect(graph[1],graph[2]);connect(graph[2],graph[3]);connect(graph[4],graph[3]);connect(graph[3],graph[5]);connect(graph[5],graph[2]);

    printf("\nDFS: ");
    dfs(graph);

    printf("\nBFS: ");
    bfs(graph);
    printf("\n");
}