/*Demo file to write superlogger 
 * Author: Shivdeep Singh */

#include <linux/init.h>
#include <linux/module.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/slab.h>

/* Structures  */
#define TEXT_LENGTH 256
#define TRUE 1
#define FALSE 0

static int hello_data __initdata = 10;

struct mybuff_t
{
  struct list_head a;
  char *data;
  int length;
};

typedef struct mybuff_t buffer;

struct debugAdapter
{
  struct mutex Lock;		/* mutex to write into this */
  buffer *buffer;		/*buffer list */
  long parent;
};

typedef struct debugAdapter dbgAdapter;

struct superLogger
{
//static LIST_HEAD(adapter);
  int a;
  dbgAdapter *Adapter;
};

#define INIT_ADAPTER_LOCK(Adapter) mutex_init(&Adapter->Lock)
#define LOCK_ADAPTER(Adapter) mutex_lock(&Adapter->Lock)
#define UNLOCK_ADAPTER(Adapter) mutex_unlock(&Adapter->Lock)

/* debug log utility API's*/
long bufferNew ();
bool bufferAddData (long listpointer, long datapointer);
bool bufferFree (long buffer);
long bufferListNew ();
bool bufferListFree (long bufferlist);
long debugAdapterNew ();
bool debugAdapterFree (long pointer);
bool debug_print (long context, const char *format, ...);
long bufferListTakeData (long bufferlist);

/*Debug API definitions*/
long
bufferNew ()
{
  buffer *temp = NULL;
  temp = (buffer *) kmalloc (sizeof (buffer), GFP_KERNEL);

  printk ("\nIn bufferNew");
  if (!temp)
    {
      printk ("Could not allocate buffer...\n");
      return 0;
    }
  temp->data = (char *) kmalloc (TEXT_LENGTH * sizeof (char), GFP_KERNEL);
  return (long) temp;
}

bool
bufferAddData (long listpointer, long datapointer)
{
  if (!listpointer || !datapointer)
    {
      return FALSE;
    }

  return;
}

bool
bufferFree (long buffer)
{
  if (!buffer)
    {
      return FALSE;
    }
  kfree (buffer);

  return TRUE;
}

long
bufferListNew ()
{
  buffer *temp = NULL;
  temp = (buffer *) kmalloc (sizeof (buffer), GFP_KERNEL);
  if (!temp)
    {
      printk ("Could not allocate buffer...\n");
      return 0;
    }
  return (long) temp;
}

bool
bufferListFree (long bufferlist)
{
  if (!bufferlist)
    {
      return -1;
    }

  return;
}

long
debugAdapterNew ()
{
  dbgAdapter *temp = NULL;
  temp = (dbgAdapter *) kmalloc (sizeof (dbgAdapter), GFP_KERNEL);
  if (!temp)
    {
      printk ("Could not allocate buffer...\n");
      return 0;
    }
  return (long) temp;
}

bool
debugAdapterFree (long pointer)
{
  if (pointer)
    {
      kfree (pointer);
      return TRUE;
    }
  return FALSE;
}

bool
debug_print (long context, const char *format, ...)
{
  buffer *buf;
  struct superLogger *sLogger;
  dbgAdapter *Ad;
  printk ("\nIn debug_print");

  if (!context)
    {
      return FALSE;
    }

  sLogger = (struct superLogger *) context;
  Ad = sLogger->Adapter;

  va_list arg_list;
  va_start (arg_list, format);
  /* Allocate buffer and add it to buffer list */
  buf = (buffer *) bufferNew ();
  if (buf->data)
    {
      vsprintf (buf->data, format, arg_list);
    }
  return;
}

long
bufferListTakeData (long bufferlist)
{
  return;
}

/*other datta structures*/
long context;
struct superLogger logger;

/* Init and Cleanup*/
static int __init
init_function (void)
{
  //struct superlogger *temp;
  printk ("\n");
  printk ("Super Logger Demo...\n");
  printk ("Process Name : %s\n", current->comm);
  printk ("Process PID  : %d\n", current->pid);

  //temp =(long)&logger;
  /*initialise adapter */
  logger.Adapter = debugAdapterNew ();
  if (!logger.Adapter)
    return;
  printk ("\nAdapter pointer is %p\n", logger.Adapter);


  return (0);
}

static void __exit
cleanup_function (void)
{
  debugAdapterFree (logger.Adapter);
  printk ("Bye\n");
}

module_init (init_function);
module_exit (cleanup_function);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Shivdeep");
MODULE_DESCRIPTION ("Demo LDD");
