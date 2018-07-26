#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<netdb.h>

#define BUFFER_SIZE 40
#define MAX_EVENT 10

static int create_and_bind(char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, sfd;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family  = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(NULL, port, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        return -1;
    }

    for(rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if(sfd == -1) {
            continue;
        }
        s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
        if(s == 0) {
            break;
        }
        close(sfd);
    }

    if(rp == NULL) {
        fprintf(stderr, "could not bind\n");
        return -1;
    }

    freeaddrinfo(result);
    return sfd;
}


static int make_socket_non_blocking(int sfd)
{
    int flags, s;
    flags = fcntl(sfd, F_GETFL, 0);
    if(flags == -1) {
        perror("fcntl");
        return -1;
    }

    flags != O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if(s == -1) {
        perror("fcntl");
        return -1;
    }
    return 0;
}

#define MAXEVENTS 64

int main(int argc, char **argv) 
{
    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;

    sfd = create_and_bind(argv[1]);
    if (sfd == -1) {
        abort();
    }

    s = make_socket_non_blocking(sfd);
    if(s == -1) {
        abord();
    }
    s = listen(sfd, SOMAXCONN);

    if(s == -1) {
        perror("listen");
        abort();
    }
}
