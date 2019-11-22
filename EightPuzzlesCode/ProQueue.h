#ifndef PROQUEUE
#define PROQUEUE
#include "DataStruct.h"
#include <malloc.h>

#define _elem EightPullze*
#define DEFAULT_SIZE 10 

typedef struct {
	_elem *pq;
	int size;
	int capacity;
}MinPQ;

void createMinPQ(MinPQ* mp, int capacity);
int isEmpty(MinPQ* mp);

void insertPQ(MinPQ* mp, _elem e);
_elem delMin(MinPQ* mp);
int larger(MinPQ* mp, int i, int j);
void exch(MinPQ* mp, int i, int j);
void swim(MinPQ* mp, int k);
void sink(MinPQ* mp, int k);



#endif // !PROQUEUE
