/*table.c
Nathan Pocta
MP7
due: Monday, December 2, 2013
Purpose: Provides ADT for a hash table. Provides functions
for use in hash table exercises. Uses the % hash function. 
Collisions handled differently based on probe type. The 
probe type is passed from the calling function. Three 
different probe types: linear, double, chain.
Bugs: Does not like incorrect values or data types being passed.
*/
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include "Common.h"

/*Local function definitions*/
int find_duplicate(table_t* T, hashkey_t key, int spot, data_t inf);
int open_addressing_find(table_t* T, hashkey_t key, int* ret_val);
data_t chain_find(table_t* T, hashkey_t key, int delete);
data_t open_find(table_t* T, hashkey_t key,int delete);
data_t deletion_routine(table_t* T, int place);
int set_place(int place, hashkey_t key, table_t* T, int decrement_val);
data_t retrieval_routine(table_t* T, int place);
int find_decrement(table_t* T,hashkey_t key);

/*Takes in the size and type of the new table, and allocates memory for it.
returns pointer to the table head.*/
table_t *table_construct(int table_size, int probe_type)
{
	int i;
	table_t* T=(table_t*) w_malloc(sizeof(table_t));
	T->size=table_size;
	T->probing_type=probe_type;
	T->num_keys=0;
	T->probe_count_recent=0;
	T->deleted_keys=0;
	T->table=w_malloc(table_size*sizeof(entry_t));
	for(i=0;i<table_size;i++){
		((T->table)+i)->K=K_e;
		((T->table)+i)->I=NULL;
		((T->table)+i)->next=NULL;
		((T->table)+i)->deleted=0;
	}
	return T;
}

/*Table rehash
creates new table of different or same size and transfers items
from original table into it. This practice is used to remove 
deletions from the table. Takes pointer to original table and 
the size of the new table and returns the pointer to the newly made 
table.*/
table_t* table_rehash(table_t* T, int new_table_size)
{
	int i; 
	hashkey_t hold;
	data_t inf=NULL;
	entry_t* probin=NULL;
	table_t* T2=table_construct(new_table_size,T->probing_type);
	for(i=0;i<T->size;i++){
		if(((T->table)+i)->K!=K_e && ((T->table)+i)->deleted!=1)
			table_insert(T2,((T->table)+i)->K,table_delete(T,((T->table)+i)->K));
		if(T->probing_type==CHAIN && ((T->table)+i)->next!=NULL){
			probin=((T->table)+i);
			while(probin->next!=NULL){
				probin=probin->next;
			}
			hold=probin->K;
			inf=table_delete(T,probin->K);
			table_insert(T2,hold,inf);
			i--;
		}	
	}
	table_destruct(T);
	return T2;
}


/*Frees all memory associated with the table that was used. 
Takes pointer to table head and returns nothing.*/
void table_destruct(table_t* T){
	w_free(T->table);
	T->table=NULL;
	w_free(T);
	T=NULL;
}

/*Simply takes as input a pointer to the
table head and returns the value in the running count
for the number of keys in the table*/	
int table_entries(table_t* T)
{
	return T->num_keys;
}

/*This function does a simple computation
to decide whether or not a table is full
returns a 1 if full, else returns a 0*/
int table_full(table_t* T)
{
	if(T->num_keys==T->size-1) return 1;
	else return 0;
}

/*Return the running count of deleted keys
in the table header*/
int table_deletekeys(table_t* T)
{
	return T->deleted_keys;
}

/*Prints the status of the table being used
used in verbose printings*/
void table_debug_print(table_t* T)
{
	int i;
	entry_t* printer=NULL;
	printf("Table Entries: %d\n",(table_entries(T)));
	printf("Number of Deleted Keys: %d\n",(table_deletekeys(T)));
	printf("Probing Type: ");
	if(T->probing_type==LINEAR)
		printf("LINEAR\n");
	else if(T->probing_type==DOUBLE)
		printf("DOUBLE\n");
	else printf("CHAIN\n");
	for(i=0;i<(T->size);i++){
		printer=(T->table)+i;
		if(printer->K==K_e && printer->next==NULL){
			printf("Entry %d is empty\n",i);
		}else{
			if(T->probing_type!=CHAIN)
				printf("Entry: %d, Key: %d",i,(printer->K));
			if(printer->next!=NULL) 
				printf("Entry: %d",i);
			while(printer->next!=NULL){
				printer=printer->next;
				printf(" --> Key: %d",printer->K);
			}
			if(T->probing_type != CHAIN)
				printf(", Deleted: %d",printer->deleted);
			printf("\n");
		}
	}
}

