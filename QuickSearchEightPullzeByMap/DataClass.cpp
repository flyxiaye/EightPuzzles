#include "DataClass.h"

unsigned char tar[] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
const Eight target(tar);
int mypow(int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		x *= 10;
	}
	return x;
}
void Eight::getIndex(void)
{
	index = 0;
	for (int i = 0; i < NUM; i++)
	{
		index += mypow(data[i], i);
	}
}
Eight::Eight(unsigned char* d, int idx, int dep, int fv, Eight* fa)
{
	for (int i = 0; i < NUM; i++)
		data[i] = d[i];
	index = idx;
	depth = dep;
	fvalue = fv;
	father = fa;
}
Eight::Eight(unsigned char* d)
{
	for (int i = 0; i < NUM; i++)
		data[i] = d[i];
	depth = 0;
	father = nullptr;
	this->getfvalue();
	this->getIndex();
}
Eight::Eight(const Eight& ei)
{
	for (int i = 0; i < NUM; i++)
		data[i] = ei.data[i];
	index = ei.index;
	depth = ei.depth;
	fvalue = ei.fvalue;
	father = ei.father;
}
bool Eight::operator==(const Eight& ei)
{
	for (int i = 0; i < NUM; i++)
	{
		if (data[i] != ei.data[i])
			return false;
	}
	return true;
}
void Eight::blankLeft(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx - 1];
	data[idx - 1] = temp;
	this->getfvalue();
	this->getIndex();
}
void Eight::blankRight(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx + 1];
	data[idx + 1] = temp;
	this->getfvalue();
	this->getIndex();
}
void Eight::blankUp(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx - 3];
	data[idx - 3] = temp;
	this->getfvalue();
	this->getIndex();
}
void Eight::blankDown(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx + 3];
	data[idx + 3] = temp;
	this->getfvalue();
	this->getIndex();
}
void Eight::getfvalue()
{
	fvalue = depth + this->notEquals(target);
}
int Eight::notEquals(const Eight& ei)
{
	int error = 0;
	for (int i = 0; i < NUM; i++)
	{
		if (data[i] != ei.data[i])
			error++;
	}
	return error;
}
bool Eight::idxEquals(const Eight* ei)
{
	return this->index == ei->index;
}