#include <stdio.h>
#include <math.h>
#include <sysexits.h>
#include <stdint.h>
#include <limits.h>

#include "egg.h"

size_t binary(int num_drops, size_t floors);
double max_drops(long floors);
int main(int argc, char *argv[])
{
	//This is checking to make sure the appropriate numbers of arguments 
	//were passed to the program
	if(argc > 3 || argc < 3)
	{
		printf("The format is floors and then eggs\n");
		return EX_USAGE;
		
	}

	char *bad;
	size_t floors = strtol(argv[1], &bad, 10);
	
	//This is checking to make sure the values passed are good values
	if(*bad|| floors > UINT_MAX || floors < 1)
	{
		printf("Floor Max=UINT_MAX\nFloor Min=1\nNo decimals\nNumbers Only\n");
		return EX_USAGE;
	}

	//This is checking to make sure the egg value is good
	int num_drops = strtol(argv[2], &bad, 10);
	if(*bad || num_drops > INT_MAX || num_drops < 1)
	{
		printf("Egg Max=INT_MAX\nEgg Min=1\nNo Decimals\nNumbers only\n");
		return EX_USAGE;
	}
	
	
	size_t half;
	while(num_drops >= 3)
	{
		half = binary(num_drops, floors);
		printf("%zd", half);
	}
	size_t start = max_drops(half);
	printf("start = %zd\n", start);

	size_t drop = start;
	int i = 1;
	size_t prior;
	egg *test = lay_egg();
	for(drop = start; drop < floors; i++)
	{
		egg_drop_from_floor(test, drop);
		if(egg_is_broken(test))
		{
			printf("Egg broke at %zd", drop);
			break;
		}
		printf("drop %zd\n", drop);
		prior = drop;
		drop += start - i;
	}

	while(egg_is_broken(test))
	{
		prior++;
		egg_drop_from_floor(test,drop);
	}

	int max_safe = prior -1;
	printf("max safe %d", max_safe);

	//TODO -> figure out if you have more eggs
	//TODO -> Command line input and all that good shit. 

}

double max_drops(long floors)
{
	double b =1;
	double a= 1;
	double c = floors * -2;

	double max_drops = ceil((-b + sqrt(b*b - 4*a*c)) / (2*a));
	//printf("temp before rounding = %lf\n", );

	//int max_drops = ceil(temp);

	//printf("%d\n", max_drops);

	return max_drops;

}

size_t binary(int num_drops, size_t floors)
{
	size_t drop_point = floors;
	egg *test  = lay_egg();
	
	while(test)
	{
		drop_point /= 2;
		egg_drop_from_floor(test, drop_point);
		size_t temp = drop_point;	
		if(egg_is_broken(test)
		{
			return temp;
		}
	}
}		
	
	


