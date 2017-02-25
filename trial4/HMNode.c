#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HMNode.h"


HMNode * newHMNode(String key, int v,int x) {

	HMNode * this;

	if(key == NULL) {
		return NULL;
	}

	if( (this = (HMNode *) malloc(sizeof(HMNode))) != NULL) {

		this->indexlist = newArrayList();
		append(this->indexlist,v,x);
		if((this->key = (String) malloc(strlen(key) * sizeof(char)))) {
			strncpy(this->key, key, strlen(key) + 1);

		} else {
			free(this);
			this = NULL;
		}
	}

	return this;
}


void freeHMNode(HMNode * node) {

	freeArrayList(node->indexlist);
	node->indexlist = NULL;

	free(node->key);
	node->key = NULL;

	free(node);
}
