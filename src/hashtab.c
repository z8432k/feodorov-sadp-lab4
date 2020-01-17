#include "include/hashtab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {
  KEY_SIZE = 7
};

uint hash(HashKey key) {
  uint h = 0;
  unsigned char *p;

  for (p = (unsigned char *) key; *p != '\0'; p++) {
    h = h + *p * *p;
  }

  return h % HASH_TAB_SIZE;
}

uint* allocHashTable() {
  uint *table = (uint *) calloc(HASH_TAB_SIZE, sizeof(uint));

  return table;
}

inline static char getNumber() {
  char sym;

  sprintf(&sym, "%d", rand() % 10);

  return sym;
}

inline static char getAlpha() {
  String base = "ABCDEFGHIGKLMNOPQARSUVWXYZ";
  size_t bSize = strlen(base);

  size_t pos = rand() % bSize;

  return base[pos];
}

HashKey allocKey() {
  return calloc(KEY_SIZE, sizeof(char));
}

HashKey genKey(HashKey key) {
  if (!key) {
    key = allocKey();
  }

  HashKey orig = key;

  size_t n = 2;


  for (size_t i = 0; i < n; i++) {
    *key = getNumber();
    key++;
  }

  for (size_t i = 0; i < n; i++) {
    *key = getAlpha();
    key++;
  }

  for (size_t i = 0; i < n; i++) {
    *key = getNumber();
    key++;
  }

  key = orig;

  return key;
}
