//
//  mymalloc.c
//  malloc
//
//  Created by Sathish Bowatta on 10/27/15.
//  Copyright © 2015 Sathish Bowatta. All rights reserved.
//

#include "mymalloc.h"

//defining the size of memory
#define MEMSIZE 20000


//defining the memory array
static char memory[MEMSIZE]={0};

//structure if doubly linked list node
typedef struct linkedListNode {
    int isfree;
    int size;
    struct linkedListNode *next, *prev;
}LinkedListNode;


//MyMalloc takes size as a argument
void *MyMalloc(size_t size) {
    
    static LinkedListNode *rootNode;
    LinkedListNode *temp, *newNode;
    
    // determine size is nonzero.
    if (!size) {
        fprintf(stderr, "Unable to allocate 0 bytes\n");
        return 0;
    }
    
    //check for memory[0]
    if (!memory[0]){
        memory[0]=1;
        
        rootNode = (LinkedListNode *) (memory + sizeof(char));; // initializing linkedkist from memory[1]
        rootNode->prev = NULL;
        rootNode->next = NULL;
        rootNode->size = MEMSIZE - sizeof(LinkedListNode) - sizeof(char); // set the size free size of memory
        
        rootNode->isfree = 1;
        
    }
    
    temp = rootNode; // pointing the temporary linked list node to root node
    
    
    //search for empty non allocated memory slot
    while(temp) {
        if (temp->size < size || !temp->isfree) {
            temp = temp->next;
        }
        else if (temp->size < (size + sizeof(LinkedListNode))) {
            temp->isfree = 0;
            return (char *) temp + sizeof(LinkedListNode);
        }
        else {
            // creating new linkedlist node
            newNode = (LinkedListNode *)((void *)temp + sizeof(LinkedListNode) + size);
            newNode->prev = temp;
            newNode->next = temp->next;
            
            newNode->size = temp->size - sizeof(LinkedListNode) - (int)size;
            newNode->isfree = 1;
            
            temp->size = (int)size;
            temp->isfree = 0;
            temp->next = newNode;
            
            //returning the memory pointer
            return (void *)temp + sizeof(LinkedListNode);
        }
    }
    
    // if unable to find non allocated memory prompts error.
    fprintf(stderr, "Unable to allocte %zu bytes from memory\n", size);
    return 0;
}


void MyFree(void *p) {
    //determine given memory location is nonzero
    if (!p) {
        fprintf(stderr, "Memory pointer is NULL\n");
        return;
    }
    
    LinkedListNode *temp;
    
    // pointing the temp linkedlist node into memory slot
    temp = (LinkedListNode *)((void *) p - sizeof(LinkedListNode));
    
    
    //check temp->prev isfree and exist
    if (temp->prev && temp->prev->isfree){
        temp->prev->size += sizeof(LinkedListNode) + temp->size;
    }
    else{
        temp->isfree = 1;
        temp->prev = temp;
    }
    
    //check temp->next isfree and exist
    if (temp->next && temp->next->isfree){
        temp->prev->size += sizeof(LinkedListNode) + temp->next->size;
        temp->prev->next = temp->next->next;
    }
    
}