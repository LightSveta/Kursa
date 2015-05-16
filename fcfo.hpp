#ifndef FCFO_HPP
#define FCFO_HPP

using namespace std;///

/*
0й столбец= №такта начала команды
1й столбец= время простоя+ время выполнения команды+...
2й -флаг(позиция в массиве)
	3,4...-указатель на каком этапе выполнения находится команда
3й -на каком такте команда перейдет в состояние готов
	(пересчитывается по мере надобности)

	если FCFO[i][2]==0 - то завершена
*/

void function_FCFO(long unsigned int **ALL, int SIZE)
{
	FILE* log_FCFO = fopen("log_FCFO.txt", "w");
	//cout << "***+++ 34%2 " << 34 % 2 << "  33%2 " << 33 % 2 << "   0%2  " << 0 % 2 << "+++***" << endl;
	//	   =>  четные%2==0       нечетные%2==1
	long unsigned int ** FCFO = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFO[j] = new long unsigned int[4];
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

	"вывод":
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
		FCFO[i][0] = ALL[i][0];
		FCFO[i][1] = 0;
		FCFO[i][2] = 2;
		FCFO[i][3] = 0;
	}

///////////////////////////////////
	int flag;
	int flag1;
	int flag2=0;
	while (done < SIZE)
	{
		flag = 0;//нет никаких команд
		flag1 = 0;//есть только заблокированные команды
		int befor_TIME;
		for (int i = 0; i < SIZE; i++)
		{
			if (flag2 == 1) i = 0;
			flag2 = 0;
			if (TIME >= ALL[i][0] && FCFO[i][2] != 0 && TIME >= FCFO[i][3])//может выполняться(поступила & не завершена &в состоянии готов )
			{//1
				if (FCFO[i][2] % 2 == 0 || flag1 == 0)// НЕ прервана(чет)
					// || есть только заблокированные команды
				{///2
					befor_TIME = TIME;
					TIME += ALL[i][FCFO[i][2]];
					FCFO[i][1] += ALL[i][FCFO[i][2]];//работает
					flag = 1;
					//FCFO[i][2]++;//!!!!!!!
					//состояние ожидания........
					//if (FCFO[i][2] < 2 + (1 + 2 * ALL[i][1]) && FCFO[i][2] % 2 == 1)//прервана(нечет)
					//	FCFO[i][3] = TIME + ALL[i][FCFO[i][2]];//нашли такт, после когторого команда перейдет в состояние готов
					//	cout << "***TIME=" << TIME << "  befor_TIME=" << befor_TIME << "   for " << FCFO[i][0]
					//	<< "   what +=" << ALL[i][FCFO[i][2]] << endl;
					fprintf(log_FCFO, "*текущий такт(TIME)=%d\t befor_TIME=%d\tFCFO[%d][0]=%d\tALL[%d][%d]=%d \n",
						TIME, befor_TIME, i, FCFO[i][0], i, FCFO[i][2], ALL[i][FCFO[i][2]]);
					fprintf(log_FCFO, "---------FCFO[%d][3]=%d\n",
						i, FCFO[i][3]);
					flag2 = 1;

					for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
					{//3
						//if (TIME <= ALL[i][0])//не поступила
						//break;
						//else
						if (TIME >= ALL[k][0] && FCFO[k][2] != 0 && i != k && TIME >= FCFO[k][3])//может выполняться и не завершена и не является текущей и закончилось прерывание
						{////4
							if (befor_TIME <= ALL[k][0] && FCFO[k][2] != 0)//если с предыдущего шага готова к работе
								//те. появилась во время работы другой команды
							{
								FCFO[k][1] += TIME - FCFO[k][0];//остальные ждут
								//	cout << "TIME=" << TIME << "  befor_TIME=" << befor_TIME << "    for" << FCFO[k][0]
								//		<< "   what +=" << TIME - FCFO[k][0] << endl;
								fprintf(log_FCFO, "ожидающие(1тип): текущий такт(TIME)=%d\tbefor_TIME=%d\tFCFO[%d][0]=%d\t TIME-FCFO[%d][0]=%d\n",
									TIME, befor_TIME, i, FCFO[k][0], i, TIME - FCFO[k][0]);
								fprintf(log_FCFO, "---------FCFO[%d][3]=%d\n",
									i, FCFO[i][3]);

							}
							else if (FCFO[k][2] != 0)
							{
								FCFO[k][1] += ALL[i][FCFO[i][2]];//остальные ждут
								//cout << "TIME=" << TIME << "  befor_TIME=" << befor_TIME << "    for" << FCFO[k][0]
								//	<< "   what +=" << ALL[i][FCFO[i][2]]
								//	<< "   from  =" << FCFO[i][0] << endl;

								fprintf(log_FCFO, "ожидающие(2тип): текущий такт(TIME)=%d\tbefor_TIME=%d\t for FCFO[%d][0]=%d\t  this ALL[%d][%d]=%d from FCFO[%d][0]=%d\n",
									TIME, befor_TIME, i, FCFO[k][0], k, FCFO[i][2], ALL[i][FCFO[i][2]], i, FCFO[i][0]);
								fprintf(log_FCFO, "---------FCFO[%d][3]=%d\n",
									i, FCFO[i][3]);
							}
						}////4

					}//3
					FCFO[i][2]++;
					if (FCFO[i][2] % 2 == 0)
					{
						flag1 = 1;
					}

					if (FCFO[i][2] >= 2 + (1 + 2 * ALL[i][1]))
					{
						FCFO[i][2] = 0;
						done++;

						//	cout << TIME << " done=" << done << " FCFO[i][0]=" << FCFO[i][0] << " FCFO[i][2]=" << FCFO[i][2] << "\n";
						fprintf(log_FCFO, "подсчет закончивших задач: текущий такт(TIME)=%d\t завершившихся(done)=%d штук; FCFO[%d][0]=%d -  завершена\t    FCFO[%d][2]=%d\n",
							TIME, done, i, FCFO[i][0], i, FCFO[i][2]);
						fprintf(log_FCFO, "---------FCFO[%d][3]=%d\n",
							i, FCFO[i][3]);
					}

				}
				///2

				if (FCFO[i][2] % 2 == 1)//прервана(нечет)
				{
					FCFO[i][3] = TIME + ALL[i][FCFO[i][2]];//нашли такт, после когторого команда перейдет в состояние готов
					fprintf(log_FCFO, "Такт на котором проснется %d FCFO[%d][3]= %d + %d = %d\n",
						FCFO[i][0], i, TIME, ALL[i][FCFO[i][2]], FCFO[i][3]);
					FCFO[i][2]++;
					flag1 = 1;
				}
				i = 0;
			}//1

		}
		if (flag == 0)
		{
			TIME++;
			fprintf(log_FCFO, "работа в холостую. задач в состоянии готов или  новых - нет, Текущий такт = %d \n", TIME);
			//+ в этот такт ждут уже поступившие задачи:
			for (int k = 0; k < SIZE; k++)//проход по массиву(увеличиваем время простаивающим командам(готовым к выполнению))
			{
				if (TIME >= ALL[k][0] && FCFO[k][2] != 0)//поступила и не завершена
					FCFO[k][1] ++;
			}
			//+
		}
	}
	
