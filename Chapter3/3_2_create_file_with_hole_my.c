#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
char buf3[16394] = {};

int main(void) 
{
    int fd;
    if((fd = creat("file.hole", FILE_MODE)) < 0) {
        printf("create error\n");
    }

    if(write(fd, buf1, 10) != 10) {
        printf("write error"); 
    }
    //现在offset是10
    
    if(lseek(fd, 16394, SEEK_SET) == -1) {
        printf("lseek error"); 
    }
    //现在offset是16384

    if(write(fd, buf2, 10) != 10) {
        printf("write error"); 
    }
    //现在offset是16394

    close(fd);

    if((fd = creat("file.nohole", FILE_MODE))<0) {
        printf("create error\n");
    }

    if(write(fd, buf3, 16394) != 16394) {
        printf("write error"); 
    }

    exit(0);
}
