/* 
 * File:   Graph.c
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */

#include "Graph.h"

typedef struct Graph {
    ListRef *adj;
    int *colour;
    int *parent;
    int *distance;
    int order;
    int size;
} Graph;

enum colours {
    WHITE, GRAY, BLACK
};

/*** Constructors-Destructors ***/

/* Returns GraphRef representing graph having n vertices and 
 * no edges */
GraphRef newGraph(int n) {
    GraphRef G = malloc(sizeof (Graph));
    G->colour = malloc((n + 1) * sizeof (int));
    G->distance = malloc((n + 1) * sizeof (int));
    G->adj = malloc((n + 1) * sizeof (ListRef));
    G->parent = malloc((n + 1) * sizeof (int));
    G->order = n;
    G->size = 0;

    int i;
    for (i = 1; i <= n; i++) {
        G->adj[i] = newList();
    }

    return G;
}

/* Frees all dynamic memory associated with *pG; sets *pG to NULL */
void freeGraph(GraphRef* pG) {
    if (pG != NULL && *pG != NULL) {
        free((*pG)->distance);
        free((*pG)->colour);
        free((*pG)->parent);

        int i;
        for (i = 0; i <= (*pG)->order; i++) {
            freeList(&((*pG)->adj[i]));
        }
        free((*pG)->adj);

        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

/* Returns order of GraphRef G */
int getOrder(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling getOrder() on NULL GraphRef\n");
        exit(1);
    }
    return G->order;
}

/* Returns size of GraphRef G */
int getSize(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling getSize() on NULL GraphRef\n");
        exit(1);
    }
    return G->size;
}

/* Returns source vertex most recently used in BFS(); or NIL if BFS() 
 * has not been called */
int getSource(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling getSource() on NULL GraphRef\n");
        exit(1);
    }
    int i;
    int source = NIL;
    for (i = 1; i <= getOrder(G); i++) {
        if (G->distance[i] == 0) {
            source = i;
        }
    }
    return source;
}

/* Returns parent of vertex u in the tree created by BFS(); or NIL if BFS()
 * has not been called 
 * Pre: 1<=u<=getOrder(G) */
int getParent(GraphRef G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getParent() on NULL GraphRef\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: calling getParent() on vertex that is outside the Graph!\n");
        exit(1);
    }

    return G->parent[u];
}

/* Returns distance from most recent BFS source to vertex u; or INF if BFS()
 * has not been called 
 * Pre: 1<=u<=getOrder(G) */
int getDist(GraphRef G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getDist() on NULL GraphRef\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: calling getDist() on vertex that is outside the Graph!\n");
        exit(1);
    }

    return G->distance[u];
}

/* appends to L the vertices of a shortest path in G from source to u; appends NIL
 * if no path exists. 
 * Pre: getSource(G) != NIL 
 *      1<=u<=getOrder(G) */
void getPath(ListRef L, GraphRef G, int u) {
    if (G == NULL) {
        printf("Graph Error: calling getPath() on NULL GraphRef\n");
        exit(1);
    }

    if (L == NULL) {
        printf("Graph Error: calling getPath() on NULL ListRef\n");
        exit(1);
    }

    if (getSource(G) == NIL) {
        printf("Graph Error: calling getPath() but BFS has not been executed yet!\n");
        exit(1);
    }

    if (!(1 <= u && u <= getOrder(G))) {
        printf("Graph Error: calling getPath() on destination that is outside the Graph!\n");
        exit(1);
    }

    if (getSource(G) == u) {
        insertFront(L, u);
    } else if (getParent(G, u) == NIL) {
        printf("%d not reachable from %d", u, getSource(G));
    } else {
        getPath(L, G, getParent(G, u));
        insertBack(L, u);
    }
}

/*** Manipulation procedures ***/

/* Deletes all edges of G */
void makeNull(GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling makeNull() on NULL GraphRef\n");
        exit(1);
    }

    int j;
    ListRef L;
    for (j = 1; j <= getOrder(G); j++) {
        L = G->adj[j];
        makeEmpty(L);
    }
    G->size = 0;
}

/* Inserts new edge joining u to v and v to u  */
void addEdge(GraphRef G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: calling addEdge() on NULL GraphRef\n");
        exit(1);
    }

    insertBack(G->adj[u], v);
    insertBack(G->adj[v], u);
    G->size++;
}

/* Inserts new directed edge from u to v */
void addArc(GraphRef G, int u, int v) {
    if (G == NULL) {
        printf("Graph Error: calling addArc() on NULL GraphRef\n");
        exit(1);
    }

    insertBack(G->adj[u], v);
    G->size++;
}

/* Runs BFS algorithm */
void BFS(GraphRef G, int s) {
    if (G == NULL) {
        printf("Graph Error: calling BFS() on NULL GraphRef\n");
        exit(1);
    }

    /* Initialisation */
    int i, j;
    for (i = 1; i <= G->order; i++) {
        /* Ignore source vertex */
        if (s == i) {
            continue;
        }

        G->colour[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->colour[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    ListRef Q = newList();
    insertBack(Q, s);

    /* Main Loop */
    while (!isEmpty(Q)) {
        i = getFront(Q);
        deleteFront(Q);
        moveTo(G->adj[i], 0);
        while (!offEnd(G->adj[i])) {
            j = getCurrent(G->adj[i]);
            if (G->colour[j] == WHITE) {
                G->colour[j] = GRAY;
                G->distance[j] = G->distance[i] + 1;
                G->parent[j] = i;
                insertBack(Q, j);
            }
            moveNext(G->adj[i]);
        }
        G->colour[i] = BLACK;
    }
    freeList(&Q);
}

/*** Other operations ***/

/* Prints adjacency list of G to out */
void printGraph(FILE* out, GraphRef G) {
    if (G == NULL) {
        printf("Graph Error: calling printGraph() on NULL GraphRef\n");
        exit(1);
    }

    if (out == NULL) {
        printf("Graph Error: calling printGraph() on NULL FILE pointer\n");
        exit(1);
    }

    int i, j;
    char str[1 + (2 * G->order)];
    ListRef L;
    for (i = 1; i <= G->order; i++) {
        *str = 0;
        L = G->adj[i];
        sprintf(str, "%d:", i);
        for (j = 0; j < getLength(L); j++) {
            moveTo(L, j);
            sprintf(str, "%s %i", str, getCurrent(L));
        }
        fprintf(out, "%s\n", str);
    }
}
