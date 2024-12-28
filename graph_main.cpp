#include"undirected_graph.h"
int main()
{
	MGraph test_G1 = { NULL,NULL,0,0,NULL,UNDEFINED};   //初始化结构体，避免野指针出现
	Vextype* test_vexs1 = NULL;  //测试的顶点数组
	ArcInfo* test_arcs1 = NULL;  //测试的边信息数组
	MGraph G = { NULL,NULL,0,0,NULL,UNDEFINED}; 
	int test_n1=0, test_e1=0;        //测试的顶点数，边数
	int choice = 1;
	int x;
	while (choice!=0)
	{
		menu();
		printf("请输入测试选择：");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Init_test(test_n1, test_e1, test_vexs1, test_arcs1, test_G1);
			if (CreateGraph(G, test_G1.G_kind, test_vexs1, test_n1, test_arcs1, test_e1) == OK)
			{
				system("cls"); printf("创建成功"); Sleep(1000);
			}
			else
			{
				system("cls"); printf("创建失败,请重新创建"); Sleep(1000);
			}
			break;
			//1.随机创建一个无向图 
		case 2:
			system("cls");
			printf("请输入查找的顶点值：");
			char case2;
			getchar();
			scanf("%c", &case2);
			getchar();
			if (-1 == LocateVex(G, case2))
				printf("查找失败");
			else
				printf("顶点值为%c的顶点位序是%d", case2, LocateVex(G, case2));
			break;
			//2.查找顶点值为v在图G中的位序 
		case 3:
			system("cls");
			printf("请输入一整数位序：");
			int case3;
			scanf("%d", &case3);
			if (-1 == FirstAdjvex(G, case3))
				printf("查找失败");
			else
				printf("%d顶点的第一个邻接顶点的位序是%d", case3, FirstAdjvex(G, case3));
			break;
			//3.求图G中k顶点的第一个邻接顶点的位序 
		case 4:
			system("cls");
			printf("请输入一整数位序：");
			int case4;
			Vextype w4;
			scanf("%d", &case4);
			if (-1 == GetVex(G, case4, w4))
				printf("输入错误，查找错误");
			else
				printf("%d顶点的值为：%c", case4, w4);
			break;
			//4.取图G的k顶点的值到w
		case 5:
			system("cls");
			int case5;
			Vextype w5;
			printf("请输入赋值顶点的位序：");
			scanf("%d", &case5);
			printf("请输入赋值：");
			getchar();
			scanf("%c", &w5);
			int ans;
			ans = PutVex(G, case5, w5);
			if (-1 == ans)
			{printf("赋值失败，输入错误");}
			else if (false == ans)
			{	printf("赋值失败，图中已含有值%c", w5);}
			else
			{
				printf("赋值成功");
			}
			break;
			//5.对图G的k顶点赋值w  
		case 6:
			system("cls");
			int case6_1, case6_2, nextadj;
			case6_1 = case6_2 = -1;
			printf("请输入位序：");
			scanf("%d", &case6_1);
			getchar();
			printf("请输入位序的一个邻接顶点的位序:");
			scanf("%d", &case6_2);
			getchar();
			nextadj = NextAdjvex(G, case6_1, case6_2);
			if (nextadj == -1)printf("输入错误或图发生错误");
			else if (nextadj == -2)printf("无下一个邻接结点");
			else
				printf("%d顶点相对于%d顶点的下一个邻接顶点的位序：%d", case6_1, case6_2, nextadj);
			break;
			//6.求图G中k顶点相对于m顶点的下一个邻接顶点的位序
		case 7:
			system("cls");
			printf("请输入位序1:");
			int case7_1, case7_2,info;
			info = -1;
			scanf("%d", &case7_1);
			printf("请输入位序2:");
			scanf("%d", &case7_2);
			if (UDG == G.G_kind)info = 1;
			else if (UDN == G.G_kind)
			{
				printf("请输入权值：");
				scanf("%d", &info);
			}
			int state6;
			state6 = AddArc(G, case7_1, case7_2, info);
			if (false == state6)
				printf("输入错误或图发生错误，加边失败");
			else if (-1 == state6)
				printf("图中已含有%d顶点和%d顶点的边", case7_1, case7_2);
			else 
				printf("加边成功");
			break;
			//7.在图G中增加k顶点到m顶点的边 
		case 8:
			system("cls");
			printf("请输入位序1:");
			int case8_1, case8_2;
			scanf("%d", &case8_1);
			printf("请输入位序2:");
			scanf("%d", &case8_2);
			int state7;
			state7 = DeleteArc(G, case8_1, case8_2);
			if (false == state7)
				printf("输入有错误或图发生错误，删边失败");
			else if (-1 == state7)
				printf("图中%d顶点和%d顶点之间不存在边", case8_1, case8_2);
			else
				printf("删边成功");
			break;
			//8.在图G中删除k顶点到m顶点的边   
		case 9:
			system("cls");
			DestroyGraph(G);
			printf("销毁成功");
			break;
			//9.销毁图G 
		case 10:
			system("cls");
			if (false == DFSTraverse(G, visit))
				printf("遍历失败");
			else
				printf("\n遍历成功");
			break;
			//10.对图的深度优先遍历
		case 11:
			system("cls");
			if (false == BFSTraverse(G, visit))
				printf("\n遍历失败");
			else
				printf("\n遍历成功");
			break;
			//11.广度优先遍历
		case 12:
			system("cls");
			Vextype case12_1, case12_2;
			printf("请输入顶点值1：");
			getchar();
			scanf("%c", &case12_1);
			printf("请输入顶点值2：");
			getchar();
			scanf("%c", &case12_2);
			getchar();
			if (-1 == JudgeAdjvex(G, case12_1, case12_2))
				printf("输入错误");
			else if (false == JudgeAdjvex(G, case12_1, case12_2))
				printf("%c不是%c的邻接顶点", case12_1, case12_2);
			else
				printf("%c是%c的邻接顶点", case12_1, case12_2);
			break;
			//12.判断顶点值为v的顶点是否为顶点值为w的顶点的邻接顶点
		case 13:
			system("cls");
			if (false == JudgeConnected(G))
				printf("此图不是连通图");
			else
				printf("此图是连通图");
			break;
			//13.判断图G是否为连通图  
		case 14:
			system("cls");
			Vextype case14;
			printf("请输入顶点值：");
			getchar();
			scanf("%c", &case14);
			getchar();
			if (-1 == CountDegree(G, case14))
				printf("输入错误");
			else
				printf("%c的度数为%d", case14, CountDegree(G, case14));
			break;
			//14.计算值为x的顶点的度数  
		case 15:
			system("cls");
			if (false == JudgeComplete(G))
				printf("此图不是完全图");
			else
				printf("此图是完全图");
			break;
			//15.判断图G是否为完全图
		case 16:
			system("cls");
			Vextype case16_1, case16_2;
			printf("请输入顶点值1:");
			getchar();
			scanf("%c", &case16_1);
			getchar();
			printf("请输入顶点值2:");
			scanf("%c", &case16_2);
			getchar();
			int Dist;
			if (UDG == G.G_kind)
			{
				 Dist = CountShortestRoad_UDG(G, case16_1, case16_2);
			}
			if (UDN == G.G_kind)
			{
				Dist = CountShortestRoad_UDN(G, case16_1, case16_2);
			}
			if (Dist < 0)printf("输入错误或无向图发生错误");
			else if (Dist == INFINITY)printf("%c到%c之间不存在最短路径", case16_1, case16_2);
			else
				printf("%c到%c的最短路径是%d", case16_1, case16_2, Dist);
			break;
			//16.计算顶点值为v的顶点到顶点值为w的顶点的最短路径 
		case 17:
			system("cls");
			Vextype case17_1, case17_2;
			printf("请输入顶点值1:");
			getchar();
			scanf("%c", &case17_1);
			getchar();
			printf("请输入顶点值2:");
			scanf("%c", &case17_2);
			getchar();
			if (-1 == JudgeReached(G, case17_1, case17_2))
				printf("输入错误");
			else if (false == JudgeReached(G, case17_1, case17_2))
				printf("%c到%c是不可达的", case17_1, case17_2);
			else
				printf("%c到%c是可达的", case17_1, case17_2);
			break;
			//17.判断值为v和值为w的两个结点是否可达
		case 18:
			system("cls");
			if (test_G1.G_kind == UDG)printf("图的类型(测试):无向无权图\n");
			if (test_G1.G_kind == UDN)printf("图的类型(测试):无向带权图\n");
			printf("顶点值(测试)：");
			printvexs(test_vexs1,test_n1);
			printf("顶点的个数(测试)：");
			printf("%d", test_n1);
			printf("\n");
			printf("边的条数(测试)：");
			printf("%d", test_e1);
			printf("\n");
			int i;
			printf("边的关系(测试):\n");
			for (i = 0; i < test_e1; i++)
			{
				if (UDG == test_G1.G_kind && test_arcs1[i].info == 1)
				{
					printf(" %c ", test_arcs1[i].v);
					printf("------");
					printf(" %c ", test_arcs1[i].w);
					printf("\n");
				}
				if (UDN == test_G1.G_kind && test_arcs1[i].info != INFINITY)
				{
					printf(" %c ", test_arcs1[i].v);
					printf("------");
					printf(" %c ", test_arcs1[i].w);
					printf("权值：%d", test_arcs1[i].info);
					printf("\n");
				}
			}
			printf("\n按回车键继续....");
			getchar();
			getchar();
			break;
			//显示test_G1的信息
		case 19:
			system("cls");
			if (OK == ScanfAndCreate_Graph(G))
			{
				system("cls"); printf("创建成功"); Sleep(750);
			}
			else
			{
				system("cls"); printf("创建失败,请重新创建"); Sleep(750);
			}
			break;
			//自己创建图
		case 20:
			system("cls");
			if (G.G_kind == UDG)printf("图的类型:无向无权图\n");
			if (G.G_kind == UDN)printf("图的类型:无向带权图\n");
			printf("图的顶点值：");
			printvexs(G.vexs,G.vexs_num);
			printf("顶点个数：%d\n", G.vexs_num);
			printf("图的边的条数：");
			printf("%d", G.arcs_num);
			printf("\n");
			printf("图的邻接矩阵：");
			printadj_marix(G);
			PrintGraph(G);
			printf("\n按回车键继续....");
			getchar();
			getchar();
			break;
			//显示图G的信息
		default:
			system("cls");break;
		}
	}
	system("pause");
}
