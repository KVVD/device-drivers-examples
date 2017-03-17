
obj-m := my_platform_driver.o my_device-1.o my_device-2.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c )


