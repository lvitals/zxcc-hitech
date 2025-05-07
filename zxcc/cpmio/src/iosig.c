#include <stdio.h>
#include <signal.h>
#include "cpmio.h"

RETSIGTYPE on_sigint(int s) /* Called if there's a fatal signal */
{
    cpm_scr_unit(); /* Clear screen, end ncurses */
    signal(s, SIG_DFL);
    raise(s); /* Re-throw */
}
