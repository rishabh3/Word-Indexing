#include "Util.h"

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
#define INITIAL_ARRAYLIST_SIZE 8
struct sent{
	int index;
	int sent_no;
};
struct arraylist {
	struct sent* sent_index;
	int listSize;
	int size;
};
typedef struct arraylist* ArrayList;

ArrayList newArrayList();
int append(ArrayList, int,int );
void clear(ArrayList);
void freeArrayList(ArrayList);
void display(ArrayList);
#endif
