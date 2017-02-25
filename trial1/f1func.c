#include "f1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String.h"
void clearBuffer(char *);
int contains(char *, WordList*);
int contains(char * buffer, WordList * wordlist){
  int true = 0;
  for(int i = 0;i < wordlist->listSize;i++){
    if(strlen(buffer) == wordlist->string[i].len){
      if(!strcmp(buffer,wordlist->string[i].str)){
        true = 1;
      }
      else{
        continue;
      }
    }
  }
  return true;
}
Book* makeBook(){
  Book * book = (Book *)malloc(sizeof(Book));
  if(book == NULL){
    return NULL;
  }
  book->size = 0;
  return book;
}
WordList* makeWordList(){
  WordList * wordlist = (WordList *)malloc(sizeof(WordList));
  if(wordlist == NULL){
    return NULL;
  }
  wordlist->listSize = 0;
  return wordlist;
}
void clearBuffer(char * buffer){
  memset(buffer , 0 , strlen(buffer));
}
int readPara(Book *book,FILE *fp){
  char * buffer = (char *)malloc(sizeof(char)*MAX);
  //char * pBuff = buffer;
  if(fp == NULL || book == NULL){
    return -1;
  }
  int c;
  int i = 0;
  int j = 0;
  while((c = getc(fp)) != EOF){
    buffer[j] = (char)c;
    j++;
    if(c == (int)'.'){
      i++;

    }
    if( i == MAXLINES ){
      i = 0;
      book->p[book->size] = (char *)malloc(sizeof(char)*strlen(buffer));
      strcpy(book->p[book->size],buffer);
      book->size++;
      clearBuffer(buffer);
      j=0;
    }
  }
  book->p[book->size] = (char *)malloc(sizeof(char)*strlen(buffer));
  strcpy(book->p[book->size],buffer);
  book->size++;
  return book->size;
}
int getUniqueWord(char * x, WordList * wordlist){
  char * buffer = (char *)malloc(sizeof(char)*LENGTH);
  if(buffer == NULL){
    return 0;
  }
  char c = *x;
  int j = 0,k = 0;
  while(c != '\0'){
    while(c){
      if(c == ' ' || c == '\n' || c == '.'){
        k++;
        c = *(x+k);
        break;
      }
      buffer[j] = c;
      j++;
      k++;
      c = *(x+k);

    }
    if(!strcmp(buffer,"")){
      continue;
    }
    else if( !contains(buffer,wordlist) ){
      if(wordlist->listSize == MAX){
        return -1;
      }
      wordlist->string[wordlist->listSize].str = (char *)malloc(sizeof(char)*strlen(buffer));
      strcpy(wordlist->string[wordlist->listSize].str, buffer);
      wordlist->string[wordlist->listSize].len = strlen(buffer);
      wordlist->listSize++;
      j = 0;
      clearBuffer(buffer);
    }
    else{
      clearBuffer(buffer);
      j = 0;
    }
  }
  return wordlist->listSize;
}
