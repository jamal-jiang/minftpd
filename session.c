/**
* auther: jamal-jiang
* date: 17/4/9
*/

#include "common.h"
#include "session.h"
#include "ftpproto.h"
#include "privparent.h"

void begin_session(session_t *sess) {
    struct passwd *pw = getpwnam("nobody");
    if (pw == NULL) {
        return;
    }
    if (setegid(pw->pw_gid) < 0) {
        ERR_EXIT("setegid");
    }
    if (seteuid(pw->pw_uid) < 0) {
        ERR_EXIT("seteuid");
    }

    int sockfd[2];
    if (socketpair(PF_UNIX, SOCK_STREAM, 0, sockfd) < 0) {
        ERR_EXIT("socketpair");
    }

    pid_t pid;
    pid = fork();
    if (pid < 0) { ERR_EXIT("fork session"); }

    if (pid == 0) {
        close(sockfd[0]);
        sess->child_fd = sockfd[1];
        handle_child(sess);
    } else {
        close(sockfd[1]);
        sess->parent_fd = sockfd[0];
        handle_parent(sess);
    }
}