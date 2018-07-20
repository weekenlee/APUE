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
}
