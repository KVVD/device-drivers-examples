

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int errno;
char device_name[32] = {"/dev/mycharDev"};

void main()
{
    int fd;
    char choice;

    fd = open(device_name, O_RDWR);
    if(-1 ==fd)
    {
        printf("\nError in opening the device %s. err# %d\n\n", device_name, errno);
        exit(-1);
    }
   
    printf("\n Device - %s, fd  = %d -- opened succesfully", device_name, fd);

    printf("\n\n----------------------------------------------------------------------\n");
    
    close(fd);

}
