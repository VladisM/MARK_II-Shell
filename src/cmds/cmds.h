#ifndef cmds_h_included
#define cmds_h_included

#define INBUF_LEN 81
#define MAX_ARGS 10

int ping(int argc, char argv[][INBUF_LEN]);
void ping_help();

int help(int argc, char argv[][INBUF_LEN]);
void help_help();

int beep(int argc, char argv[][INBUF_LEN]);
void beep_help();

#ifndef DEBUG
int poweroff(int argc, char argv[][INBUF_LEN]);
void poweroff_help();
#endif

#endif
