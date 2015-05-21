#ifndef LOTTERY_HPP
#define LOTTERY_HPP

#include <time.h>

using namespace std;///

template <typename Type>
Type interval_rand(Type a, Type b)//[a;b]
{
	return a + (b - a) * rand() / (RAND_MAX);
}
/*
0� �������= ������ ������ �������
1� �������= ����� �������+ ����� ���������� �������+...
2� -����(������� � �������)
3,4...-��������� �� ����� ����� ���������� ��������� �������
3� -�� ����� ����� ������� �������� � ��������� �����
(��������������� �� ���� ����������)

���� lottery[i][2]==0 - �� ���������
*/

void function_LOTTERY(long unsigned int **ALL, int SIZE)
{
	srand(time(NULL));

	FILE* log_lottery = fopen("log_lottery.txt", "w");

	long unsigned int ** lottery = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		lottery[j] = new long unsigned int[4];
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
		lottery[i][0] = ALL[i][0];// ������ ������ �������
		lottery[i][1] = 0;//����� �������+ ����� ���������� �������+...
		lottery[i][2] = 2;//����(������� � �������)
		lottery[i][3] = 0;//�� ����� ����� ������� �������� � ��������� �����
	}


	//����� ����� ��������� ������ ������� � ���������� �����
	//� �� ��� ����� ���������� ������ (��������� �������) ��� ����������
	long unsigned int *lottery_box = new long unsigned int [SIZE];
	
	int box_size = 0;

	///////////////////////////////////
//	int flag;
//	int flag1;
	int flag2 = 0;
while (done < SIZE)
{
		long unsigned int befor_TIME;

		box_size = 0;
		for (int i = 0, j = 0; i < SIZE; i++)
		{//for
			//�������� ������� � ���������� ������ � "���� ��� ���������"
			if (TIME >= ALL[i][0] && lottery[i][2] != 0 && TIME >= lottery[i][3])//����� �����������(��������� & �� ��������� &� ��������� ����� )
			{
				lottery_box[j] = i;//���������� ����� ������ � �������
				j++;
			}
			box_size = j;
		}//for


		if (box_size != 0)
		{//
			//����������� ��������� ����� �� 0 �� box_size (����������� ���������� �������)
			int i;//����� ����� ����������
			i = (int)interval_rand(0, box_size);
			//cout << i << "\t" << lottery_box[i] << "\t" << ALL[lottery_box[i]][0] << endl;

			i = lottery_box[i];//������ "���" ���������� (�.�. ����� ������� ���� ���������� ������ � ������� ALL)

			fprintf(log_lottery, "������� ������ %d (� %d) \n", lottery[i][0], i);

			if (lottery[i][2] % 2 == 0 )// �� ��������(���)
			// || ���� ������ ��������������� �������
			{///2
				befor_TIME = TIME;
				TIME += ALL[i][lottery[i][2]];
				lottery[i][1] += ALL[i][lottery[i][2]];//��������
				

				fprintf(log_lottery, "*������� ����(TIME)=%d\t befor_TIME=%d\tlottery[%d][0]=%d\tALL[%d][%d]=%d \n",
					TIME, befor_TIME, i, lottery[i][0], i, lottery[i][2], ALL[i][lottery[i][2]]);
				fprintf(log_lottery, "---------lottery[%d][3]=%d\n",
					i, lottery[i][3]);

				for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
				{//3
					if (TIME >= ALL[k][0] && lottery[k][2] != 0 && i != k && TIME >= lottery[k][3])//����� ����������� � �� ��������� � �� �������� ������� � ����������� ����������
					{////4
						if (befor_TIME <= ALL[k][0] && lottery[k][2] != 0)//���� � ����������� ���� ������ � ������
							//��. ��������� �� ����� ������ ������ �������
						{
							lottery[k][1] += TIME - lottery[k][0];//��������� ����
							//	cout << "TIME=" << TIME << "  befor_TIME=" << befor_TIME << "    for" << lottery[k][0]
							//		<< "   what +=" << TIME - lottery[k][0] << endl;
							fprintf(log_lottery, "���������(1���): ������� ����(TIME)=%d\tbefor_TIME=%d\tlottery[%d][0]=%d\t TIME-lottery[%d][0]=%d\n",
								TIME, befor_TIME, i, lottery[k][0], i, TIME - lottery[k][0]);
							fprintf(log_lottery, "---------lottery[%d][3]=%d\n",
								i, lottery[i][3]);
						}
						else if (lottery[k][2] != 0)
						{
							lottery[k][1] += ALL[i][lottery[i][2]];//��������� ����
							fprintf(log_lottery, "���������(2���): ������� ����(TIME)=%d\tbefor_TIME=%d\t for lottery[%d][0]=%d\t  this ALL[%d][%d]=%d from lottery[%d][0]=%d\n",
								TIME, befor_TIME, i, lottery[k][0], k, lottery[i][2], ALL[i][lottery[i][2]], i, lottery[i][0]);
							fprintf(log_lottery, "---------lottery[%d][3]=%d\n",
								i, lottery[i][3]);
						}
					}////4
				}//3
				lottery[i][2]++;

				if (lottery[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					lottery[i][2] = 0;
					done++;
					fprintf(log_lottery, "������� ����������� �����: ������� ����(TIME)=%d\t �������������(done)=%d ����; lottery[%d][0]=%d -  ���������\t    lottery[%d][2]=%d\n",
						TIME, done, i, lottery[i][0], i, lottery[i][2]);
					fprintf(log_lottery, "---------lottery[%d][3]=%d\n",
						i, lottery[i][3]);
				}
			}///2

			if (lottery[i][2] % 2 == 1)//��������(�����)
			{
				lottery[i][3] = TIME + ALL[i][lottery[i][2]];//����� ����, ����� ��������� ������� �������� � ��������� �����
				fprintf(log_lottery, "���� �� ������� ��������� %d lottery[%d][3]= %d + %d = %d\n",
					lottery[i][0], i, TIME, ALL[i][lottery[i][2]], lottery[i][3]);
				lottery[i][2]++;
			}
			
		
	}//if (box_size != 0)
	else if (box_size == 0)
	{
		TIME++;
		fprintf(log_lottery, "������ � ��������. ����� � ��������� ����� ���  ����� - ���, ������� ���� = %d \n", TIME);
		//+ � ���� ���� ���� ��� ����������� ������:
		for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
		{
			if (TIME >= ALL[k][0] && lottery[k][2] != 0)//��������� � �� ���������
				lottery[k][1] ++;
		}
		//+
	}
}
	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timelottery = 0;//�����  ����� ���� ������
	/*
	for (int i = 0; i < SIZE; i++)
	{
		cout << lottery[i][0] << "\t";
		cout << lottery[i][1] << "\t";
		cout << lottery[i][2] << "\t";
		cout << lottery[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timelottery += lottery[i][1];
	cout << "timelottery=" << timelottery << "taktov \n";


	////
	FILE* file = fopen("lottery.txt", "wt");
	{
		fprintf(file, "Time lottery: %d\n\nTime: \n", timelottery);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", lottery[i][0], lottery[i][1]);
	}
	fclose(file);
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] lottery[j];
	delete[] lottery;

	delete[] lottery_box;
	
	//--------------------------------------------
	fclose(log_lottery);
}
#endif 