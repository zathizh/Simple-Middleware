//
//  linkedlist.hpp
//  Middleware
//
//  Created by Sathish Bowatta on 5/27/16.
//  Copyright © 2016 Sathish Bowatta. All rights reserved.
//

#ifndef linkedlist_hpp
#define linkedlist_hpp

#include "objects.hpp"

typedef struct linkedListnode{
    Object obj;
    struct linkedListnode *next, *prev;
}LinkedListNode;

typedef struct {
    LinkedListNode *head, *tail;
}LinkedList;

LinkedListNode *newLinkedListNode(Object);
LinkedList *initLinkedLst();
void pushToLinkedList(LinkedList *, Object);
int lengthOfLinkedList(LinkedList *);
int searchInLinkedList(LinkedList *, Object);
void deleteFromLinkedList(LinkedList *, Object);
void deleteIndexFromLinkedList(LinkedList *, int);

#endif /* linkedlist_hpp */
