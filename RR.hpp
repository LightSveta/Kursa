#ifndef RR_HPP
#define RR_HPP

#include "outmyfile.hpp"

using namespace std;///


void function_RR(int SIZE)
{

	long unsigned int ** ALL = new long unsigned int *[SIZE];
	ReadAllFile(ALL);

	FILE* log_RR = fopen("log_RR.txt", "w");

	long unsigned int ** RR = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		RR[j] = new long unsigned int[4];

	int done = 0;//команд завершено
	long unsigned int TIME = 1;//на каком сейчас такте

	long unsigned int allow_time = 2;

	for (int i = 0; i < SIZE; i++)
	{
		RR[i][0] = ALL[i][0];// №такта начала команды
		RR[i][1] = 0;//время простоя+ время выполнения команды+...
		RR[i][2] = 2;//флаг(позиция в массиве) на какой команде остановилась задача\на каком этапе выполнения в данный момент
		RR[i][3] = 0;//на каком такте команда перейдет в состояние готов
	}


	long unsigned int *waiting_list = new long unsigned int[SIZE];
	for (int i = 0; i < SIZE; i++)//номер задачи в массиве
		waiting_list[i] = 0;

	int waiting = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (TIME >= ALL[i][0] && RR[i][2] != 0 && TIME >= RR[i][3])//может выполняться(поступила & не завершена&в состоянии готов)
		{
			waiting_list[waiting] = i;// i -это № вмассиве ALL
			waiting++;
		}

	}
	///////////////////////////////////
	//int flag;
	///////////////////////////////////
	int flag;
	int flag1;
	int flag2 = 0;

	int allow_flag = 1;//
	//1-еще не исчерпала времени
	//0-исчерпала время
	//2-  allow_time<ALL[i][RR[i][2]]//потом продолжит работу
	//3-  allow_time>ALL[i][RR[i][2]]// уложится
	//4-  allow_time==ALL[i][RR[i][2]]//работает строго отведенное время


	int befor_task = -1;//№ALL
	long unsigned int used_time = 0;


	while (done < SIZE)
	{
		long unsigned int befor_TIME;
		if (waiting != 0)
		{//5
			int allow_flag = allow_time;
			long unsigned int i = waiting_list[0];
			befor_task = i;
		
			fprintf(log_RR, "Список:\n");
			for (int k = 0; k < waiting; k++)
				fprintf(log_RR, "     %d) задача№%d, такт на котором поступила:%d (%d)\n", k + 1, waiting_list[k], RR[waiting_list[k]][0], ALL[waiting_list[k]][0]);

			fprintf(log_RR, "Выбрана задача №%d (такт на котором поступила:%d) \n", i, RR[i][0]);

			if (RR[i][2] % 2 == 0)// НЕ прервана(чет)
			{///2

			metka_goto:

				befor_task = i;
				befor_TIME = TIME;
				//TIME += ALL[i][RR[i][2]];
				//RR[i][1] += ALL[i][RR[i][2]];//работает
				befor_TIME = TIME;
				befor_task = i;
				//определяем сколько будет работать выбранная задача
				if (allow_time<ALL[i][RR[i][2]])
				{
					used_time = allow_time;//потом продолжит работу
					allow_flag = 2;//
				}
				else if (allow_time>ALL[i][RR[i][2]])
				{
					used_time = ALL[i][RR[i][2]];// уложится
					allow_flag = 3;//

				}
				else if (allow_time == ALL[i][RR[i][2]])
				{
					used_time = allow_time;//работает строго отведенное время
					allow_flag = 4;//
				}
				fprintf(log_RR, "текущий такт- %d  \n",
					TIME);
				TIME += used_time;
				
				RR[i][1] += used_time;

				flag = 1;//есть команда

				//пока текущая задача работала могли появиться новые задачи или разблокироваться старые
				for (int k = 0; k < SIZE; k++)
				{
					if (TIME >= ALL[k][0] && RR[k][2] != 0 && TIME >= RR[k][3])//может выполняться(поступила & не завершена&в состоянии готов)
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

				fprintf(log_RR, "работает задача №%d , поступившая на %d такте,  работает %d тактов (из необходимых %d ) \n",
					i, RR[i][0], used_time, ALL[i][RR[i][2]]);
				fprintf(log_RR, "текущий такт- %d  \n",
					TIME);
				//fprintf(log_RR, "			RR[%d][3]=%d \n",
				//	i, RR[i][3]);
				//fprintf(log_RR, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
				///	i, RR[i][0], RR[i][3]);

				for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
				{//3
					if (TIME >= ALL[k][0] && RR[k][2] != 0 && i != k && TIME >= RR[k][3])//может выполняться и не завершена и не является текущей и закончилось прерывание
					{////4
						if (befor_TIME <= ALL[k][0] && RR[k][2] != 0)//если с предыдущего шага готова к работе
							//те. появилась во время работы другой команды
						{
							RR[k][1] += TIME - RR[k][0];//остальные ждут
							fprintf(log_RR, "задача №%d , поступившая на %d такте,  ждет %d тактов \n",
								k, RR[k][0], TIME - RR[k][0]);
							
						}
						else if (RR[k][2] != 0)
						{
							RR[k][1] += used_time;//остальные ждут
							fprintf(log_RR, "задача №%d , поступившая на %d такте,  ждет %d тактов\n",
								k, RR[k][0], used_time);

							//fprintf(log_RR, "			RR[%d][3]=%d \n",
							//	i, RR[i][3]);
							//fprintf(log_RR, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
							//	i, RR[i][0], RR[i][3]);
						}
					}////4
				}//3

				if (allow_flag == 2)
				{
					ALL[i][RR[i][2]] -= allow_time;//потом продолжит работу с тогоже места, но требующую меньше времени
				fprintf(log_RR, "задача №%d , поступившая на %d такте, потом продолжит работу \n",
					i, RR[i][0]);
				}
				if (allow_flag == 3)
				{
					fprintf(log_RR, "задача №%d , поступившая на %d такте, уложилась \n",
						i, RR[i][0]);
					RR[i][2]++;// уложилась
					
				}
				if (allow_flag == 4)
				{
					fprintf(log_RR, "задача №%d , поступившая на %d такте, уложилась \n",
						i, RR[i][0]);
					RR[i][2]++;// уложилась;
				}
				
				//RR[i][2]++;

				if (RR[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					RR[i][2] = 0;
					//так как  задача завершена, то yбираем из очереди
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//на 1 задачу стало меньше
					//сдвинули все элементы влево на 1(затерли номер завершившейся задачи)

					done++;
					//fprintf(log_RR, "подсчет закончивших задач: текущий такт(TIME)=%d\n завершившихся(done)=%d штук (из %d); RR[%d][0]=%d -  завершена\t    RR[%d][2]=%d\n",
					//	TIME, done, SIZE, i, RR[i][0], i, RR[i][2]);
					fprintf(log_RR, "завершена  задача №%d , поступившая на %d такте) \n",
						i, RR[i][0]);
					fprintf(log_RR, "			RR[%d][3]=%d \n",
						i, RR[i][3]);
					//fprintf(log_RR, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
					//	i, RR[i][0], RR[i][3]);
				}
				else
				{
					//если не завершена убираем из списка
					for (int l = 0; l < waiting - 1; l++)
						waiting_list[l] = waiting_list[l + 1];
					waiting--;//на 1 задачу стало меньше
				}
			}///2

			if (RR[i][2] % 2 == 1)//прервана(нечет)
			{
				RR[i][3] = TIME + ALL[i][RR[i][2]];//нашли такт, после когторого команда перейдет в состояние готов
				fprintf(log_RR, "Такт на котором проснется %d RR[%d][3]= %d + %d = %d\n",
					RR[i][0], i, TIME, ALL[i][RR[i][2]], RR[i][3]);
				fprintf(log_RR, "(т.е задача №%d , поступившая на %d такте, заблокирована до такта %d ) \n",
					i, RR[i][0], RR[i][3]);
				RR[i][2]++;
			}

		if (flag == 0)
			{//8
				if (allow_flag == 2)
				{
					//так уж и быть, поработает еще, пока нет других задач, готовых к работе
					fprintf(log_RR, "(готова к работе только текущая задача) \n");
					goto metka_goto;
				}
				else//уж совсем никаких нет!
				{//7
					TIME++;
					fprintf(log_RR, "работа в холостую. Текущий такт = %d \n", TIME);

					//+ в этот такт ждут уже поступившие задачи:
					for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
					{
						if (TIME >= ALL[k][0] && RR[k][2] != 0)//поступила и не завершена
							RR[k][1] ++;
					}
					//+
				}//7
			}//8

		}//5
		else if (waiting == 0)
		{
			TIME++;
			fprintf(log_RR, "работа в холостую. задач в состоянии готов или  новых - нет, Текущий такт = %d \n", TIME);
			//+ в этот такт ждут уже поступившие задачи:
			for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
			{
				if (TIME >= ALL[k][0] && RR[k][2] != 0)//поступила и не завершена
					RR[k][1] ++;
			}
			//пока задачи ждали могли появиться новые или разблокироваться старые
			for (int k = 0; k < SIZE; k++)
			{
				if (TIME >= ALL[k][0] && RR[k][2] != 0 && TIME >= RR[k][3])//может выполняться(поступила & не завершена&в состоянии готов)
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
		fprintf(log_RR, "***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t***\t\n\n");

	}
	/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeRR = 0;//общее  время всех команд
	/*
	for (int i = 0; i < SIZE; i++)
	{
	cout << RR[i][0] << "\t";
	cout << RR[i][1] << "\t";
	cout << RR[i][2] << "\t";
	cout << RR[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timeRR += RR[i][1];
	cout << "timeRR=" << timeRR << "taktov \n";


	////
	FILE* file = fopen("RR.txt", "wt");
	{
		fprintf(file, "Time RR: %d\n\nTime: \n", timeRR);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", RR[i][0], RR[i][1]);
	}
	fclose(file);
	fprintf(log_RR, "Завершены все задачи.\n");
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] RR[j];
	delete[] RR;

	delete[] waiting_list;

	//--------------------------------------------
	fclose(log_RR);
}
#endif 