#include <iostream>
#include <list>
#include <algorithm>
#include "DataClass.h"
#include <queue>
#include <Windows.h>

using namespace std;
#define SEARCH_DEPTH 26
void PrintEight(Eight* ei);

void BFS(void)
{
	queue<Eight*> open;
	queue<Eight*> close;
	unsigned char st[] = { 4,2,5,7,0,1,3,8,6 };//{ 4,2,5,7,0,1,3,8,6 };
	Eight* s = new Eight(st);
	Eight* ei = nullptr;
	open.push(s);
	while (!open.empty())
	{
		ei = open.front();
		open.pop();
		if (!ei->notEquals(target))		//ƥ��ɹ�
		{
			break;
		}
		//��չ�ڵ�
		int blankIdx;
		for (blankIdx = 0; blankIdx < 9; blankIdx++)
		{
			if (ei->data[blankIdx] == 0)
				break;
		}

		if ((blankIdx % 3) != 0)	//�ո������Ե
		{
			Eight* left = new Eight(*ei);
			left->father = ei;
			left->blankLeft(blankIdx);
			open.push(left);
		}
		if (((blankIdx + 1) % 3) != 0) //�ո����ұ�Ե
		{
			Eight* right = new Eight(*ei);
			right->father = ei;
			right->blankRight(blankIdx);
			open.push(right);
		}
		if (blankIdx > 2)		//�ո����ϱ�Ե
		{
			Eight* up = new Eight(*ei);
			up->father = ei;
			up->blankUp(blankIdx);
			open.push(up);
		}
		if (blankIdx < 6)		//�ո����±�Ե
		{
			Eight* down = new Eight(*ei);
			down->father = ei;
			down->blankDown(blankIdx);
			open.push(down);
		}
	}
	int step_count = -1;
	while (ei)
	{
		PrintEight(ei);
		std::cout << endl;
		ei = ei->father;
		step_count++;
	}
	std::cout << "ʹ�ò�����" << step_count << endl;
	std::cout << "size of open:" << open.size() << endl;
	std::cout << "size of close:" << close.size() << endl;
}
void A(void)	//A�㷨
{
	list<Eight> open;
	list<Eight> close;
	unsigned char st[] = { 1,2,3,8,4,0,7,6,5 };//{ 4,2,5,7,0,1,3,8,6 };
	Eight s(st);
	Eight ei;
	open.push_back(s);
	while (!open.empty())
	{
		//��fֵ��С�Ľڵ�
		list<Eight>::iterator min_it = open.begin();
		int minf = (*min_it).fvalue;
		for (auto it = open.begin(); it != open.end(); it++)
		{
			if ((*it).fvalue < minf)
				min_it = it;
		}
		ei = (*min_it);
		open.erase(min_it);
		close.push_back(ei);

		if (!ei.notEquals(target))		//ƥ��ɹ�
		{
			break;
		}

		//��չ�ڵ�
		int blankIdx;
		for (blankIdx = 0; blankIdx < 9; blankIdx++)
		{
			if (ei.data[blankIdx] == 0)
				break;
		}

		if ((blankIdx % 3) != 0)	//�ո������Ե
		{
			Eight left(ei);
			left.depth = ei.depth + 1;
			left.father = &ei;
			left.getfvalue();
			left.blankLeft(blankIdx);
			//�����½ڵ�left��open���close�����Ƿ����
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), left);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), left);
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(left);
			}
			else if (ret_open == open.end() && left.fvalue < (*ret_close).fvalue)	//��close��
			{
				(*ret_close).depth = left.depth;
				(*ret_close).fvalue = left.fvalue;
				(*ret_close).father = left.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && left.fvalue < (*ret_open).fvalue)	//��open��
			{
				(*ret_open).depth = left.depth;
				(*ret_open).fvalue = left.fvalue;
				(*ret_open).father = left.father;
			}
		}
		if (((blankIdx + 1) % 3) != 0) //�ո����ұ�Ե
		{
			Eight right(ei);
			right.depth = ei.depth + 1;
			right.father = &ei;
			right.getfvalue();
			right.blankRight(blankIdx);
			//�����½ڵ�right��open���close�����Ƿ����
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), right);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), right);
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(right);
			}
			else if (ret_open == open.end() && right.fvalue < (*ret_close).fvalue)	//��close��
			{
				(*ret_close).depth = right.depth;
				(*ret_close).fvalue = right.fvalue;
				(*ret_close).father = right.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && right.fvalue < (*ret_open).fvalue)	//��open��
			{
				(*ret_open).depth = right.depth;
				(*ret_open).fvalue = right.fvalue;
				(*ret_open).father = right.father;
			}
		}
		if (blankIdx > 2)		//�ո����ϱ�Ե
		{
			Eight up(ei);
			up.depth = ei.depth + 1;
			up.father = &ei;
			up.getfvalue();
			up.blankUp(blankIdx);
			//�����½ڵ�up��open���close�����Ƿ����
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), up);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), up);
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(up);
			}
			else if (ret_open == open.end() && up.fvalue < (*ret_close).fvalue)	//��close��
			{
				(*ret_close).depth = up.depth;
				(*ret_close).fvalue = up.fvalue;
				(*ret_close).father = up.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && up.fvalue < (*ret_open).fvalue)	//��open��
			{
				(*ret_open).depth = up.depth;
				(*ret_open).fvalue = up.fvalue;
				(*ret_open).father = up.father;
			}
		}
		if (blankIdx < 6)		//�ո����±�Ե
		{
			Eight down(ei);
			down.depth = ei.depth + 1;
			down.father = &ei;
			down.getfvalue();
			down.blankDown(blankIdx);
			//�����½ڵ�down��open���close�����Ƿ����
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), down);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), down);
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(down);
			}
			else if (ret_open == open.end() && down.fvalue < (*ret_close).fvalue)	//��close��
			{
				(*ret_close).depth = down.depth;
				(*ret_close).fvalue = down.fvalue;
				(*ret_close).father = down.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && down.fvalue < (*ret_open).fvalue)	//��open��
			{
				(*ret_open).depth = down.depth;
				(*ret_open).fvalue = down.fvalue;
				(*ret_open).father = down.father;
			}
		}

	}
	int step_count = -1;
	Eight* pei = &ei;
	while (pei)
	{
		PrintEight(pei);
		std::cout << endl;
		pei = pei->father;
		step_count++;
	}
	std::cout << "ʹ�ò�����" << step_count << endl;
	std::cout << "size of open:" << open.size() << endl;
	std::cout << "size of close:" << close.size() << endl;
}
void AA(void)
{
	list<Eight*> open;
	list<Eight*> close;
	unsigned char st[] = { 8, 7, 3, 1, 6, 0, 5, 4, 2 };//21
	Eight* s = new Eight(st);
	Eight* ei = nullptr;
	open.push_back(s);
	while (!open.empty())
	{
		//��fֵ��С�Ľڵ�
		list<Eight*>::iterator min_it = open.begin();
		int minf = (*min_it)->fvalue;
		for (auto it = open.begin(); it != open.end(); it++)
		{
			if ((*it)->fvalue < minf)
				min_it = it;
		}
		ei = (*min_it);
		open.erase(min_it);
		close.push_back(ei);

		if (!ei->notEquals(target))		//ƥ��ɹ�
		{
			break;
		}
		if (ei->depth > SEARCH_DEPTH)
		{
			cout << "����������ȣ�" << SEARCH_DEPTH << endl;
			break;
		}

		//��չ�ڵ�
		int blankIdx;
		for (blankIdx = 0; blankIdx < 9; blankIdx++)
		{
			if (ei->data[blankIdx] == 0)
				break;
		}

		if ((blankIdx % 3) != 0)	//�ո������Ե
		{
			Eight* left = new Eight(*ei);
			left->depth = ei->depth + 1;
			left->father = ei;
			left->blankLeft(blankIdx);
			left->getfvalue();
			//�����½ڵ�left��open���close�����Ƿ����
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(left));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(left));
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(left);
			}
			else if (ret_open == open.end() && left->fvalue < (*ret_close)->fvalue)	//��close��
			{
				(*ret_close)->depth = left->depth;
				(*ret_close)->fvalue = left->fvalue;
				(*ret_close)->father = left->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete left;
			}
			else if (ret_close == close.end() && left->fvalue < (*ret_open)->fvalue)	//��open��
			{
				(*ret_open)->father = left->father;
				(*ret_open)->depth = left->depth;
				(*ret_open)->fvalue = left->fvalue;
				delete left;
			}
			else
				delete left;
		}
		if (((blankIdx + 1) % 3) != 0) //�ո����ұ�Ե
		{
			Eight* right = new Eight(*ei);
			right->depth = ei->depth + 1;
			right->father = ei;
			right->blankRight(blankIdx);
			right->getfvalue();
			//�����½ڵ�left��open���close�����Ƿ����
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(right));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(right));
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(right);
			}
			else if (ret_open == open.end() && right->fvalue < (*ret_close)->fvalue)	//��close��
			{
				(*ret_close)->depth = right->depth;
				(*ret_close)->fvalue = right->fvalue;
				(*ret_close)->father = right->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete right;
			}
			else if (ret_close == close.end() && right->fvalue < (*ret_open)->fvalue)	//��open��
			{
				(*ret_open)->depth = right->depth;
				(*ret_open)->fvalue = right->fvalue;
				(*ret_open)->father = right->father;
				delete right;
			}
			else
				delete right;
		}
		if (blankIdx > 2)		//�ո����ϱ�Ե
		{
			Eight* up = new Eight(*ei);
			up->depth = ei->depth + 1;
			up->father = ei;
			up->blankUp(blankIdx);
			up->getfvalue();
			//�����½ڵ�left��open���close�����Ƿ����
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(up));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(up));
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(up);
			}
			else if (ret_open == open.end() && up->fvalue < (*ret_close)->fvalue)	//��close��
			{
				(*ret_close)->depth = up->depth;
				(*ret_close)->fvalue = up->fvalue;
				(*ret_close)->father = up->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete up;
			}
			else if (ret_close == close.end() && up->fvalue < (*ret_open)->fvalue)	//��open��
			{
				(*ret_open)->father = up->father;
				(*ret_open)->depth = up->depth;
				(*ret_open)->fvalue = up->fvalue;
				delete up;
			}
			else
				delete up;
		}
		if (blankIdx < 6)		//�ո����±�Ե
		{
			Eight* down = new Eight(*ei);
			down->depth = ei->depth + 1;
			down->father = ei;
			down->blankDown(blankIdx);
			down->getfvalue();
			//�����½ڵ�left��open���close�����Ƿ����
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(down));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(down));
			//���ݽ������ȥ��
			if (ret_open == open.end() && ret_close == close.end())		//����open��close����
			{
				open.push_back(down);
			}
			else if (ret_open == open.end() && down->fvalue < (*ret_close)->fvalue)	//��close��
			{
				(*ret_close)->depth = down->depth;
				(*ret_close)->fvalue = down->fvalue;
				(*ret_close)->father = down->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete down;
			}
			else if (ret_close == close.end() && down->fvalue < (*ret_open)->fvalue)	//��open��
			{
				(*ret_open)->father = down->father;
				(*ret_open)->depth = down->depth;
				(*ret_open)->fvalue = down->fvalue;
				delete down;
			}
			else
				delete down;
		}

	}
	int step_count = -1;
	while (ei)
	{
		PrintEight(ei);
		std::cout << endl;
		ei = ei->father;
		step_count++;
	}
	std::cout << "ʹ�ò�����" << step_count << endl;
	std::cout << "size of open:" << open.size() << endl;
	std::cout << "size of close:" << close.size() << endl;

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
	//A();
	cout << "��ʱ��" << duration << endl;
	return 0;
}

void PrintEight(Eight* ei)
{
	for (int i = 0; i < 9; i++)
	{
		if (0 == ei->data[i])
			std::cout << "  ";
		else
			std::cout << (int)ei->data[i] << " ";
		if ((i + 1) % 3 == 0)
			std::cout << endl;
	}
}