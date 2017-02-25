#include "Util.h"
#ifndef F3_H_
#define F3_H_
#include"HashMap.h"
#include<stdio.h>
String readFile(FILE *,int *);
int getUniqueWord(HashMap * ,String );
void display_search(HashMap *,String ,String);
void display_search_phrase(HashMap *,String,String);
void help(ArrayList,String,String);
void displayH(HashMap *);
#endif
