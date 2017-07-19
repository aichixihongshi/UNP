#include "net.h"  
  
main(int argc, char **argv)  
{  
    int listenfd, connfd, r;  
    struct sockaddr_in servaddr;  
    char buf[MAXLINE];  
    time_t ticks;  
      
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(50000);  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  
      
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));  
      
    Listen(listenfd, LISTENEQ);  
      
    connfd = accept(listenfd, (SA*)NULL, NULL);  
      
    while(1)  
    {  
        r = read(connfd, buf, MAXLINE);  
        if (r == 0)  
        {  
            printf("客户端断开连接\n");  
            break;  
        }  
        buf[r] = 0;  
       // printf("%s\n", buf);
        Writen(connfd, buf, r);  
    }  
      
    exit(0);  
} 