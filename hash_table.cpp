/*
 Student Name: Justin Lau
 Date: 11/01/19

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
  HashTableEntry* newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry)); //utilize malloc to allocate memory for entry
  newEntry->key = key; //assign new key to entry
  newEntry->value = value; //assign new value to entry
  newEntry->next = NULL; //next pointer is null
  return newEntry; //return entry
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
  HashFunction currentHash = hashTable->hash; //creates current hash function
  int hashIndex = currentHash(key); //retrieve key of current hash
  HashTableEntry *node = hashTable->buckets[hashIndex]; //head node
  for(int i = 0; i < hashTable->num_buckets; i++){ //loop through each linked list
    while(node){ //loop through all nodes
      if(node->key == key){ //if this node's key matches desired key, return node
        return node; 
      }
      node = node->next; //if not, go to next node
    }
  }
  return NULL; //if not found
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets contain indeterminant values, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct. 
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {
  for(int i = 0; i < hashTable->num_buckets; i++){ //loop through all buckets
    HashTableEntry* currentBucket = hashTable->buckets[i]; //currentBucket initialized
    while(currentBucket){ //if there's a value
      HashTableEntry* previousBucket = currentBucket; //store currentBucket
      currentBucket = currentBucket->next; //next bucket
      free(previousBucket->value);  //destroy previousBucket's value
      free(previousBucket); //destroy previousBucket
    }
  }
    free(hashTable->buckets); //destroy all hash buckets
    free(hashTable); //destroy hash table itself
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
  HashFunction currentHash = hashTable->hash; //creates current hash function
  int hashIndex = currentHash(key); //retrieve key of current hash
  HashTableEntry* node = findItem(hashTable, key); //find node of item to insert
  if(node) //node to insert
  {
    void* previousValue = node -> value; //store node value
    node -> value = value; //replace value
    return previousValue; //return original value
  }
  HashTableEntry* newNode =  createHashTableEntry(key, value); //if item is not found, point to new entry
  if(!newNode) //if mallocing memory fails to execute
  {
    return NULL;
  }
  newNode -> next = hashTable -> buckets[hashIndex]; //insert new node at head
  hashTable -> buckets[hashIndex] = newNode; //update node

  return NULL; //if not found
}


void* getItem(HashTable* hashTable, unsigned int key) {
  HashTableEntry* getValue = findItem(hashTable, key); //retrieve item
  if(getValue) //if it contains value, return
  { 
    return getValue->value;
  }
  return NULL; //if no value

}

void* removeItem(HashTable* hashTable, unsigned int key) { 
  HashFunction currentHash = hashTable->hash; //creates current hash function
  int hashIndex = currentHash(key); //retrieve key of current hash
  HashTableEntry* node = hashTable->buckets[hashIndex]; //head node
  if(node) //if head is node to be removed
  {
    if(node->key == key)
    {
      void* previousValue = node->value; //store previous value
      hashTable->buckets[hashIndex] = node->next; //next node
      free(node); //remove node
      return previousValue; //return original value
    }
  }

  while(node) //if head is not node to be removed, loop through all other nodes
  {
    if(node->next->key == key) //if next node is one to be removed
    {
      HashTableEntry* previousNode = node->next; //store previous node
      void* previousValue = previousNode -> value; //save previous value
      node -> next = previousNode->next; //point to next node
      free(previousNode); //free and remove the desired item
      return previousValue; //return previous value
    }
    node = node->next; //onto next entry
  }
  return NULL; //if not found
}

void deleteItem(HashTable* hashTable, unsigned int key) {
  free(removeItem(hashTable, key)); //frees and deletes desired item (no return)
}


