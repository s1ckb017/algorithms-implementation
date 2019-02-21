#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

/*
 *      HashTable è una struttura dati che mappa una chiave in un valore
 *      il caso peggiore di ricerca è di O(1+a) se m < n dove a = n/m.
 *      m = numero di slot della tabella, cioè quante chiavi differenti possiamo salvare nella
 *      tabella. Mentre n è il dominio delle chiavi. 
 *      Per mappare una chiave in un indice di una tabella e' necessaria una hashFunction 
 *      che prende in input la chiave e restituisce un indice tra 0 e m.
 *      Non è possibile un hash function iniettiva poichè il dominio delle chiavi >> del numero di slot della tabella
 *      pertanto si verificano delle collisioni. Per bypassare le collisioni si può associare ad ogni indice una linked
 *      list di valori e non solo un unico valore. Oppure si può utilizzare il probing o il double hashing
 *
 *      Dunque hashtable sara una struct che contiene un vettore di hashitem il quale è una struct che conterrà
 *      la chiave e il bucket che non è altro che la lista collegata che contiene i valori che fan riferimento 
 *      alla stessa chiave.
 *      
 *      La LEN(il numero di slot) dell hashtable NON VARIA a runtime
 *      OVVIAMENTE hashfunction ritorna un interno compreso tra 0-m-1 poichè ci sono solo m slot differenti nella
 *      hashtable
 *
 * The hash table should be an array with length about 1.3 times the maximum
 * number of keys that will actually be in the table, and
 * 
 * Size of hash table array should be a prime number (especially with the 
 * simple hash function we looked at)
 *
 */



int main(int argc, char ** argv){
    
    hashTable_t * h = initHashTable(19);
    add2Table(1, 1, h);
    add2Table(2, 2, h);
    add2Table(239, 239, h);
    bucket_t *val = lookupValue(239, h);
    if (val != NULL){
        printf("value: %d at key 239\n", val->value);
    }
    removeValue(239, h);
    destroyTable(h);
    return 0;
}


hashTable_t* initHashTable(int size){
    int i = 0;
    hashTable_t * table = (hashTable_t *)malloc(sizeof(hashTable_t));
    table->size = size;
    table->table = (hashItem_t *) malloc(size*sizeof(hashItem_t *));
    
    for (i = 0; i < size; i ++){
        table->table[i].key = 0;
        table->table[i].values = NULL;
    }

    return table;
}


int hashFunction(int key, hashTable_t *h){
    int index = key % h->size;
    printf("key: %d   ====  index: %d\n", key, index);
    return index;
}

void add2Table(int key, int value, hashTable_t *h){
    int index = hashFunction(key, h);
    
    bucket_t *tmp = h->table[index].values; 
    bucket_t *toadd = (bucket_t *)malloc(sizeof(bucket_t));
    toadd->value = value;
    toadd->next = NULL;
    if(tmp == NULL){
        tmp = toadd;
    }
    else{
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = toadd;
    }
    return ;
}


bucket_t* lookupValue(int key, hashTable_t * h){
    int index = hashFunction(key, h);
    bucket_t * tmp = h->table[index].values; 
    return tmp;
}


void removeValue(int key, hashTable_t * h){
    int index = hashFunction(key, h);
    bucket_t * bucket = h->table[index].values; 
    bucket_t * tmp;
    h->table[index].key = 0;
    while(bucket != NULL){
        tmp = bucket->next;
        free(bucket);
        bucket = tmp;
    }
    return;
}


void destroyTable(hashTable_t *h){
    bucket_t * tmp; 
    for(int i = 0; i < h->size; i ++){
        bucket_t * bucket = h->table[i].values;
        while(bucket != NULL){
            tmp = bucket->next;
            free(bucket);
            bucket = tmp;
        }

    }
    free(h->table);
    free(h);
}
