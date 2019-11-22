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
	//resize(mp);
	mp->pq[++mp->size] = e;
	swim(mp, mp->size);
}
_elem delMin(MinPQ* mp)
{
	_elem v = mp->pq[1];
	mp->pq[1] = mp->pq[mp->size--];
	sink(mp, 1);
	//resize(mp);
	return v;
}
void delElem(MinPQ* mp, int k)
{
	mp->pq[k] = mp->pq[mp->size--];
	sink(mp, k);
	//resize(mp);
}
int larger(MinPQ* mp, int i, int j)
{
	return mp->pq[i]->fValue > mp->pq[j]->fValue;
	//return mp->pq[i] > mp->pq[j];
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

int find(MinPQ* mp, _elem e)
{
	for (int i = 1; i <= mp->size; i++)
		if (mp->pq[i]->code == e->code)
			return i;
	return -1;
}
void resize(MinPQ* mp)
{
	if (mp->size >= mp->capacity)
	{
		mp->capacity = mp->capacity << 1;
		_elem* tmp = (_elem*)malloc(mp->capacity * sizeof(_elem));
		for (int i = 1; i <= mp->size; i++)
			tmp[i] = mp->pq[i];
		free(mp->pq);
		mp->pq = tmp;
	}
	else if (mp->size < (mp->capacity >> 1))
	{
		mp->capacity = mp->capacity >> 1;
		_elem* tmp = (_elem*)malloc(mp->capacity * sizeof(_elem));
		for (int i = 1; i <= mp->size; i++)
			tmp[i] = mp->pq[i];
		free(mp->pq);
		mp->pq = tmp;
	}
}