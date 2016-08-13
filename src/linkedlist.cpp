//
//  linkedlist.cpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "linkedlist.hpp"
#include "objects.hpp"

LinkedListNode *newLinkedListNode(Object obj){
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (!newNode) {
        std::cerr << "Error : Memory Allocating" << std::endl;
        exit(EXIT_FAILURE);
    }
    newNode->obj = obj;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

LinkedList *initLinkedLst(){
    LinkedList *lnkdlst = (LinkedList *)malloc(sizeof(LinkedList));
    if(!lnkdlst){
        std::cerr << "Error : Memory Allocating" << std::endl;
        exit(EXIT_FAILURE);
    }
    lnkdlst->head = NULL;
    lnkdlst->tail = NULL;
    return lnkdlst;
}

void pushToLinkedList(LinkedList *lnkdlst, Object obj){
    LinkedListNode *newNode = newLinkedListNode(obj);
    if (lnkdlst->head == NULL && lnkdlst->tail == NULL) {
        lnkdlst->head = newNode;
        lnkdlst->tail = newNode;
    }
    
    newNode->prev = lnkdlst->tail;
    lnkdlst->tail->next = newNode;
    lnkdlst->tail = newNode;
}

int lengthOfLinkedList(LinkedList *lnkdlst){
    
    LinkedListNode *temp = lnkdlst->head;
    if(temp == NULL){
        std::cerr << "Error : Linked List is empty" << std::endl;
        exit(EXIT_FAILURE);
    }
    int len = 0;
    while (temp != NULL) {
        temp = temp->next;
        len++;
    }
    return len;
}

int searchInLinkedList(LinkedList *lnkdlst, Object searchObject){
    int index = 0;
    LinkedListNode *temp = lnkdlst->head;
    
    while (temp != NULL) {
        
        if (temp->obj.getSeqID() == searchObject.getSeqID())
            return index;
        
        temp = temp->next;
        index++;
    }
    return -1;
}

void deleteFromLinkedList(LinkedList *lnkdlst, Object data){
    int index = searchInLinkedList(lnkdlst, data);
    if (index != -1){
        LinkedListNode *temp = lnkdlst->head;
        if (index == 0){
            temp->next = NULL;
            temp->prev = NULL;
        }
        else{
            for(int i = 0; i < index ; i++ ){
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
        }
    }
}

void deleteIndexFromLinkedList(LinkedList *lnkdlst, int index){
    
    LinkedListNode *temp = lnkdlst->head;
    int i;
    for(i = 0; i < index ; i++){
        temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
}
