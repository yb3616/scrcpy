#include <stdio.h>

#ifdef _WIN32
#include <winsock2.h>
#endif

#ifdef _LINUX
#include <sys/socket.h>
#endif

int connect2socket(int *sock)
{
    //创建套接字
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == NULL)
    {
        printf("ERROR on socket\n");
        return -1;
    }

    //向服务器（特定的IP和端口）发起请求
    SOCKADDR_IN sin;
    sin.sin_family = AF_INET;                     // 使用IPv4地址
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // 具体的IP地址
    sin.sin_port = htons(1234);                   // 端口
    if (connect(sock, (SOCKADDR *)&sin, sizeof(sin)) < 0)
    {
        printf("ERROR on connect\n");
        return -1;
    }
}

int connect2server(int *sock)
{
    return connect2socket(sock);
}

int main()
{
    // 1. 连接服务器
    int sock;
    if (connect2server(&sock) < 0)
    {
        return -1;
    }

    //读取服务器传回的数据
    char buffer[40];
    recv(sock, buffer, sizeof(buffer) - 1, MSG_WAITALL);

    printf("Message form server: %s\n", buffer);

    //关闭套接字
    close(sock);

    return 0;
}