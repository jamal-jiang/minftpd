/**
* auther: jamal-jiang
* date: 17/4/9
*/

#include "sysutil.h"

int tcp_server(const char *host, unsigned short port) {
    int listenfd;
    if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        ERR_EXIT("tcp_server");
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    if (host != NULL) {
        if (inet_aton(host, &servaddr.sin_addr) == 0) {
            struct hostent *hp;
            hp = gethostbyname(host);
            if (host == NULL) {
                ERR_EXIT("gethostbyname");
            }

            servaddr.sin_addr = *(struct in_addr *) hp->h_addr;
        }
    } else {
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    servaddr.sin_port = htons(port);

    int on = 1;
    if ((setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on))) < 0) {
        ERR_EXIT("setsockopt");
    }
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }
    if (listen(listenfd, SOMAXCONN) < 0) {
        ERR_EXIT("listen");
    }

    return listenfd;
}

int getlocalip(char *ip) {
    char host[100] = {0};
    if (gethostname(host, sizeof(host)) < 0)
        return -1;
    struct hostent *hp;
    if ((hp = gethostbyname(host)) == NULL)
        return -1;

    strcpy(ip, inet_ntoa(*(struct in_addr *) hp->h_addr));
    return 0;
}

ssize_t readn(int fd, void *buf, size_t count) {
    size_t nleft = count;
    ssize_t nread;
    char *bufp = (char *) buf;

    while (nleft > 0) {
        if ((nread = read(fd, bufp, nleft)) < 0) {
            if (errno == EINTR)
                continue;
            return -1;
        }
        else if (nread == 0)
            return count - nleft;

        bufp += nread;
        nleft -= nread;
    }

    return count;
}

ssize_t recv_peek(int sockfd, void *buf, size_t len) {
    while (1) {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if (ret == -1 && errno == EINTR)
            continue;
        return ret;
    }
}

ssize_t readline(int sockfd, void *buf, size_t maxline) {
    int ret;
    int nread;
    char *bufp = buf;
    int nleft = maxline;
    while (1) {
        ret = recv_peek(sockfd, bufp, nleft);
        if (ret < 0)
            return ret;
        else if (ret == 0)
            return ret;

        nread = ret;
        int i;
        for (i = 0; i < nread; i++) {
            if (bufp[i] == '\n') {
                ret = readn(sockfd, bufp, i + 1);
                if (ret != i + 1)
                    exit(EXIT_FAILURE);

                return ret;
            }
        }

        if (nread > nleft)
            exit(EXIT_FAILURE);

        nleft -= nread;
        ret = readn(sockfd, bufp, nread);
        if (ret != nread)
            exit(EXIT_FAILURE);

        bufp += nread;
    }

    return -1;
}

int accept_timeout(int fd, struct sockaddr_in *addr, unsigned int wait_seconds) {
    int ret;
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (wait_seconds > 0) {
        fd_set accept_fdset;
        struct timeval timeout;
        FD_ZERO(&accept_fdset);
        FD_SET(fd, &accept_fdset);
        timeout.tv_sec = wait_seconds;
        timeout.tv_usec = 0;
        do {
            ret = select(fd + 1, &accept_fdset, NULL, NULL, &timeout);
        } while (ret < 0 && errno == EINTR);
        if (ret == -1) {
            return -1;
        }
        else if (ret == 0) {
            errno = ETIMEDOUT;
            return -1;
        }
    }

    if (addr != NULL)
        ret = accept(fd, (struct sockaddr *) addr, &addrlen);
    else
        ret = accept(fd, NULL, NULL);

    return ret;
}


