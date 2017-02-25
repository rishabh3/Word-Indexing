#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"


ArrayList newArrayList() {

	ArrayList this;

	if( (this = (ArrayList) malloc(sizeof(struct arraylist)))
		!= NULL) {

		this->listSize = 0;
		if((this->sent_index = (struct sent*) calloc (INITIAL_ARRAYLIST_SIZE, sizeof(struct sent))) != NULL) {
			this->size = INITIAL_ARRAYLIST_SIZE;
		} else {
			free(this);
			this = NULL;
		}
	}

	return this;
}


ArrayList expand(ArrayList list) {

	ArrayList this = list;

	if(this && this->listSize == this->size) {  // realloc

		int newSize = 2 * (this->size);
		struct sent* newArray = (struct sent*) realloc(this->sent_index, newSize * sizeof(struct sent));
		if(newArray == NULL) { return NULL; }
		this->sent_index = newArray;
		this->size = newSize;
	}

	return this;
}


int append(ArrayList list, int m,int k) {

	ArrayList this = expand(list);

	if(this == NULL || this->sent_index == NULL) {
		return 0;
	}
	this->sent_index[this->listSize].index = m;
	this->sent_index[this->listSize].sent_no = k;
	this->listSize++;
	return 1;
}


void clear(ArrayList list) {

	if(list && list->sent_index) {
		int i;

		for(i = 0; i < list->listSize; i++) {
			list->sent_index[i].index = 0;
			list->sent_index[i].sent_no = 0;
		}
		list->listSize = 0;
	}
}


void freeArrayList(ArrayList list) {

	clear(list);
	free(list->sent_index);
	list->sent_index = NULL;
	free(list);

}

void display(ArrayList list) {
	int i;
	if(list == NULL){
		printf("There is no index where the word occur.\n");
		return ;
	}
	for(i = 0; i < list->listSize; i++) {
		printf("%d,%d", list->sent_index[i].index,list->sent_index[i].sent_no);
	}
  printf("\b\n");
}
