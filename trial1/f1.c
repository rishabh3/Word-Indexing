#include<stdio.h>
#include "f1.h"
#include <stdlib.h>
#include <string.h>
#include"String.h"
int main(){
  FILE *fp = fopen("art2.txt","r");
  Book * book = makeBook();
  WordList* wordlist = makeWordList();
  int res = readPara(book, fp);
  int t = 0;
  printf("%d\n", res);
  for(int i = 0;i < book->size;i++){
    printf("%s\n",book->p[i]);
    t = getUniqueWord(book->p[i], wordlist);
  }
  for(int i = 0;i < wordlist->listSize;i++){
    printf("%s\n",wordlist->string[i].str);
  }
  printf("The total unique words found in the file is :%d",t);
}
