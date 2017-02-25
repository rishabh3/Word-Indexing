#ifndef F2_H
#define F2_H
#include "String.h"
#include <stdio.h>
#define MAX 1000
#define MAXAMT 5000
typedef struct array{
  int wordIndex[MAXAMT];
  int size;
}ArrayList;
typedef struct word{
  char* string;
  ArrayList* aList;
}Word;
typedef struct list{
  Word * word;
  int listSize;
}WordList;

WordList* makeWordList();
int readFile(FILE *,String *);
int getWordList(String *,WordList *);
void swap(Word *, Word *);
void qSort(WordList* , int ,int );
ArrayList* bSearch(WordList *,char *,int ,int,int *);
void display(ArrayList *);
#endif
