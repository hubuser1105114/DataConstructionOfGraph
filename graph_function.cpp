#include"undirected_graph.h"

//��ʼ����n���������ޱߵ�����ͼ
Status InitGraph(MGraph &G, Graphkind kind, Vextype* vexs, int n)
{
	int i, j;
	if (n < 0 || (kind != UDG && kind != UDN))return ERROR;     //��鶥�������ͼ������
	G.G_kind = kind;                                           
	if (n > 0 && vexs == NULL)return ERROR;                     //���vexs����Ͷ������ƥ��
	for (i = 0; i < n; i++)
	{
		for(j=i+1;j<n;j++)
		{
			if (vexs[j] == vexs[i])return ERROR;                //��������ֵ�ظ�
		}
		if (vexs[i] < 'A' || vexs[i] >'z' || (vexs[i] > 'Z'&&vexs[i] < 'a'))return ERROR;    //��������ֵ������ֵ
	}
	G.arcs_num = 0;
	G.vexs_num = n;
	if (0 == n) { G.vexs = NULL; G.arcs = NULL; return OK; }
	if (NULL == (G.vexs = (Vextype*)malloc(n * sizeof(Vextype))))
		return OVERFLOW;
	for (i = 0; i < n; i++)G.vexs[i] = vexs[i];
	if (NULL == (G.arcs = (int**)malloc(n * sizeof(int*))))     //�����ڽ�����
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (G.arcs[i] = (int*)malloc(n * sizeof(int))))
			return OVERFLOW;
	if (NULL == (G.tags = (int*)malloc(n * sizeof(int))))
		return OVERFLOW;
	for (i = 0; i < n; i++) 
	{
		G.tags[i] = UNVISITED;
		for (j = 0; j < n; j++)
		{
			if (G.G_kind == UDG)G.arcs[i][j] = 0;
			if (G.G_kind == UDN)G.arcs[i][j] = INFINITY;
		}
	}
	return OK;
}

//1.����n�������e���ߵ�ͼ��vexsΪ������Ϣ��arcsΪ����Ϣ
Status CreateGraph(MGraph &G, Graphkind kind, Vextype* &vexs, int n, ArcInfo* &arcs, int e)
{
	int i, j, k;
	Vextype v, w;
	if (OK != InitGraph(G,kind, vexs, n))
	{
		G.vexs_num = 0;
		if(NULL != G.vexs)free(G.vexs);
		G.vexs = NULL;
		G.G_kind = UNDEFINED; 
		if(NULL != G.arcs)free(G.arcs);
		G.arcs = NULL;
		return ERROR;
	}                                                         //��ʼ�������򷵻ش���
	if (e < 0 || e > n*(n-1)/2)
	{ 
		free(G.vexs); G.vexs = NULL;
		free(G.arcs); G.arcs = NULL;
		free(G.tags); G.tags = NULL;
		G.vexs_num = 0;
		G.G_kind = UNDEFINED;
		return ERROR;
	}
                                                               //���������򷵻�ERROR
	G.arcs_num = e;
	if (G.arcs_num == 0 || NULL == arcs)return OK;             //�������Ϊ0����ֱ�ӷ���OK
	for (k = 0; k < G.arcs_num; k++)                           //������Ϣ
	{
		v = arcs[k].v; w = arcs[k].w;
		if (v == w) 
		{
			G.vexs_num = 0;G.arcs_num = 0;
			free(G.vexs);G.vexs = NULL;
			free(G.arcs);G.arcs = NULL;
			G.G_kind = UNDEFINED;
			return ERROR;
		}                                                      //�������Թ�ϵ
		i = LocateVex(G, v); j = LocateVex(G, w);              //���û�д˽�㣬����ERROR
		if (i < 0 || j < 0) 
		{
			G.vexs_num = 0; G.arcs_num = 0;
			free(G.vexs); G.vexs = NULL;
			free(G.arcs); G.arcs = NULL;
			G.G_kind = UNDEFINED;
			return ERROR;
		}
		if( (G.G_kind == UDG && (arcs[k].info != 0 && arcs[k].info != 1)) || (G.G_kind == UDN && (arcs[k].info <=0 || arcs[k].info > 9)) )
		{
			G.vexs_num = 0; G.arcs_num = 0;
			free(G.vexs); G.vexs = NULL;
			free(G.arcs); G.arcs = NULL;
			G.G_kind = UNDEFINED;
			return ERROR;
		}
		for (i = k+1; i < G.arcs_num; i++)                       //���������Ϣ���ظ�
		{
			if ((arcs[k].v == arcs[i].v && arcs[k].w == arcs[i].w) || (arcs[k].v == arcs[i].w && arcs[k].w == arcs[i].v))
			{
				G.vexs_num = 0; G.arcs_num = 0;
				free(G.vexs); G.vexs = NULL;
				free(G.arcs); G.arcs = NULL;
				G.G_kind = UNDEFINED;
				return ERROR;
			}
		}
	}
	for (k = 0; k < G.arcs_num; k++)
	{
		v = arcs[k].v; w = arcs[k].w;
		i = LocateVex(G, v); j = LocateVex(G, w);
		G.arcs[i][j] = G.arcs[j][i] = arcs[k].info;
	}
	return OK;
}


