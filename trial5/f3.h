#include "Util.h"
#ifndef F3_H_
#define F3_H_
#include"HashMap.h"
#include"hash.h"
#include<stdio.h>
String readFile(FILE *,int *);
int getUniqueWord(HashMap * ,String );
int getAllSentences(HashList * , String);
void display_search(HashMap *,HashList *,String );
void display_search_phrase(HashMap *,HashList *,String);
#endif
