#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int main(int argc, char **argv)
{
    char cmdbuf[CMD_BUF_SIZE];

    snprintf(cmdbuf, CMD_BUF_SIZE, "zxcc libr.com ");

    for (int n = 1; n < argc; n++) {
        if (!argv[n]) continue;

        size_t len = strlen(cmdbuf);
        size_t remaining = CMD_BUF_SIZE - len - 1;

        char segment[256];

        if (n == 1) {
            snprintf(segment, sizeof(segment), "-%s", argv[n]);
        } else {
            snprintf(segment, sizeof(segment), "%s", argv[n]);
        }

        size_t seg_len = strlen(segment);
        if (seg_len + 1 > remaining) {
            fprintf(stderr, "Warning: Command buffer full, truncating arguments\n");
            break;
        }

        strncat(cmdbuf, segment, remaining);
        strncat(cmdbuf, " ", CMD_BUF_SIZE - strlen(cmdbuf) - 1);
    }

    printf("Executing: %s\n", cmdbuf);
    return system(cmdbuf);
}
