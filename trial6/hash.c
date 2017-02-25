#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

String searchCode(HashList * h, int x){
    return h->hashList[x - 1].sentence;
}

HashList* newHashList() {

	HashList* this;

	if( (this = (HashList *) malloc(sizeof(HashList))) != NULL) {

		this->size = 0;
		if((this->hashList = (Hash*) calloc (INITIAL_HASHLIST_SIZE, sizeof(Hash))) != NULL) {
			this->initial_size = INITIAL_HASHLIST_SIZE;
		} else {
			free(this);
			this = NULL;
		}
	}

	return this;
}


HashList* expandHashList(HashList* list) {

	HashList* this = list;

	if(this && this->size == this->initial_size) {  // realloc

		int newSize = 2 * (this->initial_size);
		Hash* newArray = (Hash*) realloc(this->hashList, newSize * sizeof(Hash));
		if(newArray == NULL) { return NULL; }
		this->hashList = newArray;
		this->initial_size = newSize;
	}

	return this;
}


int appendHashList(HashList* list, String s) {

	HashList* this = expandHashList(list);

	if(this == NULL || this->hashList == NULL) {
		return 0;
	}
	//this->hashList[this->size].sent_num = m;
	this->hashList[this->size].sentence = (String )malloc(sizeof(char)*strlen(s));
  if(this->hashList[this->size].sentence != NULL){
    strncpy(this->hashList[this->size].sentence,s,strlen(s));
  }
  else{
    return 0;
  }
	this->size++;
	return 1;
}


void clearHashList(HashList * list) {

	if(list && list->hashList) {
		int i;

		for(i = 0; i < list->size; i++) {
			//list->hashList[i].sent_num = 0;
			list->hashList[i].sentence = NULL;
		}
		list->size = 0;
	}
}


void freeHashList(HashList* list) {

	clearHashList(list);
	free(list->hashList);
	list->hashList = NULL;
	free(list);

}

void displayHashList(HashList* list) {
	int i;
	if(list == NULL){
		printf("There is no sentence and the sentence number where the word occur.\n");
		return ;
	}
	for(i = 0; i < list->size; i++) {
		printf("%s", list->hashList[i].sentence);
	}
  printf("\b\n");
}
