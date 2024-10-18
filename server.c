#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
//#include "customer.h"
//#include "bank_employee.h"
#include "administrator.h"
//#include "manager.h"

#define PORT 8000
#define MAX_CLIENTS 6
#define BUFFER_SIZE 1024

void *handleclient(void* arg);
//bool admin_operation_handler(int clientsocket);

int main()
{
int servsocket,clientsocket;
struct sockaddr_in serveraddress, clientaddress;
socklen_t clientaddrlen = sizeof(clientaddress);

servsocket = socket(AF_INET, SOCK_STREAM , 0);

serveraddress.sin_family = AF_INET;
serveraddress.sin_port = htons(PORT);
serveraddress.sin_addr.s_addr = INADDR_ANY;

if(bind(servsocket, (struct sockaddr*)&serveraddress,sizeof(serveraddress))==-1)
{
perror("binding failed\n");
exit(1);
}

if(listen(servsocket,MAX_CLIENTS)==-1)
{
perror("listening failed");
exit(1);
}
printf("server is listening on port: %d\n", PORT);


while(1)
{
clientsocket = accept(servsocket, (struct sockaddr*)&clientaddress, &clientaddrlen);

if (clientsocket == -1) {
perror("Accepting connection failed");
continue;
}

pthread_t clientthread;
pthread_create(&clientthread, NULL, handleclient, (void *)&clientsocket);
}

close(servsocket);

return 0;
}

void *handleclient(void* arg)
{
int clientsocket = *(int*)arg;
char buff[BUFFER_SIZE];

char role[] = "Select your role:\n1.customer\n2.bank_employee\n3.administrator\n4.manager\n";
send(clientsocket , role , strlen(role), 0 );
while (1) {
int bytesread = recv(clientsocket, buff, sizeof(buff), 0);
if (bytesread <= 0) 
{
close(clientsocket);
pthread_exit(NULL);
}
//printf("%s\n",buff);

buff[bytesread] = '\0';

if(strstr(buff,"administrator") != NULL)
{
admin_operation_handler(clientsocket);
}

close(clientsocket);

/* else if( strstr (buff , "customer") != NULL)
{
customer_operation_handler(clientsocket);
}
else if(strstr(buff,"manager") != NULL)
{
manager_operation_handler(clientsocket);
}
else if(strstr(buff,"bank_employee")!= NULL)
{
bank_employee_operation_handler(clientsocket);
}
*/
send(clientsocket , buff , bytesread , 0);
}
pthread_exit(NULL);
}


