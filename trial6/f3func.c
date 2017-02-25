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
      if(s[i] == '.' || s[i] == ';' || s[i] == '?' || s[i] == '!'){
	       sentence_num++;
      }
    }
    }
    if(isalnum((int)s[i]) || s[i] == '\''){
      buffer[k++] = s[i];
    }
  }
  return count;
  // int  count = 0;
  // int sentence_num = 1;
  // String del = " \n\t";
  // String x = strtok(s,del);
  // while(x){
  //   count++;
  //   if(strchr(x,'.') || strchr(x,'?') || strchr(x,'!') || strchr(x,';')){
  //     sentence_num++;
  //   }
  //   put(h,x,count,sentence_num);
  //   x = strtok(NULL,del);
  // }
  // return count;
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
  int sentence_count = 0;
  String x = strtok(s,".!?;");
  while(x){
   //printf("%s\n",x);
   appendHashList(h,x);
   x = strtok(NULL,"?!.;");
   //printf("%d\n",sentence_count);
   sentence_count++;
  }
  return sentence_count;
}
void display_search(HashMap * h,HashList * t, String k){
  ArrayList x = get(h,k);
  String str;
  //str = (String )malloc(sizeof(char)*MAX_SENTENCE_SIZE);
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
void display_search_phrase(HashMap * hm,HashList * h, String t){
  String buffer = (String)malloc(sizeof(char)*WORD_LENGTH);
  int k = 0;
  while(t[k] != ' '){
    buffer[k] = t[k];
    k++;
  }
  int found = 0;
  buffer[k] = '\0';
  String str;
  ArrayList y;
  y = get(hm,buffer);
  if(y != NULL){
    for(int i = 0;i < y->listSize;i++){
      str = searchCode(h,y->sent_index[i].sent_no);
      if(strstr(str,t)){
        found++;
        printf("The phrase \"%s\" occurs in \"%s\".\n\n",t,str);
      }
    }
    if(found == 0){
      printf("No occurences were found!\n");
      return ;
    }
    return ;
  }
  printf("No occurences were found!\n");
  return ;
  // String m = (String)malloc(sizeof(char)*strlen(t));
  // strncpy(m,t,strlen(t));
  // m[strlen(t)] = '\0';
  // String x = strtok(t , " ");
  // String str;
  // ArrayList y ;
  // int found = 0;
  // if(x!=NULL){
	// y = get(hm,x);
	// if(y){
	// 	found = 1;
	// }
  // }
  // if(found){
  // 	for(int i = 0;i < y->listSize;i++){
	// 	str = searchCode(h,y->sent_index[i].sent_no);
	// 	while(x){
	// 		if(found){
	// 			x = strtok(NULL, " ");
	// 		}
	// 		if(x){
	// 			if(strstr(str,x)){
	// 				found = 1;
	// 			}
	// 			else{
	// 				found = 0;
	// 				break;
	// 			}
	// 		}
	// 		else{
	// 			if(found){
	// 				printf("The phrase \"%s\" occurs in \"%s\".\n",m,str);
	// 				return ;
	// 			}
	// 		}
	// 	}
  // 	}
	// //return ;
  // }
  // printf("No occurences were found!");
  // return ;
}
void displayH(HashMap * hm){
	for(int i = 0;i < hm->capacity;i++){
		if(hm->hmnode_arr[i].key != NULL){
			printf("%s\n",hm->hmnode_arr[i].key);
			display(hm->hmnode_arr[i].indexlist);
			printf("\n");
		}
	}
}
