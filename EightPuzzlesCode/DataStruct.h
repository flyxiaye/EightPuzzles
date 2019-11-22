#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#define NUM 9
typedef struct eight
{
	int data[NUM];
	int code;
	int fValue;
	int depth;
	struct eight* father;
}EightPullze;


extern EightPullze Target;
int notEquals(EightPullze* src, EightPullze* dst);
int getfValue(EightPullze* ei);
EightPullze* createEightPullze(EightPullze* src);
void blankLeft(EightPullze* ei, int idx);
void blankRight(EightPullze* ei, int idx);
void blankUp(EightPullze* ei, int idx);
void blankDown(EightPullze* ei, int idx);
void PrintEightPullze(EightPullze* ei);
void getCode(EightPullze* ei);
void copyNode(EightPullze* src, EightPullze* dst);

#endif // !DATASTRUCT_H

