#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Author: Guilherme Santos
Data: 28/05/2024


Implementation of a simple hashTable with the value separated from the key

*/

struct listNode {
    int key;
    int value;
    struct listNode *nextPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

#define TABLE_SIZE 100

typedef struct {
    ListNodePtr *table;
} HashTable;

HashTable* createTable() {
    HashTable *hashTable = malloc(sizeof(HashTable));
    hashTable->table = malloc(sizeof(ListNodePtr) * TABLE_SIZE);

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(HashTable *hashTable, int key, int value) {
    int hashIndex = hashFunction(key);
    ListNodePtr newNode = malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->value = value;
    newNode->nextPtr = hashTable->table[hashIndex];
    hashTable->table[hashIndex] = newNode;
}

int search(HashTable *hashTable, int key, int *value) {
    int hashIndex = hashFunction(key);
    ListNodePtr current = hashTable->table[hashIndex];
    
    while (current != NULL) {
        if (current->key == key) {
            *value = current->value;
            return 1;
        }
        current = current->nextPtr;
    }

    return 0;
}

void delete(HashTable *hashTable, int key) {
    int hashIndex = hashFunction(key);
    ListNodePtr current = hashTable->table[hashIndex];
    ListNodePtr previous = NULL;

    while (current != NULL && current->key != key) {
        previous = current;
        current = current->nextPtr;
    }

    if (current == NULL) {
        printf("Key not found\n");
        return;
    }

    if (previous == NULL) {
        hashTable->table[hashIndex] = current->nextPtr;
    } else {
        previous->nextPtr = current->nextPtr;
    }

    free(current);
}

void display(HashTable *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ListNodePtr current = hashTable->table[i];
        printf("Index %d: ", i);

        while (current != NULL) {
            printf("(Key: %d, Value: %d) -> ", current->key, current->value);
            current = current->nextPtr;
        }

        printf("NULL\n");
    }
}

int main() {
    HashTable *hashTable = createTable();
    srand(time(NULL));

    for(int i = 0; i < 100; i++){
        int value = rand() % 100;
        int key = rand() % 1000;
        insert(hashTable, key, value);
    }

    display(hashTable);

    int value;
    if (search(hashTable, 30, &value)) {
        printf("Key 30 found with value %d\n", value);
    } else {
        printf("Key 30 not found\n");
    }
    delete(hashTable, 30)
    display(hashTable);

    return 0;
}
