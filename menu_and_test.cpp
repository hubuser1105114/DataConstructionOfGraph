#include"undirected_graph.h"

//测试选择菜单
void menu(void) {
	printf("\n\n\n\n\n");
	printf("\t*******************************************************************************************************\n");
	printf("\t**                                   测试面板                                                        **\n");
	printf("\t**   1.随机创建一个无向图                      2.查找顶点值为v在图G中的位序                          **\n");
	printf("\t**   3.求图G中k顶点的第一个邻接顶点的位序      4.取图G的k顶点的值到w                                 **\n");
	printf("\t**   5.对图G的k顶点赋值                        6.求图G中k顶点相对于m顶点的下一个邻接顶点的位序       **\n");
	printf("\t**   7.在图G中增加k顶点到m顶点的边             8.在图G中删除k顶点到m顶点的边                         **\n");
	printf("\t**   9.销毁图G                                 10.对图的深度优先遍历                                 **\n");
	printf("\t**   11.广度优先遍历                           12.判断顶点值为v的顶点是否为顶点值为w的顶点的邻接顶点 **\n");
	printf("\t**   13.判断图G是否为连通图                    14.计算值为x的顶点的度数                              **\n");
	printf("\t**   15.判断图G是否为完全图                    16.计算顶点值为v的顶点到顶点值为w的顶点的最短路径     **\n");
	printf("\t**   17.判断值为v和值为w的两个结点是否可达     18.显示随机生成的测试图                               **\n");
	printf("\t**   19.自定义创建一个图                       20.显示创建的图的信息                                 **\n");
	printf("\t**   0.退出                                                                                          **\n");
	printf("\t*******************************************************************************************************\n");
	printf("\t");
}


//对测试案例初始化,随机生成一个无向图
Status Init_test(int &n, int &e, Vextype* &test_vexs, ArcInfo* &test_arcs, MGraph &G)
{
	srand((unsigned)time(NULL));
	int i, j;
	n = 1 + rand() % 10;                                        //初始化至多10个元素,n=1~10
	e = rand() % (n + 1);                                       //初始化至多n条边,e=0~n
	G.G_kind = (Graphkind)(UDG + rand() % 2);                   //图的类型为无向无权图或无向带权图
	test_vexs = (Vextype*)malloc(n * sizeof(Vextype));
	if (NULL == test_vexs)return OVERFLOW;
	for (i = 0; i < n; i++)
	{
		test_vexs[i] = 'A' + rand() % ('Z' - 'A' + 1);          //初始化顶点的值
		for (j = 0; j < i; j++)
		{
			if (test_vexs[j] == test_vexs[i])
			{
				test_vexs[i] = 'a' + rand() % ('z' - 'a' + 1);  //有可能出现重复值的问题，此时再次随机赋值
				break;
			}
		}
	}
	if (0 == e)
	{
		test_arcs = NULL; return OK;                            //对简单图进行处理
	}
	test_arcs = (ArcInfo*)malloc(e * sizeof(ArcInfo));
	if (NULL == test_arcs)return OVERFLOW;
	for (i = 0; i < e; i++)                                     //初始化边信息
	{
		int v1, w1;
		v1 = rand() % n;                                       //v1=0~n-1
		w1 = rand() % n;                                       //w1=0~n-1
		test_arcs[i].v = test_vexs[v1];
		test_arcs[i].w = test_vexs[w1];
		if (UDG == G.G_kind)test_arcs[i].info = 1;
		if (UDN == G.G_kind)test_arcs[i].info = 1 + rand() % 9;    //权值1--9
	}
	return OK;
}

//依次显示所有结点值
void printvexs(Vextype* vexs,int num)
{
	if (NULL == vexs) { printf("无\n"); return; }
	for (int i = 0; i <num; i++)
		printf("%c",vexs[i]);
	printf("\n");
}

//显示邻接数组
void printadj_marix(MGraph G)
{
	int i, j;
	if (NULL == G.arcs) { printf("无\n"); return; }
	printf("\n");
	for (i = 0; i < G.vexs_num; i++)
	{
		for (j = 0; j < G.vexs_num; j++)
		{
			if(INFINITY != G.arcs[i][j])printf("%d  ", G.arcs[i][j]);
			if(INFINITY == G.arcs[i][j])printf("#  ");
		}
		printf("\n");
	}
}

//显示无向图G的关系
Status PrintGraph(MGraph G)
{
	printf("无向图G的关系：\n");
	if (G.arcs_num == 0 || G.vexs_num == 0 || NULL == G.arcs) { printf("无"); return OK; }
	int i, j, k;
	for (i = 0; i < G.vexs_num; i++)
	{
		for (j = 0; j <= i; j++)
		{
			if (UDG == G.G_kind && 1 == G.arcs[i][j])
			{
				printf(" %c ", G.vexs[i]);
				printf("-----");
				printf(" %c ", G.vexs[j]);
				printf("\n");
			}
			if (UDN == G.G_kind && INFINITY != G.arcs[i][j])
			{
				printf(" %c ", G.vexs[i]);
				printf("-----");
				printf(" %c ", G.vexs[j]);
				printf("   权值：%d", G.arcs[i][j]);
				printf("\n");
			}
		}
	}
	return OK;
}


//自己输入并创建一个无向图
Status ScanfAndCreate_Graph(MGraph &G)
{   //做一定的数值合法性检查
	system("cls");
	int choice = -1;
	printf("  0.无向无权图     1.无向带权图");
	printf("\n请选择创建的图的类型(输入序号)：");
	scanf("%d", &choice);
	getchar();
	if (choice == 1)G.G_kind = UDN;
	else if (choice == 0)G.G_kind = UDG;
	else return -1;
	printf("请输入结点个数:");
	int vnum = -1, anum = -1;
	scanf("%d", &vnum);
	getchar();                                                //吸收回车符
	Vextype* vexs = NULL;
	ArcInfo* arcs = NULL;
	vexs = (Vextype*)malloc(vnum*(sizeof(Vextype)));         //同时检查vnum的合法性,vnum必须>0
	if (NULL == vexs) { G.G_kind = UNDEFINED; return OVERFLOW; }
	if (0 != vnum)printf("请输入无向图的结点值(不得重复，范围在‘A’--‘Z’和‘a’--‘z’)：");
	for (int i = 0; i < vnum; i++)
	{
		scanf("%c", &vexs[i]);
		getchar();
	}                                                       //输入顶点值
	printf("请输入无向图的边的条数：");
	scanf("%d", &anum);
	getchar();                                              
	arcs = (ArcInfo*)malloc(anum * sizeof(ArcInfo));
	//if (NULL == arcs)return OVERFLOW;                       //同时检查anum的合法性
    printf("请输入%d条边的端点(不得重复，范围在‘A’--‘Z’和‘a’--‘z’,值之间用逗号隔开)\n", anum);
	for (int i = 0; i < anum; i++)
	{
		printf("请输入第%d条边：",i+1);
		scanf("%c,%c", &arcs[i].v, &arcs[i].w);
		getchar();
		if (UDN == G.G_kind)
		{
			int info = INFINITY;
			printf("权值(输入在1-9之间):");
			scanf("%d", &info);
			getchar();
			arcs[i].info = info;
			continue;
		}
		arcs[i].info = 1;
	}                                                       
	if (OK == CreateGraph(G,G.G_kind, vexs, vnum, arcs, anum))
		return OK;
	else
		return ERROR;
}

