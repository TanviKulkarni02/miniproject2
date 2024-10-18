#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#define PORT 8000
#define BUFFER_SIZE 1024

int main(){
 int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    char command[1024];

    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection to server failed");
        return 1;
    }

    printf("Connected to the server. Type your message:\n");

// Read the welcome message from the server
int    valread = read(sock, buffer, 1024);
    printf("%s", buffer);
while (1) {
        // Clear buffer and take input from user
        memset(buffer, 0, sizeof(buffer));
        memset(command, 0, sizeof(command));
        printf("> ");
        fgets(command, sizeof(command), stdin);

        // Remove the newline character from the input
        command[strcspn(command, "\n")] = 0;

        // Send the command to the server
        send(sock, command, strlen(command), 0);

        // Read the response from the server
        valread = read(sock, buffer, 1024);
        printf("%s", buffer);

        // Break the loop if the command is exit
        if (strcmp(command, "exit") == 0) {
            break;
        }
    }  
    close(sock);
    return 0;
}



/*int main()
{ // char* server_address = "127.0.0.2 "; 
   // int server_port = 12345;
int client =socket(AF_UNIX,SOCK_STREAM,0);
struct  sockaddr_in serv;
serv.sin_family=AF_UNIX;
serv.sin_port=htons(5501);
serv.sin_addr.s_addr=INADDR_ANY;


// inet_pton(AF_INET, server_address, &serv.sin_addr);
if(connect(client,(void*)(&serv),sizeof(serv))==-1)
{
        perror("connection failed");
        close(client);
        exit(1);
}
printf("connected to server\n");
while(1)
{
        char buff[1024];
        memset (buff,0,sizeof(buff));
        ssize_t read=recv(client,buff,sizeof(buff),0);
        if(read<=0)
                break;
        printf("recieved : %s\n",buff);
char buffer[1024];
fgets(buffer,sizeof(buffer),stdin);
send (client,buffer,strlen(buffer),0);

}
close(client);
return 0;
}
*/



/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{

char* serv_address = "127.0.0.1";
int serv_port = 5501;

int client_socket =  socket(AF_INET,SOCK_STREAM,0);
  if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }


struct sockaddr_in servaddr ;
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(5501);
inet_pton(AF_INET, serv_address , &servaddr.sin_addr);

if(connect(client_socket,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
{
printf("failed connection");
close(client_socket);
exit(1);
}

printf("Connected to server successfully!");

while(1)
{
char buff[1024];
memset(buff,0,sizeof(buff));
ssize_t bytesread = recv(client_socket, buff, sizeof(buff),0); 

if(bytesread<=0)
{
break;
}

printf("Received : %s",buff);

char reply[256];
//printf("Enter a message to send to server:\n");
fgets(reply, sizeof(reply),stdin);
send(client_socket, reply , strlen(reply),0);

}
close(client_socket);
return 0;
}
*/
