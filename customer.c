/*#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
#include "common.h"
#include "administrator.c"
*/

/*#define DB_FILE "customer_db.txt"
bool login (int clientsocket);
bool view_accountbalace(int clientsocket);
bool deposit_money(int clientsocket);
bool withdraw_money(int clientsocket);
bool transfer_funds(int clientsocket);
bool applyfor_loan(int clientsocket);
bool change_password(int clientsocket);
bool add_feedback(int clientsocket);
bool view_transactionhistory(int clientsocket);
bool logout(int clientsocket);
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/socket.h>
#include "administrator.h"
#include "bankemp.h"
#include "customer.h"

bool login_customer(int clientsocket);
bool authenticate_customer(int clientsocket);
bool account_balance(int clientsocket);
bool login_customer(int clientsocket)
{
printf("hello\n");
send(clientsocket,"hello\n",strlen("hello\n"),0);

if(authenticate_customer(clientsocket))

{send(clientsocket,"login successful\n",strlen("login successful\n"),0);
//ssize_t rbytes;
//char rbuff[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t readbytes;
char readbuffer[1024];
char menu[]="select the option number \n1.view account balance\n2.deposit money\n3.withdraw money\n4.transfer funds\n5.apply loan\n6.change password\n7.adding feedback\n8.view transaction history\n9.logout\n10.exit\n";
send(clientsocket,menu,strlen(menu),0);
printf("bye");
readbytes=recv(clientsocket,readbuffer,sizeof(readbuffer),0);
if(readbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(readbuffer);

switch (choice){
        case 1:
         if(account_bal(clientsocket))
       // {
       // send(clientsocket,"successfuly added\npress enter to continue\n",strlen("successfully added\npress enter to continue\n"),0);
       // }
        break;
       /* case 2:
                if(modify_customer(clientsocket))
        {send(clientsocket,"successfully modify\n",strlen("successfully modify\n"),0);}
        break;
       case 3:
         //       if(manage_user(clientsocket))
        //{send(clientsocket,"success\n",strlen("success\n"),0);}
        break;
	case 4:
	break;
        case 5:
		printf("inside case 5\n");
                if(change_password(clientsocket))
        {send(clientsocket,"successfully changed\n",strlen("successfully changed\n"),0);}

        break;
        case 6:
                send(clientsocket,"successfully logged out\n",strlen("successfully logged out\n"),0);
                return true;
        break;
        case 7:
                close(clientsocket);
                break;
         default:
                    break;*/
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end

bool authenticate_customer(int clientsocket)
{
send(clientsocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");
char cid[50];
char password[10];
send(clientsocket,"id:\n",strlen("id:\n"),0);
ssize_t read1=recv(clientsocket,cid,sizeof(cid),0);
if (read1<=0)
{
close (clientsocket);
return 0;
}
if(cid[read1 -1]=='\n')
{cid[read1 -1]='\0';}
else
{cid[read1 -1]='\0';}
send(clientsocket, "enter password:\n",strlen("enter password:\n"),0);
read1=recv(clientsocket,password,sizeof(password),0);
if(read1<=0)
{close(clientsocket);
return 0;
}
if(password[read1 -1]=='\n')
{
password[read1 -1]='\0';
}
else
{password[read1 -1]='\0';}
//if (strcmp(username,admin.username)==0 && strcmp(password,admin.password)==0)
int dbfile = open("customer.txt", O_RDONLY);
    if (dbfile == -1) {
        perror("Error in opening the database file");
        return false;
    }

    char line[300];
    struct customer temp;
    //bool is_there = false;

    //struct flock lock;
    //memset(&lock, 0, sizeof(lock));
    //lock.l_type = F_WRLCK;  
    //lock.l_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t current_position = 0;

    char buffer;
    int line_index = 0;

    while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(dbfile, 0, SEEK_CUR);
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


           // sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
           // printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,cid);

            if (atoi(temp.id)==atoi( cid)&& atoi(temp.password)==atoi(password)&&temp.active==1) {
                printf("Employee ID matched.\n");return true;}
   }//end of else
}//end of while

}//end of authenticate

