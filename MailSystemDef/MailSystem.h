#include "../DataStructures/LinkedList.h"
#include "../DataStructures/StringDict.h"
#include "MailboxDef/MailBox.h"

#ifndef MAILSYSTEM
#define MAILSYSTEM

/* Needs subscribers, which is a collection of mailboxes to check
 * Should probably be a map, so that we can supply subscribers with addresses*/
typedef struct mailsystem_t{
	StringDict_p* subscriberMap;
} mailsystem_p;

void initMailSystem(mailsystem_p* mailSystem);
void destructMailSystem(mailsystem_p* mailSystem);
// Need to be able to get subscribers
void subscribeForMail(mailsystem_p* mailSystem, char* address, mailbox_p* mailbox);
stack* envelopeMailStack(stack* letters, char* address);
// And unsub
void unsubscribe(mailsystem_p* mailSystem, char* address);
// Mail sending methods
void sendMail(mailsystem_p* mailSystem, message_p* message);
void sendSingleMail(mailsystem_p* mailSystem, message_p* message);
void blastMail(mailsystem_p* mailSystem, message_p* message);


#endif /* MAILSYSTEM */
