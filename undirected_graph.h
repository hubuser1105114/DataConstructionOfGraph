#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#define UNVISITED 0
#define VISITED 1
#define OK 1
#define ERROR 0
#define INFINITY INT_MAX         //���������int����������
#define OVERFLOW -2
typedef char Vextype;            //Ԫ���������ַ����ʹ���
typedef int Status;
typedef enum{UNDEFINED,DG,DN,UDG,UDN}Graphkind; //ͼ������

typedef struct
{
	Vextype* vexs;                    //��������
	int** arcs;                       //�ڽӾ���
	int vexs_num, arcs_num;           //�������������
	int* tags;                        //��־����
	Graphkind G_kind;                 //ͼ������
}MGraph;
//����ͼ(��Ȩ����Ȩ)  �ṹ

typedef struct
{
	Vextype v, w;                     //�ߵĶ˵�
	int info;                         //�ߵ���Ϣ,����ͼ��0��ʾ���ڽӣ�1��ʾ�ڽ�
}ArcInfo;                             //        �����Ȩͼ��INFINITY��ʾ���ڽӣ�����������Ȩֵ
//����Ϣ  �ṹ

typedef struct
{
	int* elem;                       //���еĻ�ַ
	int front;                       //��ͷԪ�ص��±�
	int rear;                        //��βԪ��+1���±�
	int length;                      //���г���
	int Maxsize;                     //��󳤶�
}LQueue;
//���нṹ

typedef struct
{
	int prev;            //��ǰ���·���ϸö����ǰ�������λ��
	int lowcast;         //��ǰ���·���ĳ���
}DistInfo;               //V-U��������·����Ϣ
// Dijkstra�㷨�ĸ�������

Status InitGraph(MGraph &G,Graphkind kind,Vextype* vexs,int n);
//��ʼ����n���������ޱߵ�kind���ͼ

Status CreateGraph(MGraph &G, Graphkind kind, Vextype* &vexs, int n, ArcInfo* &arcs, int e);
//����n�������e���ߵ�ͼ��vexsΪ������Ϣ��arcsΪ����Ϣ

Status DestroyGraph(MGraph &G);
//����ͼG

int LocateVex(MGraph G, Vextype v);
//���Ҷ���v��ͼG�е�λ��

Status GetVex(MGraph G, int k, Vextype &w);
//ȡͼG��k�����ֵ��w

Status PutVex(MGraph &G, int k, Vextype w);
//��ͼG��k���㸳ֵw

int FirstAdjvex(MGraph G, int k);
//��ͼG��k����ĵ�һ���ڽӶ����λ��

int NextAdjvex(MGraph G, int k, int m);
//m����Ϊk������ڽӶ��㣬��ͼG��k���������m�������һ���ڽӶ����λ��

Status AddArc(MGraph &G, int k, int m, int info);
//��ͼG������k���㵽m����ıߣ�infoΪȨֵ,��Ȩ��Ϊ1

Status DeleteArc(MGraph &G, int k, int m);
//��ͼG��ɾ��k���㵽m����ı�


Status DFS_ConnectedGraph(MGraph &G, Status(*visit)(Vextype),int k);
//��һ����ͨͼ��k�������������ȱ���
Status DFSTraverse(MGraph G, Status(*visit)(Vextype));
//������ȱ���

Status BFSTraverse(MGraph G, Status(*visit)(Vextype));
//������ȱ���

Status visit(Vextype);
//���ʽ�㺯��

Status InitQueue(LQueue &Q,int num);
//��ʼ��һ������

Status EnQueue(LQueue &Q,int i);
//���

Status DeQueue(LQueue &Q,int &i);
//����


//�ӿ���չ


Status JudgeAdjvex(MGraph G, Vextype v,Vextype w);
//�ж϶���ֵΪv�Ķ����Ƿ�Ϊ����ֵΪw�Ķ�����ڽӶ���

Status JudgeConnected(MGraph G);
//�ж�ͼG�Ƿ�Ϊ��ͨͼ

int CountDegree(MGraph G, Vextype x);
//����ֵΪx�Ķ���Ķ���

int CountShortestRoad_UDG(MGraph G, Vextype v, Vextype w);
//����������Ȩͼ����ֵΪv�Ķ��㵽����ֵΪw�Ķ�������·�� 

int CountShortestRoad_UDN(MGraph G, Vextype v, Vextype w);
//���������Ȩͼ����ֵΪv�Ķ��㵽����ֵΪw�Ķ�������·�� 

Status Dijkstra(MGraph G, int i, DistInfo* &Dist);
//Dijkstra�㷨����Դ��i���㵽������������·��

Status JudgeComplete(MGraph G);
//�ж�ͼG�Ƿ�Ϊ��ȫͼ

Status JudgeReached(MGraph G, Vextype v, Vextype w);
//�ж�ֵΪv��ֵΪw����������Ƿ�ɴ�


//���Ժ���

void menu(void);
//�ṩ���Բ˵�ѡ��

Status Init_test(int &n, int &e, Vextype* &test_vexs, ArcInfo* &test_arcs, MGraph &G);
//��ʼ����������

void printvexs(Vextype* vexs, int num);
//������ʾ���н��ֵ

Status PrintGraph(MGraph G);
//��ʾ����ͼG�Ĺ�ϵ

void printadj_marix(MGraph G);
//��ʾ�ڽ�����

Status ScanfAndCreate_Graph(MGraph &G);
//�Լ����벢����һ������ͼ