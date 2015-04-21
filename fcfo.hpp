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
3й -состояние 
	0- прервана или ещё не поступила
	1- завершена
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
	int done = 0;//задач завершено
	int TIMER = 1;//на каком сейчас такте

	int start = ALL[TIMER][0];//такт начала текущей задачи 
	int t_pre = 0;//время прерывания 
	int t = ALL[TIMER][3];//время работы
	//i=[0;size];j=[3;(1+2*ALL[i][1])] j=j+2; 

	for (int i = 0; i < SIZE; i++)
	{
		FCFO[i][0]= ALL[i][0];
		FCFO[i][1] = 0;
		FCFO[i][2] = 0;
	}

///////////////////////////////////
	while (done < SIZE)
{
	

	if (TIMER >= start)//может выполняться
	//number = point;
	//cout<<ALL[1][1];
	//if ((ALL[point[0]][1] + 2 - 1) == (ALL[point[0]][point[2]] + 2 - 1))served++;
	

	start = ALL[TIMER][0];//такт начала задачи


	if (ALL[TIMER][1] != 0)

	for (int i = 2; i < (1 + 2 * ALL[i][1]);i++)
	{
	//t_pre = ALL[TIMER][3];//время прерывания если есть

	//t = ALL[TIMER][2];//время работы
	}
	
	TIMER += t;
	for (int i = 0; i < SIZE; i++)
	{
		if (FCFO[i][0] == FCFO[start][0])
		{
			FCFO[i][1] += t;//сколько проработала текущая задача
		}
		else if (FCFO[i][0]<TIMER)
		{
			FCFO[i][1] += t;//сколько ждала задача своей очереди
		}
	}
}
/////////////////////////////////////////////

int timeFCFO = 0;//общее  время всех команд

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