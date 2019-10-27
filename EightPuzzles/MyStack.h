#ifndef MYSTACK_H
#define MYSTACK_H

typedef struct eight
{
	unsigned char data[9];
	int fValue;
	int depth;
	struct eight* father;
}EightPullze;


typedef struct
{
	EightPullze* elem;
	int capactiy;	//’ª¥Û–°
	int front;		//’ª∂•÷∏’Î
}Stack;

void createStack(Stack* s, int n);
void push(Stack* s, EightPullze e);
EightPullze pop(Stack* s);
int find(Stack* s, EightPullze* e);


#endif // !MYSTACK_H

