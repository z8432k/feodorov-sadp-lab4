#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <glib.h>

#define HASH_TAB_SIZE 3000
#define HASH_TAB_ROW_SIZE 8
#define HASH_TAB_KEY_SIZE 6
#define KEY_FLAG_POS 7
#define HASH_MAX_LOOP 3

typedef char* String;
typedef String HashKey;
typedef HashKey* HashTab;

size_t hash(HashKey key);
HashKey genKey(HashKey key);
HashKey allocKey();
HashTab allocHashTable();
void hashTabFree(HashTab tab);
ssize_t hashTabSet(HashTab tab, HashKey key);
ssize_t hashTabGet(HashTab tab, HashKey key, HashKey *result);
bool hasTabDel(HashTab tab, HashKey key);
bool isVacant(HashKey key);
