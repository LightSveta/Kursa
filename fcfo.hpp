#ifndef FCFO_HPP
#define FCFO_HPP

#include"outmyfile.hpp"

#include <iostream>///
using namespace std;///


/*
0� �������= ������ ������ �������(��-���� - ����� ������ �������)
1� �������= ����� �������+ ����� ���������� �������+...
2� -��������� \ ����
	0- ��� �� ���������\��������
	1- ���������
	2,3,4...-��������� �� ����� ����� ���������� ��������� �������
*/
void function_FCFO(int **ALL)
{
	int ** FCFO = new int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFO[j] = new int[3];
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
*/
	int done = 0;//������ ���������
	int TIMER = 1;//�� ����� ������ �����

	int start = ALL[TIMER][0];//���� ������ ������� �������
	int t_pre = 0;//����� ���������� 
	int t = ALL[TIMER][3];//����� ������
	//i=[0;size];j=[3;(1+2*ALL[i][1])] j=j+2; 
	// 2<= t <  2 + (1 + 2 * ALL[i][1])
	// ��������� t: 1+ALL[i][1]

	for (int i = 0; i < SIZE; i++)
	{
		FCFO[i][0]= ALL[i][0];
		FCFO[i][1] = 0;
		FCFO[i][2] = 0;
	}

///////////////////////////////////
	
	while (done < SIZE)
{
		for (int i = 0; i<SIZE; i++)
		{ 
			if (TIMER >= ALL[i][0] && FCFO[i][2] != 1)//����� ����������� � �� ���������
			{
				for (int j = 2; j < 2 + (1 + 2 * ALL[i][1]); j++)
				{
					FCFO[i][1] += ALL[i][j];//��� ������: ���� ������� ������� �� ����������
											//(���� ���� ����������), ��������� �� ��������
					int befor_timer = TIMER;
					TIMER += ALL[i][j];


					cout << "*TIMER=" << TIMER << "  befor_timer=" << befor_timer << "   for " << FCFO[i][0]
						<< "   what +=" << ALL[i][j]<<endl;

					int working = i;

					for (int k = 0; k < SIZE; k++)
					{
						//if (TIMER <= ALL[i][0])
						//	break;
						//else
						if (TIMER > ALL[k][0] && FCFO[k][2] != 1 && working!= k)//����� ����������� � �� ��������� 
						{ 
							if (befor_timer<=ALL[k][0])//���� � ����������� ���� ������ � ������
							{
								
								FCFO[k][1] += TIMER - FCFO[k][0];//��������� ����
								cout << "TIMER=" << TIMER << "  befor_timer=" << befor_timer << "    for" << FCFO[k][0]
									<< "   what +=" << TIMER - befor_timer << endl;
							}
							else
							{
								FCFO[k][1] += ALL[i][j];//��������� ����
								cout << "TIMER=" << TIMER << "  befor_timer=" << befor_timer << "    for" << FCFO[k][0]
									<< "   what +=" << ALL[i][j]
									<< "   from  =" << FCFO[i][0] << endl;
							}

							
						}
					}
				}
				FCFO[i][2] = 1;//������� �����������
				done++;
				break;
			}	
		}

	
		/*
	TIMER += t;
	for (int i = 0; i < SIZE; i++)
	{
		if (FCFO[i][0] == FCFO[start][0])
		{
			FCFO[i][1] += t;//������� ����������� ������� ������
		}
		else if (FCFO[i][0]<TIMER)
		{
			FCFO[i][1] += t;//������� ����� ������ ����� �������
		}
	}*/
}
/////////////////////////////////////////////
	cout << "\n";
int timeFCFO = 0;//�����  ����� ���� ������

for (int i = 0; i < SIZE; i++)
{
	cout << FCFO[i][0] << " ";
	cout << FCFO[i][1] << "\n";
}
for (int i = 0; i < SIZE; i++)
	timeFCFO += FCFO[i][1];
cout << "timeFCFO=" << timeFCFO << "taktov \n";

//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] FCFO[j];
	delete[] FCFO;
//--------------------------------------------
}
#endif 