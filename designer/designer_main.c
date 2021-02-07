#include <stdio.h>

void runRoomMenu();

int main(int argc, char* argv[])
{

	char selection;

    printf("What are we editing today?\n");
    printf("(a) Rooms\n");

    scanf("%c", &selection);

    switch(selection)
    {
    	case 'a':
    		runRoomMenu();
    		break;
    }

    printf("Goodbye\n");
}


void runRoomMenu()
{
	char newOrExisting;

	printf("Would you like to:\n");
	printf("(a) Create a new file?\n");
	printf("(a) Edit an existing file?\n");

	scanf("%c", &newOrExisting);
	printf("%c", newOrExisting);


}
