#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3 //�������С
#define Max_Step 50000000 //����������
#define MAX 50000000

typedef struct node//������ṹ��
{
	int form[N][N];//������
	int evalue;//����ֵ
	int udirect;//�����η��򣬷�ֹ�����Ƶ�����״̬��1��2��3��4��
	struct node* parent;//���ڵ�
}Graph;

Graph* Qu[MAX];//����
Graph* St[MAX];//��ջ

/////////��ӡ������
void Print(Graph* The_graph)
{
	int i, j;
	if (The_graph == NULL)
		printf("ͼΪ��\n");
	else
	{
		printf("---------------------\n");
		for (i = 0; i < N; i++)
		{
			printf("|\t");
			for (j = 0; j < N; j++)
			{
				printf("%d\t", The_graph->form[i][j]);//������ӡ
			}
			printf("\t|\n");
		}
		printf("|\t\t\t���:%d\t|\n", The_graph->evalue);//�����ʾ
		printf("---------------------\n");
	}
}

/////////���ۺ���
int Evaluate(Graph* The_graph, Graph* End_graph)
{
	int valute = 0;//�����
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (The_graph->form[i][j] != End_graph->form[i][j])
			{
				valute++;
			}
		}
	}
	The_graph->evalue = valute;
	return valute;
}

/////////�ƶ�������
Graph* Move(Graph* The_graph, int Direct, int CreatNew_graph)
{
	Graph* New_graph;//
	int HasGetBlank = 0;//�Ƿ��ȡ�ո�λ��
	int AbleMove = 1;//�Ƿ���ƶ�
	int i, j, t_i, t_j, x, y;

	for (i = 0; i < N; i++)//��ȡ�ո�����i,j
	{
		for (j = 0; j < N; j++)
		{
			if (The_graph->form[i][j] == 0)
			{
				HasGetBlank = 1;
				break;
			}
		}
		if (HasGetBlank == 1)
			break;
	}
	//printf("�ո�λ��:%d,%d\n",i,j);

	t_i = i;
	t_j = j;

	//�ƶ��ո�
	switch (Direct)
	{
	case 1://��
		t_i--;
		if (t_i < 0)
			AbleMove = 0;
		break;
	case 2://��
		t_i++;
		if (t_i >= N)
			AbleMove = 0;
		break;
	case 3://��
		t_j--;
		if (t_j < 0)
			AbleMove = 0;
		break;
	case 4://��
		t_j++;
		if (t_j >= N)
			AbleMove = 0;
		break;

	}

	if (AbleMove == 0)//�����ƶ��򷵻�ԭ�ڵ�
	{
		return The_graph;
	}
	if (CreatNew_graph == 1)
	{
		New_graph = (Graph*)malloc(sizeof(Graph));//���ɽڵ�
		for (x = 0; x < N; x++)
		{
			for (y = 0; y < N; y++)
			{
				New_graph->form[x][y] = The_graph->form[x][y];//����������
			}

		}
	}
	else
	{
		New_graph = The_graph;
	}
	//�ƶ���
	New_graph->form[i][j] = New_graph->form[t_i][t_j];
	New_graph->form[t_i][t_j] = 0;
	//printf("�ƶ���������ͼ:\n");
	//Print(New_graph);
	return New_graph;
}

