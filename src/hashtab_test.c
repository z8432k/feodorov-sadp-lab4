#include <stdio.h>
#include <stdlib.h>
#include "include/hashtab.h"

int main(void) {
  printf("== Hash table implementation. ==\n\n");

  HashKey key = allocKey();
  ushort *result = (ushort *) calloc(3000, sizeof(ushort));

  size_t attempts = HASH_TAB_SIZE * 3;

  for (size_t i = 0; i < attempts; i++) {
    key = genKey(key);
    uint idx = hash(key);
    printf("%d - %s\n", idx, key);
    result[idx]++;
  }

  FILE * stat = fopen("stat.csv", "w");
  for (size_t i = 0; i < HASH_TAB_SIZE; i++) {
    fprintf(stat, "%zu;%u\n", i, result[i]);
  }

  free(result);
  fclose(stat);

  HashTab htab = allocHashTable();

  hashTabSet(htab, genKey(key));
  hashTabSet(htab, "34SS43");
  hashTabSet(htab, genKey(key));

  HashKey res;
  hashTabGet(htab, "34SS43", &res);

  ssize_t deleted = hasTabDel(htab, "34SS43");

  deleted = hasTabDel(htab, "34SS43");

  free(key);
  free(res);

  hashTabFree(htab);

  exit(EXIT_SUCCESS);
}
