#ifndef FCFS_HPP
#define FCFS_HPP

#include <time.h>

using namespace std;///

/*
0� �������= ������ ������ �������
1� �������= ����� �������+ ����� ���������� �������+...
2� -����(������� � �������)
3,4...-��������� �� ����� ����� ���������� ��������� �������
3� -�� ����� ����� ������� �������� � ��������� �����
(��������������� �� ���� ����������)

���� FCFS[i][2]==0 - �� ���������
*/

void function_FCFS(long unsigned int **ALL, int SIZE)
{
	FILE* log_FCFS = fopen("log_FCFS.txt", "w");

	long unsigned int ** FCFS = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFS[j] = new long unsigned int[4];
	/*
	0  1  2 3 4  5 6

	1   2 53 8 11 9 80
	72  1 45 1 24
	131 2 49 2 13 4 35
	215 1 70 2 25
	313 2 105 6 69 9 81
	341 1 28 9 53
	411 0 105
	471 4 37 5 10 3 67 1 94 2 103
	517 2 42 5 56 4 27
	559 3 33 8 83 4 45 9 27
	641 0 93
	717 1 22 8 103

	������ ������-��� ����� ������
	��������-����� ����������
	*/
	int done = 0;//������ ���������
	long unsigned int TIME = 1;//�� ����� ������ �����

	//int start = ALL[TIME][0];//���� ������ ������� �������
	//int t_pre = 0;//����� ���������� 
	//int t = ALL[TIME][3];//����� ������
	//i=[0;size];j=[3;(1+2*ALL[i][1])] j=j+2; 
	// 2<= t <  2 + (1 + 2 * ALL[i][1])
	// ��������� t: 1+ALL[i][1]

	for (int i = 0; i < SIZE; i++)
	{
		FCFS[i][0] = ALL[i][0];// ������ ������ �������
		FCFS[i][1] = 0;//����� �������+ ����� ���������� �������+...
		FCFS[i][2] = 2;//����(������� � �������) �� ����� ������� ������������ ������\�� ����� ����� ���������� � ������ ������
		FCFS[i][3] = 0;//�� ����� ����� ������� �������� � ��������� �����
	}


	long unsigned int *waiting_list = new long unsigned int[SIZE];
	for (int i = 0; i < SIZE; i++)//����� ������ � �������
		waiting_list[i] = 0;

	int waiting = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (TIME >= ALL[i][0] && FCFS[i][2] != 0 && TIME >= FCFS[i][3])//����� �����������(��������� & �� ���������&� ��������� �����)
		{
			waiting_list[waiting] = i;// i -��� � �������� ALL
			waiting++;
		}

	}
	///////////////////////////////////
	//int flag;

	while (done < SIZE)
	{
		long unsigned int befor_TIME;
		if (waiting != 0)
		{//5
			long unsigned int i = waiting_list[0];

			fprintf(log_FCFS, "������:\n");
			for (int k = 0; k < waiting; k++)
				fprintf(log_FCFS, "     %d) ������%d, ���� �� ������� ���������:%d (%d)\n", k + 1, waiting_list[k], FCFS[waiting_list[k]][0], ALL[waiting_list[k]][0]);

			// i-����� ������ � ������� ALL,
			//��������� ������ ����� ������� �� ����������,
			//�� ���� ����� ������� � ������ �� ������ ����

			fprintf(log_FCFS, "������� ������ �%d (���� �� ������� ���������:%d) \n", i, FCFS[i][0]);

			if (FCFS[i][2] % 2 == 0)// �� ��������(���)
			{///2
				befor_TIME = TIME;
				TIME += ALL[i][FCFS[i][2]];
				FCFS[i][1] += ALL[i][FCFS[i][2]];//��������

				//���� ������� ������ �������� ����� ��������� ����� ������ ��� ���������������� ������
				for (int k = 0; k < SIZE; k++)
				{
					if (TIME >= ALL[k][0] && FCFS[k][2] != 0 && TIME >= FCFS[k][3])//����� �����������(��������� & �� ���������&� ��������� �����)
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

				fprintf(log_FCFS, "*������� ����(TIME)=%d\t befor_TIME=%d\tFCFS[%d][0]=%d\tALL[%d][%d]=%d \n",
					TIME, befor_TIME, i, FCFS[i][0], i, FCFS[i][2], ALL[i][FCFS[i][2]]);
				fprintf(log_FCFS, "(�.� �������� ������ �%d , ����������� �� %d �����,  �������� %d ������) \n",
					i, FCFS[i][0], ALL[i][FCFS[i][2]]);
				fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
					i, FCFS[i][3]);
				fprintf(log_FCFS, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
					i, FCFS[i][0], FCFS[i][3]);

				for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
				{//3
					if (TIME >= ALL[k][0] && FCFS[k][2] != 0 && i != k && TIME >= FCFS[k][3])//����� ����������� � �� ��������� � �� �������� ������� � ����������� ����������
					{////4
						if (befor_TIME <= ALL[k][0] && FCFS[k][2] != 0)//���� � ����������� ���� ������ � ������
							//��. ��������� �� ����� ������ ������ �������
						{
							FCFS[k][1] += TIME - FCFS[k][0];//��������� ����
							fprintf(log_FCFS, "���������(1���): ������� ����(TIME)=%d\tbefor_TIME=%d\tFCFS[%d][0]=%d\t TIME-FCFS[%d][0]=%d\n",
								TIME, befor_TIME, i, FCFS[k][0], i, TIME - FCFS[k][0]);
							fprintf(log_FCFS, "(�.�  ������ �%d , ����������� �� %d �����,  ���� %d ������) \n",
								k, FCFS[k][0], TIME - FCFS[k][0]);
							fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
								i, FCFS[i][3]);
							fprintf(log_FCFS, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
								i, FCFS[i][0], FCFS[i][3]);
						}
						else if (FCFS[k][2] != 0)
						{
							FCFS[k][1] += ALL[i][FCFS[i][2]];//��������� ����
							fprintf(log_FCFS, "���������(2���): ������� ����(TIME)=%d\tbefor_TIME=%d\t for FCFS[%d][0]=%d\t  this ALL[%d][%d]=%d from FCFS[%d][0]=%d\n",
								TIME, befor_TIME, i, FCFS[k][0], k, FCFS[i][2], ALL[i][FCFS[i][2]], i, FCFS[i][0]);
							fprintf(log_FCFS, "(�.�  ������ �%d , ����������� �� %d �����,  ���� %d ������) \n",
								k, FCFS[k][0], ALL[i][FCFS[i][2]]);

							fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
								i, FCFS[i][3]);
							fprintf(log_FCFS, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
								i, FCFS[i][0], FCFS[i][3]);
						}
					}////4
				}//3
				FCFS[i][2]++;

				if (FCFS[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					FCFS[i][2] = 0;

					//��� ���  ������ ���������, �� y������ �� �������
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//�� 1 ������ ����� ������
					//�������� ��� �������� ����� �� 1(������� ����� ������������� ������)

					done++;
					fprintf(log_FCFS, "������� ����������� �����: ������� ����(TIME)=%d\n �������������(done)=%d ���� (�� %d); FCFS[%d][0]=%d -  ���������\t    FCFS[%d][2]=%d\n",
						TIME, done, SIZE, i, FCFS[i][0], i, FCFS[i][2]);
					fprintf(log_FCFS, "(�.� ���������  ������ �%d , ����������� �� %d �����) \n",
						i, FCFS[i][0]);
					fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
						i, FCFS[i][3]);
					fprintf(log_FCFS, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
						i, FCFS[i][0], FCFS[i][3]);
				}
				else
				{
					//���� �� ��������� ������� �� ������
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//�� 1 ������ ����� ������
				}
			}///2

			if (FCFS[i][2] % 2 == 1)//��������(�����)
			{
				FCFS[i][3] = TIME + ALL[i][FCFS[i][2]];//����� ����, ����� ��������� ������� �������� � ��������� �����
				fprintf(log_FCFS, "���� �� ������� ��������� %d FCFS[%d][3]= %d + %d = %d\n",
					FCFS[i][0], i, TIME, ALL[i][FCFS[i][2]], FCFS[i][3]);
				fprintf(log_FCFS, "(�.� ������ �%d , ����������� �� %d �����, ������������� �� ����� %d ) \n",
					i, FCFS[i][0], FCFS[i][3]);
				FCFS[i][2]++;
			}

		}//5
		else if (waiting == 0)
		{
			TIME++;
			fprintf(log_FCFS, "������ � ��������. ����� � ��������� ����� ���  ����� - ���, ������� ���� = %d \n", TIME);
			//+ � ���� ���� ���� ��� ����������� ������:
			for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
			{
				if (TIME >= ALL[k][0] && FCFS[k][2] != 0)//��������� � �� ���������
					FCFS[k][1] ++;
			}
			//���� ������ ����� ����� ��������� ����� ��� ���������������� ������
			for (int k = 0; k < SIZE; k++)
			{
				if (TIME >= ALL[k][0] && FCFS[k][2] != 0 && TIME >= FCFS[k][3])//����� �����������(��������� & �� ���������&� ��������� �����)
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
		fprintf(log_FCFS, "***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t\n\n");

	}
	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeFCFS = 0;//�����  ����� ���� ������
	/*
	for (int i = 0; i < SIZE; i++)
	{
	cout << FCFS[i][0] << "\t";
	cout << FCFS[i][1] << "\t";
	cout << FCFS[i][2] << "\t";
	cout << FCFS[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timeFCFS += FCFS[i][1];
	cout << "timeFCFS=" << timeFCFS << "taktov \n";


	////
	FILE* file = fopen("FCFS.txt", "wt");
	{
		fprintf(file, "Time FCFS: %d\n\nTime: \n", timeFCFS);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", FCFS[i][0], FCFS[i][1]);
	}
	fclose(file);
	fprintf(log_FCFS, "��������� ��� ������.\n");
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] FCFS[j];
	delete[] FCFS;

	delete[] waiting_list;

	//--------------------------------------------
	fclose(log_FCFS);
}
#endif 