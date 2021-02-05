#include <stdio.h>
#include <stdlib.h>
#include "../Common.h"

stack* new_node(void* data)
{
	stack* node = (stack*) w_malloc(sizeof(stack));
	node->data = data;
        node->next = NULL;
	return node;
}

void push_stack(stack **head, void* new_data)
{
	stack* node = new_node(new_data);
	node->next = *head;
	*head = node;
}

void* pop_stack(stack **head)
{
	if(*head == NULL) return NULL;
	stack* node = *head;
	*head = (*head)->next;
	void* ret = node->data;
	w_free(node);
	return ret;
}

void freeStack(stack* head){ 
	void* ret = NULL;
	while((ret=pop_stack(&head))!=NULL){
		w_free(ret);	
	}
        w_free(head);
}

stack* combineStacks(stack* src, stack* dst){
    void* node = NULL;
    while( (node=pop_stack(&src)) != NULL ){
        push_stack(&dst,node);
    }
    return dst;
}

void foreach(stack* s, void* subsystem, void (*f)(void*, void*)) {
	void* node = NULL;
	while( (node=pop_stack(&s)) != NULL ){
		(*f)(subsystem, node);
	}
}
