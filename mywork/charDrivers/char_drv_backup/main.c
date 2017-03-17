
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int errno;
void main()
{
    int fd;
    char operation_type, write_buf[100] = {"hello"}, read_buf[100];

    fd = open("/dev/kdev_kvvd", O_RDWR);    
    if(fd == -1)
    {
        printf("\n\n Error in opening file...%d\n\n", errno);
        exit(-1);
    }

    printf("\nFile open succesful...\n");

    printf("\n Enter r: to read.... w: to write...\n");
    scanf("%c", &operation_type);


    switch(operation_type)
    {
        case 'r':
            printf("\n reading from the device..\n");
            read(fd, read_buf, 10);
            printf("\ndata read:.. %s\n, read_buf");
            break;

        case 'w':
            printf("\n Enter data to write into the device..\n");
            scanf("%s", write_buf);
            write(fd, write_buf, 10);
            break;
       default:
            printf("\n Wrong choice....\n");
    }

    close(fd);
}
