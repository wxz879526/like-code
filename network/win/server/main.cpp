#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void error_handler(const char *message);

int main(int argc, char* argv[]) {
    SOCKET serv_sock;
    SOCKET client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
        error_handler("WSAStartup() error");

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handler("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handler("bind error");

    printf("server start listen.....\n");

    if (listen(serv_sock, 5) == -1)
        error_handler("listen error");

    int client_len = sizeof(client_addr);
    client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_len);
    if (client_sock == -1)
        error_handler("accept error");

    send(client_sock, message, sizeof(message), 0);
    closesocket(client_sock);
    closesocket(serv_sock);

    WSACleanup();

    return 0;
}

void error_handler(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
