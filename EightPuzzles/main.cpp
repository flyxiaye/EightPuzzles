#include <iostream>
#include <Windows.h>
#include "MyList.h"


using std::cout;
using std::endl;

#define SEARCH_DEPTH 25

void AA(void)
{
	//start
	//�����ʼ״̬
	EightPullze Begin =
	{
		//{ 1, 5, 6, 2, 7, 4, 0, 3, 8 },//22
		//{ 8, 7, 3, 1, 6, 0, 5, 4, 2 },//21
		//{ 7, 2, 3, 8, 1, 6, 0, 5, 4 },//18
		//{ 7, 2, 3, 8, 1, 0, 6, 5, 4 },//13��
		//{4, 2, 5, 7, 0, 1, 3, 8, 6},
		{0 ,1, 2, 3, 4, 5, 6, 7, 8},
		0, 0, NULL
	};
	Begin.fValue = Begin.depth + notEquals(&Begin, &Target);
	EightPullze* ei = NULL;
	List Open, Close, * po, * pc;
	po = &Open;
	pc = &Close;
	createList(po);
	createList(pc);
	push_back(po, &Begin);
	while (!empty(po))
	{
		int idx = findMinfValue(po);
		ei = getValue(po, idx);
		erase(po, idx);
		push_front(pc, ei);
		if (!notEquals(ei, &Target))  //ƥ��ɹ�
		{
			break;
		}
		if (ei->depth > SEARCH_DEPTH)
		{
			printf("�����������%d\n", SEARCH_DEPTH);
			break;
		}
		//��չ�ڵ�
		int blankIdx = 0;
		for (; blankIdx < NUM; blankIdx++)
		{
			if (ei->data[blankIdx] == 0)
				break;
		}
		if ((blankIdx % 3) != 0)	//�ո������Ե
		{
			EightPullze* left = createEightPullze(ei);
			if (left)
			{
				blankLeft(left, blankIdx);
				left->fValue = getfValue(left);
				int poIdx = find(po, left);
				int pcIdx = find(pc, left);
				if (-1 == poIdx && -1 == pcIdx)	//����open��close��
					push_back(po, left);
				else if (-1 == poIdx)	//����open�� 
				{
					EightPullze* oldLeft = getValue(pc, pcIdx);
					if (left->fValue <= oldLeft->fValue)
					{
						erase(pc, pcIdx);
						oldLeft->depth = left->depth;
						oldLeft->fValue = left->fValue;
						oldLeft->father = left->father;
						free(left);
						push_back(po, oldLeft);
					}
					else free(left);
				}
				else				//����close��
				{
					EightPullze* oldLeft = getValue(po, poIdx);
					if (left->fValue <= oldLeft->fValue)
					{
						oldLeft->depth = left->depth;
						oldLeft->fValue = left->fValue;
						oldLeft->father = left->father;
						free(left);
					}
					else free(left);
				}
			}
		}
		if (((blankIdx + 1) % 3) != 0) //�ո����ұ�Ե
		{
			EightPullze* right = createEightPullze(ei);
			if (right)
			{
				blankRight(right, blankIdx);
				right->fValue = getfValue(right);
				int poIdx = find(po, right);
				int pcIdx = find(pc, right);
				if (-1 == poIdx && -1 == pcIdx)	//����open��close��
					push_back(po, right);
				else if (-1 == poIdx)	//����open�� 
				{
					EightPullze* oldRight = getValue(pc, pcIdx);
					if (right->fValue <= oldRight->fValue)
					{
						erase(pc, pcIdx);
						oldRight->depth = right->depth;
						oldRight->fValue = right->fValue;
						oldRight->father = right->father;
						free(right);
						push_back(po, oldRight);
					}
					else free(right);
				}
				else				//����close��
				{
					EightPullze* oldRight = getValue(po, poIdx);
					if (right->fValue <= oldRight->fValue)
					{
						oldRight->depth = right->depth;
						oldRight->fValue = right->fValue;
						oldRight->father = right->father;
						free(right);
					}
					else free(right);
				}
			}
		}
		if (blankIdx > 2)		//�ո����ϱ�Ե
		{
			EightPullze* up = createEightPullze(ei);
			if (up)
			{
				blankUp(up, blankIdx);
				up->fValue = getfValue(up);
				int poIdx = find(po, up);
				int pcIdx = find(pc, up);
				if (-1 == poIdx && -1 == pcIdx)	//����open��close��
					push_back(po, up);
				else if (-1 == poIdx)	//����open�� 
				{
					EightPullze* oldUp = getValue(pc, pcIdx);
					if (up->fValue <= oldUp->fValue)
					{
						erase(pc, pcIdx);
						oldUp->depth = up->depth;
						oldUp->fValue = up->fValue;
						oldUp->father = up->father;
						free(up);
						push_back(po, oldUp);
					}
					else free(up);
				}
				else				//����close��
				{
					EightPullze* oldUp = getValue(po, poIdx);
					if (up->fValue <= oldUp->fValue)
					{
						oldUp->depth = up->depth;
						oldUp->fValue = up->fValue;
						oldUp->father = up->father;
						free(up);
					}
					else free(up);
				}
			}
		}
		if (blankIdx < 6)		//�ո����±�Ե
		{
			EightPullze* down = createEightPullze(ei);
			if (down)
			{
				blankDown(down, blankIdx);
				down->fValue = getfValue(down);
				int poIdx = find(po, down);
				int pcIdx = find(pc, down);
				if (-1 == poIdx && -1 == pcIdx)	//����open��close��
					push_back(po, down);
				else if (-1 == poIdx)	//����open�� 
				{
					EightPullze* oldDown = getValue(pc, pcIdx);
					if (down->fValue <= oldDown->fValue)
					{
						erase(pc, pcIdx);
						oldDown->depth = down->depth;
						oldDown->fValue = down->fValue;
						oldDown->father = down->father;
						free(down);
						push_back(po, oldDown);
					}
					else free(down);
				}
				else				//����close��
				{
					EightPullze* oldDown = getValue(po, poIdx);
					if (down->fValue <= oldDown->fValue)
					{
						oldDown->depth = down->depth;
						oldDown->fValue = down->fValue;
						oldDown->father = down->father;
						free(down);
					}
					else free(down);
				}
			}
		}
	}
	int count = -1;
	while (ei)
	{
		PrintEightPullze(ei);
		ei = ei->father;
		printf("\n");
		count++;
	}
	printf("�ո��ƶ�������%d\n", count);
	cout << "size of open: " << po->size << endl;
	cout << "size of close: " << pc->size << endl;
}
int main(void)
{
	//��ʱ��������
	LARGE_INTEGER f;
	double dFreq;
	LARGE_INTEGER start, end;

	QueryPerformanceFrequency(&f);//��ȡ�ڲ��߾��ȼ�������Ƶ��
	dFreq = (double)f.QuadPart; //��ȡ��������Ƶ��
	QueryPerformanceCounter(&start);//��ȡ�ڲ��߾��ȼ�������ǰ�ļ���ֵ
	//��Ҫ��ʱ�Ĵ���д����
	AA();
	QueryPerformanceCounter(&end);

	double duration = (double)(end.QuadPart - start.QuadPart) / dFreq;//����ʱ��
	cout << "��ʱ��" << duration << endl;
}


