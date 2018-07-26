#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERV_PORT 8000

void perr_exit(const char * str)
{
    perror(str);
    exit(1);
}

int main() 
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0), cfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in client_addr;
    int i, len;
    socklen_t addr_len;

    bzero(&servaddr, sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;

    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perr_exit("bind error");
    }

    listen(sfd, 128);//可连接数

    printf("waiting for connect.....\n");

    while(1) {
        addr_len = sizeof(client_addr);
        cfd = accept(sfd, (struct sockaddr *)&client_addr, &addr_len);

        if(cfd == -1) {
            perr_exit("accept error");
        }

        char buf[256];
        printf("client ip: %s, %d\n", 
                inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, buf, sizeof(buf)),
                ntohs(client_addr.sin_port));


        len = read(cfd, buf , sizeof(buf));
        if(len == -1) {
            perr_exit("read error");
        }

        if(write(STDOUT_FILENO, buf , len) < 0) {
            perr_exit("write error");
        }
        for(i = 0; i < len; i++ ) {
            buf[i] = toupper(buf[i]);
        }
        if(write(cfd, buf, len) < 0) {
            perr_exit("write error");
        }
    }
    printf("服务器关闭\n");

    close(sfd);
    close(cfd);
    return 0;
}

