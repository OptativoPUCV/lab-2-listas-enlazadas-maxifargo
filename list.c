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
    List * list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
     return list;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    list->current = list->head;
    return list->head->data; 
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL|| list->current->next == NULL) {
        return NULL;
    }
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL|| list->current->prev == NULL) {
        return NULL;
    }
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node *new = createNode(data);
    if (!list->head) {
        list->head = list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}

void pushBack(List * list, void * data) {
    if (list == NULL) {
        return;
    }
    Node * new = createNode(data);
        if (list->tail == NULL){
            list->head =new;
            list->tail=new;
        } else {
            list->tail->next = new;
            new->prev = list->tail;
            list->tail=new;
        }
    }


void pushCurrent(List * list, void * data) {
    Node * new = createNode(data);
    if (!list->current) {
        list->head = list->tail = list->current = new;
    } else {
        new->next = list->current->next;
        new->prev = list->current;
        if (list->current->next) {
            list->current->next->prev = new;
        } else {
            list->tail = new;
        }
        list->current->next = new;
        list->current = new;
    }
}

void * popFront(List * list) {
    if (!list || !list->head) return NULL;
    Node * temp = list->head;
    void * data = temp->data;
    list->head = temp->next;
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
    free(temp);
    return data;
}

void * popBack(List * list) {
    if (!list || !list->tail) return NULL;
    Node * temp = list->tail;
    void * data = temp->data;
    list->tail = temp->prev;
    if (list->tail) list->tail->next = NULL;
    else list->head = NULL;
    free(temp);
    return data;
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL;

    Node * temp = list->current;
    void * data = temp->data;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    } else if (list->current == list->head) { 
        list->head = list->head->next;
        list->head->prev = NULL;
        list->current = list->head;
    } else if (list->current == list->tail) { 
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->current = list->tail;
    } else { 
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        list->current = list->current->next;
    }

    free(temp);
    return data;
}

void cleanList(List * list) {
    while (list->head) popFront(list);
    free(list);
}
