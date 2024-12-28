#include"undirected_graph.h"
int main()
{
	MGraph test_G1 = { NULL,NULL,0,0,NULL,UNDEFINED};   //��ʼ���ṹ�壬����Ұָ�����
	Vextype* test_vexs1 = NULL;  //���ԵĶ�������
	ArcInfo* test_arcs1 = NULL;  //���Եı���Ϣ����
	MGraph G = { NULL,NULL,0,0,NULL,UNDEFINED}; 
	int test_n1=0, test_e1=0;        //���ԵĶ�����������
	int choice = 1;
	int x;
	while (choice!=0)
	{
		menu();
		printf("���������ѡ��");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Init_test(test_n1, test_e1, test_vexs1, test_arcs1, test_G1);
			if (CreateGraph(G, test_G1.G_kind, test_vexs1, test_n1, test_arcs1, test_e1) == OK)
			{
				system("cls"); printf("�����ɹ�"); Sleep(1000);
			}
			else
			{
				system("cls"); printf("����ʧ��,�����´���"); Sleep(1000);
			}
			break;
			//1.�������һ������ͼ 
		case 2:
			system("cls");
			printf("��������ҵĶ���ֵ��");
			char case2;
			getchar();
			scanf("%c", &case2);
			getchar();
			if (-1 == LocateVex(G, case2))
				printf("����ʧ��");
			else
				printf("����ֵΪ%c�Ķ���λ����%d", case2, LocateVex(G, case2));
			break;
			//2.���Ҷ���ֵΪv��ͼG�е�λ�� 
		case 3:
			system("cls");
			printf("������һ����λ��");
			int case3;
			scanf("%d", &case3);
			if (-1 == FirstAdjvex(G, case3))
				printf("����ʧ��");
			else
				printf("%d����ĵ�һ���ڽӶ����λ����%d", case3, FirstAdjvex(G, case3));
			break;
			//3.��ͼG��k����ĵ�һ���ڽӶ����λ�� 
		case 4:
			system("cls");
			printf("������һ����λ��");
			int case4;
			Vextype w4;
			scanf("%d", &case4);
			if (-1 == GetVex(G, case4, w4))
				printf("������󣬲��Ҵ���");
			else
				printf("%d�����ֵΪ��%c", case4, w4);
			break;
			//4.ȡͼG��k�����ֵ��w
		case 5:
			system("cls");
			int case5;
			Vextype w5;
			printf("�����븳ֵ�����λ��");
			scanf("%d", &case5);
			printf("�����븳ֵ��");
			getchar();
			scanf("%c", &w5);
			int ans;
			ans = PutVex(G, case5, w5);
			if (-1 == ans)
			{printf("��ֵʧ�ܣ��������");}
			else if (false == ans)
			{	printf("��ֵʧ�ܣ�ͼ���Ѻ���ֵ%c", w5);}
			else
			{
				printf("��ֵ�ɹ�");
			}
			break;
			//5.��ͼG��k���㸳ֵw  
		case 6:
			system("cls");
			int case6_1, case6_2, nextadj;
			case6_1 = case6_2 = -1;
			printf("������λ��");
			scanf("%d", &case6_1);
			getchar();
			printf("������λ���һ���ڽӶ����λ��:");
			scanf("%d", &case6_2);
			getchar();
			nextadj = NextAdjvex(G, case6_1, case6_2);
			if (nextadj == -1)printf("��������ͼ��������");
			else if (nextadj == -2)printf("����һ���ڽӽ��");
			else
				printf("%d���������%d�������һ���ڽӶ����λ��%d", case6_1, case6_2, nextadj);
			break;
			//6.��ͼG��k���������m�������һ���ڽӶ����λ��
		case 7:
			system("cls");
			printf("������λ��1:");
			int case7_1, case7_2,info;
			info = -1;
			scanf("%d", &case7_1);
			printf("������λ��2:");
			scanf("%d", &case7_2);
			if (UDG == G.G_kind)info = 1;
			else if (UDN == G.G_kind)
			{
				printf("������Ȩֵ��");
				scanf("%d", &info);
			}
			int state6;
			state6 = AddArc(G, case7_1, case7_2, info);
			if (false == state6)
				printf("��������ͼ�������󣬼ӱ�ʧ��");
			else if (-1 == state6)
				printf("ͼ���Ѻ���%d�����%d����ı�", case7_1, case7_2);
			else 
				printf("�ӱ߳ɹ�");
			break;
			//7.��ͼG������k���㵽m����ı� 
		case 8:
			system("cls");
			printf("������λ��1:");
			int case8_1, case8_2;
			scanf("%d", &case8_1);
			printf("������λ��2:");
			scanf("%d", &case8_2);
			int state7;
			state7 = DeleteArc(G, case8_1, case8_2);
			if (false == state7)
				printf("�����д����ͼ��������ɾ��ʧ��");
			else if (-1 == state7)
				printf("ͼ��%d�����%d����֮�䲻���ڱ�", case8_1, case8_2);
			else
				printf("ɾ�߳ɹ�");
			break;
			//8.��ͼG��ɾ��k���㵽m����ı�   
		case 9:
			system("cls");
			DestroyGraph(G);
			printf("���ٳɹ�");
			break;
			//9.����ͼG 
		case 10:
			system("cls");
			if (false == DFSTraverse(G, visit))
				printf("����ʧ��");
			else
				printf("\n�����ɹ�");
			break;
			//10.��ͼ��������ȱ���
		case 11:
			system("cls");
			if (false == BFSTraverse(G, visit))
				printf("\n����ʧ��");
			else
				printf("\n�����ɹ�");
			break;
			//11.������ȱ���
		case 12:
			system("cls");
			Vextype case12_1, case12_2;
			printf("�����붥��ֵ1��");
			getchar();
			scanf("%c", &case12_1);
			printf("�����붥��ֵ2��");
			getchar();
			scanf("%c", &case12_2);
			getchar();
			if (-1 == JudgeAdjvex(G, case12_1, case12_2))
				printf("�������");
			else if (false == JudgeAdjvex(G, case12_1, case12_2))
				printf("%c����%c���ڽӶ���", case12_1, case12_2);
			else
				printf("%c��%c���ڽӶ���", case12_1, case12_2);
			break;
			//12.�ж϶���ֵΪv�Ķ����Ƿ�Ϊ����ֵΪw�Ķ�����ڽӶ���
		case 13:
			system("cls");
			if (false == JudgeConnected(G))
				printf("��ͼ������ͨͼ");
			else
				printf("��ͼ����ͨͼ");
			break;
			//13.�ж�ͼG�Ƿ�Ϊ��ͨͼ  
		case 14:
			system("cls");
			Vextype case14;
			printf("�����붥��ֵ��");
			getchar();
			scanf("%c", &case14);
			getchar();
			if (-1 == CountDegree(G, case14))
				printf("�������");
			else
				printf("%c�Ķ���Ϊ%d", case14, CountDegree(G, case14));
			break;
			//14.����ֵΪx�Ķ���Ķ���  
		case 15:
			system("cls");
			if (false == JudgeComplete(G))
				printf("��ͼ������ȫͼ");
			else
				printf("��ͼ����ȫͼ");
			break;
			//15.�ж�ͼG�Ƿ�Ϊ��ȫͼ
		case 16:
			system("cls");
			Vextype case16_1, case16_2;
			printf("�����붥��ֵ1:");
			getchar();
			scanf("%c", &case16_1);
			getchar();
			printf("�����붥��ֵ2:");
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
			if (Dist < 0)printf("������������ͼ��������");
			else if (Dist == INFINITY)printf("%c��%c֮�䲻�������·��", case16_1, case16_2);
			else
				printf("%c��%c�����·����%d", case16_1, case16_2, Dist);
			break;
			//16.���㶥��ֵΪv�Ķ��㵽����ֵΪw�Ķ�������·�� 
		case 17:
			system("cls");
			Vextype case17_1, case17_2;
			printf("�����붥��ֵ1:");
			getchar();
			scanf("%c", &case17_1);
			getchar();
			printf("�����붥��ֵ2:");
			scanf("%c", &case17_2);
			getchar();
			if (-1 == JudgeReached(G, case17_1, case17_2))
				printf("�������");
			else if (false == JudgeReached(G, case17_1, case17_2))
				printf("%c��%c�ǲ��ɴ��", case17_1, case17_2);
			else
				printf("%c��%c�ǿɴ��", case17_1, case17_2);
			break;
			//17.�ж�ֵΪv��ֵΪw����������Ƿ�ɴ�
		case 18:
			system("cls");
			if (test_G1.G_kind == UDG)printf("ͼ������(����):������Ȩͼ\n");
			if (test_G1.G_kind == UDN)printf("ͼ������(����):�����Ȩͼ\n");
			printf("����ֵ(����)��");
			printvexs(test_vexs1,test_n1);
			printf("����ĸ���(����)��");
			printf("%d", test_n1);
			printf("\n");
			printf("�ߵ�����(����)��");
			printf("%d", test_e1);
			printf("\n");
			int i;
			printf("�ߵĹ�ϵ(����):\n");
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
					printf("Ȩֵ��%d", test_arcs1[i].info);
					printf("\n");
				}
			}
			printf("\n���س�������....");
			getchar();
			getchar();
			break;
			//��ʾtest_G1����Ϣ
		case 19:
			system("cls");
			if (OK == ScanfAndCreate_Graph(G))
			{
				system("cls"); printf("�����ɹ�"); Sleep(750);
			}
			else
			{
				system("cls"); printf("����ʧ��,�����´���"); Sleep(750);
			}
			break;
			//�Լ�����ͼ
		case 20:
			system("cls");
			if (G.G_kind == UDG)printf("ͼ������:������Ȩͼ\n");
			if (G.G_kind == UDN)printf("ͼ������:�����Ȩͼ\n");
			printf("ͼ�Ķ���ֵ��");
			printvexs(G.vexs,G.vexs_num);
			printf("���������%d\n", G.vexs_num);
			printf("ͼ�ıߵ�������");
			printf("%d", G.arcs_num);
			printf("\n");
			printf("ͼ���ڽӾ���");
			printadj_marix(G);
			PrintGraph(G);
			printf("\n���س�������....");
			getchar();
			getchar();
			break;
			//��ʾͼG����Ϣ
		default:
			system("cls");break;
		}
	}
	system("pause");
}
