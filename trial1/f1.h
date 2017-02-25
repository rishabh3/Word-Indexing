#ifndef F1_H
#define F1_H
#include<stdio.h>
#include"String.h"
#define MAX 5000
#define MAXLINES 15
typedef struct book{
  char *p[MAX];
  int size;
}Book;
typedef struct list{
  String string[MAX];
  int listSize;
}WordList;
Book* makeBook();
WordList* makeWordList();
int readPara(Book *,FILE *);
int getUniqueWord(char *,WordList *);
#endif
