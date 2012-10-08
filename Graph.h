/* 
 * File:   Graph.h
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */

#ifndef GRAPH_H
#define	GRAPH_H
#include "List.h"
#define INF -1
#define NIL -2

typedef struct Graph* GraphRef;

/*** Constructors-Destructors ***/
GraphRef newGraph(int n);
void freeGraph(GraphRef* pG);

/*** Access functions ***/
int getOrder(GraphRef G);
int getSize(GraphRef G);
int getSource(GraphRef G);
int getParent(GraphRef G, int u);
int getDist(GraphRef G, int u);
void getPath(ListRef L, GraphRef G, int u);

/*** Manipulation procedures ***/
void makeNull(GraphRef G);
void addEdge(GraphRef G, int u, int v);
void addArc(GraphRef G, int u, int v);
void BFS(GraphRef G, int s);

/*** Other operations ***/
void printGraph(FILE* out, GraphRef G);

#endif	/* GRAPH_H */