bool account_bal(int clientsocket)
{
char cid[50];
char password[10];
send(clientsocket,"id:\n",strlen("id:\n"),0);
ssize_t read1=recv(clientsocket,cid,sizeof(cid),0);
if (read1<=0)
{
close (clientsocket);
return 0;
}
if(cid[read1 -1]=='\n')
{cid[read1 -1]='\0';}
else
{cid[read1 -1]='\0';}
int dbfile = open("customer.txt", O_RDONLY);
    if (dbfile == -1) {
        perror("Error in opening the database file");
        return false;
    }

    char line[300];
    struct customer temp;
    //bool is_there = false;

    //struct flock lock;
    //memset(&lock, 0, sizeof(lock));
    //lock.l_type = F_WRLCK;  
    //lock.l_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t current_position = 0;

    char buffer;
    int line_index = 0;

    while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(dbfile, 0, SEEK_CUR);
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


           // sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
           // printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,cid);

            if (atoi(temp.id)==atoi( cid)) {
                send(clientsocket,temp.bal,sizeof(temp.bal),0);return true;}
   }//end of else
}//end of while


}//end of account_bal








{
    struct Faculty authenticatedprof;

    bool authenticated = authenticate_prof(clientsocket, &authenticatedprof);

    if (authenticated)
    {
        ssize_t readbytes;
        char readbuffer[1000];

        // Send a welcome message after successful login
        send(clientsocket, "Login Successfully\n", strlen("Login Successfully\n"), 0);

        while (1)
        {
            // Send the professor menu to the client
            char profMenu[] = "Professor Menu:\n1. Add new Course\n2. Remove offered course\n3. View enrollments in the course\n4. View offered course detials\n  5.Update course details\n 6. Exit\n 7.Change Password\n";
            send(clientsocket, profMenu, strlen(profMenu), 0);

            // Receive the client's menu choice
            readbytes = recv(clientsocket, readbuffer, sizeof(readbuff), 0);
            if (readbytes == -1)
            {
                perror("Error while reading client's choice for PROF_MENU");
                return false;
            }

            int choice = atoi(readbuffer);

            // Handle the menu choice
            switch (choice)
            {
                case 1:
                    if (add_course(clientsocket,&authenticatedprof))
                    {
                        send(clientsocket,"Done successfully\n", strlen("Done successfully\n"), 0);
                    }
                   /* else
                     {
                     send(clientsocket,"There is some error please try again!\n", strlen("There is some error please try again\n!"), 0);
                     }*/
                    break;
               case 2:
                    if(remove_course(clientsocket,&authenticatedprof))
                     {
                     send(clientsocket,"Done successfully\n",strlen("Done successfully\n"),0);
                     }
                     else
                     {
                     send(clientsocket,"There is some error please try again!\n", strlen("There is some error please try again!\n"), 0);
                     }
                     break;
              case 3: view_enrollments(clientsocket);
                      break;
              case 4: view_offered(clientsocket);
                      break;
              case 5: if(update_course(clientsocket))
                      {
                      send(clientsocket,"Done successfully\n", strlen("Done successfully\n"), 0);
                      }
                      else
                      {
                      send(clientsocket,"There is some error please try again!\n", strlen("There is some error please try again!\n"), 0);
                      }
                     break;
              case 6:close(clientsocket);
                     break;
              case 7:
                if (change_password(clientsocket, &authenticatedprof)) {
                    send(clientsocket, "Password changed successfully\n", strlen("Password changed successfully\n"), 0);
                } else {
                    send(clientsocket, "Failed to change password\n", strlen("Failed to change password\n"), 0);
                }
                break;

              }
        }
    }
    return false;
}
