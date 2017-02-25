#include <stdlib.h>
#include <stdio.h>
#include "f2.h"
#include "String.h"
#include <string.h>
int main(){
  FILE* fp = fopen("ip5.txt","r");
  //int * xp = (int *)malloc(sizeof(int));
  String * string = makeString();
  int t = readFile(fp,string);
  printf("%d\n",t);
  printf("%s\t%d\n",string->str,string->len);
  WordList * w = makeWordList();
  int x = getWordList(string,w);
  //qSort(w, 0, w->listSize - 1);
  for(int i = 0;i < w->listSize;i++){
    printf("%s\t\t\t\t",w->word[i].string);
    display(w->word[i].aList);
    printf("\n");
  }
  //qSort(w, 0, w->listSize - 1);
  //ArrayList * m = bSearch(w, "Java", 0, w->listSize-1,xp);
  //if(m != NULL){for(int i = 0;i < m->size;i++){
    //printf("%d,",m->wordIndex[i]);
  //}}
  printf("\nTotal number unique words found:%d",x);
  return 0;
}
