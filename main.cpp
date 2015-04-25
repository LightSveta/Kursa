#include "createfile.hpp"

#include "fcfo.hpp"
#include "RR.hpp"
#include "sgn.hpp"
#include "srt.hpp"

#include "outmyfile.hpp"

#include <iostream>
using namespace std;


const int ONE_TAKT = 600;// размер 1 такта в пико-секундах=600при частоте 1.8 ГГерц(подсчеты в листке)
int ** ALL_COMMANDS = new int *[SIZE];//в этом массиве хранится все о командах

void main()
{
	//WriteFile();//создать файл
	
	ReadAllFile(ALL_COMMANDS);//заполняет массив ALL_COMMANDS[size][ALL_COMMANDS[i][1]]
	
	//пример для вывода всего содержимого ALL_COMMANDS[][]
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < 2+(1+2*ALL_COMMANDS[i][1]); j++)
		{
			cout << ALL_COMMANDS[i][j] << " ";
		}
		cout << endl;
	}
	
	//время затраченное на все команды по порядку (пока не выполнится, следующая не начнется выполняться)
	
	int Xtime = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 2; j < 2 + (1 + 2 * ALL_COMMANDS[i][1]); j++)
			Xtime += ALL_COMMANDS[i][j];
	cout << "Xtime=" << Xtime << "taktov \n";
	//меньше Xtime не должно получиться в результате вычислений алгоритмов
	//здесь не учитывается то, что поступившие команды ждут своей очереди

	function_FCFO_(ALL_COMMANDS);

	function_FCFO(ALL_COMMANDS);

	ReadAllFile(ALL_COMMANDS);
	function_RR();

	ReadAllFile(ALL_COMMANDS);
	function_SJN();
	
	ReadAllFile(ALL_COMMANDS); 
	function_SRT();

//----------------------------------
	for (int i = 0; i < SIZE; i++)
			delete [] ALL_COMMANDS[i];
	delete [] ALL_COMMANDS;
	

}