#include"Util.h"
#include"HMNode.h"
#include"ArrayList.h"
#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SIZE_INITIAL 1024
typedef struct hashmap{
  HMNode* hmnode_arr;
  int size;
  int capacity;
  double load_factor;
}HashMap;
HashMap * newHashMap(double );
void freeHashMap(HashMap *);
int search(HashMap * ,String );
int put(HashMap * ,String, int);
ArrayList get(HashMap *, String);

int hm_hash(String, int);
HashMap * hm_addHelper(HashMap *, HMNode*, int);
HashMap * hm_resizeRehash(HashMap *);
#endif
