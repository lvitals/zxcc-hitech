#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int main(int argc, char **argv)
{
    char cmdbuf[CMD_BUF_SIZE];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file> [options]\n", argv[0]);
        return EXIT_FAILURE;
    }

    snprintf(cmdbuf, CMD_BUF_SIZE, "zxcc zas.com ");

    for (int n = 1; n < argc; n++) {
        if (!argv[n]) continue;

        if (argv[n][0] == '-') {
            if (fname_opt(argv[n], 'o', cmdbuf)) continue;
            if (fname_opt(argv[n], 'l', cmdbuf)) continue;

            strncat(cmdbuf, argv[n], CMD_BUF_SIZE - strlen(cmdbuf) - 1);
            strncat(cmdbuf, " ", CMD_BUF_SIZE - strlen(cmdbuf) - 1);
        } else {
            strncat(cmdbuf, argv[n], CMD_BUF_SIZE - strlen(cmdbuf) - 1);
            strncat(cmdbuf, " ", CMD_BUF_SIZE - strlen(cmdbuf) - 1);
        }
    }

    printf("Executing: %s\n", cmdbuf);
    return system(cmdbuf);
}
