#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 20 

int edges_len=0;

typedef struct {
    int vertex;
    int weight;
} edge_t;
typedef struct {
    edge_t **edges;
    int edges_len;
    int edges_size;
    int dist;
    int prev;
    int visited;
} vertex_t;
 
typedef struct {
    vertex_t **vertices;
    int vertices_len;
    int vertices_size;
} graph_t;
 
typedef struct {
    int *data;
    int *prio;
    int *index;
    int len;
    int size;
} heap_t;
struct edges 
{
    int v1;
    int v2;
    int w;
    struct edges* next;
};
struct vertices 
{
    int v;
    char a[20];
    char c1[20],d[20];
    struct edges* next;
}
*Begin=NULL;// Basically the head of the  element
 
void add_vertex (graph_t *g, long i) {
    if (g->vertices_size < i + 1) {
        int size = g->vertices_size * 2 > i ? g->vertices_size * 2 : i + 4;
        g->vertices = realloc(g->vertices, size * sizeof (vertex_t *));
        for (int j = g->vertices_size; j < size; j++)
            g->vertices[j] = NULL;
        g->vertices_size = size;
    }
    if (!g->vertices[i]) {
        g->vertices[i] = calloc(1, sizeof (vertex_t));
        g->vertices_len++;
    }
}
 
void add_edge (graph_t *g, long a, long b, long w) {
 //   a = a - 'a';
 //   b = b - 'a';
    add_vertex(g, a);
    add_vertex(g, b);
    vertex_t *v = g->vertices[a];
    if (v->edges_len >= v->edges_size) {
        v->edges_size = v->edges_size ? v->edges_size * 2 : 4;
        v->edges = realloc(v->edges, v->edges_size * sizeof (edge_t *));
    }
    edge_t *e = calloc(1, sizeof (edge_t));
    e->vertex = b;
    e->weight = w;
    v->edges[v->edges_len++] = e;edges_len++;
}
 
heap_t *create_heap (int n) {
    heap_t *h = calloc(1, sizeof (heap_t));
    h->data = calloc(n + 1, sizeof (int));
    h->prio = calloc(n + 1, sizeof (int));
    h->index = calloc(n, sizeof (int));
    return h;
}
 
void push_heap (heap_t *h, int v, int p) {
    int i = h->index[v] == 0 ? ++h->len : h->index[v];
    int j = i / 2;
    while (i > 1) {
        if (h->prio[j] < p)
            break;
        h->data[i] = h->data[j];
        h->prio[i] = h->prio[j];
        h->index[h->data[i]] = i;
        i = j;
        j = j / 2;
    }
    h->data[i] = v;
    h->prio[i] = p;
    h->index[v] = i;
}
 
int min (heap_t *h, int i, int j, int k) {
    int m = i;
    if (j <= h->len && h->prio[j] < h->prio[m])
        m = j;
    if (k <= h->len && h->prio[k] < h->prio[m])
        m = k;
    return m;
}
int pop_heap (heap_t *h) {
    int v = h->data[1];
    int i = 1;
    while (1) {
        int j = min(h, h->len, 2 * i, 2 * i + 1);
        if (j == h->len)
            break;
        h->data[i] = h->data[j];
        h->prio[i] = h->prio[j];
        h->index[h->data[i]] = i;
        i = j;
    }
    h->data[i] = h->data[h->len];
    h->prio[i] = h->prio[h->len];
    h->index[h->data[i]] = i;
    h->len--;
    return v;
}
void dijkstra (graph_t *g, int a, int b) {
    int i, j;
    //a = a - 'a';
    //b = b - 'a';
    for (i = 0; i < g->vertices_len; i++) {
        vertex_t *a = g->vertices[i];
       // a->dist = INT_MAX;
       // a->prev = 0;
       // a->visited = 0;
    }
    vertex_t *v = g->vertices[a];
    v->dist = 0;
    heap_t *h = create_heap(g->vertices_len);
    push_heap(h, a, v->dist);
    while (h->len) {
        i = pop_heap(h);
        if (i == b)
            break;
        v = g->vertices[i];
        v->visited = 1;
        for (j = 0; j < v->edges_len; j++) {
            edge_t *e = v->edges[j];
            vertex_t *u = g->vertices[e->vertex];
            if (!u->visited && v->dist + e->weight <= u->dist) {
                u->prev = i;
                u->dist = v->dist + e->weight;
                push_heap(h, e->vertex, u->dist);
            }
        }
    }
}
 
