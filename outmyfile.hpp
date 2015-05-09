#ifndef OUTMYFILE_HPP
#define OUTMYFILE_HPP

#include <iostream>
#include <stdio.h>

int ReadSize()
{
	int size;
	FILE* file = fopen("size.txt", "r");
	fscanf(file, "%d", &size);
	fclose(file);
	return size;
}
void ReadAllFile(long unsigned int **ALL)//для удобства данные переносятся из тхт файла в массив
{
	int SIZE = ReadSize();
	long unsigned int a, n;
	FILE* file = fopen("dano.txt", "rt");

		for (int i = 0; i < SIZE; i++)
		{
			fscanf(file, "%d %d ", &a, &n);
			//std::cout << a << " " << n << " ";
			ALL[i] = new long unsigned int[2 + (1 + 2 * n)];
			ALL[i][0] = a;
			ALL[i][1] = n;
			for (long unsigned int j = 2; j <2 + (1 + 2 * n); j++)
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
