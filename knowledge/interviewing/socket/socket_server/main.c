#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  PORT           5000
#define  BUFLEN         10
int main()
{
        int ret;
        int s_fd;

        s_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (s_fd == -1) {
                perror("socket error"); 
                return -1;
        } else {
                printf("create socket successed...\n"); 
        }

        struct sockaddr_in     s_addr;
        s_addr.sin_family      = AF_INET;
        s_addr.sin_port        = htons(5000);
        /* s_addr.sin_addr.s_addr = inet_addr("192.168.0.238"); */
        s_addr.sin_addr.s_addr = INADDR_ANY;
        ret = bind(s_fd, (struct sockaddr *)&s_addr, sizeof(struct sockaddr));
        if (ret != 0) {
                perror("bind error"); 
                return -1;
        } else {
                printf("bind success...\n");
        }

        ret = listen(s_fd, 3);
        if (ret != 0) {
                perror("listen error"); 
                return -1;
        } else {
                printf("license success...\n");
        }

        int c_fd;
        char buf[BUFLEN], *msg = NULL;
        int num, addr_size, cnt = 0;
        struct sockaddr_in c_addr;
        addr_size = sizeof(struct sockaddr_in);
        while (1) {
                c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &addr_size);
                if (c_fd == -1) {
                        perror("accept error"); 
                        continue;
                } else {
                        printf("\naccept success...\n");
                }

                printf("server: got connection from %s\n", 
                                inet_ntoa(c_addr.sin_addr));

                while ((num = recv(c_fd, buf, BUFLEN, 0)) > 0) {
                        msg = (char *)realloc(msg, cnt + num);
                        memcpy(msg + cnt, buf, num);
                        cnt += num;
                        printf("%d:%s\n", num, buf);
                        memset(buf, 0, BUFLEN);
                }
                printf("receive message: %s\n", msg);
                cnt = 0;
                close(c_fd);
        }

        return 0;
}
