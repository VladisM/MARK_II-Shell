#ifndef cmds_h_included
#define cmds_h_included

int ping(int argc, char argv[][33]);
void ping_help();

int help(int argc, char argv[][33]);
void help_help();

int beep(int argc, char argv[][33]);
void beep_help();

#ifndef DEBUG
int poweroff(int argc, char argv[][33]);
void poweroff_help();
#endif

#endif
