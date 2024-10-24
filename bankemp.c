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
//#include "common.h"
#include "customer.h"
#include "loan.h"

bool login_bankemployee(int clientsocket);
bool authenticate_bankemp(int clientsocket);
bool add_customer(int clientsocket);
bool modify_customerdetails(int clientsocket);
bool change_emppassword(int clientsocket);
bool process_loan(int clientSocket); //approve/reject loan
bool view_loan( int clientSocket);

bool login_bankemployee(int clientsocket)
{printf("hello\n");
send(clientsocket,"hello\n",strlen("hello\n"),0);

if(authenticate_bankemp(clientsocket))

{send(clientsocket,"login successful\n",strlen("login successful\n"),0);
//ssize_t rbytes;
//char rbuff[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t readbytes;
char readbuffer[1024];
char menu[]="select the option number \n1.Add new customer\n2.modify customer details\n3.approve reject loans\n4.view assigned loan\n5.change password\n6.logout\n7.exit\n";
send(clientsocket,menu,strlen(menu),0);
printf("bye");
readbytes=recv(clientsocket,readbuffer,sizeof(readbuffer),0);
if(readbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(readbuffer);

switch (choice){
        case 1:
         if(add_customer(clientsocket))
        {
        send(clientsocket,"successfuly added\npress enter to continue\n",strlen("successfully added\npress enter to continue\n"),0);
        }
        break;
        case 2:
                if(modify_customerdetails(clientsocket))
        {send(clientsocket,"successfully modify\n",strlen("successfully modify\n"),0);}
        break;
       case 3:

                if(process_loan(clientsocket))
        {send(clientsocket,"success\n",strlen("success\n"),0);}

        break;

	case 4:
                  if(view_loan(clientsocket))	
	break;

        case 5:
		printf("inside case 5\n");
                if(change_emppassword(clientsocket))
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
                    break;
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end
bool authenticate_bankemp(int clientsocket)
{
send(clientsocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");
char empid[50];
char password[10];
send(clientsocket,"empid:\n",strlen("empid:\n"),0);
ssize_t read1=recv(clientsocket,empid,sizeof(empid),0);
if (read1<=0)
{
close (clientsocket);
return 0;
}
if(empid[read1 -1]=='\n')
{empid[read1 -1]='\0';}
else
{empid[read1 -1]='\0';}
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
int dbfile = open("employee.txt", O_RDONLY);
    if (dbfile == -1) {
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

    while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(dbfile, 0, SEEK_CUR);

            sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, temp.role);
            printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,empid);

            if (atoi(temp.id)==atoi( empid)&& atoi(temp.password)==atoi(password)) {
                printf("Employee ID matched.\n");return true;}
   }//end of else
}//end of while

}//end of authenticate

bool add_customer(int clientsocket)
{struct customer cust;
//int empid=get_id();
//add.id=empid;
send(clientsocket,"enter customer id\n",strlen("enter customer id\n"),0);
int read1=recv(clientsocket,cust.id,sizeof(cust.id),0);
cust.id[read1 -1]='\0';
send(clientsocket,"enter username\n",strlen("enter username\n"),0);
 read1=recv(clientsocket,cust.username,sizeof(cust.username),0);
//add.id[read -1]='\0';
if(read1<=0)
{send(clientsocket,"error in fetching username\n",strlen("error in fetching username\n"),0);
return false;}
cust.username[read1-1]='\0';
send(clientsocket,"enter password\n",strlen("enter password\n"),0);
read1=recv(clientsocket,cust.password,sizeof(cust.password),0);
if(read1<=0)
{send(clientsocket,"error in fetching password\n",strlen("error in fetching password\n"),0);
return false;}
cust.password[read1-1]='\0';

send(clientsocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
read1=recv(clientsocket,cust.bal,sizeof(cust.bal),0);
if(read<=0)
{send(clientsocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
return false;}
cust.bal[read1-1]='\0';
cust.active=true;
FILE *file=fopen("customer.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s,%d\n",cust.id,cust.password,cust.username,cust.bal,cust.active);
fclose(file);
printf("true\n");
fflush(stdout);
return true;}
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}//end of add_customer

bool modify_customerdetails(int clientsocket)
{
struct customer custmod;
        char custid[10];
        char passbuff[300];
        char enter_id[] = "Enter customer id:";

        write(clientsocket, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(clientsocket, custid, sizeof(custid));
        if (bytes_id == -1) {
                perror("Error in receiving customer id");
                return false;
        }
        custid[bytes_id] = '\0';  
        printf("Received customer id: %s\n", custid);

        int dbfile = open("customer.txt", O_RDWR);
        if (dbfile == -1) {
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

        while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        }
         else {
                line[line_index] = '\0';
                line_index = 0;

                current_position = lseek(dbfile, 0, SEEK_CUR);

                int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                lock.l_start = current_position - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(dbfile, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(dbfile);
                        return false;
                }

                write(clientsocket, "username:", strlen("username:"));
                read(clientsocket, custmod.username, sizeof(custmod.username));

                 write(clientsocket, "cid", strlen("cid"));
                ssize_t byteread1 = read(clientsocket,custmod.id,sizeof(custmod.id));

                if (byteread1 <= 0)
                {
                        close(clientsocket);
                        exit(1);
                }

                if(custmod.id[byteread1-1]=='\n')
                        custmod.id[byteread1-1]='\0';
                else    
                        custmod.id[byteread1]='\0';


                snprintf(passbuff, sizeof(passbuff), "%s,%s,%s,%s,%d\n", custmod.id, temp.password, custmod.username,temp.bal,temp.active);

                lseek(dbfile, current_position - strlen(line) - 1, SEEK_SET);

                if (write(dbfile, passbuff, strlen(passbuff)) == -1) {
                        write(clientsocket, "Error in Updating Data", strlen("Error in Updating Data"));
                        close(dbfile);
                        return false;
                }

                lock.l_type = F_UNLCK;
                if (fcntl(dbfile, F_SETLK, &lock) == -1) {
                        perror("Error in releasing the lock");
                        close(dbfile);
                        return false;
                }

                is_there = true;
                break;
            }
        }
    }

        close(dbfile);

        if (!is_there) {
                write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;
}//end of modify customer

bool change_emppassword(int clientsocket)
{printf("inside change password\n");
struct Employee empmod;
    char employeeID[10];
	char password[10];
    //char format[300]; 
char passbuff[100];
    char enter_id[] = "enter id";

    write(clientsocket, enter_id, sizeof(enter_id));
    ssize_t bytesread = read(clientsocket, employeeID, sizeof(employeeID));
    if (bytesread == -1) {
        perror("Error in receiving Employee ID");
        return false;
    }
    printf("Received Employee ID: %s\n", employeeID);
write(clientsocket, "old password\n", strlen("old password\n"));
     bytesread = read(clientsocket, password, sizeof(password));
    if (bytesread == -1) {
        perror("Error in receiving password");
        return false;
    }
    printf("password: %s\n", password);


    write(clientsocket, "new password:", strlen("new password:"));
    read(clientsocket, empmod.password, sizeof(empmod.password));
	printf("pass=%s",empmod.password);
    //write(clientsocket, "ID:", strlen("ID:"));
    //read(clientsocket, data_new.id, sizeof(data_new.id));
	//write(clientsocket,"role",strlen("role"));
	//read(clientsocket,data_new.role,sizeof(data_new.role));

    int dbfile = open("employee.txt", O_RDWR);
    if (dbfile == -1) {
        perror("Error in opening the database file");
        return false;
    }

    char line[300];
    struct Employee temp;
    bool is_there = false;

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;  
    lock.l_whence = SEEK_SET;  

//    off_t record_offset = 0;
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

            sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, temp.role);
            printf("Read Employee: ID=%s, password=%s, username=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,employeeID);
            if (atoi(temp.id)==atoi(employeeID)) {
                printf("Employee ID matched.\n");
                lock.l_start = current_position - strlen(line) - 1;
                lock.l_len = strlen(line) + 1;

                if (fcntl(dbfile, F_SETLK, &lock) == -1) {
                    perror("Error in obtaining lock");
                    close(dbfile);
                    return false;
                }		printf("%s",empmod.password);
                //strcpy(data_new.password, temp.password);  
 if (atoi(temp.id)==atoi(employeeID)&& atoi(temp.password)==atoi(password)){
                snprintf(passbuff, sizeof(passbuff), "%s,%s,%s,%s\n", temp.id, empmod.password, temp.username, temp.role);

                lseek(dbfile, current_position - strlen(line) - 1, SEEK_SET);
		printf("%s",empmod.password);
                if (write(dbfile, passbuff, strlen(passbuff)) == -1) {
                    write(clientsocket, "Error in Updating Data", strlen("Error in Updating Data"));
                    close(dbfile);
                    return false;
                }
		printf("updated");
                lock.l_type = F_UNLCK;
                if (fcntl(dbfile, F_SETLK, &lock) == -1) {
                    perror("Error in releasing the lock");
                    close(dbfile);
                    return false;
                }

                is_there = true;
                break;
}
            }
        }
    }

    close(dbfile);

    if (!is_there) {
        write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
        return false;
    }

    return true;
}


bool process_loan(int cd){
	struct loan data_new;
        char custid[10];
        char format[300];
        char enter_id[] = "Enter id of customer:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, custid, sizeof(custid));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return false;
        }	
	
        custid[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", custid);

	char ch[2];
        char ch_prompt[]="Press 1 to Approve 0 to Reject:";
	 write(cd, ch_prompt, sizeof(ch_prompt));
printf("after write\n");
        ssize_t bytes_ch = read(cd, ch, sizeof(ch));
        if (bytes_ch == -1) {
                perror("Error");
                return false;
        }
       // ch[bytes_ch] = '\0';  

        int db_fd = open("loan.txt", O_RDWR);
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

                if (strcmp(temp.cust_id, custid) == 0) {
                        printf("Customer ID matched.\n");

                lock.l_start = current_position - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(db_fd, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(db_fd);
                        return false;
                }
		
		if(ch=='1'){
			data_new.status=2;
			write(cd,"Loan Approved\n",strlen("Loan Approved\n"));
		}
		else{
			
                        write(cd,"Loan Rejected\n",strlen("Loan Rejected\n"));
                }
	

                snprintf(format, sizeof(format), "%s,%s,%d\n", temp.cust_id, temp.eid, data_new.status);

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
                write(cd, "Customer Not Found", strlen("Customer Not Found"));
                return false;
        }

        return true;

}//end of process_loan


bool view_loan(int cd)
{
struct loan data_new;
        char emplid[10];
        char format[300];
        char enter_id[] = "Enter Your ID:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, emplid, sizeof(emplid));
        if (bytes_id == -1) {
                perror("Error in receiving Employee ID");
                return false;
        }
        emplid[bytes_id] = '\0';  
        printf("Received Employee ID: %s\n", emplid);

        int db_fd = open("loan_db.txt", O_RDWR);
        if (db_fd == -1) {
                perror("Error in opening the database file");
                return false;
        }
	 char buffer;
        int line_index = 0;
	char transaction_buffer[500];

	char line[300];
        struct loan temp;
        bool is_there = false;
	off_t current_position = 0;
	

	while (read(db_fd, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        }

         else {
                line[line_index] = '\0';
                line_index = 0;

                current_position = lseek(db_fd, 0, SEEK_CUR);

                sscanf(line, "%[^,],%[^,],%d", temp.cust_id,temp.eid,&temp.status);
                printf("Read Customer: ID=%s, Employee= %s, status=%d\n", temp.cust_id,temp.eid,&temp.status);

                if (atoi(temp.eid)==atoi(emplid)) {
                        printf("Employee ID matched.\n");

		char temp1[256];
                snprintf(temp1, sizeof(temp1), "CID: %s\n",temp.cust_id);
		
		 strcat(transaction_buffer, temp1);
		continue;            
		

                }

         
            }}
	    if(transaction_buffer!=NULL){
	    write(cd,transaction_buffer,strlen(transaction_buffer));
	   return true;

        	}
	    else
		write(cd,"No Loan Applications Assigned\n",strlen("No Loan Applications Assigned\n"));
		return false;
	
//return true;
}
