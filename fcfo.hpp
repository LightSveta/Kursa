#ifndef FCFO_HPP
#define FCFO_HPP

#include"outmyfile.hpp"

#include <iostream>///
using namespace std;///


/*
0й столбец= №такта начала команды(по-сути - какая именно команда)
1й столбец= время простоя+ время выполнения команды+...
2й -состояние \ флаг
	0- ещё не поступила\прервана
	1- завершена
	2,3,4...-указатель на каком этапе выполнения находится команда
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
	int done = 0;//команд завершено
	int TIMER = 1;//на каком сейчас такте

	int start = ALL[TIMER][0];//такт начала текущей команды
	int t_pre = 0;//время прерывания 
	int t = ALL[TIMER][3];//время работы
	//i=[0;size];j=[3;(1+2*ALL[i][1])] j=j+2; 
	// 2<= t <  2 + (1 + 2 * ALL[i][1])
	// количесво t: 1+ALL[i][1]

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
			if (TIMER >= ALL[i][0] && FCFO[i][2] != 1)//может выполняться и не завершена
			{
				for (int j = 2; j < 2 + (1 + 2 * ALL[i][1]); j++)
				{
					FCFO[i][1] += ALL[i][j];//для случая: пока текущая команда не завершится
											//(даже если прервалась), следующая не начнется
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
						if (TIMER > ALL[k][0] && FCFO[k][2] != 1 && working!= k)//может выполняться и не завершена 
						{ 
							if (befor_timer<=ALL[k][0])//если с предыдущего шага готова к работе
							{
								
								FCFO[k][1] += TIMER - FCFO[k][0];//остальные ждут
								cout << "TIMER=" << TIMER << "  befor_timer=" << befor_timer << "    for" << FCFO[k][0]
									<< "   what +=" << TIMER - befor_timer << endl;
							}
							else
							{
								FCFO[k][1] += ALL[i][j];//остальные ждут
								cout << "TIMER=" << TIMER << "  befor_timer=" << befor_timer << "    for" << FCFO[k][0]
									<< "   what +=" << ALL[i][j]
									<< "   from  =" << FCFO[i][0] << endl;
							}

							
						}
					}
				}
				FCFO[i][2] = 1;//команда завершилась
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
			FCFO[i][1] += t;//сколько проработала текущая задача
		}
		else if (FCFO[i][0]<TIMER)
		{
			FCFO[i][1] += t;//сколько ждала задача своей очереди
		}
	}*/
}
/////////////////////////////////////////////
	cout << "\n";
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