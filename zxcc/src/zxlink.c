#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int main(int argc, char **argv)
{
    char cmdbuf[CMD_BUF_SIZE];
    
    snprintf(cmdbuf, CMD_BUF_SIZE, "zxcc linq.com ");

    for (int n = 1; n < argc; n++) {
        if (!argv[n]) continue;

        if (argv[n][0] == '-') {
            if (fname_opt(argv[n], 'o', cmdbuf)) continue;
            if (fname_opt(argv[n], 'm', cmdbuf)) continue;
            if (fname_opt(argv[n], 'd', cmdbuf)) continue;
        }

        size_t len = strlen(cmdbuf);
        size_t remaining = CMD_BUF_SIZE - len - 1;

        if (remaining <= strlen(argv[n]) + 1) {
            fprintf(stderr, "Warning: Command buffer full, truncating\n");
            break;
        }

        strncat(cmdbuf, argv[n], remaining);
        strncat(cmdbuf, " ", CMD_BUF_SIZE - strlen(cmdbuf) - 1);
    }

    printf("Executing: %s\n", cmdbuf);
    return system(cmdbuf);
}
