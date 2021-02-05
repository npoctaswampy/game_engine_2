#include "Mailbox.h"

mailbox_p* constructMailbox(){
	mailbox_p* mailbox = (mailbox_p*) w_malloc(sizeof(mailbox_p));
	mailbox->messageStack = NULL;
    return mailbox;
}

void deliverMail(mailbox_p* mailbox, message_p* message){
    push_stack(&(mailbox->messageStack), message);
}

message_p* checkMail(mailbox_p* mailbox){
    return (message_p*) pop_stack(&(mailbox->messageStack));
}

message_p* buildMessage(char* addr, char* actionType, void* optObj){
    message_p* message = w_malloc(sizeof(message_p));
    message->address = addr;
    message->actionType = actionType;
    message->optObj = optObj;
    return message;
}

void recycleMessage(message_p* message){
    w_free(message);
}
