/**
* auther: jamal-jiang
* date: 17/4/9
*/

#ifndef MINFTPD_SESSION_H
#define MINFTPD_SESSION_H

#include "common.h"

typedef struct session {
    int ctrl_fd;
    char cmdline[MAX_COMMAND_LINE];
    char cmd[MAX_COMMAND];
    char arg[MAX_ARG];

    int parent_fd;
    int child_fd;
} session_t;

void begin_session(session_t *sess);

#endif //MINFTPD_SESSION_H
