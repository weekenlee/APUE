#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        printf("can not seedk\n");
    }else {
        printf("seek ok\n");
    }
    exit(0);
}
