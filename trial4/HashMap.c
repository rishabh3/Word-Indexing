#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"HashMap.h"
HashMap * newHashMap(double ldfactor){
  if(ldfactor <= 0.0 || ldfactor >= 1.0){
    return NULL;
  }
  HashMap * this;
  if((this = (HashMap *)malloc(sizeof(HashMap)))){
    if((this->hmnode_arr = calloc(HASHMAP_SIZE_INITIAL,sizeof(HMNode)))){
      this->capacity = HASHMAP_SIZE_INITIAL;
      this->size = 0;
      this->load_factor = ldfactor;
      return this;
    }
    freeHashMap(this);
  }
  return NULL;
}
int hm_hash(String s, int capacity){
	unsigned int c, h = 5381;
	while ((c = *s++)) {
	    h = ((h << 5) + h) ^ c; /* h(i) = hash(i - 1) * 33 ^ c */
	}
	return h & (capacity - 1);
}
int search(HashMap * hm,String s){
  if(hm && hm->hmnode_arr){
		int index = hm_hash(s, hm->capacity);
		int i = 0;
		int pos = ((int)(index + 0.5 * i + 0.5 * i * i)) % hm->capacity;

		while((hm->hmnode_arr[pos].key)) {
			if(strcmp(s, hm->hmnode_arr[pos].key) == 0) {
				 return pos;
			}

			i++;
			pos = ((int)(index + 0.5 * i + 0.5 * i * i)) % hm->capacity;
		}
	}
	return -1;
}
int put(HashMap * hm,String k,int i,int j){
  if(hm == NULL || hm->hmnode_arr == NULL || k == NULL ){
    return 0;
 }
  int t = search(hm,k);
  if(t == -1){
	   HMNode* node;
	   if((node = newHMNode(k, i,j)) == NULL) {
		     return 0;
	      }

	   if((float) hm->size / (float) hm->capacity > hm->load_factor) {
		     HashMap * temp = hm_resizeRehash(hm);
		     if(!temp) { return 0; }
		         hm = temp;
	       }
         hm = hm_addHelper(hm, node, hm->capacity);
         hm->size++;
  }
  else{
    append(hm->hmnode_arr[t].indexlist,i,j);
  }
	return 1;
}
ArrayList get(HashMap * hm, String s) {

	if(hm && hm->hmnode_arr) {

		int index = hm_hash(s, hm->capacity);
		int i = 0;
		int pos = ((int)(index + 0.5 * i + 0.5 * i * i)) % hm->capacity;

		while(hm->hmnode_arr[pos].key && pos < hm->capacity) {
      if(hm->hmnode_arr[pos].key != NULL){
			     if(strcmp(s, hm->hmnode_arr[pos].key) == 0) {
				         return hm->hmnode_arr[pos].indexlist;
			    }
      }
			i++;
			pos = ((int)(index + 0.5 * i + 0.5 * i * i)) % hm->capacity;
		}
	}

	return NULL;
}
HashMap * hm_addHelper(HashMap * h, HMNode * node, int capacity) {

    int index = hm_hash(node->key, capacity);
    int i = 0;
    int pos = ((int)(index + 0.5 * i + 0.5 * i * i)) % capacity;

    while(h->hmnode_arr[pos].key) {
        i++;
        pos = ((int)(index + 0.5 * i + 0.5 * i * i)) % capacity;
    }

    h->hmnode_arr[pos] = *node;
    return h;
}
HashMap * hm_resizeRehash(HashMap * hm) {

	if(hm && hm->hmnode_arr) {

		HMNode * temp_array;
    int newSize = hm->capacity*2*sizeof(HMNode);
    temp_array = (HMNode *)realloc(hm->hmnode_arr , newSize);
    if (temp_array == NULL){
      return NULL;
    }
    hm->hmnode_arr = temp_array;
    hm->capacity *= 2;
			return hm;
		}

	return NULL;
}

void freeHashMap(HashMap * hm) {
	if(hm) {
		if(hm->hmnode_arr) {
			int i;
			for(i = 0; i < hm->capacity; i++) {
				if(hm->hmnode_arr[i].key ) {
					free(&hm->hmnode_arr[i]);
				}
			}
			free(hm->hmnode_arr);
		}
		free(hm);
		hm = NULL;
	}
}
