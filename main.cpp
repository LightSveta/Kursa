//#include "createfile.hpp"

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
	//WriteFile();//������� ���� #include "createfile.hpp"
	
	ReadAllFile(ALL_COMMANDS);//��������� ������ ALL_COMMANDS[size][ALL_COMMANDS[i][1]]
	
	//������ ��� ������ ����� ����������� ALL_COMMANDS[][]
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < 2+(1+2*ALL_COMMANDS[i][1]); j++)
		{
			cout << ALL_COMMANDS[i][j] << " ";
		}
		cout << endl;
	}
	

	function_FCFO();



	//int s;
	//s=ReadOneElement(1);
	//cout<<s;

	/*
	int a=999999, b=888888;
	ReadOneLine(5, a, b);
	cout<<a<<" "<<b<<endl;
	*/

	/*
	for (int i = 0; i<100; i++)
	for (int j = 0; j<2; j++)
	WriteResult(i, j);
	*/
	//WriteResult(0, 145 );
	//WriteResult(3, 17 );
	//WriteResult(3, 345 );

}