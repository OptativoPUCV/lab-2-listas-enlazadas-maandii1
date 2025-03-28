#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list= (List*) malloc(sizeof(List));
    list->head= NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;

    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    if (list->current->next == NULL) return NULL;

    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL; 
    list->current= list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* NewNode = createNode(data);
    NewNode->next = list->head;
    if (list->head) list->head->prev = NewNode;
    list->head = NewNode;
    if (list->tail == NULL) list->tail = NewNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* NewNode = createNode(data);
    if (list->current == NULL) return;
    NewNode->prev = list->current;
    NewNode->next = list->current->next;

    if (list->current->next) list->current->next->prev = NewNode;
    else list->tail = NewNode;
    list->current->next = NewNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL) return NULL;
    Node* aux = list->current;
    Node* izq = list->current->prev;
    if (list->current->next != NULL) {
        Node* der = list->current->next;
        izq->next = der;
        der->prev = izq;
        list->current = der;
    }
    else {
        list->current = NULL;
        izq->next = NULL;
    }
    return aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}