/////////��������
Graph* Search(Graph* Begin, Graph* End)
{
	Graph* g1, * g2, * g;
	int Step = 0;//���
	int Direct = 0;//����
	int i;
	int front, rear;
	front = rear = -1;//���г�ʼ��
	g = NULL;
	rear++;//���
	Qu[rear] = Begin;
	while (rear != front)//���в���
	{
		front++;//����
		g1 = Qu[front];
		//printf("��ʼ��%d��ͼ:\n",front);
		//Print(g1);
		for (i = 1; i <= 4; i++)//�ֱ���ĸ������Ƶ������ӽڵ�
		{
			Direct = i;
			if (Direct == g1->udirect)//�������η���
				continue;
			g2 = Move(g1, Direct, 1);//�ƶ�������

			if (g2 != g1)//�������Ƿ�����ƶ�
			{
				//�����ƶ�
				Evaluate(g2, End);//�����µĽڵ�
				//printf("��ʼ�����ĵ�%d��ͼ:\n",i);
				//Print(g2);
				if (g2->evalue <= g1->evalue + 1)
				{
					//����Խ�ڵ�
					g2->parent = g1;
					//�ƶ��ո�
					switch (Direct)//�������η��򣬷�ֹ������
					{
					case 1://��
						g2->udirect = 2;
						break;
					case 2://��
						g2->udirect = 1;
						break;
					case 3://��
						g2->udirect = 4;
						break;
					case 4://��
						g2->udirect = 3;
						break;

					}
					rear++;
					Qu[rear] = g2;//�洢�ڵ㵽���������
					if (g2->evalue == 0)//Ϊ0���������
					{
						g = g2;
						//i=5;
						break;
					}
				}
				else
				{
					free(g2);//�������ʽڵ�
					g2 = NULL;
				}
			}

		}

		if (g != NULL)//Ϊ0���������
		{
			if (g->evalue == 0)
			{
				break;
			}
		}

		Step++;//ͳ�����
		if (Step > Max_Step)
		{
			break;
		}
	}
	return g;
}

/////////��ʼ��һ��������ṹ��
Graph* CR_BeginGraph(Graph* The_graph)
{
	srand((unsigned)time(0));
	int M = 10;//����ƶ�����
	int Direct;
	int i, x, y;
	Graph* New_graph;
	New_graph = (Graph*)malloc(sizeof(Graph));
	for (x = 0; x < N; x++)
	{
		for (y = 0; y < N; y++)
		{
			New_graph->form[x][y] = The_graph->form[x][y];
		}
	}
	for (i = 0; i < M; i++)
	{
		Direct = rand() % 4 + 1;//����1��4�����
		//printf("Direct:%d\n",Direct);
		New_graph = Move(New_graph, Direct, 0);
		//Print(New_graph);
	}

	New_graph->evalue = 0;
	New_graph->udirect = 0;
	New_graph->parent = NULL;

	return New_graph;
}

int main(int argc, const char* argv[])
{

	// insert code here...
	/*
	Graph Begin_graph={
		{{2,8,3},{1,6,4},{0,7,5}},0,0,NULL
	};

	Graph Begin_graph={
		{{2,8,3},{1,0,4},{7,6,5}},0,0,NULL
	};


	Graph Begin_graph={
		{{2,0,1},{4,6,5},{3,7,8}},0,0,NULL
	};
	*/

	//Ŀ��������
	Graph End_graph = {
		{{1,2,3},{8,0,4},{7,6,5}},0,0,NULL
	};

	//��ʼ������
	Graph Begin = {
		{{4, 2, 5},{ 7, 0, 1},{3, 8, 6}},0,0,NULL
	};
	Graph* Begin_graph = &Begin;
	//Begin_graph = CR_BeginGraph(&End_graph);//���������ʼ������
	Evaluate(Begin_graph, &End_graph);//�Գ�ʼ������������
	printf("��ʼ������:\n");
	Print(Begin_graph);
	printf("Ŀ��������:\n");
	Print(&End_graph);

	Graph* G, * P;
	int top = -1;

	//ͼ����
	G = Search(Begin_graph, &End_graph);
	//��ӡ
	if (G)
	{
		//��·������
		P = G;
		//ѹջ
		while (P != NULL)
		{
			top++;
			St[top] = P;
			P = P->parent;
		}
		printf("<<<<<<<<<<<<<<<�������>>>>>>>>>>>>>>>>\n");
		//��ջ��ӡ
		while (top > -1)
		{
			P = St[top];
			top--;
			Print(P);
		}
		printf("<<<<<<<<<<<<<<<<<���>>>>>>>>>>>>>>>>>>\n");
	}
	else
	{
		printf("����������������Ϊ%d\n", Max_Step);
		//���������ȷ�Χ��Ҫ�Ƿ�ֹ�����ڴ�Խ��
	}


	return 0;
}
// ��������������������������������
// ��Ȩ����������ΪCSDN������wangqiuyun����ԭ�����£���ѭ CC 4.0 BY-SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
// ԭ�����ӣ�https://blog.csdn.net/wangqiuyun/article/details/7840771