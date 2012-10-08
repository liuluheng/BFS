/* 
 * File:   List.c
 * Author: Pit Apps
 * User ID: papps
 * Student ID: 1297394
 * 
 * Assignment: pa4
 */

#include "List.h"

/* Private Structs */

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef Node* NodeRef;

typedef struct List {
    NodeRef front;
    NodeRef back;
    NodeRef current;
    int length;
    int index;
} List;

/*** Constructors-Destructors ***/

NodeRef newNode(int node_data) {
    NodeRef N = malloc(sizeof (Node));
    N->data = node_data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

void freeNode(NodeRef* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

ListRef newList(void) {
    ListRef L;
    L = malloc(sizeof (List));
    L->front = NULL;
    L->back = NULL;
    L->current = NULL;
    L->length = 0;
    L->index = -1;
    return L;
}

void freeList(ListRef* pL) {
    if (pL == NULL || *pL == NULL) {
        return;
    }

    while (!isEmpty(*pL)) {
        deleteBack(*pL);
    }

    free(*pL);
    *pL = NULL;
}

/*** Access functions ***/

/*
 *  getLength
 *  Returns the length of L
 */
int getLength(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getLength() on NULL ListRef\n");
        exit(1);
    }
    return L->length;
}

/*
 *  isEmpty
 *  Returns True if L is empty, otherwise returns 0
 */
int isEmpty(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling isEmpty() on NULL ListRef\n");
        exit(1);
    }
    return L->length == 0;
}

/*
 * offEnd
 * Returns true if current is undefined.
 */
int offEnd(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling offEnd() on NULL ListRef\n");
        exit(1);
    }

    return L->current == NULL || L->index == -1;
}

/*
 * getIndex
 * If current element is defined, returns its position in
 * this List, ranging from 0 to getLength()-1 inclusive.
 * If current element is undefined, returns -1.
 */
int getIndex(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getIndex() on NULL ListRef\n");
        exit(1);
    }

    return offEnd(L) ? -1 : L->index;
}

/*
 * getFront
 * Returns front element. Pre: !isEmpty().
 */
int getFront(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getFront() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: getFront() called on empty List\n");
        exit(1);
    }

    return L->front->data;
}

/*
 * getBack
 * Returns back element. Pre: !isEmpty().
 */
int getBack(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getBack() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: getBack() called on empty List\n");
        exit(1);
    }

    return L->back->data;
}

/*
 * getCurrent
 * Returns current element. Pre: !isEmpty(), !offEnd().
 */
int getCurrent(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getCurrent() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: getCurrent() called on empty List\n");
        exit(1);
    }

    if (offEnd(L)) {
        printf("List Error: getCurrent() called but current is undefined\n");
        exit(1);
    }

    return L->current->data;
}

/*
 * equals
 * Returns true if this List and L are the same integer
 * sequence. Ignores the current element in both Lists.
 */
int equals(ListRef A, ListRef B) {
    if (A == NULL || B == NULL) {
        printf("List Error: calling equals() on NULL ListRef\n");
        exit(1);
    }

    if (A->length == B->length) {
        Node *M = A->front;
        Node *N = B->front;
        while (N != NULL) {
            if (M->data != N->data) {
                return 0;
            }
            M = M->next;
            N = N->next;
        }
        return 1;
    } else {
        return 0;
    }
}

/*** Manipulation procedures ***/

/*
 * makeEmpty
 * Sets this List to the empty state. Post: isEmpty().
 */
void makeEmpty(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling makeEmpty() on NULL ListRef\n");
        exit(1);
    }

    while (!isEmpty(L)) {
        deleteBack(L);
    }

    L->front = NULL;
    L->back = NULL;
    L->current = NULL;
    L->length = 0;
    L->index = -1;
}

/*
 * moveTo
 * If 0 <= i <= getLength()-1, moves current element
 * marker to position i in this List. Otherwise current
 * element becomes undefined.
 */
void moveTo(ListRef L, int i) {
    if (L == NULL) {
        printf("List Error: calling moveTo() on NULL ListRef\n");
        exit(1);
    }

    if (0 <= i && i <= (getLength(L) - 1)) {
        int j;

        if (i == L->index) {
            return;
        } else if (L->index == -1) {
            if (i < (getLength(L) / 2)) {
                L->current = L->front;
                L->index = 0;
                for (j = 0; j < i; j++) {
                    moveNext(L);
                }
            } else {
                L->current = L->back;
                L->index = getLength(L) - 1;
                for (j = (getLength(L) - 1); j > i; j--) {
                    movePrev(L);
                }
            }
        } else if (i < getIndex(L)) {
            for (j = (getIndex(L) - i); j > 0; j--) {
                movePrev(L);
            }
        } else if (i > getIndex(L)) {
            for (j = (i - getIndex(L)); j > 0; j--) {
                moveNext(L);
            }
        } else {
            L->index = -1;
            L->current = NULL;
        }
    }
}

/*
 * movePrev
 * Moves current one step toward front element.
 * Pre: !isEmpty(), !offEnd().
 */
void movePrev(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: movePrev() called on empty List\n");
        exit(1);
    }

    if (offEnd(L)) {
        printf("List Error: movePrev() called but current is undefined\n");
        exit(1);
    }

    L->current = L->current->prev;

    if (L->current == NULL) {
        L->index = -1;
    } else {
        L->index--;
    }
}

/*
 * moveNext
 * Moves current one step toward front element.
 * Pre: !isEmpty(), !offEnd().
 */
