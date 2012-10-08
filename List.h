/* 
 * File:   List.h
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */

#ifndef LIST_H
#define	LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List* ListRef;

/*** Constructors-Destructors ***/
ListRef newList(void);
void freeList(ListRef* pL);

/*** Access functions ***/
int getLength(ListRef L);
int isEmpty(ListRef L);
int offEnd(ListRef L);
int getIndex(ListRef L);
int getFront(ListRef L);
int getBack(ListRef L);
int getCurrent(ListRef L);
int equals(ListRef A, ListRef B);

/*** Manipulation procedures ***/
void makeEmpty(ListRef L);
void moveTo(ListRef L, int i);
void movePrev(ListRef L);
void moveNext(ListRef L);
void insertFront(ListRef L, int data);
void insertBack(ListRef L, int data);
void insertBeforeCurrent(ListRef L, int data);
void insertAfterCurrent(ListRef L, int data);
void deleteFront(ListRef L);
void deleteBack(ListRef L);
void deleteCurrent(ListRef L);

/*** Other operations ***/
void printList(FILE* out, ListRef L);
ListRef copyList(ListRef L);

#endif	/* LIST_H */
