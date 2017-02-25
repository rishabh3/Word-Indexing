#include "f2.h"
#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void clearBuffer(char *);
int partition(WordList *, int ,int);
int contains(WordList* ,char *);
void clearBuffer(char * buffer){
  memset(buffer , 0 , strlen(buffer));
}
void swap(Word *a,Word *b){
  Word temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
int partition(WordList* w,int low,int high){
  Word p = w->word[high];
  int i = low - 1;
  for(int j = low;j <= high - 1;j++){
    if(strcmp(w->word[j].string,p.string) <= 0){
      i++;
      swap(&w->word[i],&w->word[j]);
    }
  }
  swap(&w->word[i+1],&w->word[high]);
  return i+1;
}
void qSort(WordList* w, int low, int high){
  if(low < high){
    int pi = partition(w, low, high);
    qSort(w, low, pi - 1);
    qSort(w, pi + 1, high);
  }
}
ArrayList* bSearch(WordList* w,char * p,int low,int high,int * a){
  int mid = (low+high)/2;
  if(a == NULL){
    a = (int *)malloc(sizeof(int));
  }
  if(low > high || w->word[mid].string == NULL){
    *a = -1;
    return NULL;
  }
  if(strncmp(p , w->word[mid].string,strlen(p)) < 0){
    return bSearch(w, p, low, mid - 1, a);
  }
  else if(strncmp(p , w->word[mid].string,strlen(p)) > 0){
    return bSearch(w, p, mid + 1,high, a);
  }
  *a = mid;
  return w->word[mid].aList;
}
int contains(WordList * w, char * p){
  //int * x = (int *)malloc(sizeof(int));
  //qSort(w,0,w->listSize-1);
  //bSearch(w,p,0,w->listSize,x);
   for(int i = 0; i < w->listSize;i++){
  	if(strncmp(w->word[i].string,p,strlen(p)) == 0){
     		return i;
   	}
   }
   return -1;
  //   temp = bSearch(w,p,0,w->listSize,x);
  // }
 //return *x;
}
//int contains(char* , char);
//int contains(char * s, char c){
  // int true = 0;
  // for(int i = 0;i < strlen(s);i++){
  //   if(c == s[i]){
  //     true = 1;
  //   }
  // }
  // return true;
// }
ArrayList* makeArrayList(){
  ArrayList * list = (ArrayList *)malloc(sizeof(ArrayList));
  if(list == NULL){
    return NULL;
  }
  list->size = 0;
  return list;
}
WordList* makeWordList(){
  WordList* wordlist = (WordList*)malloc(sizeof(WordList));
  wordlist->word = (Word *)malloc(sizeof(Word)*MAX);
  if(wordlist == NULL || wordlist->word == NULL){
    return NULL;
  }
  wordlist->listSize = 0;
  return wordlist;
}

String* makeString(){
  String * string = (String *)malloc(sizeof(String));
  if(string == NULL){
    return NULL;
  }
  return string;
}

int readFile(FILE * fp,String * s){
  if(fp == NULL){
    return -1;
  }
  if(s == NULL){
    s = makeString();
  }
  fseek(fp, 0, SEEK_END);
  long int size = ftell(fp);
  fseek(fp, 0,SEEK_SET);
  char * buffer = (char *)malloc(sizeof(char)*size);
  fread(buffer, size, 1, fp);
  s->str = (char *)malloc(sizeof(char)*strlen(buffer));
  strcpy(s->str, buffer);
  s->len = strlen(s->str);
  free(buffer);
  buffer = NULL;
  fclose(fp);
  return s->len;
}

int getWordList(String * s,WordList * w){
  if(s == NULL){
    return -1;
  }
  int k = 0;
  int wordind = 0;
  int count = 0;
  //char a[25] = {'.',' ','(',')','[',']','{','}','?','/','-','>','<',',','*','%','$','#','@','\n','!'};
  char * buffer = (char *)malloc(sizeof(char)*LENGTH);
  clearBuffer(buffer);
  int temp = 0;
  for(int i = 0;i < s->len;i++){
    if((isspace((int)s->str[i]) || ispunct((int)s->str[i]) || s->str[i] == '\n' || s->str[i] == '\0') && (s->str[i] != '\'')){
      if(strcmp(buffer,"")){
      buffer[k] = '\0';
      k++;
      if((temp = contains(w,buffer)) == -1){
        w->word[wordind].string = (char *)malloc(sizeof(char)*strlen(buffer));
        strcpy(w->word[wordind].string,buffer);
        w->word[wordind].aList = makeArrayList();
        count++;
        w->word[wordind].aList->wordIndex[w->word[wordind].aList->size++] = count;
        wordind++;
        w->listSize++;
      }
      else{
        w->word[temp].aList->wordIndex[w->word[temp].aList->size++] = ++count;
      }
      clearBuffer(buffer);
      k = 0;
    }
    }
    if(isalnum((int)s->str[i]) || s->str[i] == '\''){
      buffer[k++] = s->str[i];
    }
  }
  return w->listSize;
}

void display(ArrayList * a){
  int i;
  for(i = 0;i < a->size-1;i++){
    printf("%d,",a->wordIndex[i]);
  }
  printf("%d.\n",a->wordIndex[a->size-1]);
}
