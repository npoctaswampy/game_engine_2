#include "MailSystem.h"

void sendSingleMail(mailsystem_p* mailSystem, message_p* message);
void blastMail(mailsystem_p* mailSystem, message_p* message);

pthread_mutex_t lock;

void initMailSystem(mailsystem_p* mailSystem){
	mailSystem->subscriberMap = malloc(sizeof(StringDict_p));
	initDict(mailSystem->subscriberMap);
}

void destructMailSystem(mailsystem_p* mailSystem){
	destructDict(mailSystem->subscriberMap);
}

void subscribeForMail(mailsystem_p* mailSystem, char* address, mailbox_p* mailbox){
	insertIntoDict(mailSystem->subscriberMap, address, mailbox);
}

void unsubscribe(mailsystem_p* mailSystem, char* address){
	deleteFromDict(mailSystem->subscriberMap, address);
}

stack* envelopeMailStack(stack* letters, char* address){
	stack* envelopeStack = NULL;
	message_p* message;
	void* letter = NULL;
	while((letter = pop_stack(&letters)) != NULL){
		message = w_malloc(sizeof(message_p));
		message->actionType = "";
		message->address = address;
		message->optObj = letter;
		push_stack(&envelopeStack, message);
	}
	return envelopeStack;
}

stack* emptyMail(mailsystem_p* mailSystem, char* address){
	pthread_mutex_lock(&lock);
	mailbox_p* mailbox = (mailbox_p*) retrieveFromDict(mailSystem->subscriberMap, address);
	stack* ret = mailbox->messageStack;
	mailbox->messageStack = NULL;
	pthread_mutex_unlock(&lock);
	return ret;
}

void sendMail(mailsystem_p* mailSystem, message_p* message){
	pthread_mutex_lock(&lock);
	if(strcmp(message->address, "*") == 0) blastMail(mailSystem, message);
	else sendSingleMail(mailSystem, message);
	pthread_mutex_unlock(&lock);
}

void sendSingleMail(mailsystem_p* mailSystem, message_p* message){
	mailbox_p* mailbox = (mailbox_p*) retrieveFromDict(mailSystem->subscriberMap, message->address);
	deliverMail(mailbox, message);
}

void blastMail(mailsystem_p* mailSystem, message_p* message){
	mailbox_p* mailbox = NULL;
	LinkedListNode_p* currentNode = getHeadLLNode(mailSystem->subscriberMap->keys);
	do{
		mailbox = (mailbox_p*) retrieveFromDict(mailSystem->subscriberMap, (char*) currentNode->data);
		deliverMail(mailbox, message);
		currentNode = currentNode->next;
	}while(currentNode != NULL);
}

void blastFlag(mailsystem_p* mailSystem, char* flag){
	message_p* message = buildMessage(NULL, flag, NULL);
	blastMail(mailSystem, message);
}



