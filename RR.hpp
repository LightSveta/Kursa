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
		RR[i][0] = ALL[i][0];// ������ ������ �������
		RR[i][1] = 0;//����� �������+ ����� ���������� �������+...
		RR[i][2] = 2;//����(������� � �������) �� ����� ������� ������������ ������\�� ����� ����� ���������� � ������ ������
		RR[i][3] = 0;//�� ����� ����� ������� �������� � ��������� �����
	}


	long unsigned int *waiting_list = new long unsigned int[SIZE];
	for (int i = 0; i < SIZE; i++)//����� ������ � �������
		waiting_list[i] = 0;

	int waiting = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (TIME >= ALL[i][0] && RR[i][2] != 0 && TIME >= RR[i][3])//����� �����������(��������� & �� ���������&� ��������� �����)
		{
			waiting_list[waiting] = i;// i -��� � �������� ALL
			waiting++;
		}

	}
	///////////////////////////////////
	//int flag;
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


	int befor_task = -1;//�ALL
	long unsigned int used_time = 0;


	while (done < SIZE)
	{
		long unsigned int befor_TIME;
		if (waiting != 0)
		{//5
			int allow_flag = allow_time;
			long unsigned int i = waiting_list[0];
			befor_task = i;
		
			fprintf(log_RR, "������:\n");
			for (int k = 0; k < waiting; k++)
				fprintf(log_RR, "     %d) ������%d, ���� �� ������� ���������:%d (%d)\n", k + 1, waiting_list[k], RR[waiting_list[k]][0], ALL[waiting_list[k]][0]);

			fprintf(log_RR, "������� ������ �%d (���� �� ������� ���������:%d) \n", i, RR[i][0]);

			if (RR[i][2] % 2 == 0)// �� ��������(���)
			{///2

			metka_goto:

				befor_task = i;
				befor_TIME = TIME;
				//TIME += ALL[i][RR[i][2]];
				//RR[i][1] += ALL[i][RR[i][2]];//��������
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
				else if (allow_time == ALL[i][RR[i][2]])
				{
					used_time = allow_time;//�������� ������ ���������� �����
					allow_flag = 4;//
				}
				fprintf(log_RR, "������� ����- %d  \n",
					TIME);
				TIME += used_time;
				
				RR[i][1] += used_time;

				flag = 1;//���� �������

				//���� ������� ������ �������� ����� ��������� ����� ������ ��� ���������������� ������
				for (int k = 0; k < SIZE; k++)
				{
					if (TIME >= ALL[k][0] && RR[k][2] != 0 && TIME >= RR[k][3])//����� �����������(��������� & �� ���������&� ��������� �����)
					{
						int flag_copy = 0;

						for (int j = 0; j < waiting; j++)
							if (waiting_list[j] == k)
								flag_copy++;

						if (flag_copy == 0)//���� ����� ��� ���
						{
							waiting_list[waiting] = k; //�������� � �����
							waiting++;
						}
					}
				}

				fprintf(log_RR, "�������� ������ �%d , ����������� �� %d �����,  �������� %d ������ (�� ����������� %d ) \n",
					i, RR[i][0], used_time, ALL[i][RR[i][2]]);
				fprintf(log_RR, "������� ����- %d  \n",
					TIME);
				//fprintf(log_RR, "			RR[%d][3]=%d \n",
				//	i, RR[i][3]);
				//fprintf(log_RR, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
				///	i, RR[i][0], RR[i][3]);

				for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
				{//3
					if (TIME >= ALL[k][0] && RR[k][2] != 0 && i != k && TIME >= RR[k][3])//����� ����������� � �� ��������� � �� �������� ������� � ����������� ����������
					{////4
						if (befor_TIME <= ALL[k][0] && RR[k][2] != 0)//���� � ����������� ���� ������ � ������
							//��. ��������� �� ����� ������ ������ �������
						{
							RR[k][1] += TIME - RR[k][0];//��������� ����
							fprintf(log_RR, "������ �%d , ����������� �� %d �����,  ���� %d ������ \n",
								k, RR[k][0], TIME - RR[k][0]);
							
						}
						else if (RR[k][2] != 0)
						{
							RR[k][1] += used_time;//��������� ����
							fprintf(log_RR, "������ �%d , ����������� �� %d �����,  ���� %d ������\n",
								k, RR[k][0], used_time);

							//fprintf(log_RR, "			RR[%d][3]=%d \n",
							//	i, RR[i][3]);
							//fprintf(log_RR, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
							//	i, RR[i][0], RR[i][3]);
						}
					}////4
				}//3

				if (allow_flag == 2)
				{
					ALL[i][RR[i][2]] -= allow_time;//����� ��������� ������ � ������ �����, �� ��������� ������ �������
				fprintf(log_RR, "������ �%d , ����������� �� %d �����, ����� ��������� ������ \n",
					i, RR[i][0]);
				}
				if (allow_flag == 3)
				{
					fprintf(log_RR, "������ �%d , ����������� �� %d �����, ��������� \n",
						i, RR[i][0]);
					RR[i][2]++;// ���������
					
				}
				if (allow_flag == 4)
				{
					fprintf(log_RR, "������ �%d , ����������� �� %d �����, ��������� \n",
						i, RR[i][0]);
					RR[i][2]++;// ���������;
				}
				
				//RR[i][2]++;

				if (RR[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					RR[i][2] = 0;
					//��� ���  ������ ���������, �� y������ �� �������
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//�� 1 ������ ����� ������
					//�������� ��� �������� ����� �� 1(������� ����� ������������� ������)

					done++;
					//fprintf(log_RR, "������� ����������� �����: ������� ����(TIME)=%d\n �������������(done)=%d ���� (�� %d); RR[%d][0]=%d -  ���������\t    RR[%d][2]=%d\n",
					//	TIME, done, SIZE, i, RR[i][0], i, RR[i][2]);
					fprintf(log_RR, "���������  ������ �%d , ����������� �� %d �����) \n",
						i, RR[i][0]);
					fprintf(log_RR, "			RR[%d][3]=%d \n",
						i, RR[i][3]);
					//fprintf(log_RR, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
					//	i, RR[i][0], RR[i][3]);
				}
				else
				{
					//���� �� ��������� ������� �� ������
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//�� 1 ������ ����� ������
				}
			}///2

			if (RR[i][2] % 2 == 1)//��������(�����)
			{
				RR[i][3] = TIME + ALL[i][RR[i][2]];//����� ����, ����� ��������� ������� �������� � ��������� �����
				fprintf(log_RR, "���� �� ������� ��������� %d RR[%d][3]= %d + %d = %d\n",
					RR[i][0], i, TIME, ALL[i][RR[i][2]], RR[i][3]);
				fprintf(log_RR, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
					i, RR[i][0], RR[i][3]);
				RR[i][2]++;
			}

		if (flag == 0)
			{//8
				if (allow_flag == 2)
				{
					//��� �� � ����, ���������� ���, ���� ��� ������ �����, ������� � ������
					fprintf(log_RR, "(������ � ������ ������ ������� ������) \n");
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

		}//5
		else if (waiting == 0)
		{
			TIME++;
			fprintf(log_RR, "������ � ��������. ����� � ��������� ����� ���  ����� - ���, ������� ���� = %d \n", TIME);
			//+ � ���� ���� ���� ��� ����������� ������:
			for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
			{
				if (TIME >= ALL[k][0] && RR[k][2] != 0)//��������� � �� ���������
					RR[k][1] ++;
			}
			//���� ������ ����� ����� ��������� ����� ��� ���������������� ������
			for (int k = 0; k < SIZE; k++)
			{
				if (TIME >= ALL[k][0] && RR[k][2] != 0 && TIME >= RR[k][3])//����� �����������(��������� & �� ���������&� ��������� �����)
				{
					int flag_copy = 0;

					for (int j = 0; j < waiting; j++)
						if (waiting_list[j] == k)
							flag_copy++;

					if (flag_copy == 0)//���� ����� ��� ���
					{
						waiting_list[waiting] = k; //�������� � �����
						waiting++;
					}
				}
			}
			//+
		}
		fprintf(log_RR, "***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t\n\n");

	}
	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeRR = 0;//�����  ����� ���� ������
	/*
	for (int i = 0; i < SIZE; i++)
	{
	cout << RR[i][0] << "\t";
	cout << RR[i][1] << "\t";
	cout << RR[i][2] << "\t";
	cout << RR[i][3] << "\n";
	}
	*/
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
	fprintf(log_RR, "��������� ��� ������.\n");
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] RR[j];
	delete[] RR;

	delete[] waiting_list;

	//--------------------------------------------
	fclose(log_RR);
}
#endif 