/////////////////////////////////////////////
	cout << "\n";
	long unsigned int timeFCFO = 0;//общее  время всех команд

	//

	/*
	for (int i = 1; i < SIZE; i++)
	{
		FCFO[i][1]--;
	}
	*/

	//
	
	for (int i = 0; i < SIZE; i++)
	{
	cout << FCFO[i][0] << "\t";
	cout << FCFO[i][1] << "\t";
	cout << FCFO[i][2] << "\t";
	cout << FCFO[i][3] << "\n";
	}
	
	for (int i = 0; i < SIZE; i++)
		timeFCFO += FCFO[i][1];
	cout << "timeFCFO=" << timeFCFO << "taktov \n";


////
	FILE* file = fopen("FCFO.txt", "wt");
	{
		fprintf(file, "Time FCFO: %d\n\nTime: \n", timeFCFO);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", FCFO[i][0], FCFO[i][1]);
	}
	fclose(file);
////
//--------------------------------------------
	for (int j = 0; j < SIZE; j++)
		delete[] FCFO[j];
	delete[] FCFO;
//--------------------------------------------
	fclose(log_FCFO);
}

//++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++

void function_FCFO_(long unsigned int **ALL, int SIZE)
{
	/* несколько видоизменненный алгоритм function_FCFO:
	первая команда пришла и выполняется до своего завершения
	(даже если прервалась,то все остальные будут ждать ее завершения)
	*/

	long unsigned int ** FCFO = new long unsigned int *[SIZE];
	for (int j = 0; j < SIZE; j++)
		FCFO[j] = new long unsigned int[3];

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
	long unsigned int TIME = 1;//на каком сейчас такте

	long unsigned int start = ALL[TIME][0];//такт начала текущей команды
	long unsigned int t_pre = 0;//время прерывания 
	long unsigned int t = ALL[TIME][3];//время работы
	//i=[0;size];j=[3;(1+2*ALL[i][1])] j=j+2; 
	// 2<= t <  2 + (1 + 2 * ALL[i][1])
	// количесво t: 1+ALL[i][1]

	for (int i = 0; i < SIZE; i++)
	{
		FCFO[i][0] = ALL[i][0];
		FCFO[i][1] = 0;
		FCFO[i][2] = 0;
	}

	///////////////////////////////////
int	flag = 0;
	while (done < SIZE)
	{
		flag = 0;
		for (int i = 0; i < SIZE; i++)
		{
			if (TIME >= ALL[i][0] && FCFO[i][2] != 1)//может выполняться и не завершена
			{
				flag = 1;
				for (long unsigned int j = 2; j < 2 + (1 + 2 * ALL[i][1]); j++)
				{
					FCFO[i][1] += ALL[i][j];//для случая: пока текущая команда не завершится
					//(даже если прервалась), следующая не начнется
					long unsigned int befor_TIME = TIME;
					TIME += ALL[i][j];


					//cout << "***TIME=" << TIME << "  befor_TIME=" << befor_TIME << "   for " << FCFO[i][0]
					//	<< "   what +=" << ALL[i][j] << endl;

					int working = i;

					for (int k = 0; k < SIZE; k++)
					{
						if (TIME <= ALL[i][0])
							break;
						else
							if (TIME > ALL[k][0] && FCFO[k][2] != 1 && working != k)//может выполняться и не завершена 
							{
							if (befor_TIME <= ALL[k][0])//если с предыдущего шага готова к работе
								{

								FCFO[k][1] += TIME - FCFO[k][0];//остальные ждут
								//cout << "TIME=" << TIME << "  befor_TIME=" << befor_TIME << "    for" << FCFO[k][0]
								//	<< "   what +=" << TIME - befor_TIME << endl;
								}
							else
								{
								FCFO[k][1] += ALL[i][j];//остальные ждут
								//cout << "TIME=" << TIME << "  befor_TIME=" << befor_TIME << "    for" << FCFO[k][0]
								//	<< "   what +=" << ALL[i][j]
								//	<< "   from  =" << FCFO[i][0] << endl;
								}
							}
					}
				}
				FCFO[i][2] = 1;//команда завершилась
				done++;
				break;
			}
		}
		if (flag == 0)TIME++;//если нет никаких задач готовых к выполнению - простой комп. 
	}
	/////////////////////////////////////////////

	long unsigned int timeFCFO = 0;//общее  время всех команд

	//
	for (int i = 1; i < SIZE; i++)
	{
		FCFO[i][1]--;
	}

	for (int i = 0; i < SIZE; i++)
		timeFCFO += FCFO[i][1];
	////
	FILE* file = fopen("FCFO_.txt", "wt");
	{
		fprintf(file, "Time FCFO_: %d\n\nTime: \n", timeFCFO);
		for (int i = 0; i < SIZE; i++)
			fprintf(file, "%d\t%d\n", FCFO[i][0], FCFO[i][1]);
	}
	fclose(file);
	////

	for (int j = 0; j < SIZE; j++)
		delete[] FCFO[j];
	delete[] FCFO;
}
#endif 