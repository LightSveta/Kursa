#ifndef SJN_HPP
#define SJN_HPP

#include <time.h>

using namespace std;///

/*
0� �������= ������ ������ �������
1� �������= ����� �������+ ����� ���������� �������+...
2� -����(������� � �������)
3,4...-��������� �� ����� ����� ���������� ��������� �������
3� -�� ����� ����� ������� �������� � ��������� �����
(��������������� �� ���� ����������)

���� SJN[i][2]==0 - �� ���������
*/

void function_SJN(long unsigned int **ALL, int SIZE)
{
	FILE* log_SJN = fopen("log_SJN.txt", "w");

	long unsigned int ** SJN = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		SJN[j] = new long unsigned int[4];
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
		SJN[i][0] = ALL[i][0];// ������ ������ �������
		SJN[i][1] = 0;//����� �������+ ����� ���������� �������+...
		SJN[i][2] = 2;//����(������� � �������)
		SJN[i][3] = 0;//�� ����� ����� ������� �������� � ��������� �����
	}


	long unsigned int **SJN_box = new long unsigned int*[SIZE];
	for (int i = 0; i < SIZE; i++)
		SJN_box[i] = new long unsigned int[2];

	for (int i = 0; i < SIZE; i++)
	{
		SJN_box[i][0] = 0;//����� ������ � �������
		SJN_box[i][1] = 0;//����������� �����
	}

	int box_size = 0;

	///////////////////////////////////
