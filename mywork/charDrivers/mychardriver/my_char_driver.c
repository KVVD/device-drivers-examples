
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // required for various structures related to files liked 
#include <asm/uaccess.h> // required for copy_from and copy_to user functions
#include <linux/semaphore.h>
#include <linux/cdev.h>


#define MYDEVNAME "mycharDev"
struct cdev *k_cdev;
dev_t dev_no, dev;
int major_num;

char kern_buff[128];



int my_open(char *dev_name, int flags)
{
    printk("\nOpening device: %s\n", MYDEVNAME);
    return 0;
}

int  my_read(struct file *fp_dev, 
             char *usrspace_buf, 
             size_t count, 
             loff_t *curr_pos_fpdev)
{
    int ret;
   // the memcpy between userspace and kernel space pointers can't be done directly. 
   // because, when kernel try to use an userspace pointer, the associated page may not be 
   // present by that time. so page fault can occur.
   // so use "int copy_to_user(void *to, const void *from, int count); OR
   //        "int copy_from_user(void *to, const void *from, int count);
    
    ret = copy_to_user(usrspace_buf, kern_buff, count);
    return ret;
}


int  my_write(struct file *fp_dev, 
             char *usrspace_buf, 
             size_t count, 
             loff_t *curr_pos_fpdev)
{
    int ret;

    ret = copy_from_user(kern_buff, usrspace_buf, count);
    return ret;
}


struct file_operations fops =
{
    open: my_open,
    read: my_read,
    write: my_write
};

int mychar_driver_init(void)
{
    int result;

    printk("char driver init....\n");

    k_cdev = cdev_alloc();
    k_cdev->ops = &fops;    
    k_cdev->owner = THIS_MODULE;

    result = alloc_chrdev_region(&dev_no, 0, 1, MYDEVNAME);
    if (result < 0)
    {
        printk("device allocation failed.. %s\n", MYDEVNAME);
        return result;
    }

    major_num = MAJOR(dev_no);
    printk("Major Number: %d\n", major_num);

    dev = MKDEV(major_num, 0);
    result = cdev_add(k_cdev, dev, 1);
    
    if(result < 0)
    {
        printk("char driver init done....\n");
        return result;
    }

    return 0;
}

void  mychar_driver_exit(void)
{
    printk("char driver exit...\n");
    
    cdev_del(k_cdev);
    unregister_chrdev_region(major_num, 1);
}



module_init(mychar_driver_init);
module_exit(mychar_driver_exit);
