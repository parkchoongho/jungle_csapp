#include "csapp.h"

int main(int argc, char **argv) {
    struct stat stat;
    char *type, *readok, *writeok;

    Stat(argv[1], &stat);

    if (S_ISREG(stat.st_mode)) type = "regular";
    else if (S_ISDIR(stat.st_mode)) type = "directory";
    else type = "other";

    if ((stat.st_mode & S_IRUSR)) readok = "yes";
    else readok = "no";

    if ((stat.st_mode & S_IWUSR)) writeok = "yes";
    else writeok = "no";

    printf("type: %s, read: %s, write: %s\n", type, readok, writeok);
    exit(0);
}
