#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

int main(int argc, char **argv)
{
    char cmdbuf[CMD_BUF_SIZE];
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.c> [options]\n", argv[0]);
        return EXIT_FAILURE;
    }

    snprintf(cmdbuf, CMD_BUF_SIZE, "zxcc c %s", argv[1]);
    
    for (int n = 2; n < argc; n++) {
        if (!argv[n]) continue;

        if (argv[n][0] == '-') {
            if (fname_opt(argv[n], 'e', cmdbuf)) continue;
            if (fname_opt(argv[n], 'f', cmdbuf)) continue;
            if (fname_opt(argv[n], 'i', cmdbuf)) continue;
            if (fname_opt(argv[n], 'm', cmdbuf)) continue;
            if (cref_opt(argv[n], cmdbuf)) continue;
            
            strncat(cmdbuf, " ", CMD_BUF_SIZE - strlen(cmdbuf) - 1);
            strncat(cmdbuf, argv[n], CMD_BUF_SIZE - strlen(cmdbuf) - 1);
        }
        else {
            strncat(cmdbuf, " ", CMD_BUF_SIZE - strlen(cmdbuf) - 1);
            strncat(cmdbuf, argv[n], CMD_BUF_SIZE - strlen(cmdbuf) - 1);
        }
    }

    printf("Executing: %s\n", cmdbuf);
    return system(cmdbuf);
}
