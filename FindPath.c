/* 
 * File:   FindPath.c
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */

#include "Graph.h"
#define MAX_LEN 200 /* should be enough for most input files */

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Usage: %s infile outfile\n", argv[0]);
        exit(1);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    char line[MAX_LEN];
    fgets(line, MAX_LEN, in); /* number of vertices */
    GraphRef G = newGraph(atoi(line));
    ListRef L = newList();
    int s, d;

    /* Filling the graph */
    while (fgets(line, MAX_LEN, in) != NULL) {

        s = atoi(strtok(line, " "));
        d = atoi(strtok(NULL, " "));
        if (s == 0 && d == 0) {
            break;
        }
        addEdge(G, s, d);
    }

    printGraph(out, G);

    /* Finding Paths */
    while (fgets(line, MAX_LEN, in) != NULL) {

        s = atoi(strtok(line, " "));
        d = atoi(strtok(NULL, " "));
        if (s == 0 && d == 0) {
            break;
        }

        fprintf(out, "\n");

        BFS(G, s);
        int dist = getDist(G, d);

        if (dist != INF) {
            fprintf(out, "The distance from %d to %d is %d\n", s, d, dist);
            fprintf(out, "A shortest %d-%d path is: ", s, d);
            getPath(L, G, d);
            printList(out, L);
        } else {
            fprintf(out, "The distance from %d to %d is infinity\n", s, d);
            fprintf(out, "No %d-%d path exists", s, d);
        }

        fprintf(out, "\n");
        makeEmpty(L);
    }

    fclose(in);
    fclose(out);
    freeGraph(&G);
    freeList(&L);

    return 0;
}
