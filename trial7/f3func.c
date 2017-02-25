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
  int j = 0;
  //int count = 0;
  //int offset = 0;
  int word_count = 0;
  char * buffer = (char *)malloc(sizeof(char)*WORD_LENGTH);
  clearBuffer(buffer);
  for(int i = 0;i < strlen(s);i++){
    if((isspace((int)s[i]) || s[i] == '\n' || s[i] == '\0') && (s[i] != '\'')){
        if(strcmp(buffer,"")){
          buffer[k] = '\0';
          k++;
          word_count++;
          j = i - 1;
          put(h,buffer,j);
          clearBuffer(buffer);
          k = 0;
        }
    }
    if(isalnum((int)s[i]) || s[i] == '\''){
      buffer[k++] = s[i];
    }

  }
  return word_count;
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
// int getAllSentences(HashList * h,String s){
//   if(s == NULL || h == NULL){
// 	return -1;
//   }
//   int sentence_count = 0;
//   String x = strtok(s,".!?;");
//   while(x){
//    //printf("%s\n",x);
//    appendHashList(h,x);
//    x = strtok(NULL,"?!.;");
//    //printf("%d\n",sentence_count);
//    sentence_count++;
//   }
//   return sentence_count;
// }
void display_search(HashMap * hm, String k,String b){
  ArrayList x = get(hm,k);
  int t;
  String l,h;
  int temp = 0;
  String str =(String )malloc(sizeof(char)*WORD_SIZE);
  clearBuffer(str);
  String buffer = (String)malloc(sizeof(char)*WORD_LENGTH);
  clearBuffer(buffer);
  String a,c;
  if(x == NULL){
    printf("The word never occurs in the book!\n");
    return ;
  }
  printf("The word occurs at following indexes and in the following sentences!\n");
  for(int i = 0 ; i < x->listSize;i++){
    t = x->index[i];
    l = (b+t-OFFSET);
    h = (b+t+OFFSET);
    if(l < b){
       l = b;
     }
     if(h > b + strlen(b)){
       h = (b + strlen(b));
     }
    strncpy(str,l,h - l);
    str[strlen(str)] = '\0';
      if(l == b){
        clearBuffer(buffer);
        int i = 0;
        while(temp < MAX_SPACE){
          if(str[i] == ' '){
            temp++;
          }
          buffer[i] = str[i];
            i++;
          }
          buffer[i] = '\0';
      }
      else if(h == b+strlen(b)){
        clearBuffer(buffer);
        c = strchr(str, ' ');
        a = strrchr(str, '\0');
        strncpy(buffer,c,a - c);
        buffer[strlen(buffer)] = '\0';
      }
      else{
        clearBuffer(buffer);
        a = strchr(str,' ');
        c = strrchr(str, ' ');
        strncpy(buffer,a,c - a);
        buffer[strlen(buffer)] = '\0';
      }
    // if(l == b){
    //   clearBuffer(buffer);
    //   int i = 0;
    //   while(temp < 3){
    //     if(str[i] == ' '){
    //       temp++;
    //     }
    //     buffer[i] = str[i];
    //     i++;
    //   }
    //   buffer[i] = '\0';
    // }
    // if(h == b + strlen(b)){
    //   a = strchr(str,' ');
    //   strncpy(buffer,a,h - a);
    //   buffer[strlen(buffer)] = '\0';
    // }
    printf("%d->....%s.....\n",t,buffer);
  }
  printf("\n");
  // free(buffer);
  // free(str);
  // buffer = NULL;
  // str = NULL;
}
void help(ArrayList x,String b,String pat){
  int t;
  String l,h;
  String str =(String )malloc(sizeof(char)*LENGTH);
  clearBuffer(str);
  if(x == NULL){
	printf("The phrase %s never occurs in the book", pat);
	return ;
  }
  printf("The phrase %s occurs in the following sentences!\n",pat);
  for(int i = 0 ; i < x->listSize;i++){
    t = x->index[i];
    l = (b+t-MAX_OFFSET);
    h = (b+t+MAX_OFFSET);
    if(l < b){
       l = b;
     }
     if(h > b + strlen(b)){
       h = (b + strlen(b));
     }
    strncpy(str,l,h - l);
    //str[strlen(str)] = '\0';
    if(strstr(str,pat)){
	//printf("%s",patx);
	printf(".....%s.....\n",str);
    }
    }
    return;
}
void display_search_phrase(HashMap * hm, String t,String b){
   String buffer = (String)malloc(sizeof(char)*WORD_LENGTH);
   clearBuffer(buffer);
   int i = 0;
   while(t[i] != ' '){
	buffer[i] = t[i];
   	i++;
   }
   ArrayList arr;
   buffer[i] = '\0';
   if(buffer){
	arr = get(hm,buffer);
 	  help(arr,b,t);
   }
   return ;
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
