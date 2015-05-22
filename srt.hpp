#ifndef SRT_HPP
#define SRT_HPP

#include <time.h>
#include "outmyfile.hpp"

using namespace std;///

void function_SRT(int SIZE)
{
	long unsigned int ** ALL = new long unsigned int *[SIZE];
	ReadAllFile(ALL);

	FILE* log_SRT = fopen("log_SRT.txt", "w");

	long unsigned int ** SRT = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		SRT[j] = new long unsigned int[4];

	int done = 0;//команд завершено
	long unsigned int TIME = 1;//на каком сейчас такте

	for (int i = 0; i < SIZE; i++)
	{
		SRT[i][0] = ALL[i][0];// №такта начала команды
		SRT[i][1] = 0;//время простоя+ время выполнения команды+...
		SRT[i][2] = 2;//флаг(позиция в массиве)
		SRT[i][3] = 0;//на каком такте команда перейдет в состояние готов
	}

	long unsigned int *SRT_box = new long unsigned int[SIZE];
	for ( int i = 0; i < SIZE; i++)
		SRT_box[i] = 0;

	long unsigned int **ready_box = new long unsigned int*[SIZE];
	for (int i = 0; i < SIZE; i++)
		ready_box[i] = new long unsigned int[2];
	//SRT_box - оставшееся время работы каждой задачи
	//ready_box - оставшееся время работы только готовых кработе
	
	for (int i = 0; i < SIZE; i++)
	{
		for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL[i][1]); j += 2)
		{
			SRT_box[i] += ALL[i][j];//время требуемое каждой задаче на выполнение
		}
		//cout <<"*"<< SRT_box[i] << endl;//////////////////////////
		ready_box[i][0] = 0;//номер задачи в массиве
		ready_box[i][1] = 0;//необходимое время
	}


	int ready_box_size = 0;//постоянно меняем
	int SRT_box_size = SIZE;//для наглядности
	int allow_flag;

	///////////////////////////////////
