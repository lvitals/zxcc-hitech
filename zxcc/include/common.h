#ifndef COMMON_H
#define COMMON_H

/* Command buffer */
#define CMD_BUF_SIZE 2048
extern char cmdbuf[CMD_BUF_SIZE];

int fname_opt(char *arg, char c, char *cmdbuf);
int cref_opt(char *arg, char *cmdbuf);

#endif /* COMMON_H */