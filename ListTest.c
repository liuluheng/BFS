/* 
 * File:   ListTest.c
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */

#include "List.h"

/*
 * This prints general info about a given List
 */
void printInfo(ListRef L) {
    printf("List info: \n");
    printf("Empty: %i\n", isEmpty(L));
    printf("Length: %i\n", getLength(L));
    printf("offEnd: %i\n", offEnd(L));
    printf("getIndex: %i\n", getIndex(L));
    if (!isEmpty(L)) {
        printf("getFront: %i\n", getFront(L));
        printf("getBack: %i\n", getBack(L));
        if (!offEnd(L)) {
            printf("getCurrent: %i\n", getCurrent(L));
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    ListRef L = newList();
    printInfo(L);

    printf("Inserting in front: 1, 2, 3\n");
    insertFront(L, 1);
    insertFront(L, 2);
    insertFront(L, 3);
    printf("Moving to index 2\n");
    moveTo(L, 2);
    printList(stdout, L);
    printf("\n");
    printf("Index: %i\n", getIndex(L));
    printf("Current: %i\n", getCurrent(L));

    printf("\n");

    printf("Inserting in back: 4, 5, 6\n");
    insertBack(L, 4);
    insertBack(L, 5);
    insertBack(L, 6);
    printList(stdout, L);
    printf("\n");

    printInfo(L);

    printf("Inserting in front: 52\n");
    insertFront(L, 52);
    printList(stdout, L);
    printf("\n");

    printInfo(L);

    printf("\n");
    printf("Moving to index 2\n");
    moveTo(L, 2);
    printf("Index %i\n", getIndex(L));
    printf("Current: %i\n", getCurrent(L));
    printf("\n");
    printf("Moving to index 2\n");
    moveTo(L, 2);
    printf("Index %i\n", getIndex(L));
    printf("Current: %i\n", getCurrent(L));
    printf("\n");
    printf("Moving to index 5\n");
    moveTo(L, 5);
    printf("Index %i\n", getIndex(L));
    printf("Current: %i\n", getCurrent(L));
    printf("\n");
    printf("Moving to index 0\n");
    moveTo(L, 0);
    printf("Index %i\n", getIndex(L));
    printf("Current: %i\n", getCurrent(L));

    printInfo(L);

    printf("Inserting after current: 7\n");
    insertAfterCurrent(L, 7);
    printf("Inserting before current: 8\n");
    insertBeforeCurrent(L, 8);
    printList(stdout, L);
    printf("\n");

    printInfo(L);

    printf("Deleting Back");
    deleteBack(L);
    printList(stdout, L);
    printf("\n");
    printf("Deleting Front");
    deleteFront(L);
    printList(stdout, L);
    printf("\n");
    printInfo(L);
    printf("Deleting Front");
    deleteFront(L);
    printList(stdout, L);
    printf("\n");
    printInfo(L);

    printf("Moving to 0");
    moveTo(L, 0);
    printf("\n");
    printInfo(L);
    printf("Deleting Current");
    deleteCurrent(L);
    printList(stdout, L);

    printf("\n");
    printInfo(L);

    ListRef B = copyList(L);

    printf("\n");
    printf("Creating Copy");
    printList(stdout, B);
    printf("\n");

    printInfo(L);
    printInfo(B);

    printf("L equals B? %i\n", equals(L, B));
    printf("\n");

    printf("Making Empty\n");
    makeEmpty(L);
    printInfo(L);

    freeList(&L);
    freeList(&B);

    return 0;
}
