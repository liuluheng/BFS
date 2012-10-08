/* 
 * File:   GraphTest.c
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */
#include "Graph.h"

int main(int argc, char* argv[]) {
    GraphRef G = newGraph(6);
    printf("Adding edges\n");
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);

    printf("Printing Graph\n");
    printGraph(stdout, G);

    printf("Running BFS\n");
    BFS(G, 3);

    ListRef result = newList();
    printf("Getting Path 3-6\n");
    getPath(result, G, 6);

    printf("Printing result\n");
    printList(stdout, result);
    printf("\nThe Graph has source %d\n", getSource(G));
    printf("The Graph from destination %d has parent %d, distance %d\n", 6, getParent(G, 6), getDist(G, 6));
    printf("The Graph has order %d, size %d\n", getOrder(G), getSize(G));

    printf("Resetting Graph\n");
    makeNull(G);
    printf("Printing Graph\n");
    printGraph(stdout, G);
    printf("Adding arcs\n");
    addArc(G, 1, 2);
    addArc(G, 1, 3);
    addArc(G, 2, 4);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 6);
    printf("Printing Graph\n");
    printGraph(stdout, G);
    printf("The Graph has order %d, size %d\n", getOrder(G), getSize(G));

    freeList(&result);
    freeGraph(&G);
    return 0;
}
