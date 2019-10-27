#pragma once

class Eight
{
	enum
	{
		NUM = 9
	};
public:
	unsigned char data[NUM];
	int depth;
	int fvalue;
	Eight* father;
public:
	Eight(unsigned char* d, int dep = 0, int fv = 0, Eight * fa = nullptr);
	Eight() {};
	Eight(const Eight& ei);
	bool operator==(const Eight& ei);
	void blankLeft(int idx);
	void blankRight(int idx);
	void blankUp(int idx);
	void blankDown(int idx);
	void getfvalue();
	int notEquals(const Eight& ei);
};

//·Âº¯ÊýÊ¹ÓÃ
class IsEu
{
public: 
	Eight* ei;
public:
	IsEu(Eight* e) :ei(e)
	{

	}
	bool operator()(Eight* e1)
	{
		for (int i = 0; i < 9; i++)
		{
			if (e1->data[i] != ei->data[i])
				return false;
		}
		return true;
	}
};

extern const Eight target;
