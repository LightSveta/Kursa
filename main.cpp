#include "createfile.hpp"

#include "fcfo.hpp"
#include "fcfs.hpp"
#include "lottery.hpp"
#include "RR.hpp"
#include "sjn.hpp"
#include "srt.hpp"

#include "outmyfile.hpp"

#include <iostream>
using namespace std;


const int ONE_TAKT = 600;// размер 1 такта в пико-секундах=600при частоте 1.8 ГГерц(подсчеты в листке)

void main()
{
	//WriteFile();//создать файл
	
	long unsigned int ** ALL_COMMANDS = new long unsigned int *[ReadSize()];//в этом массиве хранится все о командах
	
	ReadAllFile(ALL_COMMANDS);//заполняет массив ALL_COMMANDS[size][ALL_COMMANDS[i][1]]
	
	int SIZE = ReadSize();

	
	//пример для вывода всего содержимого ALL_COMMANDS[][]
	for (int i = 0; i < SIZE; i++)
	{
		for (long unsigned int j = 0; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j++)
		{
			cout << ALL_COMMANDS[i][j] << " ";
		}
		cout << endl;
	}
	

	long unsigned int Xtime = 0;
	for (int i = 0; i < SIZE; i++)
		for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j++)
			Xtime += ALL_COMMANDS[i][j];
	cout << "Xtime=" << Xtime << "taktov \n";
	//меньше Xtime не должно получиться в результате вычислений алгоритмов
	//здесь не учитывается то, что поступившие команды ждут своей очереди

	//function_FCFO_(ALL_COMMANDS, SIZE);//test

	function_FCFO(ALL_COMMANDS, SIZE);
	function_FCFS(ALL_COMMANDS, SIZE);
	/*
	cout << "\n------------------\nall\n";
	int s = 10;
	int array[10];
	for (int l = 0; l < s; l++)
	{
		array[l] = l+1;
		cout << array[l]<<" ";
	}
	cout << "\n-1\n";

	for (int l = 0; l < s - 1; l++)
		array[l] = array[l + 1];
	s--; 
	for (int l = 0; l < s - 1; l++)
		array[l] = array[l + 1];
	s--;

	for (int l = 0; l < s; l++)
	{
		cout << array[l] << " ";
	}
	cout << "\n in end->\n";

	int i = array[0];
	for (int l = 0; l < s - 1; l++)
		array[l] = array[l + 1];
	array[s - 1] = i;
	for (int l = 0; l < s; l++)
	{
		cout << array[l] << " ";
	}
	cout << "\n------------------\n";
	//пока текущая задача работала могли появиться новые задачи или разблокироваться старые

	array[s] = 45; //добавили в конец
	s++;

	for (int l = 0; l < s; l++)
	{
		cout << array[l] << " ";
	}
	cout << "\n------------------\n";
	s = 0;
	array[s] = 88;
	s++;

	array[s] = 45; //добавили в конец
	s++;
	for (int l = 0; l < s; l++)
	{
		cout << array[l] << " ";
	}
	cout << "\n------------------\n";
	*/
	function_LOTTERY(ALL_COMMANDS, SIZE);

	//function_RR(SIZE);//don'working

	function_SJN(ALL_COMMANDS, SIZE);
	
	function_SRT(ALL_COMMANDS, SIZE);
//
//---------------------------------
	for (int i = 0; i < SIZE; i++)
			delete [] ALL_COMMANDS[i];
	delete [] ALL_COMMANDS;
	
}
//---------------------------------
