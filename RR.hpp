#ifndef RR_HPP
#define RR_HPP

#include "outmyfile.hpp"
using namespace std;///

void function_RR(int SIZE)
{

	long unsigned int ** ALL = new long unsigned int *[SIZE];
	ReadAllFile(ALL);

	FILE* log_RR = fopen("log_RR.txt", "w");

	long unsigned int ** RR = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		RR[j] = new long unsigned int[4];

	int done = 0;//������ ���������
	long unsigned int TIME = 1;//�� ����� ������ �����

	long unsigned int allow_time = 2;

	for (int i = 0; i < SIZE; i++)
	{
		RR[i][0] = ALL[i][0];
		RR[i][1] = 0;
		RR[i][2] = 2;
		RR[i][3] = 0;
	}

	///////////////////////////////////
	int flag;
	int flag1;
	int flag2 = 0;

	int allow_flag = 1;//
	//1-��� �� ��������� �������
	//0-��������� �����
	//2-  allow_time<ALL[i][RR[i][2]]//����� ��������� ������
	//3-  allow_time>ALL[i][RR[i][2]]// ��������
	//4-  allow_time==ALL[i][RR[i][2]]//�������� ������ ���������� �����
	

	int befor_task=-1;//�ALL
	long unsigned int used_time = 0;

	while (done < SIZE)
	{
		long unsigned int befor_TIME;
		flag = 0;//��� ������� ������
		flag1 = 0;//���� ������ ��������������� �������
		int allow_flag = allow_time;

		for (int i = 0; i < SIZE; i++)
		{	
			if (flag2 == 1) i = 0;//��� 1 ����� � ������ ������ 
			flag2 = 0;

			if (TIME >= ALL[i][0] && RR[i][2] != 0 && TIME >= RR[i][3] && befor_task!=i)//����� �����������(��������� & �� ��������� &� ��������� ����� )
			{//1
				if (RR[i][2] % 2 == 0 || flag1 == 0)// �� ��������(���)
				// || ���� ������ ��������������� �������
				{///2
		metka_goto:

					befor_TIME = TIME;
					befor_task = i;
					//���������� ������� ����� �������� ��������� ������
					if (allow_time<ALL[i][RR[i][2]])
					{	
						used_time = allow_time;//����� ��������� ������
						allow_flag = 2;//
					}
					else if (allow_time>ALL[i][RR[i][2]])
					{
						used_time = ALL[i][RR[i][2]];// ��������
						allow_flag = 3;//
					
					}
					else if (allow_time==ALL[i][RR[i][2]])
					{
						used_time = allow_time;//�������� ������ ���������� �����
						allow_flag = 4;//
					}

				TIME += used_time;
				RR[i][1] += used_time;

				flag = 1;//���� �������

					fprintf(log_RR, "*������� ����(TIME)=%d\t befor_TIME=%d\tRR[%d][0]=%d\tused_time=%d \n",
						TIME, befor_TIME, i, RR[i][0], i, RR[i][2], used_time);
					fprintf(log_RR, "---------RR[%d][3]=%d\n",
						i, RR[i][3]);
					flag2 = 1;

				for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
				{//3
					if (TIME >= ALL[k][0] && RR[k][2] != 0 && i != k && TIME >= RR[k][3])//����� ����������� � �� ��������� � �� �������� ������� � ����������� ����������
					{////4
						if (befor_TIME <= ALL[k][0] && RR[k][2] != 0)//���� � ����������� ���� ������ � ������
							//��. ��������� �� ����� ������ ������ �������
						{
							RR[k][1] += TIME - RR[k][0];//��������� ����
							fprintf(log_RR, "���������(1���): ������� ����(TIME)=%d\tbefor_TIME=%d\tRR[%d][0]=%d\t TIME-RR[%d][0]=%d\n",
								TIME, befor_TIME, i, RR[k][0], i, TIME - RR[k][0]);
							fprintf(log_RR, "---------RR[%d][3]=%d\n",
								i, RR[i][3]);
						}
						else if (RR[k][2] != 0)
						{
							RR[k][1] += used_time;//��������� ����
							
							fprintf(log_RR, "���������(2���): ������� ����(TIME)=%d\tbefor_TIME=%d\t for RR[%d][0]=%d\t  this used_time=%d from RR[%d][0]=%d\n",
								TIME, befor_TIME, i, RR[k][0], k, RR[i][2], used_time, i, RR[i][0]);
							fprintf(log_RR, "---------RR[%d][3]=%d\n",
								i, RR[i][3]);
						}
					}////4
				}//3

				if (allow_flag == 2)ALL[i][RR[i][2]] -= allow_time;//����� ��������� ������ � ������ �����, �� ��������� ������ �������
				if (allow_flag == 3)RR[i][2]++;// ���������
				if (allow_flag == 4)RR[i][2]++;// ���������;
				
					if (RR[i][2] % 2 == 0)
					{
						flag1 = 1;//?????????????
					}
					if (RR[i][2] >= 2 + (1 + 2 * ALL[i][1]))
					{
						RR[i][2] = 0;
						done++;
						fprintf(log_RR, "������� ����������� �����: ������� ����(TIME)=%d\t �������������(done)=%d ����; RR[%d][0]=%d -  ���������\t    RR[%d][2]=%d\n",
							TIME, done, i, RR[i][0], i, RR[i][2]);
						fprintf(log_RR, "---------RR[%d][3]=%d\n",
							i, RR[i][3]);
					}
				}
				///2
				if (RR[i][2] % 2 == 1)//��������(�����)
				{
					RR[i][3] = TIME + ALL[i][RR[i][2]];//����� ����, ����� ��������� ������� �������� � ��������� �����
					fprintf(log_RR, "���� �� ������� ��������� %d RR[%d][3]= %d + %d = %d\n",
						RR[i][0], i, TIME, used_time, RR[i][3]);
					RR[i][2]++;
					flag1 = 1;
				}
				i = 0;
			}//1
		}//for

		if (flag == 0)
		{//8
			if (allow_flag == 2)
			{
				//��� �� � ����, ���������� ���, ���� ��� ������ �����, ������� � ������
				goto metka_goto;
			}
			else//�� ������ ������� ���!
			{//7
				TIME++;
				fprintf(log_RR, "������ � ��������. ������� ���� = %d \n", TIME);
			
				//+ � ���� ���� ���� ��� ����������� ������:
				for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
				{
					if (TIME >= ALL[k][0] && RR[k][2] != 0)//��������� � �� ���������
						RR[k][1] ++;
				}
				//+
			}//7
		}//8
	}//while

	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeRR = 0;//�����  ����� ���� ������

	for (int i = 0; i < SIZE; i++)
	{
	cout << RR[i][0] << "\t";
	cout << RR[i][1] << "\t";
	cout << RR[i][2] << "\t";
	cout << RR[i][3] << "\n";
	}
	
	for (int i = 0; i < SIZE; i++)
		timeRR += RR[i][1];
	cout << "timeRR=" << timeRR << "taktov \n";


	////
	FILE* file = fopen("RR.txt", "wt");
	{
		fprintf(file, "Time RR: %d\n\nTime: \n", timeRR);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", RR[i][0], RR[i][1]);
	}
	fclose(file);
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] RR[j];
	delete[] RR;
	//--------------------------------------------
	fclose(log_RR);
}
#endif 