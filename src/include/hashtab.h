#include <stdlib.h>
#include <sys/types.h>

#define HASH_TAB_SIZE 3000
#define HASH_TAB_KEY_SIZE 7

typedef char *HashKey;
typedef HashKey String;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef char * HashTab;

size_t hash(HashKey key);
HashKey genKey(HashKey key);
HashKey allocKey();
HashTab allocHashTable();
void hashTabFree(HashTab tab);
ssize_t hashTabSet(HashTab tab, HashKey key);
ssize_t hashTabGet(HashTab tab, HashKey key, HashKey *result);
ssize_t hasTabDel(HashTab tab, HashKey key);
