#include "ProQueue.h"

void createMinPQ(MinPQ* mp, int capacity)
{
	mp->capacity = capacity + 1;
	mp->size = 0;
	mp->pq = (_elem*)malloc((mp->capacity) * sizeof(_elem));
}

int isEmpty(MinPQ* mp)
{
	return mp->size == 0;
}
void insertPQ(MinPQ* mp, _elem e)
{
	mp->pq[++mp->size] = e;
	swim(mp, mp->size);
}
_elem delMin(MinPQ* mp)
{
	_elem v = mp->pq[1];
	mp->pq[1] = mp->pq[mp->size--];
	sink(mp, 1);
	return v;
}
int larger(MinPQ* mp, int i, int j)
{
	return mp->pq[i]->fValue > mp->pq[j]->fValue;
}
void exch(MinPQ* mp, int i, int j)
{
	_elem tmp = mp->pq[i];
	mp->pq[i] = mp->pq[j];
	mp->pq[j] = tmp;
}
void swim(MinPQ* mp, int k)
{
	while (k != 1)
	{
		int j = k / 2;
		if (!larger(mp, j, k)) return;
		exch(mp, j, k);
		k = j;
	}
}
void sink(MinPQ* mp, int k)
{
	int j; 
	while ((j = k * 2) <= mp->size)
	{
		if (j < mp->size && larger(mp, j, j + 1)) j++;
		if (!larger(mp, k, j)) return;
		exch(mp, k, j);
		k = j;
	}
}