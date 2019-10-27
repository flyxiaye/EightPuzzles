#pragma once

class Eight
{
	enum
	{
		NUM = 9
	};
public:
	unsigned char data[NUM];
	int index;  //������ʽ����
	int depth;
	int fvalue;
	Eight* father;
	void getIndex(void);
public:
	Eight(unsigned char* d, int idx, int dep, int fv , Eight * fa);
	Eight(unsigned char* d);
	Eight() {};
	Eight(const Eight& ei);
	bool operator==(const Eight& ei);
	void blankLeft(int idx);
	void blankRight(int idx);
	void blankUp(int idx);
	void blankDown(int idx);
	void getfvalue();
	int notEquals(const Eight& ei);
	bool idxEquals(const Eight* ei);
};

//�º���ʹ��
//class IsEu
//{
//public: 
//	pair<int, Eight*> ei;
//public:
//	IsEu(pair<int, Eight*> e) :ei(e)
//	{
//
//	}
//	bool operator()(Eight* e1)
//	{
//		return ei.first == e1->index;
//	}
//};

extern const Eight target;
int mypow(int x, int y);