//2.���Ҷ���ֵΪv��ͼG�е�λ��
int LocateVex(MGraph G, Vextype v)
{
	if (NULL == G.vexs)return -1;
	int i;
	for (i = 0; i < G.vexs_num; i++)
		if (v == G.vexs[i])return i;
	return -1;
}

//3.��ͼG��k����ĵ�һ���ڽӶ����λ��
int FirstAdjvex(MGraph G, int k)
{
	int i;
	if (NULL == G.vexs)return -1;
	if (k < 0 || k >= G.vexs_num)return -1;
	for (i = 0; i < G.vexs_num; i++)
	{
		if (UDG == G.G_kind && 0 != G.arcs[k][i])return i;
		if (UDN == G.G_kind && INFINITY != G.arcs[k][i])return i;
	}
		return -1;
}

//4.ȡͼG��k�����ֵ��w
Status GetVex(MGraph G, int k, Vextype &w)
{
	if (NULL == G.vexs || 0 >= G.vexs_num || k < 0 || k >= G.vexs_num)return -1;  //������ֵ�����Լ��
	w = G.vexs[k];
	return OK;
}

//5.��ͼG��k���㸳ֵw
Status PutVex(MGraph &G, int k, Vextype w)
{
	if (NULL == G.vexs || 0 == G.vexs_num || k < 0 || k >= G.vexs_num)return -1;  //�Ϸ��Լ��
	if (w < 'A' || w > 'z' || (w > 'Z'&&w < 'a'))return -1;                       //w�ļ��
	int i = 0;
	for (i = 0; i < G.vexs_num; i++)
	{
		if (G.vexs[i] == w) { return false; }   //�����ظ�
	}
	G.vexs[k] = w;
	return OK;
}

//6.m����Ϊk������ڽӶ��㣬��ͼG��k���������m�������һ���ڽӶ����λ��
int NextAdjvex(MGraph G, int k, int m)
{
	if (NULL == G.vexs || k < 0 || k >= G.vexs_num || m < 0 || m >= G.vexs_num)return -1;  //�Բ������ݺϷ��Լ��
	int i;  
	if (true != JudgeAdjvex(G, G.vexs[k], G.vexs[m]))return -1;
	for (i = m + 1; i < G.vexs_num; i++)
	{
		if (UDN == G.G_kind && INFINITY != G.arcs[k][i])return i;
		if (UDG == G.G_kind && G.arcs[k][i] == 1)return i;
	}
	return -2;    //��ʾû����һ���ڽӶ���
}

