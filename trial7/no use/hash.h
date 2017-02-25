#include "Util.h"
#ifndef HASH_H
#define HASH_H
#define INITIAL_HASHLIST_SIZE 8
typedef struct hash{
  //int sent_num;
  String sentence;
}Hash;
typedef struct hashlist{
  Hash * hashList;
  int initial_size;
  int size;
}HashList;

String searchCode(HashList *,int );
HashList* newHashList();
HashList * expandHashList(HashList *);
int appendHashList(HashList*, String);
void clearHashList(HashList *);
void freeHashList(HashList *);
void displayHashList(HashList *);

#endif
