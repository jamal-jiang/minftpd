/**
* auther: jamal-jiang
* date: 17/4/9
*/

#ifndef MINFTPD_COMMON_H
#define MINFTPD_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <pwd.h>

#define ERR_EXIT(m) do {perror(m); exit(EXIT_FAILURE);}while(0);

#define MAX_COMMAND_LINE 1024
#define MAX_COMMAND 32
#define MAX_ARG 2014

#endif //MINFTPD_COMMON_H
