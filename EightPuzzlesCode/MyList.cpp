#include <stdio.h>
#include "MyList.h"
#include <malloc.h>

void createList(List* l)
{
	l->head = (Node*)malloc(sizeof(Node));
	l->head->successor = NULL;
	l->size = 0;
	l->rare = l->head;
}
void push_back(List* l, _elem e)
{
	Node* p = l->rare;
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = e;
	n->successor = NULL;
	p->successor = n;
	l->rare = n;
	l->size++;
}
void push_front(List* l, _elem e)
{
	Node* p = l->head;
	Node* n = (Node*)malloc(sizeof(Node));
	n->data = e;
	n->successor = p->successor;
	p->successor = n;
	l->size++;
}
void pop_back(List* l)
{
	Node* p = l->head;
	while (p->successor->successor)p = p->successor;
	Node* n = p->successor;
	l->rare = p;
	p->successor = NULL;
	free(n);
	l->size--;
}
void replace(List* l, int idx, _elem e)
{
	Node* p = l->head->successor;
	for (int i = 0; i < idx; i++)p = p->successor;
	p->data = e;
}
_elem back(List* l)
{
	Node* p = l->head;
	while (p->successor)p = p->successor;
	return p->data;
}
_elem getValue(List* l, int idx)
{
	Node* p = l->head->successor;
	for (int i = 0; i < idx; i++)p = p->successor;
	return p->data;
}
void insert(List* l, int idx, _elem e)
{
	Node* p = l->head;
	for (int i = 0; i < idx; i++)p = p->successor;
	Node* n = (Node*)malloc(sizeof(Node));
	n->successor = p->successor;
	p->successor = n;
	n->data = e;
	l->size++;
}
void sort(List* l);
void erase(List* l, int idx)
{
	if (idx < 0) return;
	Node* p = l->head;
	for (int i = 0; i < idx; i++)p = p->successor;
	Node* n = p->successor;
	p->successor = n->successor;
	if (p->successor == NULL) l->rare = p;
	free(n);
	l->size--;
}
void remove(List* l, _elem e)
{
	int idx = find(l, e);
	if (-1 == idx) return;
	erase(l, idx);
}
int find(List* l, _elem e)
{
	int idx = 0;
	Node* p = l->head->successor;
	while (p) {
		if (p->data->code == e->code)
			return idx;
		p = p->successor;
		idx++;
	}
	return -1;
}

int empty(List* l)
{
	return !l->size;
}


//===================================================//
int findMinfValue(List* l)	//查找最小f值
{
	int idx = 0;
	int i = 0;
	Node* p = l->head->successor;
	if (p == NULL)
		return -1;
	int minf = p->data->fValue;
	p = p->successor;
	i++;
	while (p) {
		if (p->data->fValue < minf)
			idx = i;
		p = p->successor;
		i++;
	}
	return idx;
}