#include <stdio.h>
#include <math.h>
#include <sysexits.h>
#include <stdint.h>
#include <limits.h>
#include "egg.h"

//bool input_check(char *floors, char *eggs);
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
	long floors = strtol(argv[1], &bad, 10);
	
	//This is checking to make sure the values passed are good values
	if(*bad|| floors > UINT_MAX || floors < 1)
	{
		printf("Floor Max=UINT_MAX\nFloor Min=1\nNo decimals\nNumbers Only\n");
		return EX_USAGE;
	}

	int egg = strtol(argv[2], &bad, 10);
	if(*bad || egg > INT_MAX || egg < 1)
	{
		printf("Egg Max=INT_MAX\nEgg Min=1\nNo Decimals\nNumbers only\n");
		return EX_USAGE;
	}
	
	
	//TODO -> Makefile
	//TODO -> finish this code
	//TODO -> figure out how to round the float up to the nearest int
	//TODO -> figure out if you have more eggs
	//TODO -> Command line input and all that good shit. 
	floors = (floors*8)+1;
	printf("%ld\n", floors);
	floors = sqrt(floors);
	floors = (floors-1)/2;
	//g -= 1;
	printf("%ld", floors);

	

}


