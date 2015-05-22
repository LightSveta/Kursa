#ifndef SRT_HPP
#define SRT_HPP

#include <time.h>
#include "outmyfile.hpp"

using namespace std;///

void function_SRT(int SIZE)
{
	long unsigned int ** ALL = new long unsigned int *[SIZE];
	ReadAllFile(ALL);

	FILE* log_SRT = fopen("log_SRT.txt", "w");

	long unsigned int ** SRT = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		SRT[j] = new long unsigned int[4];

	int done = 0;//������ ���������
	long unsigned int TIME = 1;//�� ����� ������ �����

	for (int i = 0; i < SIZE; i++)
	{
		SRT[i][0] = ALL[i][0];// ������ ������ �������
		SRT[i][1] = 0;//����� �������+ ����� ���������� �������+...
		SRT[i][2] = 2;//����(������� � �������)
		SRT[i][3] = 0;//�� ����� ����� ������� �������� � ��������� �����
	}

	long unsigned int *SRT_box = new long unsigned int[SIZE];
	for ( int i = 0; i < SIZE; i++)
		SRT_box[i] = 0;

	long unsigned int **ready_box = new long unsigned int*[SIZE];
	for (int i = 0; i < SIZE; i++)
		ready_box[i] = new long unsigned int[2];
	//SRT_box - ���������� ����� ������ ������ ������
	//ready_box - ���������� ����� ������ ������ ������� �������
	
	for (int i = 0; i < SIZE; i++)
	{
		for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL[i][1]); j += 2)
		{
			SRT_box[i] += ALL[i][j];//����� ��������� ������ ������ �� ����������
		}
		//cout <<"*"<< SRT_box[i] << endl;//////////////////////////
		ready_box[i][0] = 0;//����� ������ � �������
		ready_box[i][1] = 0;//����������� �����
	}


	int ready_box_size = 0;//��������� ������
	int SRT_box_size = SIZE;//��� �����������
	int allow_flag;

	///////////////////////////////////
