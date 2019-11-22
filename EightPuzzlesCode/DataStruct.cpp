#include "DataStruct.h"
#include <stdio.h>
#include <malloc.h>

EightPullze Target =
{
	{1, 2, 3, 8, 0, 4, 7, 6, 5},
	123804765,
	0, 0, 0
};		//目标状态

//判断两数据是否相等（返回不相等的数）
int notEquals(EightPullze* src, EightPullze* dst)
{
	int error = 0;
	for (int i = 0; i < NUM; i++) {
		if (src->data[i] != dst->data[i])
			error++;
	}
	return error;
}

//计算f值
int getfValue(EightPullze* ei)
{
	return ei->depth + notEquals(ei, &Target);
}
EightPullze* createEightPullze(EightPullze* src)
{
	EightPullze* dst = (EightPullze*)malloc(sizeof(EightPullze));
	if (!dst)return NULL;
	for (int i = 0; i < NUM; i++) {
		dst->data[i] = src->data[i];
	}
	dst->depth = src->depth + 1;
	dst->fValue = 0;//getfValue(dst);
	dst->father = src;
	return dst;
}
//数码操作函数
void blankLeft(EightPullze* ei, int idx)
{
	unsigned char temp = ei->data[idx];
	ei->data[idx] = ei->data[idx - 1];
	ei->data[idx - 1] = temp;
}
void blankRight(EightPullze* ei, int idx)
{
	unsigned char temp = ei->data[idx];
	ei->data[idx] = ei->data[idx + 1];
	ei->data[idx + 1] = temp;
}
void blankUp(EightPullze* ei, int idx)
{
	unsigned char temp = ei->data[idx];
	ei->data[idx] = ei->data[idx - 3];
	ei->data[idx - 3] = temp;
}
void blankDown(EightPullze* ei, int idx)
{
	unsigned char temp = ei->data[idx];
	ei->data[idx] = ei->data[idx + 3];
	ei->data[idx + 3] = temp;
}

void PrintEightPullze(EightPullze* ei)
{
	for (int i = 0; i < 9; i++) {
		if (0 == ei->data[i])
			printf("  ");
		else
			printf("%d ", ei->data[i]);
		if ((i + 1) % 3 == 0)
			printf("\n");
	}
}

void getCode(EightPullze* ei)
{
	int v = 0;
	for (int i = 0; i < NUM; i++)
		v = v * 10 + ei->data[i];
	ei->code = v;
}

void copyNode(EightPullze* src, EightPullze* dst)
{
	dst->depth = src->depth;
	dst->fValue = src->fValue;
	dst->father = src->father;
}