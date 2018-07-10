#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<asm-generic/errno-base.h>
#include<arpa/tftp.h>
#include<bits/errno.h>
int main(int argc, char **argv) 
{
    fprintf(stderr, "EACCESS: %s\n", strerror(EACCESS));
    perror(argv[0]);
    exit(0);
}
