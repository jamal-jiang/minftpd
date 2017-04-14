/**
* auther: jamal-jiang
* date: 17/4/9
*/

#ifndef MINFTPD_SYSUTIL_H
#define MINFTPD_SYSUTIL_H

#include "common.h"

#define ERR_EXIT(m) do {perror(m); exit(EXIT_FAILURE);}while(0);


int tcp_server(const char *host, unsigned short port);

int getlocalip(char *ip);

int accept_time_out(int fd, struct sockaddr_in *addr, unsigned int wait_seconds);

ssize_t readn(int fd, void *buf, size_t count);

ssize_t writen(int fd, const void *buf, size_t count);

ssize_t recv_peek(int sockfd, void *buf, size_t len);

ssize_t readline(int sockfd, void *buf, size_t manline);

#endif //MINFTPD_SYSUTIL_H
