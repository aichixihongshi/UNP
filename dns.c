
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usag...\n");
        exit(1);
    }
    struct addrinfo hints;
    struct addrinfo *res, *cur;
    int ret;
    struct sockaddr_in *addr;
    char ipbuf[16];

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* Allow IPv4 */
    hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_socktype = SOCK_STREAM;
       
    ret = getaddrinfo(argv[1], NULL,&hints,&res);
    
    if (ret == -1) {
        perror("getaddrinfo");
        exit(1);
    }
    
    for (cur = res; cur != NULL; cur = cur->ai_next) {
        addr = (struct sockaddr_in *)cur->ai_addr;
        printf("%s\n", inet_ntop(AF_INET, 
            &addr->sin_addr, ipbuf, 16));
    }
    freeaddrinfo(res);
    exit(0);
}


// struct addrinfo 
// {
//      int ai_flags;             /* 指定处理地址和名字方式 */
//      int ai_family;            /* 指定地址族：AF_INET */
//      int ai_socktype;          /* 套接字类型：SOCK_STREAM，SOCK_DGRAM*/
//      int ai_protocol;          /* 指定协议类型 */
//      socklen_t ai_addrlen;      地址的字节长度 
//      struct sockaddr *ai_addr; /* ip地址 */
//      char *ai_canonname;       /* 主机官方名*/
//      struct addrinfo *ai_next; /* 下一个服务器节点 */
// };

// struct sockaddr 
// {  
//     sa_family_t     sa_family;      /* 协议类型  */  
//     char            sa_data[14];    /* ip地址 */  
  
// }  