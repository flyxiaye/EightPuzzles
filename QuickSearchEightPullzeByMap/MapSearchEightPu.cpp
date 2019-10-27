#include <iostream>
#include "DataClass.h"
#include <map>
#include <algorithm>
#include <Windows.h>
#define SEARCH_DEPTH 25
using namespace std;
void PrintEight(Eight* ei);
void AA(void)
{
	map<int, Eight*> open;
	map<int, Eight*> close;
	unsigned char st[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	//{ 8, 7, 3, 1, 6, 0, 5, 4, 2 };//21
	//{ 7, 2, 3, 8, 1, 0, 6, 5, 4 };//13
	//{ 7, 2, 3, 8, 1, 6, 0, 5, 4 };//18
	//{ 4, 2, 5, 7, 0, 1, 3, 8, 6 };
	Eight* s = new Eight(st);
	Eight* ei = nullptr;
	open.insert(make_pair(s->index, s));
	while (!open.empty())
	{
		//找f值最小的节点
		map<int, Eight*>::iterator min_it = open.begin();
		int minf = (*min_it).second->fvalue;
		for (auto it = open.begin(); it != open.end(); it++)
		{
			if ((*it).second->fvalue < minf)
				min_it = it;
		}
		ei = (*min_it).second;
		open.erase(min_it);
		close.insert(make_pair(ei->index, ei));

		if (ei->idxEquals(&target))		//匹配成功
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
			//查找新节点left在open表和close表中是否存在
			map<int, Eight*>::iterator ret_open = open.find(left->index);
			map<int, Eight*>::iterator ret_close = close.find(left->index);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.insert(make_pair(left->index, left));
			}
			else if (ret_open == open.end() && left->fvalue < (*ret_close).second->fvalue)	//在close表
			{
				(*ret_close).second->depth = left->depth;
				(*ret_close).second->fvalue = left->fvalue;
				(*ret_close).second->father = left->father;
				open.insert(*ret_close);
				close.erase(ret_close);
				delete left;
			}
			else if (ret_close == close.end() && left->fvalue < (*ret_open).second->fvalue)	//在open表
			{
				(*ret_open).second->father = left->father;
				(*ret_open).second->depth = left->depth;
				(*ret_open).second->fvalue = left->fvalue;
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
			//查找新节点left在open表和close表中是否存在
			map<int, Eight*>::iterator ret_open = open.find(right->index);
			map<int, Eight*>::iterator ret_close = close.find(right->index);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.insert(make_pair(right->index, right));
			}
			else if (ret_open == open.end() && right->fvalue < (*ret_close).second->fvalue)	//在close表
			{
				(*ret_close).second->depth = right->depth;
				(*ret_close).second->fvalue = right->fvalue;
				(*ret_close).second->father = right->father;
				open.insert(*ret_close);
				close.erase(ret_close);
				delete right;
			}
			else if (ret_close == close.end() && right->fvalue < (*ret_open).second->fvalue)	//在open表
			{
				(*ret_open).second->depth = right->depth;
				(*ret_open).second->fvalue = right->fvalue;
				(*ret_open).second->father = right->father;
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
			//查找新节点left在open表和close表中是否存在
			map<int, Eight*>::iterator ret_open = open.find(up->index);
			map<int, Eight*>::iterator ret_close = close.find(up->index);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.insert(make_pair(up->index, up));
			}
			else if (ret_open == open.end() && up->fvalue < (*ret_close).second->fvalue)	//在close表
			{
				(*ret_close).second->depth = up->depth;
				(*ret_close).second->fvalue = up->fvalue;
				(*ret_close).second->father = up->father;
				open.insert(*ret_close);
				close.erase(ret_close);
				delete up;
			}
			else if (ret_close == close.end() && up->fvalue < (*ret_open).second->fvalue)	//在open表
			{
				(*ret_open).second->father = up->father;
				(*ret_open).second->depth = up->depth;
				(*ret_open).second->fvalue = up->fvalue;
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
			//查找新节点left在open表和close表中是否存在
			map<int, Eight*>::iterator ret_open = open.find(down->index);
			map<int, Eight*>::iterator ret_close = close.find(down->index);
			//根据结果决定去留
			if (ret_open == open.end() && ret_close == close.end())		//不在open和close表里
			{
				open.insert(make_pair(down->index, down));
			}
			else if (ret_open == open.end() && down->fvalue < (*ret_close).second->fvalue)	//在close表
			{
				(*ret_close).second->depth = down->depth;
				(*ret_close).second->fvalue = down->fvalue;
				(*ret_close).second->father = down->father;
				open.insert(*ret_close);
				close.erase(ret_close);
				delete down;
			}
			else if (ret_close == close.end() && down->fvalue < (*ret_open).second->fvalue)	//在open表
			{
				(*ret_open).second->father = down->father;
				(*ret_open).second->depth = down->depth;
				(*ret_open).second->fvalue = down->fvalue;
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
	cout << "用时：" << duration << endl;
	//cout << mypow(9, 8);
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