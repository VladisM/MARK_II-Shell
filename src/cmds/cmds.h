#ifndef cmds_h_included
#define cmds_h_included

int ping(int argc, char *argv[]);
void ping_help();

int help(int argc, char *argv[]);
void help_help();

int beep(int argc, char *argv[]);
void beep_help();

int color(int argc, char *argv[]);
void color_help();

int game(int argc, char *argv[]);
void game_help();

#ifndef DEBUG
int poweroff(int argc, char *argv[]);
void poweroff_help();
#endif

#endif
