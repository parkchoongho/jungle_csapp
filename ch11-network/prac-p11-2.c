#include "csapp.h"

int main(int argc, char *argv[]) {
    struct in_addr inaddr;
    uint16_t addr;
    char buf[MAXBUF];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <hex number>\n", argv[0]);
        exit(0);
    }

    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htons(addr);

    inet_ntop(AF_INET, &inaddr, buf, MAXBUF);
    // if(!inet_ntop(AF_INET, &inaddr, buf, MAXBUF))
    //     unix_error("inet_ntop");
    printf("%s\n", buf);

    exit(0);
}
