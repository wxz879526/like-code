#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void error_handler(const char *message);

int main(int argc, char* argv[]) {
    SOCKET sock_fd;

    struct sockaddr_in serv_addr;

    if (argc != 3)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        error_handler("WSAStartup() error");

    sock_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1)
        error_handler("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handler("connect() error");

    char message[100]{0};
    int str_len = recv(sock_fd, message, 100, 0);
    if (str_len == -1)
        error_handler("read() error");

    printf("message from server: %s\n", message);

    closesocket(sock_fd);

    WSACleanup();

    return 0;
}

void error_handler(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
