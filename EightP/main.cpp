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
		if (!ei->notEquals(target))		//匹配成功
		{
			break;
		}
		//扩展节点
		int blankIdx;
		for (blankIdx = 0; blankIdx < 9; blankIdx++)
		{
			if (ei->data[blankIdx] == 0)
				break;
		}

		if ((blankIdx % 3) != 0)	//空格不在左边缘
		{
			Eight* left = new Eight(*ei);
			left->father = ei;
			left->blankLeft(blankIdx);
			open.push(left);
		}
		if (((blankIdx + 1) % 3) != 0) //空格不在右边缘
		{
			Eight* right = new Eight(*ei);
			right->father = ei;
			right->blankRight(blankIdx);
			open.push(right);
		}
		if (blankIdx > 2)		//空格不在上边缘
		{
			Eight* up = new Eight(*ei);
			up->father = ei;
			up->blankUp(blankIdx);
			open.push(up);
		}
		if (blankIdx < 6)		//空格不在下边缘
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
	std::cout << "使用步数：" << step_count << endl;
	std::cout << "size of open:" << open.size() << endl;
	std::cout << "size of close:" << close.size() << endl;
}
void A(void)	//A算法
{
	list<Eight> open;
	list<Eight> close;
	unsigned char st[] = { 1,2,3,8,4,0,7,6,5 };//{ 4,2,5,7,0,1,3,8,6 };
	Eight s(st);
	Eight ei;
	open.push_back(s);
	while (!open.empty())
	{
		//找f值最小的节点
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

		if (!ei.notEquals(target))		//匹配成功
		{
			break;
		}

		//扩展节点
		int blankIdx;
		for (blankIdx = 0; blankIdx < 9; blankIdx++)
		{
			if (ei.data[blankIdx] == 0)
				break;
		}

		if ((blankIdx % 3) != 0)	//空格不在左边缘
		{
			Eight left(ei);
			left.depth = ei.depth + 1;
			left.father = &ei;
			left.getfvalue();
			left.blankLeft(blankIdx);
			//查找新节点left在open表和close表中是否存在
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), left);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), left);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(left);
			}
			else if (ret_open == open.end() && left.fvalue < (*ret_close).fvalue)	//在close表
			{
				(*ret_close).depth = left.depth;
				(*ret_close).fvalue = left.fvalue;
				(*ret_close).father = left.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && left.fvalue < (*ret_open).fvalue)	//在open表
			{
				(*ret_open).depth = left.depth;
				(*ret_open).fvalue = left.fvalue;
				(*ret_open).father = left.father;
			}
		}
		if (((blankIdx + 1) % 3) != 0) //空格不在右边缘
		{
			Eight right(ei);
			right.depth = ei.depth + 1;
			right.father = &ei;
			right.getfvalue();
			right.blankRight(blankIdx);
			//查找新节点right在open表和close表中是否存在
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), right);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), right);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(right);
			}
			else if (ret_open == open.end() && right.fvalue < (*ret_close).fvalue)	//在close表
			{
				(*ret_close).depth = right.depth;
				(*ret_close).fvalue = right.fvalue;
				(*ret_close).father = right.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && right.fvalue < (*ret_open).fvalue)	//在open表
			{
				(*ret_open).depth = right.depth;
				(*ret_open).fvalue = right.fvalue;
				(*ret_open).father = right.father;
			}
		}
		if (blankIdx > 2)		//空格不在上边缘
		{
			Eight up(ei);
			up.depth = ei.depth + 1;
			up.father = &ei;
			up.getfvalue();
			up.blankUp(blankIdx);
			//查找新节点up在open表和close表中是否存在
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), up);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), up);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(up);
			}
			else if (ret_open == open.end() && up.fvalue < (*ret_close).fvalue)	//在close表
			{
				(*ret_close).depth = up.depth;
				(*ret_close).fvalue = up.fvalue;
				(*ret_close).father = up.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && up.fvalue < (*ret_open).fvalue)	//在open表
			{
				(*ret_open).depth = up.depth;
				(*ret_open).fvalue = up.fvalue;
				(*ret_open).father = up.father;
			}
		}
		if (blankIdx < 6)		//空格不在下边缘
		{
			Eight down(ei);
			down.depth = ei.depth + 1;
			down.father = &ei;
			down.getfvalue();
			down.blankDown(blankIdx);
			//查找新节点down在open表和close表中是否存在
			list<Eight>::iterator ret_open = find(open.begin(), open.end(), down);
			list<Eight>::iterator ret_close = find(close.begin(), close.end(), down);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(down);
			}
			else if (ret_open == open.end() && down.fvalue < (*ret_close).fvalue)	//在close表
			{
				(*ret_close).depth = down.depth;
				(*ret_close).fvalue = down.fvalue;
				(*ret_close).father = down.father;
				Eight tmp(*ret_close);
				close.erase(ret_close);
				open.push_back(tmp);
			}
			else if (ret_close == close.end() && down.fvalue < (*ret_open).fvalue)	//在open表
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
	std::cout << "使用步数：" << step_count << endl;
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
		//找f值最小的节点
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

		if (!ei->notEquals(target))		//匹配成功
		{
			break;
		}
		if (ei->depth > SEARCH_DEPTH)
		{
			cout << "超过搜索深度：" << SEARCH_DEPTH << endl;
			break;
		}

		//扩展节点
		int blankIdx;
		for (blankIdx = 0; blankIdx < 9; blankIdx++)
		{
			if (ei->data[blankIdx] == 0)
				break;
		}

		if ((blankIdx % 3) != 0)	//空格不在左边缘
		{
			Eight* left = new Eight(*ei);
			left->depth = ei->depth + 1;
			left->father = ei;
			left->blankLeft(blankIdx);
			left->getfvalue();
			//查找新节点left在open表和close表中是否存在
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(left));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(left));
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(left);
			}
			else if (ret_open == open.end() && left->fvalue < (*ret_close)->fvalue)	//在close表
			{
				(*ret_close)->depth = left->depth;
				(*ret_close)->fvalue = left->fvalue;
				(*ret_close)->father = left->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete left;
			}
			else if (ret_close == close.end() && left->fvalue < (*ret_open)->fvalue)	//在open表
			{
				(*ret_open)->father = left->father;
				(*ret_open)->depth = left->depth;
				(*ret_open)->fvalue = left->fvalue;
				delete left;
			}
			else
				delete left;
		}
		if (((blankIdx + 1) % 3) != 0) //空格不在右边缘
		{
			Eight* right = new Eight(*ei);
			right->depth = ei->depth + 1;
			right->father = ei;
			right->blankRight(blankIdx);
			right->getfvalue();
			//查找新节点left在open表和close表中是否存在
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(right));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(right));
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(right);
			}
			else if (ret_open == open.end() && right->fvalue < (*ret_close)->fvalue)	//在close表
			{
				(*ret_close)->depth = right->depth;
				(*ret_close)->fvalue = right->fvalue;
				(*ret_close)->father = right->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete right;
			}
			else if (ret_close == close.end() && right->fvalue < (*ret_open)->fvalue)	//在open表
			{
				(*ret_open)->depth = right->depth;
				(*ret_open)->fvalue = right->fvalue;
				(*ret_open)->father = right->father;
				delete right;
			}
			else
				delete right;
		}
		if (blankIdx > 2)		//空格不在上边缘
		{
			Eight* up = new Eight(*ei);
			up->depth = ei->depth + 1;
			up->father = ei;
			up->blankUp(blankIdx);
			up->getfvalue();
			//查找新节点left在open表和close表中是否存在
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(up));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(up));
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(up);
			}
			else if (ret_open == open.end() && up->fvalue < (*ret_close)->fvalue)	//在close表
			{
				(*ret_close)->depth = up->depth;
				(*ret_close)->fvalue = up->fvalue;
				(*ret_close)->father = up->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete up;
			}
			else if (ret_close == close.end() && up->fvalue < (*ret_open)->fvalue)	//在open表
			{
				(*ret_open)->father = up->father;
				(*ret_open)->depth = up->depth;
				(*ret_open)->fvalue = up->fvalue;
				delete up;
			}
			else
				delete up;
		}
		if (blankIdx < 6)		//空格不在下边缘
		{
			Eight* down = new Eight(*ei);
			down->depth = ei->depth + 1;
			down->father = ei;
			down->blankDown(blankIdx);
			down->getfvalue();
			//查找新节点left在open表和close表中是否存在
			list<Eight*>::iterator ret_open = find_if(open.begin(), open.end(), IsEu(down));
			list<Eight*>::iterator ret_close = find_if(close.begin(), close.end(), IsEu(down));
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.push_back(down);
			}
			else if (ret_open == open.end() && down->fvalue < (*ret_close)->fvalue)	//在close表
			{
				(*ret_close)->depth = down->depth;
				(*ret_close)->fvalue = down->fvalue;
				(*ret_close)->father = down->father;
				open.push_back(*ret_close);
				close.erase(ret_close);
				delete down;
			}
			else if (ret_close == close.end() && down->fvalue < (*ret_open)->fvalue)	//在open表
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
	std::cout << "使用步数：" << step_count << endl;
	std::cout << "size of open:" << open.size() << endl;
	std::cout << "size of close:" << close.size() << endl;

}
int main(void)
{
	//计时变量定义
	LARGE_INTEGER f;
	double dFreq;
	LARGE_INTEGER start, end;

	QueryPerformanceFrequency(&f);//获取内部高精度计数器的频率
	dFreq = (double)f.QuadPart; //获取计数器的频率
	QueryPerformanceCounter(&start);//获取内部高精度计数器当前的计数值
	//需要计时的代码写在这
	AA();
	QueryPerformanceCounter(&end);

	double duration = (double)(end.QuadPart - start.QuadPart) / dFreq;//计算时间
	//A();
	cout << "用时：" << duration << endl;
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