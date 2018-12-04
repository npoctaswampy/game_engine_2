/*table.h
MP7
Nathan Pocta

Purpose: File holds definitions necessary for the 
hash table ADT library*/

enum ProbeDec_t {LINEAR, DOUBLE, QUAD, CHAIN};

#define K_e 0

typedef void* data_t;   /* pointer to the information, I, to be stored in the table */
typedef unsigned int hashkey_t;   /* the key, K, for the pair (K, I) */
typedef struct entry_tag{
	hashkey_t K;
	int deleted;
	data_t I;
	struct entry_tag* next;
}entry_t;
typedef struct table_tag{
	int size;
	int deleted_keys;
	int retrieve_loc;
	int probing_type;
	int num_keys;
	int probe_count_recent;
	entry_t* table;
}table_t;


/*  The empty table is created.  The table must be dynamically allocated and
 *  have a total size of table_size.  The maximum number of (K, I) entries
 *  that can be stored in the table is table_size-1.  That is, there must
 *  always be at least one empty position.  For open addressing, the table is
 *  filled with a special empty key distinct from all other nonempty keys.  
 *
 *  the probe_type must be one of {LINEAR, DOUBLE, CHAIN}
 */
table_t *table_construct (int table_size, int probe_type);  

/* Sequentially remove each table entry (K, I) and insert into a new
 * empty table with size new_table_size.  Free the memory for the old table
 * and return the pointer to the new table.  The probe type should remain
 * the same
 */
table_t *table_rehash (table_t * T, int new_table_size);  

int table_entries (table_t *T);  /* returns number of entries in the table */
int table_full(table_t *T);  /* returns 1 if table is full and 0 if not full. */

/* returns the number of table entries marked as deleted */
int table_deletekeys(table_t *T);
   
/* Insert a new table entry (K, I) into the table provided the table is not
 * already full.  
 * Return:
 *      0 if (K, I) is inserted, 
 *      1 if an older (K, I) is already in the table (update with the new I), or 
 *     -1 if the (K, I) pair cannot be inserted.
 */
int table_insert (table_t *T, hashkey_t K, data_t I);

/* Delete the table entry (K, I) from the table.  
 * Return:
 *     pointer to I, or
 *     null if (K, I) is not found in the table.  
 *
 * See the note on page 490 in Standish's book about marking table entries for
 * deletions when using open addressing.
 */
data_t table_delete (table_t *T, hashkey_t K); 

/* Given a key, K, retrieve the pointer to the information, I, from the table,
 * but do not remove (K, I) from the table.  Return NULL if the key is not
 * found.
 */
data_t table_retrieve (table_t *T, hashkey_t K); 

/* Free all information in the table, the table itself, and any additional
 * headers or other supporting data structures.  
 */
void table_destruct (table_t *T);

/* The number of probes for the most recent call to table_retrieve,
 * table_insert, or table_delete.  See additional details in PDF
 */
int table_stats (table_t *T);  

/* This function is for testing purposes only.  Given an index position into
 * the hash table return the value of the key stored there or a 0 if the index
 * position does not contain a key.  For separate chaining, return the key
 * found in the list_position at this index position.  see PDF.  Make the first
 * lines of this function 
 *       assert(0 <= index && index < table_size); 
 *       assert(0 < list_position); 
 */
hashkey_t table_peek(table_t *T, int index, int list_position); 

/* Print the table position and keys in a easily readable and compact format.
 * Only useful when the table is small.
 */
void table_debug_print(table_t *T);

