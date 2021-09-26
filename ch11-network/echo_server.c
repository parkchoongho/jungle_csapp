#include "csapp.h"

void echo(int connfd);
// int open_listenfd(char *port);

int main(int argc, char *argv[]) {
    int listenfd, connfd;
    socklen_t clientlen;

    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s %s)\n", client_hostname, client_port);
        echo(connfd);
        close(connfd);
    }
    exit(0);
}

// int open_listenfd(char *port) {
//     struct addrinfo hints, *listp, *p;
//     int listenfd, optval = 1;

//     /* GEt a list of potential server addresses */
//     memset(&hints, 0 ,sizeof(struct addrinfo));
//     hints.ai_socktype = SOCK_STREAM;             /* Accept connections */
//     hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG; /* ... on any IP address */
//     hints.ai_flags |= AI_NUMERICSERV;            /* ... using port number */
//     getaddrinfo(NULL, port, &hints, &listp);

//     /* Walk the list for one that we can bind to */
//     for (p = listp; p; p = p->ai_next) {
//         /* Create a socket descriptor */
//         if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
//             continue; /* Socker failed, try the next */

//         /* Eliminates "Address already in use" error from bind */
//         Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

//         /* Bind the descriptor to the address */
//         if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
//             break; /* Success */
//         close(listenfd);
//     }

//     /* Clean up */
//     freeaddrinfo(listp);
//     if (!p) return -1; /* No address worked */

//     /* Make it a listening socker ready to accept connection requests */
//     if (listen(listenfd, LISTENQ) < 0) {
//         close(listenfd);
//         return -1;
//     }
//     return listenfd;
// }

void echo(int connfd) {
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    rio_readinitb(&rio, connfd);
    while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("server received %d bytes\n", (int) n);
        printf("Buffer: %s\n", buf);
        buf[0] = 'j';
        rio_writen(connfd, buf, n);
    }
}