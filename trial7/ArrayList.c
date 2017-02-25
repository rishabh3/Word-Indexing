#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"


ArrayList newArrayList() {

	ArrayList this;

	if( (this = (ArrayList) malloc(sizeof(struct arraylist)))
		!= NULL) {

		this->listSize = 0;
		if((this->index = (int*) calloc (INITIAL_ARRAYLIST_SIZE, sizeof(int))) != NULL) {
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
		int* newArray = (int*) realloc(this->index, newSize * sizeof(int));
		if(newArray == NULL) { return NULL; }
		this->index = newArray;
		this->size = newSize;
	}

	return this;
}


int append(ArrayList list, int m) {

	ArrayList this = expand(list);

	if(this == NULL || this->index == NULL) {
		return 0;
	}
	this->index[this->listSize] = m;
	this->listSize++;
	return 1;
}


void clear(ArrayList list) {

	if(list && list->index) {
		int i;

		for(i = 0; i < list->listSize; i++) {
			list->index[i] = 0;
		}
		list->listSize = 0;
	}
}


void freeArrayList(ArrayList list) {

	clear(list);
	free(list->index);
	list->index = NULL;
	free(list);

}

void display(ArrayList list) {
	int i;
	if(list == NULL){
		printf("There is no index where the word occur.\n");
		return ;
	}
	for(i = 0; i < list->listSize; i++) {
		printf("%d,", list->index[i]);
	}
  printf("\b\n");
}
