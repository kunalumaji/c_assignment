#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct HashNode {
    char* key;
    int value;
    struct HashNode* next;
};

struct HashMap {
    int bucket_size;
    int total_elements;
    struct HashNode** list;
};


unsigned int hasher(const char* str) {

    const unsigned int initial_offset = 2166136261;
    unsigned int prime_multiple = 16777619U;

    for (int i = 0; i < strlen(str); i++) {
        prime_multiple = prime_multiple * (initial_offset ^ str[i]);
    }

    return prime_multiple;
}


int GET_VALUE(struct HashMap* hashmap, char* key) {

    int answer = -1;

    unsigned int hash_value = hasher(key);
    unsigned int array_index = hash_value % hashmap->bucket_size;

    printf("finding at bucket index: (%u)\n", array_index);

    struct HashNode* bucket = *(hashmap->list + array_index);

    while (bucket != NULL) {

        printf("checking key: (%s)\n", bucket->key);

        if (strcmp(bucket->key, key) == 0) {
            return bucket->value;
        }
        bucket = bucket->next;
    }

    printf("element not found in hash table\n");

    return answer;
}

int ADD_KEY(struct HashMap* hashmap, char* key, int value);

struct HashMap RESIZE_TABLE(struct HashMap* oldMap, int oldMapCount) {

    printf("---\nResizing Table\n");
    struct HashMap* newMap = (struct HashMap*) malloc(sizeof(struct HashMap));
    newMap->bucket_size = oldMap->bucket_size;
    newMap->total_elements = 0;
    newMap->list = calloc(newMap->bucket_size, sizeof(struct HashNode*));

    printf("Copied: ");
    for (int i = 0; i < oldMapCount; i++) {
        // printf("processing bukcet (%d)... ", i);
        struct HashNode* bucket = *(oldMap->list + i);
        while (bucket != NULL) {
            ADD_KEY(newMap, bucket->key, bucket->value);
            bucket = bucket->next;
        }
        printf("\n");
    }

    printf("Table Resized to (%d) and (%d) elements copied\n---\n", newMap->bucket_size, newMap->total_elements);
    return *newMap;
}


int ADD_KEY(struct HashMap* hashmap, char* key, int value) {

    int status = 0;

    double load_factor = (double) hashmap->total_elements / hashmap->bucket_size;

    // printf("proceeding to add key (load factor: %f)\n", load_factor);

    if (load_factor > 0.75) {
        int oldMapCount = hashmap->total_elements;
        hashmap->bucket_size = ((hashmap->total_elements) / load_factor) + 1;
        *hashmap = RESIZE_TABLE(hashmap, oldMapCount);
    }

    // printf("new bucket size: (%d)\n", hashmap->bucket_size);

    int hash_value = hasher(key);
    int array_index = hash_value % hashmap->bucket_size;

    // printf("bucket index: (%d)\n", array_index);

    struct HashNode* node = (struct HashNode*) malloc(sizeof(struct HashNode));
    if (node == NULL) {
        printf("failed to allocate memory for struct HashNode");
        return status;
    }

    char* key_buffer = (char*) malloc(strlen(key) * sizeof(char));
    strcpy(key_buffer, key);

    node->key = key_buffer;
    node->value = value;
    node->next = NULL;

    struct HashNode** bucket = (hashmap->list + array_index);

    while (*bucket != NULL) {
        if (strcmp((*bucket)->key, key) == 0) {
            (*bucket)->value = value;
            return 1;
        }
        if ((*bucket)->next != NULL) {
            *bucket = (*bucket)->next;
            break;
        }
        else {
            (*bucket)->next = node;
            break;
        }
    }
    if (*bucket == NULL)
        *bucket = node;

    hashmap->total_elements += 1;
    printf("key added (%s)\n", key);

    status = 1;

    return status;
}


int main() {

    struct HashMap map = {
        1, 0, NULL
    };
    map.list = calloc(map.bucket_size, sizeof(struct HashNode*));
    for (int i = 0; i < map.bucket_size; i++) {
        map.list[i] = NULL;
    }

    printf("Hashmap created\n");

    if (ADD_KEY(&map, "MH224", 2) == 1) {
        printf("element added successfully\n");
    }

    if (ADD_KEY(&map, "MH227", 9) == 1) {
        printf("element added successfully\n");
    }

    if (ADD_KEY(&map, "MH230", 12) == 1) {
        printf("element added successfully\n");
    }

    if (ADD_KEY(&map, "MH234", 11) == 1) {
        printf("element added successfully\n");
    }

    if (ADD_KEY(&map, "MH23", 12) == 1) {
        printf("element added successfully\n");
    }

    if (ADD_KEY(&map, "MH2309", 11) == 1) {
        printf("element added successfully\n");
    }

    printf("\nTotal Elements: %d\n", map.total_elements);

    int ans = GET_VALUE(&map, "MH230");

    if (ans >= 0) {
        printf("value of the element: %d\n", ans);
    }

    return 0;

}