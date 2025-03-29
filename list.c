#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
    Node *prev;
};

struct List {
    Node *head;
    Node *tail;
    Node *current;
};

typedef List List;

Node * createNode(void *data) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) return NULL;
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

List * createList() {
    List *list = (List *)malloc(sizeof(List));
    if (!list) return NULL;
    list->head = list->tail = list->current = NULL;
    return list;
}

void * getFirst(List *list) {
    if (!list || !list->head) return NULL;
    list->current = list->head;
    return list->head->data;
}

void *getNext(List *list) {
    if (!list || !list->current || !list->current->next) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void pushFront(List *list, void *data) {
    Node *new = createNode(data);
    if (!list || !new) return;
    if (!list->head) {
        list->head = list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}

void pushBack(List *list, void *data) {
    Node *new = createNode(data);
    if (!list || !new) return;
    if (!list->tail) {
        list->head = list->tail = new;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }
}

void * popFront(List *list) {
    Node *aux = list->head;
    void *data = aux->data;
    list->head = aux->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
    free(aux);
    return data;
}

void * popBack(List *list) {
    if (list==NULL || list->tail==NULL) return NULL;
    Node *aux = list->tail;
    void *data =aux->data;
    list->tail =aux->prev;
    if (list->tail)list->tail->next = NULL;
    else list->head = NULL;
    free(aux);
    return data;
}

void cleanList(List *list) {
    while (list && list->head) {
        popFront(list);
    }
    free(list);
}
