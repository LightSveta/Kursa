#ifndef FCFO_HPP
#define FCFO_HPP

#include"outmyfile.hpp"

#include <iostream>///
using namespace std;///

//int FCFO[SIZE][2];
/**/


/*
1й столбец= №такта начала команды(по-сути - какая именно команда)
2й столбец= время простоя+ время выполнения команды
*/



void function_FCFO()
{/*
	int ** FCFO = new int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFO[j] = new int[2];

	int timeFCFO = 0;//общее время всех команд
	//=прстой проход по массиву FCFO

	//int point = 0;//номер задачи текущей
	//int p_point = 0;//
	//int number; //= ALL_COMMANDS[point][0];//задача текущая


	int point[3];
		point[0] = 0;//номер задачи
		point[1] = ALL_COMMANDS[point[0]][0];//такт начала задачи 
		point[2] = 2;//время до прерывания [2;3+n-1]
	//n=ALL_COMMANDS[i][1]

	int served = 0;//задач обслужено
	int TIMER = 1;//на каком сейчас такте


while (served < SIZE)
{
	//if(takt >= ALL_COMMANDS[i][0])может выполняться
	//number = point;
	//cout<<ALL_COMMANDS[1][1];
	if ((ALL_COMMANDS[point[0]][1] + 2 - 1) == (ALL_COMMANDS[point[0]][point[2]] + 2 - 1))served++;
	TIMER += point[1] / ONE_TAKT;
}
*/
}

/*
//пример для вывода всего содержимого ALL_COMMANDS[][]
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