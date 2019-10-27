#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#define NUM 9
typedef struct eight
{
	unsigned char data[NUM];
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

#endif // !DATASTRUCT_H

