#include "DataClass.h"

unsigned char tar[] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };
const Eight target(tar, 0, 0);
Eight::Eight(unsigned char* d, int dep, int fv, Eight* fa)
{
	for (int i = 0; i < NUM; i++)
		data[i] = d[i];
	depth = dep;
	fvalue = fv;
	father = fa;
}
Eight::Eight(const Eight& ei)
{
	for (int i = 0; i < NUM; i++)
		data[i] = ei.data[i];
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
}
void Eight::blankRight(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx + 1];
	data[idx + 1] = temp;
}
void Eight::blankUp(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx - 3];
	data[idx - 3] = temp;
}
void Eight::blankDown(int idx)
{
	unsigned char temp = data[idx];
	data[idx] = data[idx + 3];
	data[idx + 3] = temp;
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