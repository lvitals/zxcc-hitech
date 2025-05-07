/* General terminal emulation library: Declarations  */

#ifdef TERM_CORE_C
int core_x, core_y, core_wx, core_wy, core_ww, core_wh;
int core_attr, core_fg, core_bg, core_pair, core_wrap;
int core_ansi_buf[20];
int core_ansi_count;
char core_ansi_char;
#else
extern int core_x, core_y, core_wx, core_wy, core_ww, core_wh;
extern int core_attr, core_fg, core_bg, core_pair, core_wrap;
extern int core_ansi_buf[20];
extern int core_ansi_count;
extern char core_ansi_char;
#endif

void core_scroll_down(void);
void core_scroll_up(void);
void core_up(int scrl);
void core_down(int scrl);
void core_left(int wrap);
void core_right(int wrap);
void core_addch(char c);
void core_tab(void);
void core_cr(void);
void core_move(int x, int y);
void core_save_pos(int restore);
void core_win(int tr, int lc, int h, int w);
void core_24x80(void);
void core_fullscr(void);
void core_clrtobol(void);
void core_clrline(int row);
void core_clrtobos(void);
void core_clrtoeol(void);
void core_clrtoeos(void);
void core_init(void);
void core_setattr(int attr);
void core_clearattr(int attr);
void core_setfg(int fg);
void core_setbg(int bg);
void core_cursor(int type); /* 0 = none  1 = block  2 = underline */
int core_term(int func, int param);
int core_ansi(char c);
void core_ansi_begin(void);
