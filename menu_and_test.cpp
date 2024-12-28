#include"undirected_graph.h"

//����ѡ��˵�
void menu(void) {
	printf("\n\n\n\n\n");
	printf("\t*******************************************************************************************************\n");
	printf("\t**                                   �������                                                        **\n");
	printf("\t**   1.�������һ������ͼ                      2.���Ҷ���ֵΪv��ͼG�е�λ��                          **\n");
	printf("\t**   3.��ͼG��k����ĵ�һ���ڽӶ����λ��      4.ȡͼG��k�����ֵ��w                                 **\n");
	printf("\t**   5.��ͼG��k���㸳ֵ                        6.��ͼG��k���������m�������һ���ڽӶ����λ��       **\n");
	printf("\t**   7.��ͼG������k���㵽m����ı�             8.��ͼG��ɾ��k���㵽m����ı�                         **\n");
	printf("\t**   9.����ͼG                                 10.��ͼ��������ȱ���                                 **\n");
	printf("\t**   11.������ȱ���                           12.�ж϶���ֵΪv�Ķ����Ƿ�Ϊ����ֵΪw�Ķ�����ڽӶ��� **\n");
	printf("\t**   13.�ж�ͼG�Ƿ�Ϊ��ͨͼ                    14.����ֵΪx�Ķ���Ķ���                              **\n");
	printf("\t**   15.�ж�ͼG�Ƿ�Ϊ��ȫͼ                    16.���㶥��ֵΪv�Ķ��㵽����ֵΪw�Ķ�������·��     **\n");
	printf("\t**   17.�ж�ֵΪv��ֵΪw����������Ƿ�ɴ�     18.��ʾ������ɵĲ���ͼ                               **\n");
	printf("\t**   19.�Զ��崴��һ��ͼ                       20.��ʾ������ͼ����Ϣ                                 **\n");
	printf("\t**   0.�˳�                                                                                          **\n");
	printf("\t*******************************************************************************************************\n");
	printf("\t");
}


//�Բ��԰�����ʼ��,�������һ������ͼ
Status Init_test(int &n, int &e, Vextype* &test_vexs, ArcInfo* &test_arcs, MGraph &G)
{
	srand((unsigned)time(NULL));
	int i, j;
	n = 1 + rand() % 10;                                        //��ʼ������10��Ԫ��,n=1~10
	e = rand() % (n + 1);                                       //��ʼ������n����,e=0~n
	G.G_kind = (Graphkind)(UDG + rand() % 2);                   //ͼ������Ϊ������Ȩͼ�������Ȩͼ
	test_vexs = (Vextype*)malloc(n * sizeof(Vextype));
	if (NULL == test_vexs)return OVERFLOW;
	for (i = 0; i < n; i++)
	{
		test_vexs[i] = 'A' + rand() % ('Z' - 'A' + 1);          //��ʼ�������ֵ
		for (j = 0; j < i; j++)
		{
			if (test_vexs[j] == test_vexs[i])
			{
				test_vexs[i] = 'a' + rand() % ('z' - 'a' + 1);  //�п��ܳ����ظ�ֵ�����⣬��ʱ�ٴ������ֵ
				break;
			}
		}
	}
	if (0 == e)
	{
		test_arcs = NULL; return OK;                            //�Լ�ͼ���д���
	}
	test_arcs = (ArcInfo*)malloc(e * sizeof(ArcInfo));
	if (NULL == test_arcs)return OVERFLOW;
	for (i = 0; i < e; i++)                                     //��ʼ������Ϣ
	{
		int v1, w1;
		v1 = rand() % n;                                       //v1=0~n-1
		w1 = rand() % n;                                       //w1=0~n-1
		test_arcs[i].v = test_vexs[v1];
		test_arcs[i].w = test_vexs[w1];
		if (UDG == G.G_kind)test_arcs[i].info = 1;
		if (UDN == G.G_kind)test_arcs[i].info = 1 + rand() % 9;    //Ȩֵ1--9
	}
	return OK;
}

//������ʾ���н��ֵ
void printvexs(Vextype* vexs,int num)
{
	if (NULL == vexs) { printf("��\n"); return; }
	for (int i = 0; i <num; i++)
		printf("%c",vexs[i]);
	printf("\n");
}

//��ʾ�ڽ�����
void printadj_marix(MGraph G)
{
	int i, j;
	if (NULL == G.arcs) { printf("��\n"); return; }
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

//��ʾ����ͼG�Ĺ�ϵ
Status PrintGraph(MGraph G)
{
	printf("����ͼG�Ĺ�ϵ��\n");
	if (G.arcs_num == 0 || G.vexs_num == 0 || NULL == G.arcs) { printf("��"); return OK; }
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
				printf("   Ȩֵ��%d", G.arcs[i][j]);
				printf("\n");
			}
		}
	}
	return OK;
}


//�Լ����벢����һ������ͼ
Status ScanfAndCreate_Graph(MGraph &G)
{   //��һ������ֵ�Ϸ��Լ��
	system("cls");
	int choice = -1;
	printf("  0.������Ȩͼ     1.�����Ȩͼ");
	printf("\n��ѡ�񴴽���ͼ������(�������)��");
	scanf("%d", &choice);
	getchar();
	if (choice == 1)G.G_kind = UDN;
	else if (choice == 0)G.G_kind = UDG;
	else return -1;
	printf("�����������:");
	int vnum = -1, anum = -1;
	scanf("%d", &vnum);
	getchar();                                                //���ջس���
	Vextype* vexs = NULL;
	ArcInfo* arcs = NULL;
	vexs = (Vextype*)malloc(vnum*(sizeof(Vextype)));         //ͬʱ���vnum�ĺϷ���,vnum����>0
	if (NULL == vexs) { G.G_kind = UNDEFINED; return OVERFLOW; }
	if (0 != vnum)printf("����������ͼ�Ľ��ֵ(�����ظ�����Χ�ڡ�A��--��Z���͡�a��--��z��)��");
	for (int i = 0; i < vnum; i++)
	{
		scanf("%c", &vexs[i]);
		getchar();
	}                                                       //���붥��ֵ
	printf("����������ͼ�ıߵ�������");
	scanf("%d", &anum);
	getchar();                                              
	arcs = (ArcInfo*)malloc(anum * sizeof(ArcInfo));
	//if (NULL == arcs)return OVERFLOW;                       //ͬʱ���anum�ĺϷ���
    printf("������%d���ߵĶ˵�(�����ظ�����Χ�ڡ�A��--��Z���͡�a��--��z��,ֵ֮���ö��Ÿ���)\n", anum);
	for (int i = 0; i < anum; i++)
	{
		printf("�������%d���ߣ�",i+1);
		scanf("%c,%c", &arcs[i].v, &arcs[i].w);
		getchar();
		if (UDN == G.G_kind)
		{
			int info = INFINITY;
			printf("Ȩֵ(������1-9֮��):");
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

