#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "f3.h"

int main(){
  printf("Enter File Name:\n");
  String c = (String)malloc(sizeof(char)*WORD_LENGTH);
  scanf("%s",c);
  FILE * fp = fopen(c,"r");
  int * t =(int *)malloc(sizeof(int));
  String book = readFile(fp,t);
  printf("\nThe number of characters read : %d\n",*t);
  HashMap* h = newHashMap(DEFAULT_LOAD_FACTOR);
  int m = getUniqueWord(h,book);
  printf("\nThe total number of unique words are : %d\n",m);
  printf("Enter the search word:\n");
  String x = (String)malloc(sizeof(char)*WORD_LENGTH);
  scanf("%s", x);
  ArrayList a = get(h,x);
  display(a);

  return 0;
}
