#ifndef MYLIST_H
#define MYLIST_H
#include "DataStruct.h"


#define _elem EightPullze*

typedef struct node
{
	_elem data;
	struct node* successor;
}Node;

typedef struct
{
	Node* head;
	long size;
	Node* rare;	//尾节点指针
}List;



void createList(List* l);
void push_back(List* l, _elem e);
void push_front(List* l, _elem e);
void pop_back(List* l);
void replace(List* l, int idx, _elem e);
_elem back(List* l);
_elem getValue(List* l, int idx);
void insert(List* l, int idx, _elem e);
void sort(List* l);
void erase(List* l, int idx);
void remove(List* l, _elem e);
int find(List* l, _elem e);
int empty(List* l);


//===================================================//
int findMinfValue(List* l);	//查找最小f值

#endif // !MYLIST_H