//7.��ͼG������k���㵽m����ıߣ�infoΪȨֵ,��Ȩ��Ϊ1
Status AddArc(MGraph &G, int k, int m, int info)
{
	if (NULL == G.vexs || NULL == G.arcs || k < 0 || m < 0 || k >= G.vexs_num || m >= G.vexs_num||k == m)return ERROR;
	//�Ϸ��Լ��
	if (UDG == G.G_kind && info != 1)return ERROR;
	if (UDN == G.G_kind && (info < 1 || info >9))return ERROR;
	if (UDG == G.G_kind && 1 == G.arcs[k][m])return -1;
	if (UDN == G.G_kind && INFINITY != G.arcs[k][m])return -1;
	G.arcs[k][m] = G.arcs[m][k] = info;
	G.arcs_num++;
	return OK;
}

//8.��ͼG��ɾ��k���㵽m����ı�
Status DeleteArc(MGraph &G, int k, int m)
{
	if (NULL == G.vexs || NULL == G.arcs || k < 0 || m < 0 || k >= G.vexs_num || m >= G.vexs_num || k == m)return ERROR;
	//�Ϸ��Լ��
	if (UDG == G.G_kind && 0 == G.arcs[k][m])return -1;
	if (UDN == G.G_kind && INFINITY == G.arcs[k][m])return -1;
	if (UDG == G.G_kind)G.arcs[k][m] = G.arcs[m][k] = 0;
	if (UDN == G.G_kind)G.arcs[k][m] = G.arcs[m][k] = INFINITY;
	G.arcs_num--;
	return OK;
}

//9.����ͼG
Status DestroyGraph(MGraph &G)
{
	free(G.vexs);
	free(G.tags);
	for (int i = 0; i < G.vexs_num; i++)
		free(G.arcs[i]);
	free(G.arcs);
	G.vexs = NULL;
	G.tags = NULL;
	G.arcs = NULL;
	G.arcs_num = 0;
	G.vexs_num = 0;
	G.G_kind = UNDEFINED;
	return OK;
}

//���ʽ�㺯��
Status visit(Vextype data)
{
	if (data == 0)return ERROR;
	printf("%c ", data);
	return OK;
}

//��һ����ͨͼ��k�������������ȱ���  
Status DFS_ConnectedGraph(MGraph &G,Status(*visit)(Vextype),int k)
{
	if (k < 0 || NULL == G.vexs)return ERROR;
	int i;
	if (ERROR == visit(G.vexs[k]))return ERROR;
	G.tags[k] = VISITED;
	for (i = FirstAdjvex(G, k); -1 != i; i = NextAdjvex(G, k, i))
	{
		if (G.tags[i] == UNVISITED)
		{
			if (ERROR == DFS_ConnectedGraph(G, visit, i))return ERROR;
		}
	}
	return OK;
}
//10.��һ��ͼ��������ȱ���
Status DFSTraverse(MGraph G, Status(*visit)(Vextype))
{
	if (NULL == G.vexs)return ERROR;
	int i;
	for (i = 0; i < G.vexs_num; i++)
		G.tags[i] = UNVISITED;
	for (i = 0; i < G.vexs_num; i++)
	{
		if (G.tags[i] == UNVISITED)
		{
			if (ERROR ==DFS_ConnectedGraph(G, visit, i))return ERROR;
		}
	}
	return OK;
}


//��ʼ��һ������
Status InitQueue(LQueue &Q,int num)
{
	if (num <= 0)return false;
	Q.elem = (int*)malloc(sizeof(int)*num);
	if (NULL == Q.elem)return OVERFLOW;
	for (int i = 0; i < num; i++)Q.elem[i] = 0;
	Q.front = Q.rear = Q.length = 0;
	Q.Maxsize = num;
	return OK;
}

//���
Status EnQueue(LQueue &Q, int i)
{
	if (NULL == Q.elem)return ERROR;
	if (Q.length == Q.Maxsize)return false;
	Q.elem[Q.rear] = i;
	Q.length++;
	Q.rear = (Q.rear + 1) % Q.Maxsize;
	return OK;
}

