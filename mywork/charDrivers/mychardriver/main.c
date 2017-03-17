

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int errno;
char buf[128];
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
    printf("enter r to read; w to write...:   ");
    scanf("%c", &choice);

    switch(choice)
    {
        case 'r':
            read(fd, buf, 16);
            printf("\n data read ... :   %s \n", buf);
            break;
 
        case 'w':
            printf("\nenter the data to write into the device... : ");
            scanf("%s", buf);
            write(fd, buf, 16);
            break;
        
        default:
            printf("\n Invalid choice...\n");
            
    }
            
    printf("----------------------------------------------------------------------\n");
    
    close(fd);

}
