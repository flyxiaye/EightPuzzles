#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3 //数码组大小
#define Max_Step 50000000 //最大搜索深度
#define MAX 50000000

typedef struct node//八数码结构体
{
	int form[N][N];//数码组
	int evalue;//评估值
	int udirect;//所屏蔽方向，防止往回推到上已状态，1上2下3左4右
	struct node* parent;//父节点
}Graph;

Graph* Qu[MAX];//队列
Graph* St[MAX];//堆栈

/////////打印数码组
void Print(Graph* The_graph)
{
	int i, j;
	if (The_graph == NULL)
		printf("图为空\n");
	else
	{
		printf("---------------------\n");
		for (i = 0; i < N; i++)
		{
			printf("|\t");
			for (j = 0; j < N; j++)
			{
				printf("%d\t", The_graph->form[i][j]);//遍历打印
			}
			printf("\t|\n");
		}
		printf("|\t\t\t差距:%d\t|\n", The_graph->evalue);//差距显示
		printf("---------------------\n");
	}
}

/////////评价函数
int Evaluate(Graph* The_graph, Graph* End_graph)
{
	int valute = 0;//差距数
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

/////////移动数码组
Graph* Move(Graph* The_graph, int Direct, int CreatNew_graph)
{
	Graph* New_graph;//
	int HasGetBlank = 0;//是否获取空格位置
	int AbleMove = 1;//是否可移动
	int i, j, t_i, t_j, x, y;

	for (i = 0; i < N; i++)//获取空格坐标i,j
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
	//printf("空格位置:%d,%d\n",i,j);

	t_i = i;
	t_j = j;

	//移动空格
	switch (Direct)
	{
	case 1://上
		t_i--;
		if (t_i < 0)
			AbleMove = 0;
		break;
	case 2://下
		t_i++;
		if (t_i >= N)
			AbleMove = 0;
		break;
	case 3://左
		t_j--;
		if (t_j < 0)
			AbleMove = 0;
		break;
	case 4://右
		t_j++;
		if (t_j >= N)
			AbleMove = 0;
		break;

	}

	if (AbleMove == 0)//不能移动则返回原节点
	{
		return The_graph;
	}
	if (CreatNew_graph == 1)
	{
		New_graph = (Graph*)malloc(sizeof(Graph));//生成节点
		for (x = 0; x < N; x++)
		{
			for (y = 0; y < N; y++)
			{
				New_graph->form[x][y] = The_graph->form[x][y];//复制数码组
			}

		}
	}
	else
	{
		New_graph = The_graph;
	}
	//移动后
	New_graph->form[i][j] = New_graph->form[t_i][t_j];
	New_graph->form[t_i][t_j] = 0;
	//printf("移动产生的新图:\n");
	//Print(New_graph);
	return New_graph;
}

/////////搜索函数
Graph* Search(Graph* Begin, Graph* End)
{
	Graph* g1, * g2, * g;
	int Step = 0;//深度
	int Direct = 0;//方向
	int i;
	int front, rear;
	front = rear = -1;//队列初始化
	g = NULL;
	rear++;//入队
	Qu[rear] = Begin;
	while (rear != front)//队列不空
	{
		front++;//出队
		g1 = Qu[front];
		//printf("开始第%d个图:\n",front);
		//Print(g1);
		for (i = 1; i <= 4; i++)//分别从四个方向推导出新子节点
		{
			Direct = i;
			if (Direct == g1->udirect)//跳过屏蔽方向
				continue;
			g2 = Move(g1, Direct, 1);//移动数码组

			if (g2 != g1)//数码组是否可以移动
			{
				//可以移动
				Evaluate(g2, End);//评价新的节点
				//printf("开始产生的第%d个图:\n",i);
				//Print(g2);
				if (g2->evalue <= g1->evalue + 1)
				{
					//是优越节点
					g2->parent = g1;
					//移动空格
					switch (Direct)//设置屏蔽方向，防止往回推
					{
					case 1://上
						g2->udirect = 2;
						break;
					case 2://下
						g2->udirect = 1;
						break;
					case 3://左
						g2->udirect = 4;
						break;
					case 4://右
						g2->udirect = 3;
						break;

					}
					rear++;
					Qu[rear] = g2;//存储节点到待处理队列
					if (g2->evalue == 0)//为0则搜索完成
					{
						g = g2;
						//i=5;
						break;
					}
				}
				else
				{
					free(g2);//抛弃劣质节点
					g2 = NULL;
				}
			}

		}

		if (g != NULL)//为0则搜索完成
		{
			if (g->evalue == 0)
			{
				break;
			}
		}

		Step++;//统计深度
		if (Step > Max_Step)
		{
			break;
		}
	}
	return g;
}

/////////初始化一个八数码结构体
Graph* CR_BeginGraph(Graph* The_graph)
{
	srand((unsigned)time(0));
	int M = 10;//随机移动步数
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
		Direct = rand() % 4 + 1;//产生1－4随机数
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

	//目标数码组
	Graph End_graph = {
		{{1,2,3},{8,0,4},{7,6,5}},0,0,NULL
	};

	//初始数码组
	Graph Begin = {
		{{4, 2, 5},{ 7, 0, 1},{3, 8, 6}},0,0,NULL
	};
	Graph* Begin_graph = &Begin;
	//Begin_graph = CR_BeginGraph(&End_graph);//随机产生初始数码组
	Evaluate(Begin_graph, &End_graph);//对初始的数码组评价
	printf("初始数码组:\n");
	Print(Begin_graph);
	printf("目标数码组:\n");
	Print(&End_graph);

	Graph* G, * P;
	int top = -1;

	//图搜索
	G = Search(Begin_graph, &End_graph);
	//打印
	if (G)
	{
		//把路径倒序
		P = G;
		//压栈
		while (P != NULL)
		{
			top++;
			St[top] = P;
			P = P->parent;
		}
		printf("<<<<<<<<<<<<<<<搜索结果>>>>>>>>>>>>>>>>\n");
		//弹栈打印
		while (top > -1)
		{
			P = St[top];
			top--;
			Print(P);
		}
		printf("<<<<<<<<<<<<<<<<<完成>>>>>>>>>>>>>>>>>>\n");
	}
	else
	{
		printf("搜索不到结果，深度为%d\n", Max_Step);
		//设计搜索深度范围主要是防止队列内存越界
	}


	return 0;
}
// ————————————————
// 版权声明：本文为CSDN博主「wangqiuyun」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/wangqiuyun/article/details/7840771