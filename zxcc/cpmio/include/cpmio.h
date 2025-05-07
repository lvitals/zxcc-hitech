/* CPMIO: CP/M Console Emulation Library - Unified Header */
#ifndef CPMIO_H
#define CPMIO_H

/* ================= PUBLIC INTERFACE ================= */

/* Console initialization/termination */
void cpm_scr_init(void); /* Initialize console */
void cpm_scr_unit(void); /* Terminate console */

/* BIOS functions */
char cpm_const(void);    /* Console status */
char cpm_conin(void);    /* Console input */
void cpm_conout(char c); /* Console output */

/* BDOS functions */
int cpm_bdos_1(void);                        /* Console input with echo */
int cpm_bdos_2(char c);                      /* Console output */
int cpm_bdos_6(unsigned char c);             /* Direct console access */
int cpm_bdos_9(char *buf);                   /* Print a string */
unsigned cpm_bdos_10(unsigned char *buf);    /* Read a line */
int cpm_bdos_11(void);                       /* Poll console */
unsigned int cpm_bdos_109(unsigned int arg);  /* Console mode set/get */
unsigned char cpm_bdos_110(unsigned int arg); /* String delimiter set/get */
int cpm_bdos_111(char *buf, unsigned int len); /* Output fixed-length string */

/* Terminal control */
int cpm_bdos_set_get_typeahead(int flag);    /* Set/get Typeahead flag */
char *cpm_get_terminal(void);                /* Get terminal ID */
int cpm_set_terminal(char *s);               /* Set terminal ID */
void cpm_enum_terminals(char *s);            /* List all terminal IDs */
int cpm_term_direct(int function, int param); /* Direct terminal control */

/* Terminal control functions */
#define CPM_TERM_INIT      0   /* Initialize terminal */
#define CPM_TERM_GETATTR   1   /* Get attributes */
#define CPM_TERM_SETATTR   2   /* Set attributes */
#define CPM_TERM_GETCOLOUR 3   /* Get color */
#define CPM_TERM_SETCOLOUR 4   /* Set color */
#define CPM_TERM_CLEAR     5   /* Clear screen */
#define CPM_TERM_MOVE      6   /* Move cursor */
#define CPM_TERM_IFCOLOUR  7   /* Check color support */
#define CPM_TERM_CHAR      20  /* Write character */
#define CPM_TERM_HEIGHT    60  /* Get/set height */
#define CPM_TERM_WRAP      61  /* Get/set wrap mode */
#define CPM_TERM_WIDTH     62  /* Get/set width */

/* ================= INTERNAL DECLARATIONS ================= */
/* (For library implementation use) */

/* Platform detection */
#if defined(_WIN32) || defined(_WIN64)
#define CPMIO_WINDOWS 1
#include <windows.h>
#include <conio.h>
#include <io.h>
#undef MOUSE_MOVED    /* Prevent conflict with PDcurses */
#define PDC_DLL_BUILD /* Use DLL build of PDCurses */
#else
#define CPMIO_UNIX 1
#include <termios.h>
#include <unistd.h>
#endif

/* Curses detection */
#ifndef HAVE_NCURSES_H
# if defined(CPMIO_WINDOWS)
#  define HAVE_CURSES_H 1
# elif __has_include(<ncurses.h>)
#  define HAVE_NCURSES_H 1
# elif __has_include(<curses.h>)
#  define HAVE_CURSES_H 1
# endif
#endif

#if defined(HAVE_NCURSES_H)
#include <ncurses.h>
#elif defined(HAVE_CURSES_H)
#include <curses.h>
#endif

/* Standard headers */
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Signal handling */
#ifndef RETSIGTYPE
#define RETSIGTYPE void
#endif

/* Internal functions */
RETSIGTYPE on_sigint(int a);
void cpm_console_bdos_init(void);

/* Terminal emulations */
int raw_term(int func, int param);
int vt52_term(int func, int param);
int ansi_term(int func, int param);
int generic_term(int func, int param);
int termios_term(int func, int param);

/* Helper macros */
#define CPM_HI(x) ((x >> 8) & 0xFF)
#define CPM_LO(x) (x & 0xFF)

/* Attribute flags */
#define AT_BRIGHT      (1 << 0)
#define AT_UNDERSCORE  (1 << 1)
#define AT_BLINK       (1 << 2)
#define AT_REVERSE     (1 << 3)

/* Control characters */
#define CTL_C ('C' - '@')
#define CTL_P ('P' - '@')
#define CTL_Q ('Q' - '@')
#define CTL_S ('S' - '@')

#endif /* CPMIO_H */