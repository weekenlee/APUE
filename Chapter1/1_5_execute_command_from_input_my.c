#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

#define MAXLINE 500

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;
    int cur_buff_len;
    char *quits="q";

    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        cur_buff_len = strlen(buf);
        if(buf[cur_buff_len - 1] == '\n') {
            buf[cur_buff_len - 1] = 0;
        }
        if(strcmp(buf, quits) == 0) {
            exit(0);
        }
        if((pid=fork()) < 0) {
            printf("fork error!\n");
        }else if (pid == 0) {
            execlp(buf, buf, (char*)0);
            printf("cann't execute: %s\n'", buf);
            exit(127);
        }

        /*parent*/
        if((pid = waitpid(pid, &status, 0)) < 0) {
            printf("wait error");
        }
        printf("%% ");
    }
    exit(0);
}
