
/*
    reference for this:
    http://linuxseekernel.blogspot.in/2014/05/platform-device-driver-practical.html


    Platform drivers are not discover-able. i.e 
    HW can't say -- Hey I am present. Ex: I2C.
    But PCI and USB are self discover-able.

    In the embedded world and syste-on-chip world, non-disciverable devices are inceasing. 
    So kernel needs to handle these. PLATFORM DEVICES will help in this.
    Two components in PLATFORM DEVICES:
    - Platform Driver
    - Platform Device

    Linux kernel defines set of standard operations which will be performed on a platform device.
    Refer http://lxr.free-electrons.com/source/include/linux/platform_device.h#L173   

    At a minimum, probe() and remove() have to be written. Other functions/callbacks 
    are for the power management.

*/


    #include <linux/module.h>
    #include <linux/kernel.h>
    #include <linux/platform_device.h>   // for platform drivers


    #define DRIVER_NAME  "MyPlatformDriver"

    
    static struct platform_device my_pf_device = 
    {
        .name = DRIVER_NAME,
        .id = -1
    };

    // 1. write probe, remove functions

    static int my_platform_probe(struct platform_device *pdev)
    {
        printk("my_patform_probe()....\n");
        return 0;
    }


    static int my_platform_remove(struct platform_device *pdev)
    {
        printk("my_patform_remove()....\n");
        return 0;
    }

    // 2. initialize the platform driver structure.
    static struct platform_driver my_pf_driver  = 
    {
        .probe  = my_platform_probe,
        .remove = my_platform_remove,
        .driver = {
            .name = DRIVER_NAME,
            .owner= THIS_MODULE,
        }
 
    };


    // 3. driver init and exit functions
    
    static int __init my_platform_driver_init(void)
    {
        printk("My platform driver init()......\n");
        platform_driver_register(&my_pf_driver);
        
        return 0;
    }

    static void __exit my_platform_driver_exit(void)

    {
        printk("My platform driver exit()......\n");
        platform_driver_unregister(&my_pf_driver);
    }


    // 4. kernel driver format
    MODULE_LICENSE("GPL");
    module_init(my_platform_driver_init);
    module_exit(my_platform_driver_exit);

