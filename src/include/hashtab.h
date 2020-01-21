#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <glib.h>

#define HASH_TAB_SIZE 3000
#define HASH_TAB_KEY_SIZE 7

typedef char* String;
typedef String HashKey;
typedef HashTabItem_t* HashTab;

typedef struct {
	char[HASH_TAB_KEY_SIZE] key;
	bool used;
	gpointer data;
} HashTabItem_t;

size_t hash(HashKey key);
void genKey(HashKey key);
HashKey allocKey();
HashTab allocHashTable();
void hashTabFree(HashTab tab);
ssize_t hashTabSet(HashTab tab, HashKey key, gpointer data);
gpointer hashTabGet(HashTab tab, HashKey key);
ssize_t hasTabDel(HashTab tab, HashKey key);
