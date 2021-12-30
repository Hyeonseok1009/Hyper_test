#include "./calculator.cpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    socklen_t size;

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) 
    {
        printf("\nError establishing socket...\n");
        exit(1);
    }

    printf("\n=> Socket server has been created...\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        printf("=> Error binding connection, the socket has already been established...\n"); 
        return -1;
    }

    size = sizeof(server_addr);
    printf("=> Looking for clients...\n");

    listen(client, 1);

    int clientCount = 1;
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    // first check if it is valid or not
    if (server < 0) 
        printf("=> Error on accepting...\n");

    while (server > 0) 
    {
        strcpy(buffer, "=> Server connected...\n");
        send(server, buffer, bufsize, 0);
        
        printf("\n=> Enter # to end the connection\n");
        
        printf("Client: ");
        recv(server, buffer, bufsize, 0);
        printf("%s \n",buffer);

       
        do {
            sprintf(buffer,"%.5f",calcuator(buffer));
            send(server, buffer, bufsize, 0);
            if (*buffer == '#') {
                send(server, buffer, bufsize, 0);
                isExit = true;
                continue;
            }
           
            printf("Client: ");

            recv(server, buffer, bufsize, 0);
            printf("%s \n",buffer);
            if (*buffer == '#') {
                isExit = true;
                continue;
            }
        } while (!isExit);

        printf("\n\n=> Connection terminated with IP " );
        close(server);
        printf("\nGoodbye...") ;
        isExit = false;
        exit(1);
    }

    close(client);  
    return 0;
}