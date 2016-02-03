/*
 *A Demo Program for using gobject and glib library
 * Shivdeep Singh <shivdeep@khalsa.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/* This program demonstrates declaring a class and using it using glib and gobject system
 * */

/* headers */
#include <glib-2.0/glib.h>
#include <glib-2.0/glib-object.h>
#include <gst/gst.h>

/*  structures */
struct _MyBox
{
  GObject parent;
  gint32 width;
  gint32 height;
  gint32 length;
};

struct _MyBoxClass
{
  GObjectClass parent_class;
  guint32 (*volume) (struct MyBox * object);
};

/* setting data type */
GType my_box_get_type (void);

typedef struct _MyBox MyBox;
typedef struct _MyBoxClass MyBoxClass;

/* boiler plate convenience macros*/

#define MY_TYPE_BOX            (my_box_get_type())
#define MY_BOX(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj),MY_TYPE_BOX,MyBox))
#define MY_BOX_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass),MY_TYPE_BOX,MyBoxClass))
#define MY_IS_BOX(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj),MY_TYPE_BOX))
#define MY_IS_BOX_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),MY_TYPE_BOX))
#define MY_BOX_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), MY_TYPE_BOX, MyBoxClass))

/* the new gtype has to be registered to the gobject system */

/* this can also be detailed if we want to add our own finalise etc methods*/
G_DEFINE_TYPE (MyBox, my_box, G_TYPE_OBJECT);

/* prototypes and func */
guint32
volume (MyBox * this)
{
  g_print ("Volume Function ");
  g_print ("\nLength = %d, Width= %d, height = %d\n", this->length,
       this->width, this->height);
  return (this->length * this->width * this->height);
}

/* init methods  class and base init*/
static void
my_box_class_init (MyBoxClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  /* assign the function pointers in class init function */
  klass->volume = volume;
  g_print ("Class Init\n");
}

static void
my_box_init (MyBox * this)
{
  g_print ("Instance Init\n");
  this->length = 0;
  this->width = 0;
  this->height = 0;
}

guint32
my_box_volume (MyBox * this)
{

  MyBoxClass *cubeClass;
  cubeClass = MY_BOX_GET_CLASS (this);
  g_print ("Volume Function Accesor Function");
  return cubeClass->volume (this);
}

/* main code */
int
main (int argc, char *argv[])
{
  g_print ("Demo program using gobject \n");
  /* instantiate an instance of the object MyBox */
  /* Initialise types system */
  g_type_init ();
  /* create instance of object  */
  MyBox *cube;
  cube = g_object_new (MY_TYPE_BOX, NULL);
  cube->height = 10;
  cube->width = 10;
  cube->length = 10;
  /* calling method from the class */
  g_print ("\nThe volume of the cube is %d\n", my_box_volume (cube));
  g_object_unref (cube);
  return 0;
}