void print_path (graph_t *g, int i) {
    int n, j;
    vertex_t *v, *u;
    i = i - 'a';
    v = g->vertices[i];
    if (v->dist == INT_MAX) {
        printf("no path\n");
        return;
    }
    for (n = 1, u = v; u->dist; u = g->vertices[u->prev], n++)
        ;
    char *path = malloc(n);
    path[n - 1] = 'a' + i;
    for (j = 0, u = v; u->dist; u = g->vertices[u->prev], j++)
        path[n - j - 2] = 'a' + u->prev;
    printf("%d %.*s\n", v->dist, n, path);
}
void print( struct edges *p ) 
{
    int i=0;
        if(p!=NULL)
        printf("\n%d||%d||%d||%d\n",++i,p->v1,p->v2,p->w);else p=p->next;
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}
void printy( struct vertices *p ) 
{
    int i=0;
        printf("\n%d  %s||%s||%s\n",p->v,p->a,p->c1,p->d);
        //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}
void linkedlist(FILE *f)
{
    while(!feof(f))
    {
        struct vertices *newdata,*curr;
        newdata=(struct vertices *)malloc(sizeof(struct vertices));
        //fetch_title( f, newdata );
        //newdata->score;newdata->next=NULL;
        if(Begin==NULL)
        {
            Begin=newdata;
            curr=newdata;
        }
        else
        {
            curr=newdata;
            curr=newdata;
        }
    }
}
int next_field( FILE *f, char *buf, int max ) //Reffered from solutions of Assedgesment 0
{
    int i=0, end=0, quoted=0;
    for(;;) {
        buf[i] = fgetc(f);
        if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
        if(buf[i]==',' &&  !quoted) { break; }
        if(feof(f) || buf[i]=='\n') { end=1; break; } 
        if( i<max-1 ) { ++i; } 
    }
    buf[i] = 0; 
    return end;
}
void fetch_title (FILE *csv, struct edges *p )//Reffered from solutions of Assedgesment 0
{
    char buf[SIZE];
    next_field( csv, buf, SIZE );
    p->v1=atoi(buf);//printf("%d\n",p->v1 );
    next_field( csv, buf, SIZE );
    p->v2=atoi(buf);
    next_field( csv, buf, SIZE );
    p->w=atoi(buf);
 }
void search(FILE *csv, struct vertices *p )//Reffered from solutions of Assedgesment 0
{
    char buf[SIZE];
    next_field( csv, buf, SIZE );
    p->v=atoi(buf);//printf("%d\n",p->v1 );
    next_field( csv, p->a, SIZE );
    //next_field( csv, p->b, SIZE );
    next_field( csv, p->c1, SIZE );
    next_field( csv, p->d, SIZE );
    //p->w=atoi(buf);
 }
int main () {
    graph_t *g = calloc(6, sizeof (graph_t));
    struct edges *newdata;
        newdata=(struct edges *)malloc(sizeof(struct edges));
    FILE *f = fopen("edges.csv", "r");
    if(!f) 
    { 
        printf("unable to open\n"); 
        return 1; 
    }
    //printf("dfdf\n");

    fetch_title(f,newdata);
    int i=0;//printf("dfdf\n");

    while(!feof(f))
    {
        fetch_title(f,newdata);
        add_edge(g, newdata->v1, newdata->v2, newdata->w);
        //add_edge(g, newdata->v2, newdata->v1, newdata->w);
        if(newdata->v1==7681 && newdata->v2==987 && newdata->w==1411)
         break;
    }//     printf("aaaa\n");
    printf("Loaded %d vertices\n",g->vertices_len -1 );
    printf("Loaded %d edges\n",edges_len-1);
    
    FILE *f1 = fopen("vertices.csv", "r");
    if(!f1) 
    { 
        printf("unable to open\n"); 
        return 1; 
    }
 	//printf("dfdf\n");
   
    dijkstra(g, 300, 253);printf("bbb\n");
    print_path(g, 253);
    return 0;
}