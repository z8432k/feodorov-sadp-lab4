#include <stdio.h>
#include <stdlib.h>
#include "include/hashtab.h"

void seed() {
  HashKey key = allocKey();
  gushort *result = (gushort *)calloc(3000, sizeof(gushort));

  size_t attempts = HASH_TAB_SIZE * 3;

  for (size_t i = 0; i < attempts; i++) {
    key = genKey(key);
    guint idx = hash(key);
    printf("%d - %s\n", idx, key);
    result[idx]++;
  }

  FILE *stat = fopen("stat.csv", "w");
  for (size_t i = 0; i < HASH_TAB_SIZE; i++) {
    fprintf(stat, "%zu;%u\n", i, result[i]);
  }

  free(result);
  free(key);
  fclose(stat);
}

void printTab(HashTab tab) {
  HashKey current;
  for (size_t i = 0; i < HASH_TAB_SIZE; i++) {
    current = &tab[i];

    if (!isVacant(current)) {
      printf("%zu - %s\n", i, current);
    }
  }

  printf("\n\n");
}

int main(void) {
  printf("== Hash table implementation. ==\n\n");

  // seed();

  HashKey key = allocKey();
  HashTab htab = allocHashTable();

  ssize_t idx1 = hashTabSet(htab, genKey(key));
  ssize_t idx2 = hashTabSet(htab, "34SS43");
  ssize_t idx3 = hashTabSet(htab, genKey(key));

  HashKey res;
  ssize_t idx4 = hashTabGet(htab, "34SS43", &res);

  printTab(htab);

  bool idx5 = hasTabDel(htab, "34SS43");

  bool idx6 = hasTabDel(htab, "34SS43");

  ssize_t idx7 = hashTabSet(htab, "34SS43");

  free(key);
  free(res);

  printTab(htab);

  hashTabFree(htab);

  exit(EXIT_SUCCESS);
}
