#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  PORT           5000
#define  BUFLEN         64
int main()
{
        int ret;
        int fd;

        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (fd == -1) {
                perror("socket error"); 
                return -1;
        } else {
                printf("create socket successed...\n"); 
        }

        struct sockaddr_in     s_addr;
        s_addr.sin_family      = AF_INET;
        s_addr.sin_port        = htons(5000);
        s_addr.sin_addr.s_addr = inet_addr("192.168.0.238");
        ret = connect(fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr));
        if (ret != 0) {
                perror("connect error"); 
                return -1;
        } else {
                printf("connect success...\n");
        }

        char str[BUFLEN];
        memset(str, 'a', BUFLEN);
        str[BUFLEN - 1] = '\0';
        ret = send(fd, str, BUFLEN, 0);
        if (ret == -1) {
                perror("send error"); 
                return -1;
        } else {
                printf("send successed...\n"); 
        }

        return 0;
}
