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
    return list->head->next->data;
}

void * lastList(List * list) {
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }
    return list->tail->data;
}

void * prevList(List * list) {
    if (list == NULL || list->current == NULL) {
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
        new = list->head;
        new = list->tail;
        list->head->prev = NULL;
        list->head->next = NULL;
    } else {
        list->head->prev = new;
        new->next = list->head;
    }
}

void pushBack(List * list, void * data) {
    if (list == NULL) {
        return;
    }
    Node * new = createNode(data);
        if (list->tail == NULL){
            new = list->head;
            new = list->tail;
            list->head->prev = NULL;
            list->head->next = NULL;
        } else {
            list->tail->next = new;
            new = list->tail;
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
    void * data = list->current->data;
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
        
        return list->tail->data;
    }
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }
    void * data = list->current->data;
    if (list->current->prev == NULL && list->current->next == NULL){
    return list->current->data;} else {
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

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}