#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void emptyListInsert(LinkedList_p* list, LinkedListNode_p* node);

void initLinkedList(LinkedList_p* list){
	list->head = NULL;
	list->tail = NULL;
	list->sizeOfList = 0;
}

void destructLinkedList(LinkedList_p* list){
	LinkedListNode_p* nextNode = NULL;
	LinkedListNode_p* currentNode = getHeadLLNode(list);
	do{
		nextNode = getNextLLNode(currentNode);
		free(currentNode);
		currentNode = nextNode;
	}while(nextNode != NULL);
}

void destructLinkedListAndData(LinkedList_p* list){
	LinkedListNode_p* nextNode = NULL;
	LinkedListNode_p* currentNode = getHeadLLNode(list);
	do{
		nextNode = getNextLLNode(currentNode);
		free(currentNode->data);
		free(currentNode);
		currentNode = nextNode;
	}while(nextNode != NULL);
}

void insertAtTail(LinkedList_p* list, void* data){
	LinkedListNode_p* node = malloc(sizeof(LinkedListNode_p));
	node->data = data;
	node->next = NULL;
	if(list->sizeOfList == 0) emptyListInsert(list, node);
	else{
		list->tail->next = node;
		list->tail = node;
	}
	list->sizeOfList++;
}

void insertAtHead(LinkedList_p* list, void* data){
	LinkedListNode_p* node = malloc(sizeof(LinkedListNode_p));
	node->data = data;
	node->next = NULL;
	if(list->sizeOfList == 0)emptyListInsert(list, node);
	else{
		node->next = list->head;
		list->head = node;
	}
	list->sizeOfList++;
}

LinkedListNode_p* getHeadLLNode(LinkedList_p* list){
	return list->head;
}

LinkedListNode_p* getTailLLNode(LinkedList_p* list){
	return list->tail;
}

LinkedListNode_p* getNextLLNode(LinkedListNode_p* currentNode){
	return currentNode->next;
}

void* getDataFromLLNode(LinkedListNode_p* node){
	return node->data;
}

void emptyListInsert(LinkedList_p* list, LinkedListNode_p* node){
	list->head = node;
	list->tail = node;
}