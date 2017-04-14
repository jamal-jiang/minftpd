/**
* auther: jamal-jiang
* date: 17/4/11
*/

#include "session.h"
#include "ftpproto.h"
#include "sysutil.h"
#include "common.h"
#include "str.h"

void handle_child(session_t *sess) {
    printf("handle_child\n");
    int ret;
    writen(sess->ctrl_fd, "220, hello world\r\n", strlen("220, hello world\r\n"));
    while (1) {
        memset(sess->cmdline, 0, sizeof(sess->cmdline));
        memset(sess->cmd, 0, sizeof(sess->cmd));
        memset(sess->arg, 0, sizeof(sess->arg));
        ret = readline(sess->ctrl_fd, sess->cmdline, MAX_COMMAND_LINE);
        if (ret == -1) {
            ERR_EXIT("readline");
        } else if (ret == 0) {
            exit(EXIT_SUCCESS);
        }

        //printf("cmdline:[%s]\n", sess->cmdline);
        // 解析ftp命令行和参数,处理ftp命令
        // 去除\r\n
        str_trim_crlf(sess->cmdline);
        //printf("cmdline:[%s]\n", sess->cmdline);
        // 解析ftp命令和参数
        str_split(sess->cmdline, sess->cmd, sess->arg, ' ');
        printf("当前需要解析的命令cmd:[%s],参数:[%s]\n", sess->cmd, sess->arg);
    }
}