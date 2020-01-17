#include "include/hashtab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t hash(HashKey key) {
  size_t h = 0;
  unsigned char *p;

  for (p = (unsigned char *) key; *p != '\0'; p++) {
    h = h + *p * *p;
  }

  return h % HASH_TAB_SIZE;
}

HashTab allocHashTable() {
  HashKey table = (HashKey) calloc(HASH_TAB_SIZE, sizeof(char) * HASH_TAB_KEY_SIZE);

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
  return calloc(HASH_TAB_KEY_SIZE, sizeof(char));
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

ssize_t hashTabSet(HashTab tab, HashKey key) {
  size_t idx = hash(key) * HASH_TAB_KEY_SIZE;
  size_t step = 1;


  do {
    if (!tab[idx]) {
      strncpy(&tab[idx], key, HASH_TAB_KEY_SIZE - 1);
      return idx;
      break;
    }
    else {
      idx = idx + step * step;
    }

    step++;
  } while (idx < HASH_TAB_SIZE);

  return -1;
}

ssize_t hashTabGet(HashTab tab, HashKey key, HashKey *result) {
  size_t idx = hash(key);
  size_t step = 1;

  do {
    if (tab[idx * HASH_TAB_KEY_SIZE] > 0) {
      if (result) {
        HashKey data = allocKey();
        strncpy(data, &tab[idx], HASH_TAB_KEY_SIZE - 1);
        *result = data;
      }

      break;
    }
    else if (tab[idx * HASH_TAB_KEY_SIZE] < 0)
    {
      idx = idx + step * step;
    }
    else {
      return -1;
    }

    step++;
  } while (idx < HASH_TAB_SIZE);

  return idx;
}

void hashTabFree(HashTab tab) {
  free(tab);
}

ssize_t hasTabDel(HashTab tab, HashKey key) {
  ssize_t idx = hashTabGet(tab, key, NULL);

  if (idx >= 0) {
    tab[idx * HASH_TAB_KEY_SIZE] = -1;
  }

  return idx;
}
