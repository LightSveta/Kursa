#ifndef FCFO_HPP
#define FCFO_HPP

#include"outmyfile.hpp"

#include <iostream>///
using namespace std;///

//int FCFO[SIZE][2];
/**/


/*
1� �������= ������ ������ �������(��-���� - ����� ������ �������)
2� �������= ����� �������+ ����� ���������� �������
*/



void function_FCFO()
{/*
	int ** FCFO = new int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFO[j] = new int[2];

	int timeFCFO = 0;//����� ����� ���� ������
	//=������ ������ �� ������� FCFO

	//int point = 0;//����� ������ �������
	//int p_point = 0;//
	//int number; //= ALL_COMMANDS[point][0];//������ �������


	int point[3];
		point[0] = 0;//����� ������
		point[1] = ALL_COMMANDS[point[0]][0];//���� ������ ������ 
		point[2] = 2;//����� �� ���������� [2;3+n-1]
	//n=ALL_COMMANDS[i][1]

	int served = 0;//����� ���������
	int TIMER = 1;//�� ����� ������ �����


while (served < SIZE)
{
	//if(takt >= ALL_COMMANDS[i][0])����� �����������
	//number = point;
	//cout<<ALL_COMMANDS[1][1];
	if ((ALL_COMMANDS[point[0]][1] + 2 - 1) == (ALL_COMMANDS[point[0]][point[2]] + 2 - 1))served++;
	TIMER += point[1] / ONE_TAKT;
}
*/
}

/*
//������ ��� ������ ����� ����������� ALL_COMMANDS[][]
for (int i = 0; i < SIZE; i++)
{
	for (int j = 0; j < 2 + ALL_COMMANDS[i][1]; j++)
	{
		cout << ALL_COMMANDS[i][j] << " ";
	}
	cout << endl;
}
*/
#endif 