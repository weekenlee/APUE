#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    int c;
    while((c = getc(stdin)) != EOF) {
        if(putc(c, stdout) == EOF) {
            printf("output error");
        }
    }

    if(ferror(stdin)) {
       printf("output error");
    }

    exit(0);
}

