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
#include "transaction.h"
#include "loan.h"
#include "feedback.h"

bool customer_login(int clientSocket);
bool authenticate_customer(int clientSocket);
bool account_bal(int clientSocket);
bool deposit(int clientSocket);
bool transaction(int clientSocket);
//void update_bal(int amount);
bool withdraw(int clientSocket);
bool changepass(int clientSocket);
bool trans_history(int clientSocket);
bool apply_loan(int clientSocket);
bool feedback(int clientSocket);


bool customer_login(int clientSocket)

{printf("hello\n");
send(clientSocket,"hello\n",strlen("hello\n"),0);

if(authenticate_customer(clientSocket))

{send(clientSocket,"login successful\n",strlen("login successful\n"),0);
//ssize_t rbytes;
//char rbuff[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t rbytes;
char rbuff[1024];
char menu[]="select the option number \n1.view account balance\n2.deposit money\n3.withdraw money\n4.transfer funds\n5.apply loan\n6.change password\n7.adding feedback\n8.view transaction history\n9.logout\n10.exit\n";
send(clientSocket,menu,strlen(menu),0);
printf("bye");
rbytes=recv(clientSocket,rbuff,sizeof(rbuff),0);
if(rbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(rbuff);

switch (choice){
        case 1:
         if(account_bal(clientSocket))
        {
        send(clientSocket,"successfuly retreived account balance\npress enter to continue\n",strlen("successfully retreived account balance\npress enter to continue\n"),0);
        }
        break;
        case 2:
                if(deposit(clientSocket))
        {send(clientSocket,"successfully deposit\n",strlen("successfully deposit\n"),0);}
        break;
       case 3:
                if(withdraw(clientSocket))
        {send(clientSocket,"successfully withdrawal\n",strlen("successfully withdrawal\n"),0);}
        break;
	case 4:
		if(transaction(clientSocket))
	 {send(clientSocket,"successfully withdrawal\n",strlen("successfully withdrawal\n"),0);}

	break;
	case 5:
		if(apply_loan(clientSocket))
		 {send(clientSocket,"successfully applied\n",strlen("successfully applied\n"),0);}

	break;
	
        case 6:
		printf("inside case 5\n");
                if(changepass(clientSocket))
        {send(clientSocket,"successfully changed\n",strlen("successfully changed\n"),0);}

        break;
	case 7: if(feedback(clientSocket));
	break;
	case 8:
		if(trans_history(clientSocket));
	break;
        case 9:
                send(clientSocket,"successfully logged out\n",strlen("successfully logged out\n"),0);
                return true;
        break;
        case 10:
                close(clientSocket);
                break;
         default:
                    break;
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end

bool authenticate_customer(int clientSocket)
{
send(clientSocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");
char cid[50];
char password[10];
write(clientSocket,"id:\n",strlen("id:\n"));
ssize_t read1=read(clientSocket,cid,sizeof(cid));
if (read1<=0)
{
close (clientSocket);
return 0;
}
if(cid[read1 -1]=='\n')
{cid[read1 -1]='\0';}
else
{cid[read1 -1]='\0';}
write(clientSocket, "enter password:\n",strlen("enter password:\n"));
read1=read(clientSocket,password,sizeof(password));
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
int db_fd = open("customer.txt", O_RDONLY);
    if (db_fd == -1) {
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

    while (read(db_fd, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(db_fd, 0, SEEK_CUR);
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

bool account_bal(int clientSocket)
{
char cid[50];
char password[10];
write(clientSocket,"id:\n",strlen("id:\n"));
ssize_t read1=read(clientSocket,cid,sizeof(cid));
if (read1<=0)
{
close (clientSocket);
return 0;
}
if(cid[read1 -1]=='\n')
{cid[read1 -1]='\0';}
else
{cid[read1 -1]='\0';}
int db_fd = open("customer.txt", O_RDONLY);
    if (db_fd == -1) {
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

    while (read(db_fd, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(db_fd, 0, SEEK_CUR);
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


           // sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
           // printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,cid);

            if (atoi(temp.id)==atoi( cid)) {
                write(clientSocket,temp.bal,sizeof(temp.bal));return true;}
   }//end of else
}//end of while


}//end of account_bal

bool deposit(int cd)
{
struct transaction add;
//int empid=get_id();
//add.id=empid;
write(cd,"enter senderid\n",strlen("enter senderid\n"));
int read1=read(cd,add.sender,sizeof(add.sender));
add.sender[read1 -1]='\0';
write(cd,"enter receiver\n",strlen("enter receiver\n"));
 read1=read(cd,add.receiver_id,sizeof(add.receiver_id));
//add.id[read -1]='\0';
if(read1<=0)
{send(cd,"error in receiver\n",strlen("error in receiver\n"),0);
return false;}
add.receiver_id[read1-1]='\0';
write(cd,"enter amount\n",strlen("enter amount\n"));
read1=read(cd,add.amount,sizeof(add.amount));
int amount=atoi(add.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{send(cd,"error in amount\n",strlen("error in amount\n"),0);
return false;}
add.amount[read1-1]='\0';

//send(clientSocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
//read1=recv(clientSocket,add.bal,sizeof(add.bal),0);
//if(read<=0)
//{send(clientSocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
//return false;}
strcpy(add.flag, "1");

//add.flag[read1-1]='\0';
//add.active=true;
FILE *file=fopen("transaction.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",add.sender,add.receiver_id,add.amount,add.flag);
fclose(file);
printf("true\n");
fflush(stdout);
}
else{
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}

struct customer data_new;
        char cid[10];
        char format[300];
        char enter_id[] = "Enter sender id:";

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

                //write(cd, "username:", strlen("username:"));
              //ssize_t read1=  read(cd, data_new.username, sizeof(data_new.username));
		//if(read1<=0)
//{
		//close(cd);exit(1);}
		//if(data_new.username[read1 -1]=='\n')
		//	data_new.username[read1 -1]='\0';
		//else
		//	data_new.username[read1]='\0';
                 //write(cd, "cid", strlen("cid"));
               // ssize_t data_read = read(cd,data_new.id,sizeof(data_new.id));

               // if (data_read <= 0)
                //{
                  //      close(cd);
                    //    exit(1);
               // }

               // if(data_new.id[data_read-1]=='\n')
                 //       data_new.id[data_read-1]='\0';
                //else    
                  //      data_new.id[data_read]='\0';
		int new_bal=amount+atoi(temp.bal);
		sprintf(data_new.bal, "%d", new_bal);
		printf("%s\n",data_new.bal);
                snprintf(format, sizeof(format), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,data_new.bal,temp.active);

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

}// end of deposit

bool withdraw(int cd)
{
struct transaction add;
//int empid=get_id();
//add.id=empid;
write(cd,"enter senderid\n",strlen("enter senderid\n"));
int read1=read(cd,add.sender,sizeof(add.sender));
add.sender[read1 -1]='\0';
write(cd,"enter receiver\n",strlen("enter receiver\n"));
 read1=read(cd,add.receiver_id,sizeof(add.receiver_id));
//add.id[read -1]='\0';
if(read1<=0)
{send(cd,"error in receiver\n",strlen("error in receiver\n"),0);
return false;}
add.receiver_id[read1-1]='\0';
write(cd,"enter amount\n",strlen("enter amount\n"));
read1=read(cd,add.amount,sizeof(add.amount));
int amount=atoi(add.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{send(cd,"error in amount\n",strlen("error in amount\n"),0);
return false;}
add.amount[read1-1]='\0';

//send(clientSocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
//read1=recv(clientSocket,add.bal,sizeof(add.bal),0);
//if(read<=0)
//{send(clientSocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
//return false;}
strcpy(add.flag, "0");

//add.flag[read1-1]='\0';
//add.active=true;
FILE *file=fopen("transaction.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",add.sender,add.receiver_id,add.amount,add.flag);
fclose(file);
printf("true\n");
fflush(stdout);
}
else{
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}

struct customer data_new;
        char cid[10];
        char format[300];
        char enter_id[] = "Enter sender id:";

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

                //write(cd, "username:", strlen("username:"));
              //ssize_t read1=  read(cd, data_new.username, sizeof(data_new.username));
		//if(read1<=0)
//{
		//close(cd);exit(1);}
		//if(data_new.username[read1 -1]=='\n')
		//	data_new.username[read1 -1]='\0';
		//else
		//	data_new.username[read1]='\0';
                 //write(cd, "cid", strlen("cid"));
               // ssize_t data_read = read(cd,data_new.id,sizeof(data_new.id));

               // if (data_read <= 0)
                //{
                  //      close(cd);
                    //    exit(1);
               // }

               // if(data_new.id[data_read-1]=='\n')
                 //       data_new.id[data_read-1]='\0';
                //else    
                  //      data_new.id[data_read]='\0';
		int new_bal=atoi(temp.bal)-amount;
		sprintf(data_new.bal, "%d", new_bal);
		printf("%s\n",data_new.bal);
                snprintf(format, sizeof(format), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,data_new.bal,temp.active);

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

}// end of withdraw

bool transaction(int cd)
{
struct transaction add;
//int empid=get_id();
//add.id=empid;
write(cd,"enter senderid\n",strlen("enter senderid\n"));
int read1=read(cd,add.sender,sizeof(add.sender));
add.sender[read1 -1]='\0';
write(cd,"enter receiver id\n",strlen("enter receiver id\n"));
 read1=read(cd,add.receiver_id,sizeof(add.receiver_id));
//add.id[read -1]='\0';
if(read1<=0)
{write(cd,"error in receiver\n",strlen("error in receiver\n"));
return false;}
add.receiver_id[read1-1]='\0';
write(cd,"enter amount\n",strlen("enter amount\n"));
read1=read(cd,add.amount,sizeof(add.amount));
int amount=atoi(add.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{write(cd,"error in amount\n",strlen("error in amount\n"));
return false;}
add.amount[read1-1]='\0';

//send(clientSocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
//read1=recv(clientSocket,add.bal,sizeof(add.bal),0);
//if(read<=0)
//{send(clientSocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
//return false;}
strcpy(add.flag, "2");

//add.flag[read1-1]='\0';
//add.active=true;
FILE *file=fopen("transaction.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",add.sender,add.receiver_id,add.amount,add.flag);
fclose(file);
printf("true\n");
fflush(stdout);
}
else{
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}

struct customer data_new;
        char cid[10];
        char format[300];
        char enter_id[] = "Enter sender id:";

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
                printf("Read customer: id=%s, Password=%s, Username=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);

                if (atoi(temp.id)==atoi( cid)) {
                        printf("customer is matched.\n");

                lock.l_start = current_position - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(db_fd, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(db_fd);
                        return false;
                }

		int new_bal=atoi(temp.bal)-amount;
		sprintf(data_new.bal, "%d", new_bal);
		printf("%s\n",data_new.bal);
                snprintf(format, sizeof(format), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,data_new.bal,temp.active);

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

        struct customer data_new1;
        char cid1[10];
        char format1[300];
        char enter_id1[] = "Enter receiver id:";

        write(cd, enter_id1, sizeof(enter_id1));
        ssize_t bytes_id1 = read(cd, cid1, sizeof(cid1));
        if (bytes_id1 == -1) {
                perror("Error in receiving customer id");
                return false;
        }
        cid1[bytes_id1] = '\0';  
        printf("Received customer id: %s\n", cid1);

        int db_fd1 = open("customer.txt", O_RDWR);
        if (db_fd1 == -1) {
                perror("Error in opening the customer file");
                return false;
        }

        char line1[300];
        struct customer temp1;
        bool is_there1 = false;

        struct flock lock1;
        memset(&lock1, 0, sizeof(lock1));
        lock1.l_type = F_WRLCK;  
        lock1.l_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t current_position1 = 0;

         char buffer1;
        int line_index1 = 0;

        while (read(db_fd1, &buffer1, 1) > 0) {
        if (buffer1 != '\n') {
            line1[line_index1++] = buffer1;
        }
         else {
                line1[line_index1] = '\0';
                line_index1 = 0;

                current_position1 = lseek(db_fd1, 0, SEEK_CUR);

                int is_active_int1;
                sscanf(line1, "%[^,],%[^,],%[^,],%[^,],%d", temp1.id, temp1.password, temp1.username,temp1.bal, &is_active_int1);
                temp1.active = (is_active_int1 != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp1.id, temp1.password, temp1.username,temp1.bal,temp1.active);

                if (atoi(temp1.id)==atoi( cid1)) {
                        printf("customer is matched.\n");

                lock1.l_start = current_position1 - strlen(line1) - 1;  
                lock1.l_len = strlen(line1) + 1; 

                if (fcntl(db_fd1, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(db_fd1);
                        return false;
                }

                //write(cd, "username:", strlen("username:"));
              //ssize_t read1=  read(cd, data_new.username, sizeof(data_new.username));
		//if(read1<=0)
//{
		//close(cd);exit(1);}
		//if(data_new.username[read1 -1]=='\n')
		//	data_new.username[read1 -1]='\0';
		//else
		//	data_new.username[read1]='\0';
                 //write(cd, "cid", strlen("cid"));
               // ssize_t data_read = read(cd,data_new.id,sizeof(data_new.id));

               // if (data_read <= 0)
                //{
                  //      close(cd);
                    //    exit(1);
               // }

               // if(data_new.id[data_read-1]=='\n')
                 //       data_new.id[data_read-1]='\0';
                //else    
                  //      data_new.id[data_read]='\0';
		int new_bal1=atoi(temp1.bal)+amount;
		sprintf(data_new1.bal, "%d", new_bal1);
		printf("%s\n",data_new1.bal);
                snprintf(format1, sizeof(format1), "%s,%s,%s,%s,%d\n", temp1.id, temp1.password, temp1.username,data_new1.bal,temp1.active);

                lseek(db_fd, current_position1 - strlen(line1) - 1, SEEK_SET);

                if (write(db_fd1, format1, strlen(format1)) == -1) {
                        write(cd, "Error in Updating Data", strlen("Error in Updating Data"));
                        close(db_fd1);
                        return false;
                }

                lock1.l_type = F_UNLCK;
                if (fcntl(db_fd1, F_SETLK, &lock1) == -1) {
                        perror("Error in releasing the lock");
                        close(db_fd1);
                        return false;
                }

                is_there1 = true;
                break;
}
}
}

        close(db_fd1);

        if (!is_there1) {
                write(cd, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;


}// end of transaction

bool changepass(int cd)
{printf("inside change password\n");
struct customer data_new;
    char empid[10];
	char password[10];
    char format[300];
    char enter_id[] = "enter id";

    write(cd, enter_id, sizeof(enter_id));
    ssize_t bytes_id = read(cd, empid, sizeof(empid));
    if (bytes_id == -1) {
        perror("Error in receiving Employee ID");
        return false;
    }
    printf("Received Employee ID: %s\n", empid);
write(cd, "old password\n", strlen("old password\n"));
     bytes_id = read(cd, password, sizeof(password));
    if (bytes_id == -1) {
        perror("Error in receiving password");
        return false;
    }
    printf("password: %s\n", password);


    write(cd, "new password:", strlen("new password:"));
    read(cd, data_new.password, sizeof(data_new.password));
	printf("pass=%s",data_new.password);
    //write(cd, "ID:", strlen("ID:"));
    //read(cd, data_new.id, sizeof(data_new.id));
	//write(cd,"role",strlen("role"));
	//read(cd,data_new.role,sizeof(data_new.role));

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

    off_t record_offset = 0;
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
		int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


            //sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
            //printf("Read Employee: ID=%s, password=%s, username=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
	   printf("%s,%s\n",temp.id,empid);
            if (atoi(temp.id)==atoi( empid)) {
                printf("Employee ID matched.\n");
                lock.l_start = current_position - strlen(line) - 1;
                lock.l_len = strlen(line) + 1;

                if (fcntl(db_fd, F_SETLK, &lock) == -1) {
                    perror("Error in obtaining lock");
                    close(db_fd);
                    return false;
                }
		printf("%s",data_new.password);
                //strcpy(data_new.password, temp.password);  
 	if (atoi(temp.id)==atoi( empid)&& atoi(temp.password)==atoi(password)){
                //snprintf(format, sizeof(format), "%s,%s,%s,%s\n", temp.id, data_new.password, temp.username, temp.role);
	snprintf(format, sizeof(format), "%s,%s,%s,%s,%d\n", temp.id, data_new.password, temp.username,temp.bal,temp.active);


                lseek(db_fd, current_position - strlen(line) - 1, SEEK_SET);
		printf("%s",data_new.password);
                if (write(db_fd, format, strlen(format)) == -1) {
                    write(cd, "Error in Updating Data", strlen("Error in Updating Data"));
                    close(db_fd);
                    return false;
                }
		printf("updated");
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
}

    close(db_fd);

    if (!is_there) {
        write(cd, "Employee Not Found", strlen("Employee Not Found"));
        return false;
    }

    return true;
}

bool trans_history(int cd){
	 struct transaction data_new;
        char emplid[10];
        char format[300];
        char enter_id[] = "Enter id:";

        write(cd, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(cd, emplid, sizeof(emplid));
        if (bytes_id == -1) {
                perror("Error in receiving customer id");
                return false;
        }
        emplid[bytes_id] = '\0';  
        printf("Received customer id: %s\n", emplid);

        int db_fd = open("transaction.txt", O_RDWR);
        if (db_fd == -1) {
                perror("Error in opening the database file");
                return false;
        }
	 char buffer;
        int line_index = 0;
	char transaction_buffer[500];
char line[300];
        struct transaction temp;
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

                sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.sender,temp.receiver_id, temp.amount,temp.flag);
               // printf("Read Customer: ID=%s, Name=%s, Password=%s, Is Employed=%d\n", temp.id, temp.name, temp.pass, temp.is_empl);

                if (atoi(temp.sender)==atoi(emplid) ||atoi(temp.receiver_id)==atoi(emplid)) {
                        printf("Employee ID matched.\n");

		char temp1[256];
                snprintf(temp1, sizeof(temp1), "CID: %s,amount:%s,transaction performed:%s\n",temp.sender,temp.amount,temp.flag);
		
		 strcat(transaction_buffer, temp1);
		continue;            
		

                }

         
            }}
	    if(transaction_buffer!=NULL){
	    write(cd,transaction_buffer,strlen(transaction_buffer));
	   return true;

        	}
	    else
		write(cd,"No Loan Assigned\n",strlen("No Loan Assigned\n"));
		return false;
	
//return true;
}// end of transaction view


bool apply_loan(int cd){
	 struct loan l;

        char buf_id[]="customer id:\n";
        write(cd,buf_id,sizeof(buf_id));

        int bytes_id=read(cd,l.cust_id,sizeof(l.cust_id));
        if(bytes_id<=0){
                write(cd,"Error in receiving data from client\n",strlen("Error in receiving data from client\n"));
                return false;
        }
        l.cust_id[bytes_id]='\0';
        if(l.cust_id[bytes_id-1]=='\n'){
                l.cust_id[bytes_id-1]='\0';
        }

	
	l.status=0;
	//strcmp(l.empl_id,"EEEEE");

        FILE *file=fopen("loan_db.txt","a");
        if(file!=NULL){
                fprintf(file,"%s,%d,%s\n",l.cust_id,l.status,"EE");
                fclose(file);
                printf("true\n");
                fflush(stdout);
                return true;
        }
        perror("Error in opening Loan file");
        printf("false\n");
        fflush(stdout);
        return false;

}//end of loan



bool feedback(int cd)
{
struct feedback add;
write(cd,"enter cid\n",strlen("enter cid\n"));
int read1=read(cd,add.id,sizeof(add.id));
add.id[read1]='\0';
write(cd,"enter feedback\n",strlen("enter feedback\n"));
 read1=read(cd,add.feed,sizeof(add.feed));
//add.id[read -1]='\0';
if(read1<=0)
{send(cd,"error in feedback\n",strlen("error in feedback\n"),0);
return false;}
add.feed[read1]='\0';
FILE *file=fopen("feedback.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s\n",add.id,add.feed);
fclose(file);
printf("true\n");
fflush(stdout);
return true;}
else{
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}


}//end of feedback
