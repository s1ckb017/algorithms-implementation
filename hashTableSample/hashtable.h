/**
 * @file hashtable.h
 * @Synopsis  Simple HashTable Header
 * @author Michele Campa aka s1ckb017
 * @date 2018-03-10
 */

#define PRIME 1264565347

// linked list
struct bucket{
    int value;
    struct bucket * next;
};

typedef struct bucket bucket_t;


struct hashItem{
    int key;
    bucket_t * values;
};

typedef struct hashItem hashItem_t;

struct hashTable{
    int size;
    hashItem_t * table;
};

typedef struct hashTable hashTable_t;



hashTable_t *initHashTable(int size);
int hashFunction(int key, hashTable_t *h);
void add2Table(int key, int value, hashTable_t * table);
bucket_t * lookupValue(int key, hashTable_t * table);
void removeValue(int key, hashTable_t * table);
void destroyTable(hashTable_t *h);

