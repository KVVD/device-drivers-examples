
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // required for various structures related to files liked 
#include <asm/uaccess.h> // required for copy_from and copy_to user functions
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>

#define MYDEVNAME "myIoctlDev"

struct cdev *k_cdev;
dev_t dev_no, dev;
int major_num;



int my_ioctl(struct file *fp_dev,
            unsigned int cmd,
            unsigned int temp)
{
    int ret = 0;

    printk("my_ioctl()....entered. \n");

    return ret;
}
struct file_operations fops =
{
    ioctl: my_ioctl,
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
