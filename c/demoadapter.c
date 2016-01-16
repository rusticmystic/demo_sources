#include <stdio.h>
#include <string.h>

#define SIZE 10

typedef struct myadapter
{
  char **array;
  unsigned int size;
  unsigned int row;
  int (*push) (struct myadapter * ad, char *buff);
  unsigned int (*available) (struct myadapter * ad);
  char *(*take) (struct myadapter * ad, unsigned int size);
  unsigned int active_rows;
  long private_data;
} myadapter;

/* My Adapter functions */
unsigned int
myavailable (myadapter * ad)
{


  return 0;
}

int
mypush (myadapter * ad, char *buff)
{
  int size_array = SIZE;

  if (ad->active_rows == SIZE)
    return -1;          /* array full */l

  printf("\nSize of buff = %d\n",strlen (buff));
  ad->array[ad->row] = malloc (strlen (buff));

  /*memcpy into array */
  memcpy (ad->array[ad->row], buff, sizeof (buff));
  ad->row++;
  ad->active_rows++;

  return 0;
}

unsigned int
mytake (struct myadapter *ad, unsigned int size)
{


  return 0;
}



int
main ()
{

  char *data = "This is the data , which i want to push in the buffer";

  myadapter adt;
  myadapter *ad = &adt;
    ad->array = (char *) malloc (SIZE);
/* initialise*/
  adt.size = 0;
  adt.row = 0;
  adt.active_rows=0;
  /* adding function pointers */
  adt.push = mypush;
  adt.take = mytake;
  adt.available = myavailable;

 /*--add data to buffer -*/
  adt.push (ad, data);

/* see data */
  printf ("\n The data is %s and size of=%d\n", ad->array[0],sizeof(ad->array[0]));

  return 0;
}
