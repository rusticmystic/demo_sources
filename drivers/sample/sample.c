/* A sample character driver */

/* Headers */
#include <linux/init.h>
#include <linux/module.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/device.h>

/* Structures */
struct SampleDevice {
    struct cdev cDevice;
    char        cName[10];
    dev_t       cDevNo;
    struct class* cDeviceClass;
    struct device* Device;
};

static struct SampleDevice SDevice;

/* prototypes */
static int       sample_device_open(struct inode* inode, struct file* filp);
static int       sample_device_close(struct inode* inode, struct file* filp);
static ssize_t   sample_device_read(struct file* filp, char __user *buffer, size_t length, loff_t* offset);
static ssize_t   sample_device_write(struct file* filp, const char __user *buffer, size_t length, loff_t* offset);
long             sample_device_ioctl (struct file *, unsigned int, unsigned long);
int              sample_device_mmap (struct file *, struct vm_area_struct *);

/* File Operations */
static const struct file_operations sample_fops = {
    .owner            = THIS_MODULE,
    .unlocked_ioctl   = sample_device_ioctl,
    .read             = sample_device_read,
    .write            = sample_device_write,
    .mmap             = sample_device_mmap,
    .open             = sample_device_open,
    .release          = sample_device_close
};

static int     sample_device_open(struct inode* inode, struct file* filp)
{
    return 1;
}

static int     sample_device_close(struct inode* inode, struct file* filp)
{
    return 1;
}

static ssize_t sample_device_read(struct file* filp, char __user *buffer, size_t length, loff_t* offset)
{
    return 1;
}

static ssize_t sample_device_write(struct file* filp, const char __user *buffer, size_t length, loff_t* offset)
{
    return 1;
}

long           sample_device_ioctl (struct file *filp, unsigned int command, unsigned long ptr)
{
    return 1;
}

int            sample_device_mmap (struct file *filp, struct vm_area_struct *vma)
{
    return 1;
}

/* Proc Interfaces */



/* Sysfs Interfaces */
ssize_t show_sample_device(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t store_sample_device(struct device *dev, struct device_attribute *attr,
                            const char *buf, size_t count);

static struct device_attribute dev_attr_sample = {
    .attr = {
        .name = "SampleDevice",
        .mode = S_IWUSR | S_IRUGO,
    },
    .show  = show_sample_device,
    .store = store_sample_device,
};

ssize_t show_sample_device(struct device *dev, struct device_attribute *attr, char *buf)
{

    return 0;
}

ssize_t store_sample_device(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{

    return 0;
}

/* Init */
static int __init
init_function (void)
{
    dev_t Major;
    int ret;

    printk ("Super Device Driver Demo...\n");
    printk ("Process Name : %s\n", current->comm);
    printk ("Process PID  : %d\n", current->pid);

    Major = 0;
    strcpy(SDevice.cName,"SDevice");

    ret = register_chrdev_region(Major,0,SDevice.cName);
    if(ret < 0) {
        goto reg_failed;
    }

    SDevice.cDevNo = MKDEV(Major, 0);
    // printk Major
    // cdev related
    cdev_init(&SDevice.cDevice,&sample_fops);

    ret = cdev_add (&SDevice.cDevice,SDevice.cDevNo,1);
    if(ret < 0) {
        goto class_create_failed;
    }

    // Create class and device node
    SDevice.cDeviceClass = class_create(THIS_MODULE, "SampleClass");
    if(SDevice.cDeviceClass < 0) {
        goto class_create_failed;
    }

    SDevice.Device       = device_create(SDevice.cDeviceClass, NULL, SDevice.cDevNo, NULL, "SampleClass_SampleDevice");
    if(SDevice.Device) {
        goto device_create_failed;
    }

    ret                  = device_create_file(SDevice.Device, &dev_attr_sample);
    if (ret < 0) {
        // node not created
    }

    // Set procfs callbacks

    // Set Interrupt callback

    // handle failures
    //
    return (0);

device_create_failed:
    class_unregister(SDevice.cDeviceClass);
    class_destroy(SDevice.cDeviceClass);
class_create_failed:
    unregister_chrdev_region(SDevice.cDevNo,0);
reg_failed:
    return -1;
}

/* Cleanup */
static void __exit
cleanup_function (void)
{
    device_remove_file(SDevice.Device, &dev_attr_sample);
    device_destroy(SDevice.cDeviceClass,  SDevice.cDevNo);
    class_unregister(SDevice.cDeviceClass);
    class_destroy(SDevice.cDeviceClass);
    unregister_chrdev_region(SDevice.cDevNo,0);
    printk ("Bye\n");
}

module_init (init_function);
module_exit (cleanup_function);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Shivdeep");
MODULE_DESCRIPTION ("Demo LDD");