//	int flag;
	//int flag1;
	int flag2 = 0;
	while (done < SIZE)
	{
		long unsigned befor_TIME;

		box_size = 0;
		/*	for (long unsigned int i = 0; i < SIZE; i++)
	{
	long unsigned int s=0;
	for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j+=2)
	{
	s += ALL_COMMANDS[i][j];
	}
	cout << i << " " << ALL_COMMANDS[i][0] << " " << s << endl;
	s = 0;
	}*/
		for ( int i = 0, k = 0; i < SIZE; i++)
		{
			if (TIME >= ALL[i][0] && SJN[i][2] != 0 && TIME >= SJN[i][3])//����� �����������(��������� & �� ��������� &� ��������� ����� )
			{//���������� ����� ������ ������� � ������
				SJN_box[k][1] = 0;//������ ������ ������
				for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL[i][1]); j += 2)
				{
					SJN_box[k][0] = i; //����� ������ � �������
					SJN_box[k][1] += ALL[i][j];//����� ��������� ������ ������ �� ����������
				}
				k++;
				box_size++;
			}
		}
		if (box_size != 0)
	{//5
		//���� ������ �� ����������� ������ � ���������� ��������
		long unsigned int i = SJN_box[0][0];
		long unsigned int min = SJN_box[0][1];
		for (int k = 1; k < box_size; k++)
		{
			if (SJN_box[k][1] < min)
			{
				min = SJN_box[k][1];//���� ����������� �����
				i = SJN_box[k][0];//���� ����� � ������� ���� ������
			}
		}


		for (int k = 0; k < box_size; k++)
			fprintf(log_SJN, "		%d	%d=%d	%d \n", SJN_box[k][0], SJN[SJN_box[k][0]][0], ALL[SJN_box[k][0]][0], SJN_box[k][1]);


		//����� �������, i-����� ������ � ������� ALL,
		//��������� ������ ����� ������� �� ����������,
		//�� ����� ������� � ������ �� ������ ����

		fprintf(log_SJN, "������� ������ %d (� %d) \n", SJN[i][0], i);

		if (SJN[i][2] % 2 == 0)// �� ��������(���)
		{///2
			befor_TIME = TIME;
			TIME += ALL[i][SJN[i][2]];
			SJN[i][1] += ALL[i][SJN[i][2]];//��������

			fprintf(log_SJN, "*������� ����(TIME)=%d\t befor_TIME=%d\tSJN[%d][0]=%d\tALL[%d][%d]=%d \n",
				TIME, befor_TIME, i, SJN[i][0], i, SJN[i][2], ALL[i][SJN[i][2]]);
			fprintf(log_SJN, "---------SJN[%d][3]=%d\n",
				i, SJN[i][3]);

			for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
			{//3
				if (TIME >= ALL[k][0] && SJN[k][2] != 0 && i != k && TIME >= SJN[k][3])//����� ����������� � �� ��������� � �� �������� ������� � ����������� ����������
				{////4
					if (befor_TIME <= ALL[k][0] && SJN[k][2] != 0)//���� � ����������� ���� ������ � ������
						//��. ��������� �� ����� ������ ������ �������
					{
						SJN[k][1] += TIME - SJN[k][0];//��������� ����
						//	cout << "TIME=" << TIME << "  befor_TIME=" << befor_TIME << "    for" << SJN[k][0]
						//		<< "   what +=" << TIME - SJN[k][0] << endl;
						fprintf(log_SJN, "���������(1���): ������� ����(TIME)=%d\tbefor_TIME=%d\tSJN[%d][0]=%d\t TIME-SJN[%d][0]=%d\n",
							TIME, befor_TIME, i, SJN[k][0], i, TIME - SJN[k][0]);
						fprintf(log_SJN, "---------SJN[%d][3]=%d\n",
							i, SJN[i][3]);
					}
					else if (SJN[k][2] != 0)
					{
						SJN[k][1] += ALL[i][SJN[i][2]];//��������� ����
						fprintf(log_SJN, "���������(2���): ������� ����(TIME)=%d\tbefor_TIME=%d\t for SJN[%d][0]=%d\t  this ALL[%d][%d]=%d from SJN[%d][0]=%d\n",
							TIME, befor_TIME, i, SJN[k][0], k, SJN[i][2], ALL[i][SJN[i][2]], i, SJN[i][0]);
						fprintf(log_SJN, "---------SJN[%d][3]=%d\n",
							i, SJN[i][3]);
					}
				}////4
			}//3
			SJN[i][2]++;

			if (SJN[i][2] >= 2 + (1 + 2 * ALL[i][1]))
			{
				SJN[i][2] = 0;
				done++;
				fprintf(log_SJN, "������� ����������� �����: ������� ����(TIME)=%d\t �������������(done)=%d ����; SJN[%d][0]=%d -  ���������\t    SJN[%d][2]=%d\n",
					TIME, done, i, SJN[i][0], i, SJN[i][2]);
				fprintf(log_SJN, "---------SJN[%d][3]=%d\n",
					i, SJN[i][3]);
			}
		}///2

		if (SJN[i][2] % 2 == 1)//��������(�����)
		{
			SJN[i][3] = TIME + ALL[i][SJN[i][2]];//����� ����, ����� ��������� ������� �������� � ��������� �����
			fprintf(log_SJN, "���� �� ������� ��������� %d SJN[%d][3]= %d + %d = %d\n",
				SJN[i][0], i, TIME, ALL[i][SJN[i][2]], SJN[i][3]);
			SJN[i][2]++;
		}
	}//5
	else if (box_size == 0)
	{
		TIME++;
		fprintf(log_SJN, "������ � ��������. ����� � ��������� ����� ���  ����� - ���, ������� ���� = %d \n", TIME);
		//+ � ���� ���� ���� ��� ����������� ������:
		for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
		{
			if (TIME >= ALL[k][0] && SJN[k][2] != 0)//��������� � �� ���������
				SJN[k][1] ++;
		}
		//+
	}
}
	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeSJN = 0;//�����  ����� ���� ������
	/*
	for (int i = 0; i < SIZE; i++)
	{
		cout << SJN[i][0] << "\t";
		cout << SJN[i][1] << "\t";
		cout << SJN[i][2] << "\t";
		cout << SJN[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timeSJN += SJN[i][1];
	cout << "timeSJN=" << timeSJN << "taktov \n";


	////
	FILE* file = fopen("SJN.txt", "wt");
	{
		fprintf(file, "Time SJN: %d\n\nTime: \n", timeSJN);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", SJN[i][0], SJN[i][1]);
	}
	fclose(file);
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] SJN[j];
	delete[] SJN;

	for (int j = 0; j < SIZE; j++)
		delete[] SJN_box[j];
	delete[] SJN_box;

	//--------------------------------------------
	fclose(log_SJN);
}
#endif 