/*INSERTION FUNCTIONS*/
/*-----------------------------------------------------------------------------------*/		

/*The mother insertion function. Decides what to do based
on probe type. If open addressing, other function finds the location for 
the item to go, and inserts there. 
if chain, finds location itself and inserts there
returns status of insertion*/
int table_insert(table_t* T, hashkey_t key, data_t inf)
{
	int ret_val=-1;
	if(T!=NULL && T->table!=NULL){
		T->probe_count_recent=0;

		if(T->probing_type==LINEAR || T->probing_type==DOUBLE){
			int spot=open_addressing_find(T,key,&ret_val);
			if(spot==-1)
		 		return -1;
			if(spot==-2){
				printf("CATASTROPHIC ERROR! Exiting...\n");
				exit(1);
			}
			if(ret_val==1){
				w_free(((T->table)+spot)->I);
				((T->table)+spot)->I=NULL;
			}
			if(ret_val==0) T->num_keys++;
			((T->table)+spot)->K=key;
			((T->table)+spot)->I=inf;
			if(((T->table)+spot)->deleted==1){
				((T->table)+spot)->deleted=0;
				T->deleted_keys--;
			}
		}else{
			int spot=(key%(T->size));
			ret_val=find_duplicate(T,key,spot,inf);
			if(ret_val==0){
				entry_t* new=(entry_t*)w_malloc(sizeof(entry_t));
				new->K=key;
				new->I=inf;
				new->next=NULL;
				entry_t* prev=((T->table)+spot);
				T->probe_count_recent++;
				while(prev->next!=NULL){ 
					prev=prev->next;
					T->probe_count_recent++;
				}
				prev->next=new;
				T->num_keys++;
			}
		}
	
		return ret_val;
	}else{
		printf("Not a valid table. Has not been constructed properly\n");
		printf("Exiting\n");
		exit(1);
	}
}

/*Locates position for the proper insertion of an item
in the table. Returns position and is able to change the 
return value of insert function based on findings*/
int open_addressing_find(table_t* T, hashkey_t key, int* ret_val)
{
	int decrement_val=find_decrement(T,key);
	int place=(key%T->size);
	if(table_deletekeys(T)>0){ /*If there are deleted keys, the path*/
		if(table_retrieve(T,key)!=NULL){/*could be messed up. In this*/
			*ret_val=1;	        /*case, a duplicate could be overlooked*/
			return T->retrieve_loc; /*so we check for a duplicate*/
		}				/*using retrieve*/
	}
	*ret_val=0;
	int initplace=place; 
	 T->probe_count_recent++;
	 while(((T->table)+place)->K!=K_e && ((T->table)+place)->deleted==0){
		if(((T->table)+place)->K==key && ((T->table)+place)->deleted==0){ 
			*ret_val=1; /*Finds duplicates if no deleted keys*/
			return place;
		}
		place=set_place(place, key, T, decrement_val);/*decrements*/
		T->probe_count_recent++;
		if(place==initplace){ /*protects against infinite loops*/
			return -2;    /*If not full, and returns to initplace*/
		}		      /*without finding anything, it is not*/
	}			      /*checking every space. catastrophic error*/
	if(table_full(T) == 1){
		*ret_val=-1;
		return -1;
	}
	return place;
}

/*Function that supports insertions of chain probe types.
returns 1 if duplicate is found. 0 if not found*/
int find_duplicate(table_t* T, hashkey_t key, int spot, data_t inf)
{
	entry_t* find=((T->table)+spot);
	while(find!=NULL){
		if(find->K==key){
			w_free(find->I);
			find->I=inf;
			return 1;
		}else find=find->next;
	}
	return 0;
}
	

/*DELETION/RETRIEVAL FUNCTIONS*/
/*-----------------------------------------------------------------------------------*/
/*Mother deletion function. Basically decides what function to call
based on which probe type is used. Returns information stored at specific 
loctaion (or NULL if the information is not found).*/
data_t table_delete(table_t* T, hashkey_t K)
{
	if(T!=NULL && T->table!=NULL){
		T->probe_count_recent=0;
		if(T->probing_type==CHAIN){
			return chain_find(T, K, 1);
		}
		else return open_find(T,K,1);
	}else{
		printf("Not a valid table. Has not been constructed properly\n");
		return NULL;
	}
}

