#ifndef FCFS_HPP
#define FCFS_HPP

#include <time.h>

using namespace std;///

/*
0й столбец= №такта начала команды
1й столбец= время простоя+ время выполнения команды+...
2й -флаг(позиция в массиве)
3,4...-указатель на каком этапе выполнения находится команда
3й -на каком такте команда перейдет в состояние готов
(пересчитывается по мере надобности)

если FCFS[i][2]==0 - то завершена
*/

void function_FCFS(long unsigned int **ALL, int SIZE)
{
	FILE* log_FCFS = fopen("log_FCFS.txt", "w");

	long unsigned int ** FCFS = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFS[j] = new long unsigned int[4];
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

	четные номера-это время работы
	нечетные-время прерывания
	*/
	int done = 0;//команд завершено
	long unsigned int TIME = 1;//на каком сейчас такте

	//int start = ALL[TIME][0];//такт начала текущей команды
	//int t_pre = 0;//время прерывания 
	//int t = ALL[TIME][3];//время работы
	//i=[0;size];j=[3;(1+2*ALL[i][1])] j=j+2; 
	// 2<= t <  2 + (1 + 2 * ALL[i][1])
	// количесво t: 1+ALL[i][1]

	for (int i = 0; i < SIZE; i++)
	{
		FCFS[i][0] = ALL[i][0];// №такта начала команды
		FCFS[i][1] = 0;//время простоя+ время выполнения команды+...
		FCFS[i][2] = 2;//флаг(позиция в массиве) на какой команде остановилась задача\на каком этапе выполнения в данный момент
		FCFS[i][3] = 0;//на каком такте команда перейдет в состояние готов
	}


	long unsigned int *waiting_list = new long unsigned int[SIZE];
	for (int i = 0; i < SIZE; i++)//номер задачи в массиве
		waiting_list[i] = 0;

	int waiting = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (TIME >= ALL[i][0] && FCFS[i][2] != 0 && TIME >= FCFS[i][3])//может выполняться(поступила & не завершена&в состоянии готов)
		{
			waiting_list[waiting] = i;// i -это № вмассиве ALL
			waiting++;
		}

	}
	///////////////////////////////////
	//int flag;

	while (done < SIZE)
	{
		long unsigned int befor_TIME;
		if (waiting != 0)
		{//5
			long unsigned int i = waiting_list[0];

			fprintf(log_FCFS, "Список:\n");
			for (int k = 0; k < waiting; k++)
				fprintf(log_FCFS, "     %d) задача№%d, такт на котором поступила:%d (%d)\n", k + 1, waiting_list[k], FCFS[waiting_list[k]][0], ALL[waiting_list[k]][0]);

			// i-номер задачи в массиве ALL,
			//требующей меньше всего времени на выполнение,
			//из всех задач готовых к работе на данный такт

			fprintf(log_FCFS, "Выбрана задача №%d (такт на котором поступила:%d) \n", i, FCFS[i][0]);

			if (FCFS[i][2] % 2 == 0)// НЕ прервана(чет)
			{///2
				befor_TIME = TIME;
				TIME += ALL[i][FCFS[i][2]];
				FCFS[i][1] += ALL[i][FCFS[i][2]];//работает

				//пока текущая задача работала могли появиться новые задачи или разблокироваться старые
				for (int k = 0; k < SIZE; k++)
				{
					if (TIME >= ALL[k][0] && FCFS[k][2] != 0 && TIME >= FCFS[k][3])//может выполняться(поступила & не завершена&в состоянии готов)
					{
						int flag_copy = 0;

						for (int j = 0; j < waiting; j++)
							if (waiting_list[j] == k)
								flag_copy++;

						if (flag_copy == 0)//если такой еще нет
						{
							waiting_list[waiting] = k; //добавили в конец
							waiting++;
						}
					}
				}

				fprintf(log_FCFS, "*текущий такт(TIME)=%d\t befor_TIME=%d\tFCFS[%d][0]=%d\tALL[%d][%d]=%d \n",
					TIME, befor_TIME, i, FCFS[i][0], i, FCFS[i][2], ALL[i][FCFS[i][2]]);
				fprintf(log_FCFS, "(т.е работает задача №%d , поступившая на %d такте,  работает %d тактов) \n",
					i, FCFS[i][0], ALL[i][FCFS[i][2]]);
				fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
					i, FCFS[i][3]);
				fprintf(log_FCFS, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
					i, FCFS[i][0], FCFS[i][3]);

				for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
				{//3
					if (TIME >= ALL[k][0] && FCFS[k][2] != 0 && i != k && TIME >= FCFS[k][3])//может выполняться и не завершена и не является текущей и закончилось прерывание
					{////4
						if (befor_TIME <= ALL[k][0] && FCFS[k][2] != 0)//если с предыдущего шага готова к работе
							//те. появилась во время работы другой команды
						{
							FCFS[k][1] += TIME - FCFS[k][0];//остальные ждут
							fprintf(log_FCFS, "ожидающие(1тип): текущий такт(TIME)=%d\tbefor_TIME=%d\tFCFS[%d][0]=%d\t TIME-FCFS[%d][0]=%d\n",
								TIME, befor_TIME, i, FCFS[k][0], i, TIME - FCFS[k][0]);
							fprintf(log_FCFS, "(т.е  задача №%d , поступившая на %d такте,  ждет %d тактов) \n",
								k, FCFS[k][0], TIME - FCFS[k][0]);
							fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
								i, FCFS[i][3]);
							fprintf(log_FCFS, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
								i, FCFS[i][0], FCFS[i][3]);
						}
						else if (FCFS[k][2] != 0)
						{
							FCFS[k][1] += ALL[i][FCFS[i][2]];//остальные ждут
							fprintf(log_FCFS, "ожидающие(2тип): текущий такт(TIME)=%d\tbefor_TIME=%d\t for FCFS[%d][0]=%d\t  this ALL[%d][%d]=%d from FCFS[%d][0]=%d\n",
								TIME, befor_TIME, i, FCFS[k][0], k, FCFS[i][2], ALL[i][FCFS[i][2]], i, FCFS[i][0]);
							fprintf(log_FCFS, "(т.е  задача №%d , поступившая на %d такте,  ждет %d тактов) \n",
								k, FCFS[k][0], ALL[i][FCFS[i][2]]);

							fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
								i, FCFS[i][3]);
							fprintf(log_FCFS, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
								i, FCFS[i][0], FCFS[i][3]);
						}
					}////4
				}//3
				FCFS[i][2]++;

				if (FCFS[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					FCFS[i][2] = 0;

					//так как  задача завершена, то yбираем из очереди
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//на 1 задачу стало меньше
					//сдвинули все элементы влево на 1(затерли номер завершившейся задачи)

					done++;
					fprintf(log_FCFS, "подсчет закончивших задач: текущий такт(TIME)=%d\n завершившихся(done)=%d штук (из %d); FCFS[%d][0]=%d -  завершена\t    FCFS[%d][2]=%d\n",
						TIME, done, SIZE, i, FCFS[i][0], i, FCFS[i][2]);
					fprintf(log_FCFS, "(т.е завершена  задача №%d , поступившая на %d такте) \n",
						i, FCFS[i][0]);
					fprintf(log_FCFS, "			FCFS[%d][3]=%d \n",
						i, FCFS[i][3]);
					fprintf(log_FCFS, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
						i, FCFS[i][0], FCFS[i][3]);
				}
				else
				{
					//если не завершена убираем из списка
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//на 1 задачу стало меньше
				}
			}///2

			if (FCFS[i][2] % 2 == 1)//прервана(нечет)
			{
				FCFS[i][3] = TIME + ALL[i][FCFS[i][2]];//нашли такт, после когторого команда перейдет в состояние готов
				fprintf(log_FCFS, "Такт на котором проснется %d FCFS[%d][3]= %d + %d = %d\n",
					FCFS[i][0], i, TIME, ALL[i][FCFS[i][2]], FCFS[i][3]);
				fprintf(log_FCFS, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
					i, FCFS[i][0], FCFS[i][3]);
				FCFS[i][2]++;
			}

		}//5
		else if (waiting == 0)
		{
			TIME++;
			fprintf(log_FCFS, "работа в холостую. задач в состоянии готов или  новых - нет, Текущий такт = %d \n", TIME);
			//+ в этот такт ждут уже поступившие задачи:
			for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
			{
				if (TIME >= ALL[k][0] && FCFS[k][2] != 0)//поступила и не завершена
					FCFS[k][1] ++;
			}
			//пока задачи ждали могли появиться новые или разблокироваться старые
			for (int k = 0; k < SIZE; k++)
			{
				if (TIME >= ALL[k][0] && FCFS[k][2] != 0 && TIME >= FCFS[k][3])//может выполняться(поступила & не завершена&в состоянии готов)
				{
					int flag_copy = 0;

					for (int j = 0; j < waiting; j++)
						if (waiting_list[j] == k)
							flag_copy++;

					if (flag_copy == 0)//если такой еще нет
					{
						waiting_list[waiting] = k; //добавили в конец
						waiting++;
					}
				}
			}
			//+
		}
		fprintf(log_FCFS, "***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t\n\n");

	}
	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeFCFS = 0;//общее  время всех команд
	/*
	for (int i = 0; i < SIZE; i++)
	{
	cout << FCFS[i][0] << "\t";
	cout << FCFS[i][1] << "\t";
	cout << FCFS[i][2] << "\t";
	cout << FCFS[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timeFCFS += FCFS[i][1];
	cout << "timeFCFS=" << timeFCFS << "taktov \n";


	////
	FILE* file = fopen("FCFS.txt", "wt");
	{
		fprintf(file, "Time FCFS: %d\n\nTime: \n", timeFCFS);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", FCFS[i][0], FCFS[i][1]);
	}
	fclose(file);
	fprintf(log_FCFS, "Завершены все задачи.\n");
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] FCFS[j];
	delete[] FCFS;

	delete[] waiting_list;

	//--------------------------------------------
	fclose(log_FCFS);
}
#endif 