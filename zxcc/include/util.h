#ifndef UTIL_H
#define UTIL_H

/* Command buffer */
#define CMD_BUF_SIZE 2048
extern char cmdbuf[CMD_BUF_SIZE];

/* Utility functions */
int fname_opt(char *arg, char c);
int cref_opt(char *arg);

#endif /* UTIL_H */