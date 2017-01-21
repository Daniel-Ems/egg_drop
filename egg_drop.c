#include <stdio.h>
#include <math.h>
#include <sysexits.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "egg.h"

size_t binary (size_t floors);
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

  // Site Mcmaster
  char *bad;
  errno = 0;
  if (argv[1][0] == '-' || argv[2][0] == '-')
    {
      printf ("Negative numbers not allowed");
      return EX_USAGE;
    }

  size_t floors = strtoull (argv[1], &bad, 10);
  if (*bad || errno)
    {
      printf ("Floor Max=UINT_MAX\nNo decimals\nNumbers Only\n");
      return EX_USAGE;
    }


  errno = 0;
  size_t num_drops = strtoull (argv[2], &bad, 10);
  if (*bad || errno)
    {
      printf ("Egg Max=INT_MAX\nEgg Min=1\nNo Decimals\nNumbers only\n");
      return EX_USAGE;
    }


  double half;
  double step;
  double drop;
  int i = 1;
  double min = 0;
  double max = floors;

  egg *test = lay_egg ();
  while (num_drops > 2)
    {
      half = ceil ((max - min) / 2);
      drop = max - half;

      egg_drop_from_floor (test, drop);
      ++count;

      if (egg_is_broken (test))
	{
	  num_drops--;
	  printf ("#%zd CRACK\n", (size_t) drop);
	  destroy_egg (test);
	  test = lay_egg ();
	  max = drop;
	}
      else
	{
	  printf ("#%zd safe\n", (size_t) drop);
	  min = drop;
	  if ((size_t) (min + 1) == (size_t) max)
	    {
	      num_drops = 0;
	      min = max;
	      break;
	    }
	}


    }




  if (num_drops == 2)
    {
      step = max_drops (max);
      drop = min + step;

      while (num_drops > 1)
	{

	  egg_drop_from_floor (test, drop);
	  ++count;

	  if (egg_is_broken (test))
	    {
	      num_drops--;
	      printf ("#%zd CRACKED\n", (size_t) drop);
	      break;
	    }
	  printf ("#%zd safe\n", (size_t) drop);
	  min = drop;
	  drop += step - i;
	  i++;
	  if ((size_t) min == (size_t) floors)
	    {
	      num_drops = 0;
	      min = max + 1;
	      break;
	    }
	}


      destroy_egg (test);
      test = lay_egg ();

    }

  if (num_drops == 1)
    {

      while (num_drops)
	{

	  min++;
	  egg_drop_from_floor (test, min);
	  count++;

	  if (egg_is_broken (test))
	    {
	      num_drops--;
	      printf ("#%zd CRACK\n", (size_t) min);
	      destroy_egg (test);
	      //count++;
	      break;
	    }

	  printf ("#%zd safe\n", (size_t) min);

	  if ((size_t) min == (size_t) floors)
	    {
	      num_drops--;
	      min++;
	      break;
	    }


	}
    }

  printf ("%zd is the maximum safe floor found in %d drops\n",
	  (size_t) min - 1, count);

}



double
max_drops (double floors)
{
  double b = 1;
  double a = 1;
  double c = floors * -2;
  double max_trys = ceil ((-b + sqrt (b * b - 4 * a * c)) / (2 * a));
  //printf("temp before rounding = %lf\n", );

  //int max_drops = ceil(temp);

  printf ("%zd\n", (size_t) max_trys);

  return max_trys;

}
