#ifndef OUTMYFILE_HPP
#define OUTMYFILE_HPP

#include <iostream>
#include <stdio.h>
/*
void WriteResult(int Number, int Time)//  для создания результата выполнения...
{
	FILE* file = fopen("result.txt", "a");
	fprintf(file, "%d %d\n", Number, Time);
	fclose(file);
}
*/
void ReadAllFile(int **ALL)//для удобства данные переносятся из тхт файла в массив
{
	int a, n;
	FILE* file = fopen("dano.txt", "rt");

		///while (!feof(file))//пока файл дочитан не до конца...
		for (int i = 0; i < SIZE; i++)
		{
			fscanf(file, "%d %d ", &a, &n);
			//std::cout << a << " " << n << " ";
		ALL [i]= new int [2+(1+2*n)];
			ALL[i][0] = a;
			ALL[i][1] = n;
			for (int j = 2; j <2+(1+2*n); j++)
			{
				fscanf(file, "%d ", &a);
				ALL[i][j] = a;
				//std::cout << a << " ";
			}
		fscanf(file, "\n");
		//std::cout << std::endl;
		}
	fclose(file);
}

#endif 


//////////////////////////////////////////////////////////
/*int ReadOneElement(int str)//считывает 2-й элемент строки
{
	if (str>SIZE || SIZE <= 0)
		return 0;
	else
	{
		int a = 0, b = 0;
		FILE* file = fopen("dano.txt", "rt");

		if ((file = fopen("dano.txt", "rt")) == 0)
		{
			//std::cout<<"ERROR!!!";
			return 0;
		}

		for (int i = 0; i<str; i++)
		{
			fscanf(file, "%d %d \n", &a, &b);
			//std::cout<<a<<" "<<b<<std::endl;
		}
		fclose(file);
		return b;
	}
}
*/