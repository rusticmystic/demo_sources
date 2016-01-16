/* Author: Shivdeep Singh
 *
 * Description : A beautiful program to print nth digit of a number from right without using shifting operations or bitwise and/or
 * */

#include <stdio.h>

struct nibble
{
  char nibble2:4;
  char nibble1:4;
};

unsigned int
nth_nibble (void *number, int n)
{
  struct nibble *n1 = (struct nibble *) number;
  unsigned int k;
  if (n % 2)
    {
      k = n1[(int) (n / 2)].nibble1;
    }
  else
    {
      k = n1[(int) ((n - 1) / 2)].nibble2;
    }

  return k;
}

int
main ()
{
  unsigned int x = 0x123456;
  int digit_no;
  int digit;
  struct nibble *p;

/*  add values */
  digit_no=3;
  digit_no--;


  p = (struct nibble *) &x;

  printf ("\n %uth digit from right %u\n", digit_no, nth_nibble (p,digit_no));

  return 0;
}