//����
Status DeQueue(LQueue &Q, int &i)
{
	if (NULL == Q.elem)return ERROR;
	if (Q.length == 0)return false;
	i = Q.elem[Q.front];
	Q.front = (Q.front + 1) % Q.Maxsize;
	Q.length--;
	return OK;
}

//11.������ȱ���
Status BFSTraverse(MGraph G, Status(*visit)(Vextype))
{
	if (0  == G.vexs_num || NULL == G.vexs)return ERROR;
	int i, j, s;
	for (i = 0; i < G.vexs_num; i++)
		G.tags[i] = UNVISITED;
	//��ʼ��
	for (s = 0; s < G.vexs_num; s++)
	{
		if (G.tags[s] == UNVISITED)
		{
			if (ERROR == visit(G.vexs[s]))return ERROR;
			G.tags[s] = VISITED;
			LQueue Q;
			InitQueue(Q, G.vexs_num);
			EnQueue(Q, s);
			while (OK == DeQueue(Q, j))
			{
				for (i = FirstAdjvex(G, j); i >= 0; i = NextAdjvex(G, j, i))
				{
					if (G.tags[i] == UNVISITED)
					{
						if (ERROR == visit(G.vexs[i]))return ERROR;
						G.tags[i] = VISITED;
						EnQueue(Q, i);
					}
				}
			}
		}
	}
	return OK;
}  


//12.�ж϶���ֵΪv�Ķ����Ƿ�Ϊ����ֵΪw�Ķ�����ڽӶ���
Status JudgeAdjvex(MGraph G, Vextype v, Vextype w)
{
	int vi, wi;
	vi = LocateVex(G, v);
	wi = LocateVex(G, w);
	if (-1 == vi || -1 == wi)return -1;
	if (G.vexs_num == 0 || NULL == G.vexs)return -1;
	if (G.arcs_num == 0)return false;
	if (UDG == G.G_kind && G.arcs[vi][wi] == 1)return true;
	else if (UDN == G.G_kind && G.arcs[vi][wi] != INFINITY)return true;
	else return false;
}


//13.�ж�ͼG�Ƿ�Ϊ��ͨͼ
Status JudgeConnected(MGraph G)
{
	if (G.vexs == NULL)return ERROR;
	if (G.vexs_num == 0)return false;
	int i;
	for (i = 0; i < G.vexs_num; i++)
		G.tags[i] = UNVISITED;
	if (DFS_ConnectedGraph(G, visit, 0) == ERROR)return ERROR;
	system("cls");
	for (i = 0; i < G.vexs_num; i++)
		if (G.tags[i] == UNVISITED)return false;
	return true;
}


//14.����ֵΪx�Ķ���Ķ���
int CountDegree(MGraph G, Vextype x)
{
	if (NULL == G.vexs)return -1;
	int v,i;
	if ((v = LocateVex(G, x)) < 0)return -1;
	int count = 0;
	for (i = FirstAdjvex(G, v); i >= 0; i = NextAdjvex(G, v, i))
		count++;
	return count;
}


//15.�ж�ͼG�Ƿ�Ϊ��ȫͼ
Status JudgeComplete(MGraph G)
{
	if (G.vexs_num == 0 || NULL == G.vexs || NULL == G.arcs)return false;
	int i, j;
	for (i = 0; i < G.vexs_num; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (UDN == G.G_kind && G.arcs[i][j] == INFINITY)return false;
			if (UDG == G.G_kind && G.arcs[i][j] == 0)return false;
		}
	}
	return true;
}

