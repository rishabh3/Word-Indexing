#ifndef HMNODE_H
#define HMNODE_H
#include "Util.h"
#include "ArrayList.h"
typedef struct hmnode{
  String key;
  ArrayList  indexlist;
}HMNode;
HMNode* newHMNode(String , int ,int);
void freeHMNode(HMNode *);
#endif
