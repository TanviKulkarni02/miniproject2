#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#define PORT 5031



int main()
{ // char* server_address = "127.0.0.2 "; 
   // int server_port = 12345;
int client =socket(AF_UNIX,SOCK_STREAM,0);
struct  sockaddr_in serv;
serv.sin_family=AF_UNIX;
serv.sin_port=htons(PORT);
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
printf("in client\n");
send (client,buffer,strlen(buffer),0);

}
close(client);
return 0;
}