//16.����������Ȩͼ����ֵΪv�Ķ��㵽����ֵΪw�Ķ�������·�� 
int CountShortestRoad_UDG(MGraph G, Vextype v, Vextype w)
{
	if (G.vexs_num == 0 || NULL == G.vexs)return -1;
	int* D = (int*)malloc(G.vexs_num * sizeof(int));
	if (NULL == D)return OVERFLOW;
	int i, j;
	for (i = 0; i < G.vexs_num; i++)
		D[i] = INFINITY;
	for (i = 0; i < G.vexs_num; i++)
		G.tags[i] = UNVISITED;
	int vi, wi;
	vi = LocateVex(G, v);
	wi = LocateVex(G, w);
	if (vi < 0 || wi < 0)return -1;
	if (vi == wi)return 0;
	LQueue Q;
	InitQueue(Q,G.vexs_num);
	EnQueue(Q, vi);
	D[vi] = 0;
	G.tags[vi] = VISITED;
	while (OK == DeQueue(Q, j))
	{
		for (i = FirstAdjvex(G, j); i >= 0; i = NextAdjvex(G, j, i))
		{
			if (G.tags[i] == UNVISITED)
			{
				D[i] = D[j] + 1;
				G.tags[i] = VISITED;
				EnQueue(Q, i);
			}
		}
	}
	return D[wi];
}

//17.�ж�ֵΪv��ֵΪw����������Ƿ�ɴ�
Status JudgeReached(MGraph G, Vextype v, Vextype w)
{
	if (NULL == G.vexs)return -1;
	int reach;
	if (UDG == G.G_kind)reach = CountShortestRoad_UDG(G, v, w);
	if (UDN == G.G_kind)reach = CountShortestRoad_UDN(G, v, w);
	if (reach < 0)return -1;
	else if (reach == INFINITY)return false;
	else if (reach >= 0)return true;
}

//Dijkstra�㷨����Դ��i���㵽������������·��
Status Dijkstra(MGraph G, int i, DistInfo* &Dist)
{
	int j, k, min,m;
	Dist = (DistInfo*)malloc(sizeof(DistInfo)*G.vexs_num);
	if (NULL == Dist)return OVERFLOW;
	if (G.arcs == NULL)return -1;
	for (j = 0; j < G.vexs_num; j++)
	{
		G.tags[j] = UNVISITED;
		Dist[j].lowcast = INFINITY;
	}
	for (j = FirstAdjvex(G, i); j >= 0; j = NextAdjvex(G, i, j))
	{
		Dist[j].prev = i;
		Dist[j].lowcast = G.arcs[i][j];
	}                                                              //��ʼ��Dist����
	Dist[i].prev = -1; Dist[i].lowcast = 0; G.tags[i] = VISITED;   //��i��������·��
	for (j = 1; j < G.vexs_num; j++)
	{
		min = INFINITY; k = 0;           
		for (m = 0; m < G.vexs_num; m++)
		{
			if(UNVISITED == G.tags[m] && min > Dist[m].lowcast)
			{
				min = Dist[m].lowcast; k = m;
			}
		}
		G.tags[k] = VISITED;
		for (m = FirstAdjvex(G, k); m >= 0; m = NextAdjvex(G, k, m))
		{
			if (UNVISITED == G.tags[m] && (Dist[k].lowcast + G.arcs[k][m] < Dist[m].lowcast))
			{
				Dist[m].lowcast = Dist[k].lowcast + G.arcs[k][m];
				Dist[m].prev = k;
			}
		}
	}
	return OK;
}


//18.���������Ȩͼ����ֵΪv�Ķ��㵽����ֵΪw�Ķ�������·�� 
int CountShortestRoad_UDN(MGraph G, Vextype v, Vextype w)
{
	int i, j;
	i = LocateVex(G, v); j = LocateVex(G, w);
	if (i < 0 || j < 0 || G.vexs_num == 0)return -1;
	DistInfo* Dist = NULL;
	if (OK == Dijkstra(G, i, Dist))
	{
		int distance = Dist[j].lowcast;
		free(Dist);
		Dist = NULL;
		return distance;
	}
	else return -1;
}
