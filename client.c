#include "net.h"  
  
main()  
{  
    int    sockfd, r, len;  
    char   recvline[MAXLINE + 1];  
    struct sockaddr_in servaddr;  
    fd_set rset;  
    int    maxfd, nfds,filefd;  
          
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);  
    bzero(&servaddr, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(50000);  
    Inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);  
      
    filefd = open("test.txt",O_RDWR,0777);
    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));  
    //printf("连接成功\n");  
      
    maxfd = sockfd;  
    nfds = maxfd + 1;  
    FD_ZERO(&rset);  
  
    while (1)  
    {  
        FD_SET(fileno(stdin), &rset);  
        FD_SET(sockfd, &rset);  
          
        r = select(nfds, &rset, NULL,  
                   NULL, NULL);  
        if (r == -1)  
        {  
            //perror("select error");  
            exit(-1);  
        }  
          
        //标注输入可读  
        if (FD_ISSET(fileno(stdin), &rset))  
        {  
            if(fgets(recvline,strlen(recvline),filefd) != NULL)  
            {  
                len = strlen(recvline);  
                r = Writen(sockfd, recvline, len);  
            }  
            else  
            {  
                shutdown(sockfd, SHUT_WR);  
                //close(sockfd);
            }  
        }  
          
        //套接字描述符可读  
        if (FD_ISSET(sockfd, &rset))  
        {  
            r = Readn(sockfd, recvline, len);  
            if (r == 0)  
            {  
                break;  
            }  
            //recvline[r] = 0;  
            printf("%s\n", recvline);  
        }  
    }  
      
    exit(0);  
}  