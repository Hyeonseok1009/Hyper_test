/*!
 * Simple chat program (client side).cpp - http://github.com/hassanyf
 * Version - 2.0.1
 *
 * Copyright (c) 2016 Hassan M. Yousuf
 */
#include "./mycode3.cpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>



int main()
{
    int client;
    int portNum = 1500; // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char* ip = "127.0.0.1";

    struct sockaddr_in server_addr;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        printf("\nError establishing socket...\n");
        exit(1);
    }

    printf("\n=> Socket client has been created...\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        printf("=> Connection to the server port number: %d ",portNum);

    printf("=> Awaiting confirmation from the server...\n"); //line 40
    recv(client, buffer, bufsize, 0);
    printf("=> Connection confirmed, you are good to go...");

    printf("\n\n=> Enter # to end the connection\n");

    do {
        printf("Client: ");
        read_line(stdin, buffer, bufsize);
        send(client, buffer, bufsize, 0);
        if (*buffer == '#') {
            send(client, buffer, bufsize, 0);
            isExit = true;
            continue;
        }

        printf("Server: ");
       
        recv(client, buffer, bufsize, 0);
        printf("%s \n",buffer);
        if (*buffer == '#') {
            isExit = true;
            continue;
        }
        printf("\n");

    } while (!isExit);

    printf("\n=> Connection terminated.\nGoodbye...\n");
    close(client);
    
    return 0;
}