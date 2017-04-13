#include "common.h"
#include "sysutil.h"
#include "session.h"

int main(int argc, char **argv) {
    if (getuid() != 0) {
        fprintf(stderr, "need root\n");
    }

    session_t sess = {
            -1, "", "", "",
            -1, -1
    };
    int listenfd = tcp_server(NULL, 5188);
    int conn;
    pid_t pid;
    while (1) {
        conn = accept(listenfd, NULL, NULL);
        if (conn == -1) {
            ERR_EXIT("acc to");
        }

        pid = fork();
        printf("pid: %d\n", pid);
        if (pid == 0) {
            //close(listenfd);
            sess.ctrl_fd = conn;
            begin_session(&sess);
        } else {
            //close(conn);
        }
    }
    return 0;
}