
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
#include "loan.h"


bool manager_login(int clientSocket);
bool authenticate_manager(int clientSocket);
bool assign_loan(int clientSocket);
bool change_active(int clientSocket);
//bool change_password(clientSocket);

bool manager_login(int clientSocket)
{printf("hello\n");
send(clientSocket,"hello\n",strlen("hello\n"),0);

if(authenticate_manager(clientSocket))

{send(clientSocket,"login successful\n",strlen("login successful\n"),0);
//ssize_t rbytes;
//char rbuff[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t rbytes;
char rbuff[1024];
char menu[]="select the option number \n1.activate/deactivate\n2.assign loan process to emp\n3.reviw feedback.\n4.change password\n5.logout\n6.exit\n";
send(clientSocket,menu,strlen(menu),0);
printf("bye");
rbytes=recv(clientSocket,rbuff,sizeof(rbuff),0);
if(rbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(rbuff);

switch (choice){
        case 1:
         if(change_active(clientSocket))
        {
        send(clientSocket,"successfuly done the activation/deactivation\npress enter to continue\n",strlen("successfully done the activation/deactivation\npress enter to continue\n"),0);
        }
        break;
        case 2:
                if(assign_loan(clientSocket))
        {send(clientSocket,"successfully assigned loan to bank employee\n",strlen("successfully assigned loan to bank employee\n"),0);}
        break;
       case 3:
         //       if(review_feed(clientSocket))
       // {send(clientSocket,"success\n",strlen("success\n"),0);}
        break;
	case 4:
		if(change_emppassword(clientSocket))
		 {send(clientSocket,"success\n",strlen("success\n"),0);}

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
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end
bool authenticate_manager(int clientSocket)
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
    struct Employee temp;
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
bool assign_loan(int cd){
	struct loan data_new;
        char custid[10];
        char format[300];
        char enter_id[] = "enter customer id:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, custid, sizeof(custid));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return false;
        }
        custid[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", custid);

        int db_fd = open("loan_db.txt", O_RDWR);
        if (db_fd == -1) {
                perror("Error in opening the database file");
                return false;
        }

        char line[300];
        struct loan temp;
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

                sscanf(line, "%[^,],%[^,],%d", temp.cust_id,temp.eid,&temp.status);
                printf("Read Customer: ID=%s, eid=%d, status=%d\n", temp.cust_id, temp.eid, temp.status);

                if (atoi(temp.cust_id)==atoi(custid)){
                        printf("Customer ID matched.\n");

                lock.l_start = current_position - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(db_fd, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(db_fd);
                        return false;
                }

                write(cd, "Enter Employee ID:", strlen("Enter Employee ID:"));
                ssize_t data_read1=read(cd, data_new.eid, sizeof(data_new.eid));
                if (data_read1 <= 0)
                {
                        close(cd);
                        exit(1);
                }

                if(data_new.eid[data_read1-1]=='\n')
                        data_new.eid[data_read1-1]='\0';
                else    
                        data_new.eid[data_read1]='\0';


		data_new.status=1;//Means empl is assigned
		snprintf(format, sizeof(format), "%s,%s,%d\n", temp.cust_id,data_new.eid, data_new.status);


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
                write(cd, "Customer Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;

}//end of assign loan


bool change_active(int cd)
{
struct customer data_new;
        char custid[10];
        char format[300];
        char enter_id[] = "Enter id of the Customer:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, custid, sizeof(custid));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return false;
        }
        custid[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", custid);

        int db_fd = open("customer.txt", O_RDWR);
        if (db_fd == -1) {
                perror("Error in opening the database file");
                return false;
        }

        char line[300];
        struct customer temp;
        bool is_there = false;

        struct flock lock;
        memset(&lock, 0, sizeof(lock));
        lock.l_type = F_WRLCK;  
        lock.l_whence = SEEK_SET;  

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

                int active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username, temp.bal,&active_int);
                temp.active = (active_int != 0); 

                if (atoi(temp.id)==atoi(custid)) {
                        printf("Customer ID matched.\n");

                lock.l_start = current_position - strlen(line) - 1;  
                lock.l_len = strlen(line); 

                if (fcntl(db_fd, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(db_fd);
                        return false;
                }

		char ch[2];
		if(temp.active==1){
			write(cd,"Customer Account is Active. Do you want to Deactivate the Account?\nPress 1 or 0:",strlen("Customer Account is Active. Do you want to Deactivate the Account?\nPress 1 or 0:")); 
        		ssize_t bytes_ch = read(cd, ch, sizeof(ch));
        		if (bytes_ch == -1) {
                		perror("Error in receiving");
                		return false;
        		}
        		ch[bytes_ch] = '\0';
			if(atoi(ch)==1){
				data_new.active=0;
				write(cd," Account Deactivated",strlen(" Account Deactivated"));  
			}
			else{
				write(cd,"No Change",strlen("No Change"));
				data_new.active=1;
			}
		}
		
		else{
                        write(cd,"Customer Account is Deactive. Do you want to Activate the Account?\nPress 1 or 0:",strlen("Customer Account is Deactive. Do you want to Activate the Account\nPress 1 or 0"));
                        ssize_t bytes_ch = read(cd, ch, sizeof(ch));
                        if (bytes_ch == -1) {
                                perror("Error in receiving");
                                return false;
                        }
                        ch[bytes_ch] = '\0';
                        if(atoi(ch)==1){
                                data_new.active=1;
                                write(cd," Account Activated",strlen(" Account Activated"));  
                        }
                        else{
                                write(cd,"No Change",strlen("No Change"));
                                data_new.active=0;
                        }
                }



                snprintf(format, sizeof(format), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,temp.bal,data_new.active);

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


}//end of change_Active
