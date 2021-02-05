#include "../../Common.h"

#ifndef MAILBOX
#define MAILBOX

typedef struct mailbox_t{
    stack* messageStack;
} mailbox_p;


typedef struct message_t{
    char* address;
    char* actionType;
    void* optObj;
} message_p;

mailbox_p* constructMailbox();
void deliverMail(mailbox_p* mailbox, message_p* message);
message_p* checkMail(mailbox_p* mailbox);
message_p* buildMessage(char* addr, char* actionType, void* optObj);
void recycleMessage(message_p* message);


#endif
