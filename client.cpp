/*!
 * Simple chat program (client side).cpp - http://github.com/hassanyf
 * Version - 2.0.1
 *
 * Copyright (c) 2016 Hassan M. Yousuf
 */
#include "./calculator.cpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>



int main()
{
    int client;
    int portNum = 1500; 
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

    printf("\n[Socket client has been created...]\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        printf("[Connection to the server port number: %d] \n",portNum);

    printf("[Awaiting confirmation from the server...]\n");
    recv(client, buffer, bufsize, 0);
    printf("[Connection confirmed]\n");

    printf("\nEnter # to end the connection\n");
    FILE* test = fopen("test.txt","r");
    char IsAuto = 'N';
    do { 
        printf("\nCalculate with test.txt?[Y/N] ");
        scanf("%c",&IsAuto);
    }while(!(IsAuto == 'Y'||IsAuto == 'y'||IsAuto == 'N'||IsAuto == 'n' ));
    
    do {
        //입력버퍼 비우기
        fflush(stdin);

        printf("Client: ");
        if(IsAuto == 'Y'|| IsAuto =='y') 
            read_line(test, buffer, bufsize);
            printf("\n");
        else 
            read_line(stdin, buffer, bufsize);

        send(client, buffer, bufsize, 0);
        if (*buffer == '#') 
        {
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

    printf("\nConnection terminated.\n");
    close(client);
    
    return 0;
}