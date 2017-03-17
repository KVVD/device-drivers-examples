

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>   // for platform drivers


#define DRIVER_NAME  "MyPlatformDriver"

MODULE_LICENSE("GPL");


static struct platform_device my_device_1 = 
{
    .name = DRIVER_NAME,
    .id = -1
};


static int __init my_device_1_init(void)
{
    printk("My device-1 init()... with Driver - :%s", DRIVER_NAME);
    platform_device_register(&my_device_1);

    return 0;
}



static void __exit my_device_1_exit(void)
{
    printk("My device-1 exit()... with Driver - :%s", DRIVER_NAME);
    platform_device_unregister(&my_device_1);

}

MODULE_LICENSE("GPL");
module_init(my_device_1_init);
module_exit(my_device_1_exit);
