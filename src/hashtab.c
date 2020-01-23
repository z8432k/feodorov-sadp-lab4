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
  HashKey table = (HashKey) calloc(HASH_TAB_SIZE, sizeof(char) * HASH_TAB_ROW_SIZE);

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

bool isVacant(HashKey key) {
  return key[0] == 0 || key[KEY_FLAG_POS];
}

static inline bool isDeleted(HashKey key) {
  return key[KEY_FLAG_POS];
}

static inline bool isBingo(HashKey key, HashKey target) {
  return !isVacant(key) && !strncmp(key, target, HASH_TAB_KEY_SIZE);
}

static inline void markDeleted(HashKey key) {
  key[KEY_FLAG_POS] = 1;
}

static setData(HashKey key, HashKey data) {
  strncpy(key, data, HASH_TAB_KEY_SIZE);
}

ssize_t hashTabSet(HashTab tab, HashKey key) {
  size_t idx = hash(key);
  size_t step = 1, loop = 1;

  HashKey current;
  do {
    current = &tab[idx];

    if (isVacant(current)) {
      setData(current, key);
      return idx;
      break;
    }
    else {
      idx = idx + step * step;
    }

    step++;

    if (idx >= HASH_TAB_SIZE) {
      idx = step;
      loop++;
    }
  } while (loop < HASH_MAX_LOOP);

  return -1;
}

ssize_t hashTabGet(HashTab tab, HashKey key, HashKey *result) {
  size_t idx = hash(key);
  size_t step = 1, loop = 1;

  HashKey current;
  do {
    current = &tab[idx];

    if (isBingo(current, key)) {
      if (result) {
        HashKey data = allocKey();
        setData(data, current);
        *result = data;
      }

      break;
    }
    else if (isDeleted(current)) {
      idx = idx + step * step;
    }
    else {
      return -1;
    }

    step++;

    if (idx >= HASH_TAB_SIZE) {
      idx = step;
      loop++;
    }
  } while (loop < HASH_MAX_LOOP);

  return idx;
}

void hashTabFree(HashTab tab) {
  free(tab);
}

bool hasTabDel(HashTab tab, HashKey key) {
  ssize_t idx = hashTabGet(tab, key, NULL);

  if (idx > 0) {
    HashKey target = &tab[idx];

    bool already = isDeleted(target);

    if (!already) {
      markDeleted(target);
    }

    return !already;
  }
  else {
    return false;
  }
}
