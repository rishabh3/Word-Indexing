#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "f3.h"

int main(){
  printf("Enter File Name:\n");
  String c = (String)malloc(sizeof(char)*WORD_LENGTH);
  scanf("%s",c);
  printf("The File Name entered is:%s.\n",c);
  FILE * fp = fopen(c,"r");
  int * t =(int *)malloc(sizeof(int));
  String book = readFile(fp,t);
  printf("\nThe number of characters read : %d\n",*t);
  HashMap* h = newHashMap(DEFAULT_LOAD_FACTOR);
  int m = getUniqueWord(h,book);
  printf("\nThe total number of unique words are : %d\n",m);
  //HashList * hList = (HashList *)newHashList();
  //int th = getAllSentences(hList, book);
  //displayHashList(hList);
  //printf("%d\n",th);
  printf("Enter the search word:\n");
  String x = (String)malloc(sizeof(char)*WORD_LENGTH);
  scanf("%s", x);
  printf("The search word entered is: %s.\n",x);
  display_search(h,x,book);
  printf("Enter the search phrase:\n");
  String z = (String)malloc(sizeof(char)*MAX_SENTENCE_SIZE);
  scanf("\n%[^\t\n]s\n", z);
  z[strlen(z)]='\0';
  printf("The search phrase entered is: %s.\n",z);
  display_search_phrase(h,z,book);
   return 0;
}