void moveNext(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: moveNext() called on empty List\n");
        exit(1);
    }

    if (offEnd(L)) {
        printf("List Error: moveNext() called but current is undefined\n");
        exit(1);
    }

    L->current = L->current->next;

    if (L->current == NULL) {
        L->index = -1;
    } else {
        L->index++;
    }
}

/*
 * insertFront
 * Inserts new element before front element.
 * Post: !isEmpty().
 */
void insertFront(ListRef L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertFront() on NULL ListRef\n");
        exit(1);
    }

    NodeRef node = newNode(data);

    if (isEmpty(L)) {
        L->front = L->back = node;
    } else {
        L->front->prev = node;
        node->next = L->front;
        L->front = node;
    }
    L->length++;

    /* Update index */
    if (L->current != NULL) {
        L->index++;
    }
}

/*
 * insertBack
 * Inserts new element after back element.
 * Post: !isEmpty().
 */
void insertBack(ListRef L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBack() on NULL ListRef\n");
        exit(1);
    }

    NodeRef node = newNode(data);

    if (isEmpty(L)) {
        L->front = L->back = node;
    } else {
        L->back->next = node;
        node->prev = L->back;
        L->back = node;
    }
    L->length++;
}

/*
 * insertBeforeCurrent
 * Inserts new element before current element.
 * Pre: !isEmpty(), !offEnd().
 */
void insertBeforeCurrent(ListRef L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBeforeCurrent() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: insertBeforeCurrent() called on empty List\n");
        exit(1);
    }

    if (offEnd(L)) {
        printf("List Error: insertBeforeCurrent() called but current is undefined\n");
        exit(1);
    }

    NodeRef node = newNode(data);

    if (L->current->prev == NULL) {
        L->front = node;
    } else {
        L->current->prev->next = node;
        node->prev = L->current->prev;
    }
    node->next = L->current;
    L->current->prev = node;

    L->index++;
    L->length++;
}

/*
 * insertAfterCurrent
 * Inserts new element after current element.
 * Pre: !isEmpty(), !offEnd().
 */
void insertAfterCurrent(ListRef L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertAfterCurrent() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: insertAfterCurrent() called on empty List\n");
        exit(1);
    }

    if (offEnd(L)) {
        printf("List Error: insertAfterCurrent() called but current is undefined\n");
        exit(1);
    }

    NodeRef node = newNode(data);

    if (L->current->next == NULL) {
        L->back = node;
    } else {
        L->current->next->prev = node;
        node->next = L->current->next;
    }
    node->prev = L->current;
    L->current->next = node;

    L->length++;
}

/*
 * deleteFront
 * Deletes front element. Pre: !isEmpty().
 */
void deleteFront(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: deleteFront() called on empty List\n");
        exit(1);
    }

    NodeRef node = L->front;

    if (L->length > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else {
        L->front = L->back = NULL;
    }

    /* Make necessary changes if front was current */
    if (node == L->current) {
        L->index = -1;
        L->current = NULL;
    } else {
        L->index--;
    }

    L->length--;
    freeNode(&node);
}

/*
 * deleteFront
 * Deletes front element. Pre: !isEmpty().
 */
void deleteBack(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: deleteBack() called on empty List\n");
        exit(1);
    }

    NodeRef node = L->back;

    if (L->length > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->front = L->back = NULL;
    }

    /* Make necessary changes if back was current */
    if (node == L->current) {
        L->index = -1;
        L->current = NULL;
    }

    L->length--;
    freeNode(&node);
}

/*
 * deleteCurrent
 * Deletes front element. Pre: !isEmpty().
 * Pre: !isEmpty(), !offEnd(); Post: offEnd()
 */
void deleteCurrent(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling deleteCurrent() on NULL ListRef\n");
        exit(1);
    }

    if (isEmpty(L)) {
        printf("List Error: deleteCurrent() called on empty List\n");
        exit(1);
    }

    if (offEnd(L)) {
        printf("List Error: deleteCurrent() called but current is undefined\n");
        exit(1);
    }

    if (L->current == L->back) {
        deleteBack(L);
    } else if (L->current == L->front) {
        deleteFront(L);
    } else {
        NodeRef node = L->current;

        NodeRef tempPrev = L->current->prev;
        NodeRef tempNext = L->current->next;
        tempPrev->next = tempNext;
        tempNext->prev = tempPrev;

        L->length--;
        L->index = -1;
        L->current = NULL;

        freeNode(&node);
    }

}

/*** Other operations ***/

/*
 * printList
 * Prints the List L to the file pointed to by out,
 * formatted as a space-separated string. 
 */
void printList(FILE* out, ListRef L) {
    if (L == NULL) {
        printf("List Error: calling printList() on NULL ListRef\n");
        exit(1);
    }

    if (out == NULL) {
        printf("List Error: calling printList() on NULL FILE pointer\n");
        exit(1);
    }

    char str[getLength(L)*2 + 1]; /* length of List * a space each, + brackets*/
    NodeRef N;

    strcpy(str, ""); /* hack to initialise str before sprintf */
    for (N = L->front; N != NULL; N = N->next) {
        sprintf(str, "%s%i", str, N->data);
        if (N->next != NULL) {
            strcat(str, " ");
        }
    }

    fprintf(out, "%s", str);
}

/* Returns a new list which is identical to this list. The current
 * element in the new list is undefined, regardless of the state of
 * the current element in this List. The state of this List is
 * unchanged.
 */
ListRef copyList(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling copyList() on NULL ListRef\n");
        exit(1);
    }

    ListRef newL = newList();
    NodeRef N;
    for (N = L->front; N != NULL; N = N->next) {
        insertBack(newL, N->data);
    }
    return newL;
}
