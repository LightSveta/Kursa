#include "createfile.hpp"

#include "fcfo.hpp"
#include "RR.hpp"
#include "sjn.hpp"
#include "srt.hpp"

#include "outmyfile.hpp"

#include <iostream>
using namespace std;


const int ONE_TAKT = 600;// ������ 1 ����� � ����-��������=600��� ������� 1.8 �����(�������� � ������)

void main()
{
	WriteFile();//������� ����
	
	long unsigned int ** ALL_COMMANDS = new long unsigned int *[ReadSize()];//� ���� ������� �������� ��� � ��������
	
	ReadAllFile(ALL_COMMANDS);//��������� ������ ALL_COMMANDS[size][ALL_COMMANDS[i][1]]
	
	int SIZE = ReadSize();

	/*
	//������ ��� ������ ����� ����������� ALL_COMMANDS[][]
	for (int i = 0; i < SIZE; i++)
	{
		for (long unsigned int j = 0; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j++)
		{
			cout << ALL_COMMANDS[i][j] << " ";
		}
		cout << endl;
	}
	*/

	long unsigned int Xtime = 0;
	for (int i = 0; i < SIZE; i++)
		for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j++)
			Xtime += ALL_COMMANDS[i][j];
	cout << "Xtime=" << Xtime << "taktov \n";
	//������ Xtime �� ������ ���������� � ���������� ���������� ����������
	//����� �� ����������� ��, ��� ����������� ������� ���� ����� �������

	function_FCFO_(ALL_COMMANDS, SIZE);//

	function_FCFO(ALL_COMMANDS, SIZE);

	function_RR(ALL_COMMANDS, SIZE);

	function_SJN(ALL_COMMANDS, SIZE);
	
	function_SRT(ALL_COMMANDS, SIZE);

//---------------------------------
	for (int i = 0; i < SIZE; i++)
			delete [] ALL_COMMANDS[i];
	delete [] ALL_COMMANDS;
	
}
//---------------------------------
