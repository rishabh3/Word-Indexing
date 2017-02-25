#include "f3.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>
#include "Util.h"
void clearBuffer(String);
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
      put(h,buffer,count);
      clearBuffer(buffer);
      k = 0;
    }
    }
    if(isalnum((int)s[i]) || s[i] == '\''){
      buffer[k++] = s[i];
    }
  }
  return count;
}
