#include "f3.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include "Util.h"
int realloced_sentence_size = MAX_SENTENCE_SIZE;
void clearBuffer(String);
String addSpace(String);
void clearBuffer(char * buffer){
  memset(buffer , 0 , strlen(buffer));
}
String readFile(FILE * fp,int *  t){
  if(fp == NULL){
    return NULL;
  }
  fseek(fp, 0, SEEK_END);
  long int size = ftell(fp);
  fseek(fp, 0,SEEK_SET);
  String s = (String)malloc(sizeof(char)*size);
  fread(s, size, 1, fp);
  fclose(fp);
  *t = strlen(s);
  return s;
}
int getUniqueWord(HashMap* h,String s){
  if(s == NULL || h == NULL){
      return -1;
  }
  int k = 0;
  int sentence_num = 1;
  int count = 0;
  char * buffer = (char *)malloc(sizeof(char)*WORD_LENGTH);
  clearBuffer(buffer);
  for(int i = 0;i < strlen(s);i++){
    if((isspace((int)s[i]) || ispunct((int)s[i]) || s[i] == '\n' || s[i] == '\0') && (s[i] != '\'')){
      if(strcmp(buffer,"")){
      buffer[k] = '\0';
      k++;
      count++;
      //insert into hashmap
      put(h,buffer,count,sentence_num);
      clearBuffer(buffer);
      k = 0;
      if(ispunct((int)s[i]) && s[i] != ','){
	       sentence_num++;
      }
    }
    }
    if(isalnum((int)s[i]) || s[i] == '\''){
      buffer[k++] = s[i];
    }
  }
  return count;
}
String addSpace(String x){
  if(strlen(x) == MAX_SENTENCE_SIZE){
    int newSize = 2*realloced_sentence_size;
    String temp = (String )realloc(x, newSize*sizeof(char));
    if(temp != NULL){
      realloced_sentence_size = newSize;
      x = temp;
    }
  }
  return x;
}
int getAllSentences(HashList * h,String s){
  if(s == NULL || h == NULL){
    return -1;
  }
  int sentence_num = 0;
  int k = 0;
  char * buffer = (char *)malloc(sizeof(char)*MAX_SENTENCE_SIZE);
  clearBuffer(buffer);
  for(int i = 0;i < strlen(s);i++){
      if(ispunct((int)s[i]) && s[i] != ',' && s[i] != '\''){
        if(strcmp(buffer,"")){
        buffer[k] = '\0';
        k++;
        sentence_num++;
        //insert into hashmap
        appendHashList(h,sentence_num,buffer);
        clearBuffer(buffer);
        k = 0;
      }
    }
    if(isalnum((int)s[i]) || s[i] == '\'' || s[i] == ' '){
      buffer = addSpace(buffer);
      buffer[k++] = s[i];
    }
  }
  return sentence_num;
}
void display_search(HashMap * h,HashList * t, String k){
  ArrayList x = get(h,k);
  String str;
  str = (String )malloc(sizeof(char)*MAX_SENTENCE_SIZE);
  if(x == NULL){
    printf("The word never occurs in the book!\n");
    return ;
  }
  printf("The word occurs at following indexes and in the following sentences!\n");
  for(int i = 0 ; i < x->listSize;i++){
    str  = searchCode(t,x->sent_index[i].sent_no);
    printf("%d->%s\n",x->sent_index[i].index,str);
  }
  printf("\n");
}
