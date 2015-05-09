#ifndef CREATEFILE_HPP
#define CREATEFILE_HPP

#include <iostream>
#include <stdio.h>
#include <time.h>

//----------------------------------------
long unsigned int T;// длительность одной команды 
int pre;// общее число прерываний задачи
long unsigned int t;//время одного прерывания
//----------------------------------------
void WriteSize(int size)
{
	FILE* file = fopen("size.txt", "w");
	fprintf(file, "%d", size);
	fclose(file);
}
double interval_rand(double a, double b)//[a;b]
{
	return a + (b - a) * rand() / (RAND_MAX);
}
void WriteFile()// запускается 1 раз для создания исходных данных
{
	FILE* file = fopen("dano.txt", "w");
	int SIZE = 10;//общее число поступивших задач
	WriteSize(SIZE);

	srand(time(NULL));

	long unsigned int rnd = 0;//промежуток между появлениями новых задач
	long unsigned int i = 1;//номер такта
	int created_comands = 0;

	double x;

	do {
		i = i + rnd;
		
		rnd = rand() % 100000 + 1000;//[1000;100000]//те задачи поступают каждые 1000000-100000000 тактов

		//T = (rand() % 100 + 10);//[10;100] длительность 1 команды = 10,....,100 тактов 
		//pre = rand() % 10;//[0;10] 0=> нет прерывания

		x = interval_rand(0., 1.);
		pre = int(0 - 1 * log(x) * 100);//0-999

		x = interval_rand(0., 1.);
		T = long unsigned int(0 - 1 * log(x) * 100000+1);//[1-?]
		

		fprintf(file, "%d", i);
		fprintf(file, " %d", pre);

		//takt_pre = i;
		if (pre == 1)
		{
			//T = (rand() % 100 + 10);
			x = interval_rand(0., 1.);
			T = long unsigned int(0 - 1 * log(x) * 100000 + 1);//[1-?]
			fprintf(file, " %d", T);

			//t = rand() % 10 + 1;
			x = interval_rand(0., 0.2);
			t = long unsigned int(0 - 1 * log(x) * 100000 + 1);//[1-?]
			fprintf(file, " %d", t);

			//T = (rand() % 100 + 10);
			x = interval_rand(0., 1.);
			T = long unsigned int(0 - 1 * log(x) * 100000 + 1);//[1-?]
			fprintf(file, " %d", T);
		}
		else if (pre != 0)
			for (int j = 1; j <= pre + 1; j++)
			{
			//T = (rand() % 100 + 10);
			x = interval_rand(0., 1.);
			T = long unsigned int(0 - 1 * log(x) * 100000 + 1);//[1-?]
			fprintf(file, " %d", T);

			if (j != pre + 1)
			{
				//t = rand() % 10 + 1;
				x = interval_rand(0., 0.2);
				t = long unsigned int(0 - 1 * log(x) * 100000 + 1);//[1-?]
				fprintf(file, " %d", t);
			}
			}
		else
		{
			fprintf(file, " %d", T);
		}
		fprintf(file, "\n");
		created_comands++;

	} while (created_comands <= SIZE);// =>создали SIZE команд!

	fclose(file);
}
#endif 