#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void error_handler(char *message);

int main(int argc, char* argv[]) {
    int serv_sock;
    int client_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    char message[] = "Hello World!";

    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

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

    socklen_t client_len = sizeof(client_addr);
    client_sock = accept(serv_sock, (struct sockaddr*)&client_addr, &client_len);
    if (client_sock == -1)
        error_handler("accept error");

    write(client_sock, message, sizeof(message));
    close(client_sock);
    close(serv_sock);

    return 0;
}

void error_handler(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