/*Mother retrieve function. Basically decides what function to call
based on which probe type is used. Returns information stored at specific 
loctaion (or NULL if the information is not found).*/
data_t table_retrieve(table_t* T, hashkey_t K)
{
	if(T!=NULL && T->table!=NULL){
		T->probe_count_recent=0;
		if(T->probing_type==CHAIN){
			return chain_find(T, K, 0);
		}
		else return open_find(T,K,0);
	}else{
		printf("Not a valid table. Has not been constructed properly\n");
		return NULL;
	}
}

/*Function that finds and deletes (if called from the mother
delete function) or just finds (if called from the mother retrieve
function). returns a pointer to information in spot specified
by key in function.*/
data_t chain_find(table_t* T, hashkey_t key, int delete)
{
	data_t ret=NULL;
	entry_t* n=NULL;
	entry_t* find=(T->table)+(key%T->size);
	while(find->next != NULL){
		T->probe_count_recent++;
		if((find->next)->K==key){
			ret=(find->next)->I;
			if(delete==1){
				find->next->I=NULL;
				n=find->next->next;
				w_free(find->next);
				find->next=n;
				T->num_keys--;
			}
			return ret;
		}
		find=find->next;
	}
	return ret;
}

/*This function is the same as the one above. However, 
if a key is found in this function, the support functions
called deletion_routine or retriveal_routine are called
based on the mother function that calls them*/
data_t open_find(table_t* T, hashkey_t key, int delete)
{
	int decrement_val=find_decrement(T,key);
	data_t ret=NULL;
	int place=(key%(T->size));
	int initplace=place;
	T->probe_count_recent++;
	while(((T->table)+place)->K!=key || ((T->table)+place)->deleted==1){
		if(((T->table)+place)->K==K_e) return ret;
		place=set_place(place, key, T, decrement_val);
		if(place==initplace) break;
		T->probe_count_recent++;
	}
	if(((T->table)+place)->K==key){
		if(delete==1)
			ret = deletion_routine(T, place);
		else ret = retrieval_routine(T,place);
	}
	return ret;
}

/*This function is used to delete an item
from the table and returns the information located at that 
item*/
data_t deletion_routine(table_t* T, int place)
{
	data_t ret=((T->table)+place)->I;
	((T->table)+place)->I=NULL;
	((T->table)+place)->deleted=1;
	T->deleted_keys++;
	T->num_keys--;
	return ret;
}

/*This function is used to simply retrieve the 
data located at a specific place in the table*/
data_t retrieval_routine(table_t* T, int place)
{
	T->retrieve_loc=place;
	return ((T->table)+place)->I;
}	

/*-------------------------------------------------------------------------*/

/*Simply accesses and returns the count of the most recent number
of probes from the most recent insertion, deletion, or retrieval.*/
int table_stats(table_t* T)
{
	return T->probe_count_recent;
}

/*Takes a position of the list and returns the key located at that 
specific location.*/
hashkey_t table_peek(table_t* T, int index, int list_position)
{
	assert(0<=index && index < T->size);
	assert(0<list_position);
	int i;
	if(T->probing_type!=CHAIN){
		if(((T->table)+index)->K==K_e || ((T->table)+index)->deleted==1)
			return 0;
		else
			return (((T->table)+index)->K);
	}else{
		entry_t* h=((T->table)+index);
		for(i=0; (i<list_position && h!=NULL); i++){
			h=h->next;
		}
		if(h==NULL){
			return 0;
		}else return h->K;
	}
}

/*Used to decrement a position in a hashtable. Returns the 
offset that is used to find the location*/
int set_place(int place, hashkey_t key, table_t* T, int decrement_val)
{
	if((place-decrement_val)>=0) place= place-decrement_val;
	else place=(T->size+(place-decrement_val));
	return place;
}

/*Used to find a decrement based on the key and size
of the table*/
int find_decrement(table_t* T,hashkey_t key){
	int decrement_val;
	if(T->probing_type==LINEAR){
		decrement_val=1;
	}else{
		if(((key/(T->size))%T->size)>1)
			decrement_val=((key/(T->size))%T->size);
		else decrement_val=1;
	}
	return decrement_val;
}










































































