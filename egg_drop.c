#include <stdio.h>
#include <math.h>
#include <sysexits.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "egg.h"

//double linear_search(double min, int *count, size_t *num_drops, size_t floors);
double max_drops (double floors);
int
main (int argc, char *argv[])
{
  int count = 0;
  //This is checking to make sure the appropriate numbers of arguments 
  //were passed to the program
  if (argc > 3 || argc < 3)
    {
      printf ("The format is floors and then eggs\n");
      return EX_USAGE;
    }

  //This checks for negative numbers
  if (argv[1][0] == '-' || argv[2][0] == '-')
    {
      printf ("Negative numbers not allowed\n");
      return EX_USAGE;
    }

  // Site McMaster --> McMaster found, and then explained that way to handle
  // potentially dealing with numbers too large.
  char *bad;
  errno = 0;
  size_t floors = strtoull (argv[1], &bad, 10);
  if (*bad || errno)
    {
      printf ("Floor Max=UINT_MAX\nNo decimals\nNumbers Only\n");
      return EX_USAGE;
    }

  //McMaster is also sited here for the same reason, however, it is being
  //applied to the other argument.
  errno = 0;
  size_t num_eggs = strtoull (argv[2], &bad, 10);
  if (*bad || errno)
    {
      printf ("Egg Max=INT_MAX\nEgg Min=1\nNo Decimals\nNumbers only\n");
      return EX_USAGE;
    }

  double half, step, drop; 
  double min = 0;
  double max = floors;

  //This is the beginning of the program checks for the first 

  if(num_eggs> 2)
	{
		egg *Binedict = lay_egg ();
  //The first case is to check and use any eggs over two to perform binary
  //searches. This for loop, will continue to perform binary searches as long
  //as either the number has not been found, or their are only two eggs left.
  while (num_eggs > 2)
    {
	  
	  //half is used to find the next point in the binary search
	  half = ceil ((max - min) / 2);		
	  
      drop = max - half;
	   
  	  //Here we drop the egg and increment our counter
      egg_drop_from_floor (Binedict, drop);
      ++count;

	  //This will check if the egg is broken. If so, we will subtract from our 
	  //num_eggs, and set up the program for it's next pass. 
      if (egg_is_broken (Binedict))
	{
	  printf ("#%zd CRACK\n", (size_t) drop);

      //Decrementing the eggs is necessary to know which formula to run
	  num_eggs--;	
	  
	  //This destroy will catch the first egg laid, and any others produced by 
	  //this function.
	  destroy_egg (Binedict);
	  Binedict = lay_egg ();
	  max = drop;
	}
	  //if the egg is not broken we need to update our min.
      else 
	{
	  printf ("#%zd safe\n", (size_t) drop);
	  min = drop;

	  //This prevents an instance of our binary being within 1 of our max. 
	  //causing the program looping.
	  if((size_t)drop == (size_t)(max-1))
	  {
      	  num_eggs = 0;
		  min = max+1;
	      break;
	  }
	  
	}

    }
	destroy_egg(Binedict);
	}

  //The following statement is used when there are only two eggs remaining. 
  //This allows for the most consistantly efficient search.

  int i = 1;
  if (num_eggs == 2)
    {
	  egg *Humpty = lay_egg();
	  //This will return the incrementing value for qudratic search
      step = max_drops (max);
     
      //this will determine our first place to drop
      drop = min + step;

	//The quadratic search wil only be 
      while (num_eggs > 1)
	{

	  egg_drop_from_floor (Humpty, drop);
	  ++count;

	  if (egg_is_broken (Humpty))
	    {
	      num_eggs--;
	      printf ("#%zd CRACK\n", (size_t) drop);
	      max=drop;
	      break;
	    }
	  printf ("#%zd safe\n", (size_t) drop);
		
	  //The quadratic search works because of the following increment formula
      //the summation is used to balance present counts against the risk of 
	  //potential future counts. 
	  min = drop;
	  drop += step - i;
	  i++;

	  //This makes sure that if the min doesn't run past the max floor
	  if ((size_t) min == (size_t) max)
	    {
	      num_eggs = 0;
	      min++;
	      break;
	    }
	}
	destroy_egg(Humpty);
    }
  
  //This will implement the linear search when there is one egg
  if (num_eggs == 1)
    {
      egg *Dumpty = lay_egg ();
	
	//This will simply walk forward until your egg cracks
      while (num_eggs)
	{

	  min++;
	  egg_drop_from_floor (Dumpty, min);
	  count++;

	  if (egg_is_broken (Dumpty))
	    {
	      num_eggs--;
	      printf ("#%zd CRACK\n", (size_t) min);
	      break;
	    }

	  printf ("#%zd safe\n", (size_t) min);

	  if ((size_t) (min+1) == (size_t) max)
	    {
	      num_eggs--;
	      min++;
	      break;
	    }


	}
	destroy_egg(Dumpty);
	}

  printf ("%zd is the maximum safe floor found in %d drops\n",
	  (size_t) min - 1, count);

}
/*******************************************************************************
Max_drops applies the quadratic formula to value passed, and then returns it to 
program. Before the qudratic formula is applied, the value passed is multiplied
by a -2. This comes from the formula N*(N+1)/2=floors. This, in addition with
the quadratic formula provides the first step, as well as the incrementing value
to be applied between min and max.

---> Site Ciullo <---
The programmed formula was programmed earlier in the course. Ciullo helped me to
locate a good working version of the formula. 
*******************************************************************************/
double
max_drops (double floors)
{
  double b = 1;
  double a = 1;
  double c = floors * -2;
  double max_trys = ceil ((-b + sqrt (b * b - 4 * a * c)) / (2 * a));

  return max_trys;

}


 
