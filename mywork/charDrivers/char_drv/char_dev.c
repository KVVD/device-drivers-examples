
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // required for various structures related to files liked 
#include <asm/uaccess.h> // required for copy_from and copy_to user functions
#include <linux/semaphore.h>
#include <linux/cdev.h>



dev_t dev_no,dev;
static int major_num;

struct device
{
    char array[100];
    struct semaphore sem;
} char_dev;


int k_open(struct inode *inode, struct file *filp  )
{
    printk("\n open() called...\n");

    if(down_interruptible(&char_dev.sem)) 
    {
        printk( "\n could not hold semaphore\n");
        return -1;
    } 
    return 0;
}

int k_release( struct inode *inode, struct file *filp  )
{
    printk("\n release() called...\n");
    up(&char_dev.sem);
    return 0;
}

int k_read( struct file *filp, char *buff, size_t count, loff_t *offp  )
{
    int ret;

    printk("\n read() called...\n");
    
    ret = copy_to_user(buff, char_dev.array, count);
    return ret;
}

int k_write( struct file *filp, const char *buff, size_t count, loff_t *offp  )
{
    int ret;

    printk("\n write() called...\n");
    ret = copy_from_user(char_dev.array, buff, count);

    return ret;
}


struct file_operations fops = 
{
	 read   : k_read,
	 write  : k_write,
	 open   : k_open,
	 release: k_release
};

struct cdev *k_cdev;

int  kd_char_init(void )
{
	int result;

	printk("\nchar init entered...\n");

	k_cdev = cdev_alloc();
	k_cdev->ops   = &fops;
	k_cdev->owner = THIS_MODULE;

	printk("\nchar init entered...\n");

	result = alloc_chrdev_region(&dev_no, 0,1, "kdev_kvvd");    

	if(result < 0)
	{
		printk("\n Device allocation failed..result: %d\n", result);
		return result;
	}

	major_num = MAJOR(dev_no);
	dev = MKDEV(major_num, 0);
	sema_init(&char_dev.sem,1);

	printk("\n Major number .. %d\n", major_num);
	printk("\nMKDEV done...\n");

	result = cdev_add(k_cdev, dev,1);

	printk("\ncdev_add() done... %d\n", result);

	if(result < 0)
	{
		printk("\n cdev_add() failed....\n");
		return result;
	}

	return 0;
}

void  kd_char_exit(void)
{
    printk("\nchar_close().....\n");
    cdev_del(k_cdev);
    unregister_chrdev_region(major_num, 1);
}

MODULE_LICENSE("GPL");
module_init(kd_char_init);
module_exit(kd_char_exit);

