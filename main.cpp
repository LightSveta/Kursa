#include "createfile.hpp"

#include "fcfo.hpp"
#include "RR.hpp"
#include "sgn.hpp"
#include "srt.hpp"

#include "outmyfile.hpp"

#include <iostream>
using namespace std;


const int ONE_TAKT = 600;// ������ 1 ����� � ����-��������=600��� ������� 1.8 �����(�������� � ������)
int ** ALL_COMMANDS = new int *[SIZE];//� ���� ������� �������� ��� � ��������

void main()
{
	//WriteFile();//������� ����
	
	ReadAllFile(ALL_COMMANDS);//��������� ������ ALL_COMMANDS[size][ALL_COMMANDS[i][1]]
	/*
	//������ ��� ������ ����� ����������� ALL_COMMANDS[][]
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < 2+(1+2*ALL_COMMANDS[i][1]); j++)
		{
			cout << ALL_COMMANDS[i][j] << " ";
		}
		cout << endl;
	}
*/		
	//����� ����������� �� ��� ������� �� ������� (������ ���������� ��������� �� �������� �����������)
	int MAXtime = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 2; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j++)
			MAXtime += ALL_COMMANDS[i][j];
	cout << "MAXtime=" << MAXtime << "taktov \n";
	//������ MAXtime �� ������ ���������� � ���������� ���������� ����������

	function_FCFO(ALL_COMMANDS);

	ReadAllFile(ALL_COMMANDS);
	function_RR();

	ReadAllFile(ALL_COMMANDS);
	function_SJN();
	
	ReadAllFile(ALL_COMMANDS); 
	function_SRT();

//----------------------------------
	for (int i = 0; i < SIZE; i++)
			delete [] ALL_COMMANDS[i];
	delete [] ALL_COMMANDS;
	

}