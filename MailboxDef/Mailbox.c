#include "Mailbox.h"

mailbox_p* constructMailbox(){
    return w_malloc(sizeof(mailbox_p));
}

void deliverMail(mailbox_p* mailbox, message_p* message){
    push_stack(&(mailbox->messageStack), message);
}

message_p* checkMail(mailbox_p* mailbox){
    pop_stack(&(mailbox->messageStack));
}

message_p* buildMessage(int majorSys, int actionType, void* optObj){
    message_p* message = w_malloc(sizeof(message_p));
    message->majorSubsystem = majorSys;
    message->actionType = actionType;
    message->optObj = optObj;
    return message;
}

void recycleMessage(message_p* message){
    w_free(message);
}