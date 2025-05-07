#include "common.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int fname_opt(char *arg, char c, char *cmdbuf)
{
    if (!arg || !arg[0]) return 0;

    if ((tolower(arg[1]) == tolower(c)) && arg[2]) {
        size_t current_len = strlen(cmdbuf);
        int needed = snprintf(NULL, 0, " -%c +%s", tolower(c), arg + 2);

        if (current_len + needed < CMD_BUF_SIZE) {
            sprintf(cmdbuf + current_len, " -%c +%s", tolower(c), arg + 2);
            return 1;
        }
    }
    return 0;
}

int cref_opt(char *arg, char *cmdbuf)
{
    if (!arg || !arg[0]) return 0;

    if ((arg[1] == 'c' || arg[1] == 'C') &&
        (arg[2] == 'r' || arg[2] == 'R') && arg[3]) {
        size_t current_len = strlen(cmdbuf);
        int needed = snprintf(NULL, 0, " -cr +%s", arg + 3);

        if (current_len + needed < CMD_BUF_SIZE) {
            sprintf(cmdbuf + current_len, " -cr +%s", arg + 3);
            return 1;
        }
    }
    return 0;
}
