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
    return list->head->data; 
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }
    list->current = list->current->next;
    return list->current->next->data;
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
    if (list == NULL) {
        return;
    }
    Node * new = createNode(data);
    if (list->head == NULL){
        list->head=new;
        list->tail=new;
        list->head->prev = NULL;
        list->head->next = NULL;
    } else {
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
    if (list == NULL) {
        return;
    }
    Node * new = createNode(data);
    if (list->current == NULL){
        list->current = new;
        list->head = new;
        list->tail = new;
    } else {
        list->current->next = new;
        new->prev = list->current;
        list->current = new;
    } return;
}

void * popFront(List * list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }
    void * data = list->head->data;
    if (list->head->prev == NULL && list->head->next == NULL){
    return list->head->data;} else {
        list->current = list->head; 
        if (list->current->prev == NULL){
            list->current->next->prev = NULL;
            list->head = list->current->next;
            list->current->next = NULL;}
        else if (list->current->next == NULL){
            list->current->prev->next = NULL;
            list->tail = list->current->prev;
            list->current->prev = NULL;}
        else {
            list->current->prev->next = list->current->next;
            list->current->next->prev = list->current->prev;
            list->current->next = NULL;
            list->current->prev = NULL;
            list->current = list->current->next;
        }
    }
}

void * popBack(List * list) {
    list->current = list->tail;
    if (list->tail->prev == NULL && list->tail->next == NULL){
    }
    void * data = list->tail->data;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
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
    while (list->head != NULL) {
        popFront(list);
    }
}