//	int flag;
	//int flag1;
	int flag2 = 0;
	while (done < SIZE)
	{
		long unsigned int befor_TIME;

		ready_box_size = 0;
		
		for (int i = 0, k = 0; i < SIZE; i++)
		{
			if (TIME >= ALL[i][0] && SRT[i][2] != 0 && TIME >= SRT[i][3])//может выполняться(поступила & не завершена &в состоянии готов )
			{//запоминаем время только готовых к работе
				ready_box[k][0] = i;
				ready_box[k][1] = SRT_box[i];
			//	cout << "***" << ready_box[k][0] << "  " << ready_box[k][1]<< endl;
				k++;
				ready_box_size++;
			}
		}
		if (ready_box_size != 0)
		{//5
			//ищем задачу из полученного списка с наименьшим оставшимся временем
			long unsigned int i = ready_box[0][0];
			long unsigned int min = ready_box[0][1];
			for (int k = 1; k < ready_box_size; k++)
			{
				if (ready_box[k][1] < min)
				{
					min = ready_box[k][1];//ищем минимальное время
					i = ready_box[k][0];//ищем номер в массиве этой задачи
				}
			}

			for (int k = 0; k < ready_box_size; k++)
				fprintf(log_SRT, "		%d	%d=%d	%d \n", ready_box[k][0], SRT[ready_box[k][0]][0], ALL[ready_box[k][0]][0], ready_box[k][1]);

			//таким образом, i-номер задачи в массиве ALL,
			//требующей меньше всего времени на выполнение,
			//из задач готовых к работе на данный такт

			fprintf(log_SRT, "Выбрана задача %d (№ %d) \n", SRT[i][0], i);

			if (SRT[i][2] % 2 == 0)// НЕ прервана(чет)
			{///2
				befor_TIME = TIME;
				TIME ++;
				SRT[i][1] ++;//работает
				SRT_box[i] -= 1;//так как она проработала, то ее оставшееся время работы уменьшится

				fprintf(log_SRT, "*текущий такт(TIME)=%d\t befor_TIME=%d\tSRT[%d][0]=%d\tALL[%d][%d]=%d \n",
					TIME, befor_TIME, i, SRT[i][0], i, SRT[i][2], ALL[i][SRT[i][2]]);
				fprintf(log_SRT, "работает задача №%d , поступившая на %d такте,  работает 1 такт (из необходимых %d ) \n",
					i, SRT[i][0], ALL[i][SRT[i][2]]);

				
					ALL[i][SRT[i][2]] -= 1;//потом продолжит работу с тогоже места
					fprintf(log_SRT, "задача №%d , поступившая на %d такте, потом продолжит работу \n",
						i, SRT[i][0]);
				

				for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
				{//3
					if (TIME >= ALL[k][0] && SRT[k][2] != 0 && i != k && TIME >= SRT[k][3])//может выполняться и не завершена и не является текущей и закончилось прерывание
					{////4
						if (befor_TIME <= ALL[k][0] && SRT[k][2] != 0)//если с предыдущего шага готова к работе
							//те. появилась во время работы другой команды
						{
							SRT[k][1] += TIME - SRT[k][0];//остальные ждут
							fprintf(log_SRT, "ожидающие(1тип): текущий такт(TIME)=%d\tbefor_TIME=%d\tSRT[%d][0]=%d\t TIME-SRT[%d][0]=%d\n",
								TIME, befor_TIME, i, SRT[k][0], i, TIME - SRT[k][0]);
							fprintf(log_SRT, "---------SRT[%d][3]=%d\n",
								i, SRT[i][3]);
						}
						else if (SRT[k][2] != 0)
						{
							SRT[k][1] += ALL[i][SRT[i][2]];//остальные ждут
							fprintf(log_SRT, "ожидающие(2тип): текущий такт(TIME)=%d\tbefor_TIME=%d\t for SRT[%d][0]=%d\t  this ALL[%d][%d]=%d from SRT[%d][0]=%d\n",
								TIME, befor_TIME, i, SRT[k][0], k, SRT[i][2], ALL[i][SRT[i][2]], i, SRT[i][0]);
							fprintf(log_SRT, "---------SRT[%d][3]=%d\n",
								i, SRT[i][3]);
						}
					}////4
				}//3
				//SRT[i][2]++;
				if (ALL[i][SRT[i][2]]==0)//завершена одна команд задачи
					SRT[i][2]++;

				if (SRT[i][2] >= 2 + (1 + 2 * ALL[i][1]))
				{
					SRT[i][2] = 0;
					done++;
					fprintf(log_SRT, "подсчет закончивших задач: текущий такт(TIME)=%d\t завершившихся(done)=%d штук; SRT[%d][0]=%d -  завершена\t    SRT[%d][2]=%d\n",
						TIME, done, i, SRT[i][0], i, SRT[i][2]);
					fprintf(log_SRT, "---------SRT[%d][3]=%d\n",
						i, SRT[i][3]);
				}
			}///2

			if (SRT[i][2] % 2 == 1)//прервана(нечет)
			{
				SRT[i][3] = TIME + ALL[i][SRT[i][2]];//нашли такт, после когторого команда перейдет в состояние готов
				fprintf(log_SRT, "Такт на котором проснется %d SRT[%d][3]= %d + %d = %d\n",
					SRT[i][0], i, TIME, ALL[i][SRT[i][2]], SRT[i][3]);
				SRT[i][2]++;
			}
		}//5
		else if (ready_box_size == 0)
		{
			TIME++;
			fprintf(log_SRT, "работа в холостую. задач в состоянии готов или  новых - нет, Текущий такт = %d \n", TIME);
			//+ в этот такт ждут уже поступившие задачи:
			for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
			{
				if (TIME >= ALL[k][0] && SRT[k][2] != 0)//поступила и не завершена
					SRT[k][1] ++;
			}
			//+
		}
	}
	/////////////////////////////////////////////

	fprintf(log_SRT, "Оставшееся время работы для каждой задачи: \n");
	for (int i = 0; i < SIZE; i++)
	{
		fprintf(log_SRT, " %d %d %d \n", i, ALL[i][0], SRT_box[i]);
	}

	cout << "\n";
	long unsigned int timeSRT = 0;//общее  время всех команд
	/*
	for (int i = 0; i < SIZE; i++)
	{
		cout << SRT[i][0] << "\t";
		cout << SRT[i][1] << "\t";
		cout << SRT[i][2] << "\t";
		cout << SRT[i][3] << "\n";
	}
	*/
	for (int i = 0; i < SIZE; i++)
		timeSRT += SRT[i][1];
	cout << "timeSRT=" << timeSRT << "taktov \n";


	////
	FILE* file = fopen("SRT.txt", "wt");
	{
		fprintf(file, "Time SRT: %d\n\nTime: \n", timeSRT);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", SRT[i][0], SRT[i][1]);
	}
	fclose(file);
	////
	//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] SRT[j];
	delete[] SRT;

	delete[] SRT_box;

	for (int j = 0; j < SIZE; j++)
		delete[] ready_box[j];
	delete[] ready_box;
	//--------------------------------------------
	fclose(log_SRT);
}
#endif 