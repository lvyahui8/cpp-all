#ifndef __DAEMON_H_
#define __DAEMON_H_
int lockfile(int fd);
int already_running();
void daemonize(const char * cmd);
#endif //__DAEMON_H_
