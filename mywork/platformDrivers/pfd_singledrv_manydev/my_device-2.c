

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>   // for platform drivers


#define DRIVER_NAME  "MyPlatformDriver"

MODULE_LICENSE("GPL");


static struct platform_device my_device_2 = 
{
    .name = DRIVER_NAME,
    .id = -2
};


static int __init my_device_2_init(void)
{
    printk("My device-2 init()... with Driver - :%s\n", DRIVER_NAME);
    platform_device_register(&my_device_2);

    return 0;
}



static void __exit my_device_2_exit(void)
{
    printk("My device-2 exit()... with Driver - :%s\n", DRIVER_NAME);
    platform_device_unregister(&my_device_2);

}

MODULE_LICENSE("GPL");
module_init(my_device_2_init);
module_exit(my_device_2_exit);
