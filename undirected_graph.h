#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#define UNVISITED 0
#define VISITED 1
#define OK 1
#define ERROR 0
#define INFINITY INT_MAX         //无穷以最大int型整数代替
#define OVERFLOW -2
typedef char Vextype;            //元素类型以字符类型代替
typedef int Status;
typedef enum{UNDEFINED,DG,DN,UDG,UDN}Graphkind; //图的类型

typedef struct
{
	Vextype* vexs;                    //顶点数组
	int** arcs;                       //邻接矩阵
	int vexs_num, arcs_num;           //顶点个数，边数
	int* tags;                        //标志数组
	Graphkind G_kind;                 //图的类型
}MGraph;
//无向图(无权，带权)  结构

typedef struct
{
	Vextype v, w;                     //边的端点
	int info;                         //边的信息,无向图：0表示不邻接，1表示邻接
}ArcInfo;                             //        无向带权图：INFINITY表示不邻接，其他数代表权值
//边信息  结构

typedef struct
{
	int* elem;                       //队列的基址
	int front;                       //队头元素的下标
	int rear;                        //队尾元素+1的下标
	int length;                      //队列长度
	int Maxsize;                     //最大长度
}LQueue;
//队列结构

typedef struct
{
	int prev;            //当前最短路径上该顶点的前驱顶点的位序
	int lowcast;         //当前最短路径的长度
}DistInfo;               //V-U顶点的最短路径信息
// Dijkstra算法的辅助函数

Status InitGraph(MGraph &G,Graphkind kind,Vextype* vexs,int n);
//初始化有n个顶点且无边的kind类的图

Status CreateGraph(MGraph &G, Graphkind kind, Vextype* &vexs, int n, ArcInfo* &arcs, int e);
//创建n个顶点和e条边的图，vexs为顶点信息，arcs为边信息

Status DestroyGraph(MGraph &G);
//销毁图G

int LocateVex(MGraph G, Vextype v);
//查找顶点v在图G中的位序

Status GetVex(MGraph G, int k, Vextype &w);
//取图G的k顶点的值到w

Status PutVex(MGraph &G, int k, Vextype w);
//对图G的k顶点赋值w

int FirstAdjvex(MGraph G, int k);
//求图G中k顶点的第一个邻接顶点的位序

int NextAdjvex(MGraph G, int k, int m);
//m顶点为k顶点的邻接顶点，求图G中k顶点相对于m顶点的下一个邻接顶点的位序

Status AddArc(MGraph &G, int k, int m, int info);
//在图G中增加k顶点到m顶点的边，info为权值,无权则为1

Status DeleteArc(MGraph &G, int k, int m);
//在图G中删除k顶点到m顶点的边


Status DFS_ConnectedGraph(MGraph &G, Status(*visit)(Vextype),int k);
//对一个连通图从k顶点进行深度优先遍历
Status DFSTraverse(MGraph G, Status(*visit)(Vextype));
//深度优先遍历

Status BFSTraverse(MGraph G, Status(*visit)(Vextype));
//广度优先遍历

Status visit(Vextype);
//访问结点函数

Status InitQueue(LQueue &Q,int num);
//初始化一个队列

Status EnQueue(LQueue &Q,int i);
//入队

Status DeQueue(LQueue &Q,int &i);
//出队


//接口拓展


Status JudgeAdjvex(MGraph G, Vextype v,Vextype w);
//判断顶点值为v的顶点是否为顶点值为w的顶点的邻接顶点

Status JudgeConnected(MGraph G);
//判断图G是否为连通图

int CountDegree(MGraph G, Vextype x);
//计算值为x的顶点的度数

int CountShortestRoad_UDG(MGraph G, Vextype v, Vextype w);
//计算无向无权图顶点值为v的顶点到顶点值为w的顶点的最短路径 

int CountShortestRoad_UDN(MGraph G, Vextype v, Vextype w);
//计算无向带权图顶点值为v的顶点到顶点值为w的顶点的最短路径 

Status Dijkstra(MGraph G, int i, DistInfo* &Dist);
//Dijkstra算法，求源点i顶点到其他顶点的最短路径

Status JudgeComplete(MGraph G);
//判断图G是否为完全图

Status JudgeReached(MGraph G, Vextype v, Vextype w);
//判断值为v和值为w的两个结点是否可达


//测试函数

void menu(void);
//提供测试菜单选择

Status Init_test(int &n, int &e, Vextype* &test_vexs, ArcInfo* &test_arcs, MGraph &G);
//初始化测试数据

void printvexs(Vextype* vexs, int num);
//依次显示所有结点值

Status PrintGraph(MGraph G);
//显示无向图G的关系

void printadj_marix(MGraph G);
//显示邻接数组

Status ScanfAndCreate_Graph(MGraph &G);
//自己输入并创建一个无向图