//	int flag;
	//int flag1;
	int flag2 = 0;
	while (done < SIZE)
	{
		long unsigned int befor_TIME;

		ready_box_size = 0;
		
		for (int i = 0, k = 0; i < SIZE; i++)
		{
			if (TIME >= ALL[i][0] && SRT[i][2] != 0 && TIME >= SRT[i][3])//����� �����������(��������� & �� ��������� &� ��������� ����� )
			{//���������� ����� ������ ������� � ������
				ready_box[k][0] = i;
				ready_box[k][1] = SRT_box[i];
			//	cout << "***" << ready_box[k][0] << "  " << ready_box[k][1]<< endl;
				k++;
				ready_box_size++;
			}
		}
		if (ready_box_size != 0)
		{//5
			//���� ������ �� ����������� ������ � ���������� ���������� ��������
			long unsigned int i = ready_box[0][0];
			long unsigned int min = ready_box[0][1];
			for (int k = 1; k < ready_box_size; k++)
			{
				if (ready_box[k][1] < min)
				{
					min = ready_box[k][1];//���� ����������� �����
					i = ready_box[k][0];//���� ����� � ������� ���� ������
				}
			}

			for (int k = 0; k < ready_box_size; k++)
				fprintf(log_SRT, "		%d	%d=%d	%d \n", ready_box[k][0], SRT[ready_box[k][0]][0], ALL[ready_box[k][0]][0], ready_box[k][1]);

			//����� �������, i-����� ������ � ������� ALL,
			//��������� ������ ����� ������� �� ����������,
			//�� ����� ������� � ������ �� ������ ����

			fprintf(log_SRT, "������� ������ %d (� %d) \n", SRT[i][0], i);

			if (SRT[i][2] % 2 == 0)// �� ��������(���)
			{///2
				befor_TIME = TIME;
				TIME ++;
				SRT[i][1] ++;//��������
				SRT_box[i] -= 1;//��� ��� ��� �����������, �� �� ���������� ����� ������ ����������

				fprintf(log_SRT, "*������� ����(TIME)=%d\t befor_TIME=%d\tSRT[%d][0]=%d\tALL[%d][%d]=%d \n",
					TIME, befor_TIME, i, SRT[i][0], i, SRT[i][2], ALL[i][SRT[i][2]]);
				fprintf(log_SRT, "�������� ������ �%d , ����������� �� %d �����,  �������� 1 ���� (�� ����������� %d ) \n",
					i, SRT[i][0], ALL[i][SRT[i][2]]);

				
					ALL[i][SRT[i][2]] -= 1;//����� ��������� ������ � ������ �����
					fprintf(log_SRT, "������ �%d , ����������� �� %d �����, ����� ��������� ������ \n",
						i, SRT[i][0]);
				

				for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
				{//3
					if (TIME >= ALL[k][0] && SRT[k][2] != 0 && i != k && TIME >= SRT[k][3])//����� ����������� � �� ��������� � �� �������� ������� � ����������� ����������
					{////4
						if (befor_TIME <= ALL[k][0] && SRT[k][2] != 0)//���� � ����������� ���� ������ � ������
							//��. ��������� �� ����� ������ ������ �������
						{
							SRT[k][1] += TIME - SRT[k][0];//��������� ����
							fprintf(log_SRT, "���������(1���): ������� ����(TIME)=%d\tbefor_TIME=%d\tSRT[%d][0]=%d\t TIME-SRT[%d][0]=%d\n",
								TIME, befor_TIME, i, SRT[k][0], i, TIME - SRT[k][0]);
							fprintf(log_SRT, "---------SRT[%d][3]=%d\n",
								i, SRT[i][3]);
						}
						else if (SRT[k][2] != 0)
						{
							SRT[k][1] += ALL[i][SRT[i][2]];//��������� ����
							fprintf(log_SRT, "���������(2���): ������� ����(TIME)=%d\tbefor_TIME=%d\t for SRT[%d][0]=%d\t  this ALL[%d][%d]=%d from SRT[%d][0]=%d\n",
								TIME, befor_TIME, i, SRT[k][0], k, SRT[i][2], ALL[i][SRT[i][2]], i, SRT[i][0]);
							fprintf(log_SRT, "---------SRT[%d][3]=%d\n",
								i, SRT[i][3]);
						}
					}////4
				}//3
				//SRT[i][2]++;
				if (ALL[i][SRT[i][2]]==0)//��������� ���� ������ ������
					SRT[i][2]++;

				if (SRT[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					SRT[i][2] = 0;
					done++;
					fprintf(log_SRT, "������� ����������� �����: ������� ����(TIME)=%d\t �������������(done)=%d ����; SRT[%d][0]=%d -  ���������\t    SRT[%d][2]=%d\n",
						TIME, done, i, SRT[i][0], i, SRT[i][2]);
					fprintf(log_SRT, "---------SRT[%d][3]=%d\n",
						i, SRT[i][3]);
				}
			}///2

			if (SRT[i][2] % 2 == 1)//��������(�����)
			{
				SRT[i][3] = TIME + ALL[i][SRT[i][2]];//����� ����, ����� ��������� ������� �������� � ��������� �����
				fprintf(log_SRT, "���� �� ������� ��������� %d SRT[%d][3]= %d + %d = %d\n",
					SRT[i][0], i, TIME, ALL[i][SRT[i][2]], SRT[i][3]);
				SRT[i][2]++;
			}
		}//5
		else if (ready_box_size == 0)
		{
			TIME++;
			fprintf(log_SRT, "������ � ��������. ����� � ��������� ����� ���  ����� - ���, ������� ���� = %d \n", TIME);
			//+ � ���� ���� ���� ��� ����������� ������:
			for (int k = 0; k < SIZE; k++)//������ �� �������(����������� ����� ������������� ��������(������� � ����������))
			{
				if (TIME >= ALL[k][0] && SRT[k][2] != 0)//��������� � �� ���������
					SRT[k][1] ++;
			}
			//+
		}
	}
	/////////////////////////////////////////////

	fprintf(log_SRT, "���������� ����� ������ ��� ������ ������: \n");
	for (int i = 0; i < SIZE; i++)
	{
		fprintf(log_SRT, " %d %d %d \n", i, ALL[i][0], SRT_box[i]);
	}

	cout << "\n";
	long unsigned int timeSRT = 0;//�����  ����� ���� ������
	/*
	for (int i = 0; i < SIZE; i++)
	{
		cout << SRT[i][0] << "\t";
		cout << SRT[i][1] << "\t";
		cout << SRT[i][2] << "\t";
		cout << SRT[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timeSRT += SRT[i][1];
	cout << "timeSRT=" << timeSRT << "taktov \n";


	////
	FILE* file = fopen("SRT.txt", "wt");
	{
		fprintf(file, "Time SRT: %d\n\nTime: \n", timeSRT);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", SRT[i][0], SRT[i][1]);
	}
	fclose(file);
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] SRT[j];
	delete[] SRT;

	delete[] SRT_box;

	for (int j = 0; j < SIZE; j++)
		delete[] ready_box[j];
	delete[] ready_box;
	//--------------------------------------------
	fclose(log_SRT);
}
#endif 