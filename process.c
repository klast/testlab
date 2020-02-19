#include <stdbool.h>
#include <math.h>
/*Находим квадрат числа*/
int find(double num,bool is_max)
{
//Если num - максимальное число,
//то нам нужен ближайший квадрат <= num
	if(is_max)
	{
		int res = sqrt(num);
		return res*res;
	}
//если num - минимум
	else
	{
		int res = sqrt(num) + 1;
		//printf("res = %i\n",res);
		return res*res;
	}
}

/*Разница между минимальным и максимальным квадратом
в отрезке от first до second(или наоборот)*/

int Process(double first, double second)
{
	bool more;
	if (first>second)
		more = true;
	else
		more = false;
	if (more)
	{
		return find(first,true) - find(second,false);
	}
	else
	{
		return find(second,true) - find(first,false);
	}
}
