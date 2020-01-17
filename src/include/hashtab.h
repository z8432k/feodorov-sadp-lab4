#define HASH_TAB_SIZE 3000

typedef char *HashKey;
typedef HashKey String;
typedef unsigned int uint;
typedef unsigned short ushort;

uint hash(HashKey key);
HashKey genKey();
HashKey allocKey();
