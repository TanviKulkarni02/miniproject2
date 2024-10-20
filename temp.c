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
#include "admin.h"
#include "employee.h"
#include "customer.h"
bool employee_login(int clientSocket);
bool authenticate_emp(int clientSocket);
bool add_customer(int cd);
bool modify_customer(int clientSocket);
bool employee_login(int clientSocket)
{printf("hello\n");
send(clientSocket,"hello\n",strlen("hello\n"),0);

if(authenticate_emp(clientSocket))

{send(clientSocket,"login successful\n",strlen("login successful\n"),0);
//ssize_t rbytes;
//char rbuff[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t rbytes;
char rbuff[1024];
char menu[]="select the option number \n1.Add new customer\n2.modify customer details\n3.process loan application\n4.process loan\n5.approve reject loans\n6.view assigned loan\n7.change password\n8.logout\n9.exit";
send(clientSocket,menu,strlen(menu),0);
printf("bye");
rbytes=recv(clientSocket,rbuff,sizeof(rbuff),0);
if(rbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(rbuff);

switch (choice){
        case 1:
         if(add_customer(clientSocket))
        {
        send(clientSocket,"successfuly added\npress enter to continue\n",strlen("successfully added\npress enter to continue\n"),0);
        }
        break;
        case 2:
                if(modify_customer(clientSocket))
        {send(clientSocket,"successfully modify\n",strlen("successfully modify\n"),0);}
        break;
       /* case 3:
                if(manage_user(clientSocket))
        {send(clientSocket,"success\n",strlen("success\n"),0);}
        break;
        case 4:
                if(change_pass(clientSocket))
        {send(clientSocket,"successfully changed\n",strlen("successfully changed\n"),0);}

        break;
        case 5:
                send(clientSocket,"successfully logged out\n",strlen("successfully logged out\n"),0);
                return true;
        break;
        case 6:
                close(clientSocket);
                break;
         default:
                    break;
}*///switch end
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end
bool authenticate_emp(int clientSocket)
{
send(clientSocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");
char empid[50];
char password[10];
send(clientSocket,"empid:\n",strlen("empid:\n"),0);
ssize_t read1=recv(clientSocket,empid,sizeof(empid),0);
if (read1<=0)
{
close (clientSocket);
return 0;
}
if(empid[read1 -1]=='\n')
{empid[read1 -1]='\0';}
else
{empid[read1 -1]='\0';}
send(clientSocket, "enter password:\n",strlen("enter password:\n"),0);
read1=recv(clientSocket,password,sizeof(password),0);
if(read1<=0)
{close(clientSocket);
return 0;
}
if(password[read1 -1]=='\n')
{
password[read1 -1]='\0';
}
else
{password[read1 -1]='\0';}
//if (strcmp(username,admin.username)==0 && strcmp(password,admin.password)==0)
int db_fd = open("employee.txt", O_RDONLY);
    if (db_fd == -1) {
        perror("Error in opening the database file");
        return false;
    }

    char line[300];
    struct employee temp;
    //bool is_there = false;

    //struct flock lock;
    //memset(&lock, 0, sizeof(lock));
    //lock.l_type = F_WRLCK;  
    //lock.l_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t current_position = 0;

    char buffer;
    int line_index = 0;

    while (read(db_fd, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(db_fd, 0, SEEK_CUR);

            sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
            printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,empid);

            if (atoi(temp.id)==atoi( empid)&& atoi(temp.password)==atoi(password)) {
                printf("Employee ID matched.\n");return true;}
   }//end of else
}//end of while

}//end of authenticate

bool add_customer(int clientSocket)
{struct customer add;
//int empid=get_id();
//add.id=empid;
send(clientSocket,"enter coustmerid\n",strlen("enter customerid\n"),0);
int read1=recv(clientSocket,add.id,sizeof(add.id),0);
add.id[read1 -1]='\0';
send(clientSocket,"enter username\n",strlen("enter username\n"),0);
 read1=recv(clientSocket,add.username,sizeof(add.username),0);
//add.id[read -1]='\0';
if(read1<=0)
{send(clientSocket,"error in fetching username\n",strlen("error in fetching username\n"),0);
return false;}
add.username[read1-1]='\0';
send(clientSocket,"enter password\n",strlen("enter password\n"),0);
read1=recv(clientSocket,add.password,sizeof(add.password),0);
if(read1<=0)
{send(clientSocket,"error in fetching password\n",strlen("error in fetching password\n"),0);
return false;}
add.password[read1-1]='\0';

send(clientSocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
read1=recv(clientSocket,add.bal,sizeof(add.bal),0);
if(read<=0)
{send(clientSocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
return false;}
add.bal[read1-1]='\0';
add.active=true;
FILE *file=fopen("customer.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s,%d\n",add.id,add.password,add.username,add.bal,add.active);
fclose(file);
printf("true\n");
fflush(stdout);
return true;}
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}//end of add_customer

bool modify_customer(int cd)
{
struct customer data_new;
        char cid[10];
        char format[300];
        char enter_id[] = "Enter customer id:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, cid, sizeof(cid));
        if (bytes_id == -1) {
                perror("Error in receiving customer id");
                return false;
        }
        cid[bytes_id] = '\0';  
        printf("Received customer id: %s\n", cid);

        int db_fd = open("customer.txt", O_RDWR);
        if (db_fd == -1) {
                perror("Error in opening the customer file");
                return false;
        }

        char line[300];
        struct customer temp;
        bool is_there = false;

        struct flock lock;
        memset(&lock, 0, sizeof(lock));
        lock.l_type = F_WRLCK;  
        lock.l_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t current_position = 0;

         char buffer;
        int line_index = 0;

        while (read(db_fd, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        }
         else {
                line[line_index] = '\0';
                line_index = 0;

                current_position = lseek(db_fd, 0, SEEK_CUR);

                int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);

                if (atoi(temp.id)==atoi( cid)) {
                        printf("customer is matched.\n");

                lock.l_start = current_position - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(db_fd, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(db_fd);
                        return false;
                }

                write(cd, "username:", strlen("username:"));
                read(cd, data_new.username, sizeof(data_new.username));

                 write(cd, "cid", strlen("cid"));
                ssize_t data_read = read(cd,data_new.id,sizeof(data_new.id));

                if (data_read <= 0)
                {
                        close(cd);
                        exit(1);
                }

                if(data_new.id[data_read-1]=='\n')
                        data_new.id[data_read-1]='\0';
                else    
                        data_new.id[data_read]='\0';


                snprintf(format, sizeof(format), "%s,%s,%s,%s,%d\n", data_new.id, temp.password, data_new.username,temp.bal,temp.active);

                lseek(db_fd, current_position - strlen(line) - 1, SEEK_SET);

                if (write(db_fd, format, strlen(format)) == -1) {
                        write(cd, "Error in Updating Data", strlen("Error in Updating Data"));
                        close(db_fd);
                        return false;
                }

                lock.l_type = F_UNLCK;
                if (fcntl(db_fd, F_SETLK, &lock) == -1) {
                        perror("Error in releasing the lock");
                        close(db_fd);
                        return false;
                }

                is_there = true;
                break;
            }
        }
    }

        close(db_fd);

        if (!is_there) {
                write(cd, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;
}//end of modify customer

