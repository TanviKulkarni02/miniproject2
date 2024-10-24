#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#include<stdbool.h>
#include<string.h>
#include"administrator.h"
#include"bankemp.h"
//#include"login.h"
#include "loan.h"
#include "customer.h"

//#include "common.h"
#define PORT 5031


#define MAX 5
void *handleclient(void * clientSocket)
{
int socket = *(int *)clientSocket;
while(1){
char buff[1024];
 char *role="enter number according to your role\n1.customer\n2.bank employee\n3.manager\n4.admin\n";
send(socket,role,strlen(role),0);

ssize_t read=recv(socket,buff,sizeof(buff),0);
if(read<=0)
{
close(socket);
pthread_exit (NULL);
}
buff[read]='\0';
if(strstr(buff,"admin")!=NULL)
{
login_administrator(socket);
}
else if(strstr(buff,"customer")!=NULL)
{customer_login(socket);}
else if (strstr(buff,"employee")!=NULL)
{login_bankemployee(socket);}
else if(strstr(buff,"manager")!=NULL)
{manager_login(socket);}
send(socket,buff,read,0); //when none of these print menu again

}// while end
pthread_exit(NULL);
}//handleclient end
/*void *handleclient(void *client_socket) {
	printf("connected with client"); 
   int socket = *(int *)client_socket;

    // Display the menu to the client
    const char *menu = "Welcome! Please select your role:\n"
                       "1. Customer\n"
                       "2. Bank Employee\n"
                       "3. Manager\n"
                       "4. Admin\n"
                       "Enter your choice (1-4): ";
    
    send(socket, menu, strlen(menu), 0);
	printf("sent to client\n");
    char choice[10];  // Buffer for the client's choice
    ssize_t bytes_read = read(socket, choice, sizeof(choice) - 1);
    if (bytes_read < 0) {
        perror("Failed to read from client");
        close(socket);
        return NULL;  // Handle the error
    }
    
    choice[bytes_read] = '\0';  // Null-terminate the string

    // Determine the role based on the choice
    int role_choice = atoi(choice);
	printf("%d",role_choice);
    switch (role_choice) {
        case 1:
            //handle_customer(socket);
            break;
        case 2:
           // handle_bank_employee(socket);
            break;
        case 3:
            //handle_manager(socket);
            break;
        case 4:
            admin_login(socket);
            break;
        default:
            const char *invalid_choice = "Invalid choice. Please try again.\n";
            send(socket, invalid_choice, strlen(invalid_choice), 0);
            break;
    }

 

    // Close the client socket when done
    close(socket);
    printf("Client disconnected.\n");
    return NULL;

}*/
int main()
{
int serverSocket,clientSocket;
struct sockaddr_in serverAddr,clientAddr;
socklen_t clientAddrLen = sizeof(clientAddr);

serverSocket=socket(AF_UNIX,SOCK_STREAM,0);
if(serverSocket==-1)
{
	perror("creation failed");
	exit(1);
}
serverAddr.sin_family=AF_UNIX;
serverAddr.sin_port=htons(PORT);
serverAddr.sin_addr.s_addr=INADDR_ANY;
if(bind(serverSocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr))==-1)
{	perror("binding failed");
	exit(1);
}
if(listen(serverSocket,MAX)==-1)
{
	perror("listening failed");
	exit(1);
}
while(1)
{
clientSocket=accept(serverSocket,(struct sockaddr *)&clientAddr,&clientAddrLen);
if(clientSocket==-1)
{
	perror("connection failed");
	continue;
}
pthread_t client_thread;
pthread_create(&client_thread,NULL,handleclient,(void *)&clientSocket);
}
close(serverSocket);
return 0;
}
