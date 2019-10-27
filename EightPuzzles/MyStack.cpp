#include "MyStack.h"
#include <malloc.h>
#include <stdio.h>

void createStack(Stack* s, int n)
{
	s->capactiy = n;
	s->elem = (EightPullze*)malloc(s->capactiy * sizeof(EightPullze));
	s->front = -1;
}
void push(Stack* s, EightPullze e)
{
	if (s->front + 2 >= s->capactiy)
	{
		printf("Õ»Âú");
		return;
	}
	s->elem[++s->front] = e;
}
EightPullze pop(Stack* s)
{
	if (s->front < 0)
	{
		printf("Õ»¿Õ");
	}
	return s->elem[s->front--];
}
int find(Stack* s, EightPullze *e)
{
	int i = 0;
	for (; i <= s->front; i++)
	{
		int error = 0;
		for (int j = 0; j < 9; j++)
		{
			if (s->elem->data[j] != e->data[j])
				error++;
		}
		if (error == 0)
			return i;
	}
	if (i == s->front)
		return -1;
}