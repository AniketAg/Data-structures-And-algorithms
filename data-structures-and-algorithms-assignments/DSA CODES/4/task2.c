#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
struct adjlist
{
    int dest, weight;
    struct adjlist* next;
};
struct alist
{
    struct adjlist *head;  // pointer to head node of list
};
struct Graph
{
    int V;
    struct alist* arr;
};
struct min_node
{
    int  v,dist;
};
struct min_heap
{
    int size,capacity; 
    int *pos;
    struct min_node **arr;
};

struct Graph* create_graph(int V);
void adding(struct Graph* graph, int src, int dest, int weight);
void dijkstra(struct Graph* graph, int src);
void OrderOfPermanentArr(int dist[], int n);
int main()
{
    int V = 7;
    struct Graph* graph = create_graph(V);
    adding(graph, 0, 1,  1);adding(graph, 0, 2,  3);adding(graph, 0, 5, 10);adding(graph, 1, 6,  2);adding(graph, 1, 3,  7);adding(graph, 1, 2,  1);
    adding(graph, 1, 4,  5);adding(graph, 2, 3,  9);adding(graph, 2, 4,  3);adding(graph, 3, 4,  2);adding(graph, 3, 6, 12);adding(graph, 3, 5,  1);
    adding(graph, 4, 5,  2);
    
    dijkstra(graph, 0);
 
    return 0;
}
struct adjlist* n_adjlist(int dest, int weight)
{
    struct adjlist* node = (struct adjlist*) malloc(sizeof(struct adjlist));
    node->dest = dest;
    node->weight = weight;
    node->next = NULL;
    return node;
}
struct Graph* create_graph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->arr = (struct alist*) malloc(V * sizeof(struct alist));
    for (int i = 0; i < V; ++i)
        graph->arr[i].head = NULL;
    return graph;
}
void adding(struct Graph* graph, int src, int dest, int weight)
{
    struct adjlist* node = n_adjlist(dest, weight);
    node->next = graph->arr[src].head;
    graph->arr[src].head = node;
    node = n_adjlist(src, weight);
    node->next = graph->arr[dest].head;
    graph->arr[dest].head = node;
}
struct min_node* newmin_node(int v, int dist)
{
    struct min_node* mheapnode = (struct min_node*) malloc(sizeof(struct min_node));
    mheapnode->v = v;
    mheapnode->dist = dist;
    return mheapnode;
}
struct min_heap* createmin_heap(int capacity)
{
    struct min_heap* mheap = (struct min_heap*) malloc(sizeof(struct min_heap));
    mheap->pos = (int *)malloc(capacity * sizeof(int));
    mheap->size = 0;
    mheap->capacity = capacity;
    mheap->arr = (struct min_node**) malloc(capacity * sizeof(struct min_node*));
    return mheap;
}
void swapmin_node(struct min_node** a, struct min_node** b)
{
    struct min_node* t = *a;
    *a = *b;
    *b = t;
}
void mheapify(struct min_heap* mheap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < mheap->size && mheap->arr[left]->dist < mheap->arr[smallest]->dist )
      smallest = left;
 
    if (right < mheap->size && mheap->arr[right]->dist < mheap->arr[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        struct min_node *snode = mheap->arr[smallest];
        struct min_node *idxnode = mheap->arr[idx];
 
        mheap->pos[snode->v] = idx;
        mheap->pos[idxnode->v] = smallest;
 
        swapmin_node(&mheap->arr[smallest], &mheap->arr[idx]);
 
        mheapify(mheap, smallest);
    }
}
int isEmpty(struct min_heap* mheap){return mheap->size == 0;}
struct min_node* extractMin(struct min_heap* mheap)
{
    if (isEmpty(mheap))
        return NULL;
    struct min_node* root = mheap->arr[0];
    struct min_node* lnode = mheap->arr[mheap->size - 1];
    mheap->arr[0] = lnode;
 
    mheap->pos[root->v] = mheap->size-1;
    mheap->pos[lnode->v] = 0;
 
    --mheap->size;
    mheapify(mheap, 0);
 
    return root;
}
void min_key(struct min_heap* mheap, int v, int dist)
{
    int i = mheap->pos[v];
    mheap->arr[i]->dist = dist;
    while (i && mheap->arr[i]->dist < mheap->arr[(i - 1) / 2]->dist)
    {
        mheap->pos[mheap->arr[i]->v] = (i-1)/2;
        mheap->pos[mheap->arr[(i-1)/2]->v] = i;
        swapmin_node(&mheap->arr[i],  &mheap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
int minheap(struct min_heap *mheap, int v){
   if (mheap->pos[v] < mheap->size) return 1;
   return 0;
}
void print(int i, int j){printf("   %c\t|\t%d\n", i, j);}
void dijkstra(struct Graph* graph, int src)
{
    int V = graph->V;
    int dist[V];      
    struct min_heap* mheap = createmin_heap(V);
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;//printf("%d\n",dist[1] );
        mheap->arr[v] = newmin_node(v, dist[v]);
        mheap->pos[v] = v;
    }
    mheap->arr[src] = newmin_node(src, dist[src]);
    mheap->pos[src]   = src;
    dist[src] = 0;
    min_key(mheap, src, dist[src]);
    mheap->size = V;
    while (!isEmpty(mheap))
    {
        struct min_node* mheapnode = extractMin(mheap);
        int u = mheapnode->v; // Store the extracted vertex number
        struct adjlist* pmov = graph->arr[u].head;
        while (pmov != NULL)
        {
            int v = pmov->dest;
            if (minheap(mheap, v) && dist[u] != INT_MAX && pmov->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pmov->weight;
                min_key(mheap, v, dist[v]);
            }
            pmov = pmov->next;
        }
    }
    OrderOfPermanentArr(dist, V);
}
void OrderOfPermanentArr(int dist[], int n)
{   
    int i;
    for (i = 0; i < n; ++i)                                              
        print(i+65, dist[i]);
    }