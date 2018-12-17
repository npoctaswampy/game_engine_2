
#ifndef LINKEDLIST
#define LINKEDLIST

typedef struct LinkedListNode_t{
	struct LinkedListNode_t* next;
	void* data;
}LinkedListNode_p;

typedef struct LinkedList_t{
	LinkedListNode_p* head;
	LinkedListNode_p* tail;
	int sizeOfList;
}LinkedList_p;

void initLinkedList(LinkedList_p* list);
void destructLinkedList(LinkedList_p* list);
void insertAtTail(LinkedList_p* list, void* data);
void insertAtHead(LinkedList_p* list, void* data);
LinkedListNode_p* getHeadLLNode(LinkedList_p* list);
LinkedListNode_p* getTailLLNode(LinkedList_p* list);
LinkedListNode_p* getNextLLNode(LinkedListNode_p* currentNode);
void* getDataFromLLNode(LinkedListNode_p* node);

#endif
