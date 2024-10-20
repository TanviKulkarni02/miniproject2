///#include<stdio.h>
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
#include "transaction.h"
bool login_customer(int clientsocket);
bool authenticate_customer(int clientsocket);
bool account_balance(int clientsocket);
bool deposit(int clientsocket);
bool transaction(int clientsocket);
//void update_bal(int amount);
bool withdraw(int clientsocket);
bool change_password(int clientsocket);
bool transaction_history(clientsocket);
bool customer_login(int clientsocket)
{
send(clientsocket,"hii\n",strlen("hii\n"),0);

if(authenticate_customer(clientsocket))

{send(clientsocket,"Successfully logged in\n",strlen("Successfully logged in\n"),0);
//ssize_t readbytes;
//char readbuffer[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t readbytes;
char readbuffer[1024];
char menu[]="select among the options \n1.view account balance\n2.deposit money\n3.withdraw money\n4.transfer funds\n5.apply loan\n6.change password\n7.adding feedback\n8.view transaction history\n9.logout\n10.exit\n";
send(clientsocket,menu,strlen(menu),0);
printf("bye");
readbytes=recv(clientsocket,readbuffer,sizeof(readbuffer),0);
if(readbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(readbuffer);

switch (choice){
        case 1:
         if(account_balance(clientsocket))
       // {
       // send(clientsocket,"successfuly added\npress enter to continue\n",strlen("successfully added\npress enter to continue\n"),0);
       // }
        break;
        case 2:
                if(deposit(clientsocket))
        {send(clientsocket,"successfully deposit\n",strlen("successfully deposit\n"),0);}
        break;
       case 3:
                if(withdraw(clientsocket))
        {send(clientsocket,"successfully withdrawal\n",strlen("successfully withdrawal\n"),0);}
        break;
	case 4:
		if(transaction(clientsocket))
	 {send(clientsocket,"successfully withdrawal\n",strlen("successfully withdrawal\n"),0);}

	break;
	case 5:
	break;
	
        case 6:
		printf("inside case 5\n");
                if(change_password(clientsocket))
        {send(clientsocket,"successfully changed\n",strlen("successfully changed\n"),0);}

        break;
	case 7:
	break;
	case 8:
		if(transaction_history(clientsocket);
	break;
        case 9:
                send(clientsocket,"successfully logged out\n",strlen("successfully logged out\n"),0);
                return true;
        break;
        case 10:
                close(clientsocket);
                break;
         default:
                    break;
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end

bool authenticate_customer(int clientsocket)
{
send(clientsocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");
char custid[50];
char password[10];
write(clientsocket,"id:\n",strlen("id:\n"));
ssize_t read1=read(clientsocket,custid,sizeof(custid));
if (read1<=0)
{
close (clientsocket);
return 0;
}
if(custid[read1 -1]=='\n')
{custid[read1 -1]='\0';}
else
{custid[read1 -1]='\0';}
write(clientsocket, "enter password:\n",strlen("enter password:\n"));
read1=read(clientsocket,password,sizeof(password));
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
    //bool flag = false;

    //struct flock lock;
    //memset(&lock, 0, sizeof(lock));
    //lock.l_type = F_WRLCK;  
    //lock.l_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t curr_pos = 0;

    char buffer;
    int line_ind = 0;

    while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        } else {
            line[line_ind] = '\0';
            line_ind = 0;

            curr_pos = lseek(dbfile, 0, SEEK_CUR);
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Reading customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


           // sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
           // printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,custid);

            if (atoi(temp.id)==atoi( custid)&& atoi(temp.password)==atoi(password)&&temp.active==1) {
                printf("The Employee ID was matched.\n");return true;}
   }//end of else
}//end of while

}//end of authenticate

bool account_balanceance(int clientsocket)
{
char custid[50];
char password[10];
write(clientsocket,"id:\n",strlen("id:\n"));
ssize_t read1=read(clientsocket,custid,sizeof(custid));
if (read1<=0)
{
close (clientsocket);
return 0;
}
if(custid[read1 -1]=='\n')
{custid[read1 -1]='\0';}
else
{custid[read1 -1]='\0';}
int dbfile = open("customer.txt", O_RDONLY);
    if (dbfile == -1) {
        perror("Error occurred while opening the database file");
        return false;
    }

    char line[300];
    struct customer temp;
    //bool flag = false;

    //struct flock lock;
    //memset(&lock, 0, sizeof(lock));
    //lock.l_type = F_WRLCK;  
    //lock.l_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t curr_pos = 0;

    char buffer;
    int line_ind = 0;

    while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        } else {
            line[line_ind] = '\0';
            line_ind = 0;

            curr_pos = lseek(dbfile, 0, SEEK_CUR);
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Reading customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


           // sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
           // printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,custid);

            if (atoi(temp.id)==atoi( custid)) {
                write(clientsocket,temp.bal,sizeof(temp.bal));return true;}
   }//end of else
}//end of while


}//end of account_balanceance

bool deposit(int clientsocket)
{
struct transaction dp;
//int empid=get_id();
//add.id=empid;
write(clientsocket,"enter senderid\n",strlen("enter senderid\n"));
int read1=read(clientsocket,dp.sender,sizeof(dp.sender));
dp.sender[read1 -1]='\0';
write(clientsocket,"enter receiver\n",strlen("enter receiver\n"));
 read1=read(clientsocket,dp.rec,sizeof(dp.rec));
//add.id[read -1]='\0';
if(read1<=0)
{send(clientsocket,"error in receiver\n",strlen("error in receiver\n"),0);
return false;}
dp.rec[read1-1]='\0';
write(clientsocket,"enter amount\n",strlen("enter amount\n"));
read1=read(clientsocket,dp.amount,sizeof(dp.amount));
int amount=atoi(dp.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{send(clientsocket,"error in amount\n",strlen("error in amount\n"),0);
return false;}
dp.amount[read1-1]='\0';

//send(clientsocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
//read1=recv(clientsocket,add.bal,sizeof(add.bal),0);
//if(read<=0)
//{send(clientsocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
//return false;}
strcpy(add.flag, "1");

//add.flag[read1-1]='\0';
//add.active=true;
FILE *file=fopen("transaction.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",dp.sender,dp.rec,dp.amount,dp.flag);
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

struct customer custmod;
        char custid[10];
        char buff2[300];
        char enter_id[] = "Enter sender id:";

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
        bool flag = false;

        struct flock lock;
        memset(&lock, 0, sizeof(lock));
        lock.l_type = F_WRLCK;  
        lock.l_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos = 0;

         char buffer;
        int line_ind = 0;

        while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        }
         else {
                line[line_ind] = '\0';
                line_ind = 0;

                curr_pos = lseek(dbfile, 0, SEEK_CUR);

                int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                lock.l_start = curr_pos - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(dbfile, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(dbfile);
                        return false;
                }

                //write(clientsocket, "username:", strlen("username:"));
              //ssize_t read1=  read(clientsocket, custmod.username, sizeof(custmod.username));
		//if(read1<=0)
//{
		//close(clientsocket);exit(1);}
		//if(custmod.username[read1 -1]=='\n')
		//	custmod.username[read1 -1]='\0';
		//else
		//	custmod.username[read1]='\0';
                 //write(clientsocket, "custid", strlen("custid"));
               // ssize_t data_read = read(clientsocket,custmod.id,sizeof(custmod.id));

               // if (data_read <= 0)
                //{
                  //      close(clientsocket);
                    //    exit(1);
               // }

               // if(custmod.id[data_read-1]=='\n')
                 //       custmod.id[data_read-1]='\0';
                //else    
                  //      custmod.id[data_read]='\0';
		int new_balance=amount+atoi(temp.bal);
		sprintf(custmod.bal, "%d", new_balance);
		printf("%s\n",custmod.bal);
                snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,custmod.bal,temp.active);

                lseek(dbfile, curr_pos - strlen(line) - 1, SEEK_SET);

                if (write(dbfile, buff2, strlen(buff2)) == -1) {
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

                flag = true;
                break;
            }
        }
    }

        close(dbfile);

        if (!flag) {
                write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;

}// end of deposit

bool withdraw(int clientsocket)
{
struct transaction wd;
//int empid=get_id();
//add.id=empid;
write(clientsocket,"enter id of sender\n",strlen("enter id of sender\n"));
int read1=read(clientsocket,wd.sender,sizeof(add.sender));
wd.sender[read1 -1]='\0';
write(clientsocket,"enter receiver\n",strlen("enter receiver\n"));
 read1=read(clientsocket,wd.rec,sizeof(wd.rec));
//add.id[read -1]='\0';
if(read1<=0)
{send(clientsocket,"error in receiver\n",strlen("error in receiver\n"),0);
return false;}
wd.rec[read1-1]='\0';
write(clientsocket,"enter the amount to withdraw\n",strlen("enter the amount to withdraw\n"));
read1=read(clientsocket,wd.amount,sizeof(wd.amount));
int amount=atoi(wd.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{send(clientsocket,"error in amount\n",strlen("error in amount\n"),0);
return false;}
wd.amount[read1-1]='\0';

//send(clientsocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
//read1=recv(clientsocket,add.bal,sizeof(add.bal),0);
//if(read<=0)
//{send(clientsocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
//return false;}
strcpy(wd.flag, "0");

//add.flag[read1-1]='\0';
//add.active=true;
FILE *file=fopen("transaction.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",wd.sender,wd.rec,wd.amount,wd.flag);
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

struct customer custmod;
        char custid[10];
        char buff2[300];
        char enter_id[] = "Enter sender id:";

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
        bool flag = false;

        struct flock lock;
        memset(&lock, 0, sizeof(lock));
        lock.l_type = F_WRLCK;  
        lock.l_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos = 0;

         char buffer;
        int line_ind = 0;

        while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        }
         else {
                line[line_ind] = '\0';
                line_ind = 0;

                curr_pos = lseek(dbfile, 0, SEEK_CUR);

                int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Reading customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                lock.l_start = curr_pos - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(dbfile, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(dbfile);
                        return false;
                }

                //write(clientsocket, "username:", strlen("username:"));
              //ssize_t read1=  read(clientsocket, custmod.username, sizeof(custmod.username));
		//if(read1<=0)
//{
		//close(clientsocket);exit(1);}
		//if(custmod.username[read1 -1]=='\n')
		//	custmod.username[read1 -1]='\0';
		//else
		//	custmod.username[read1]='\0';
                 //write(clientsocket, "custid", strlen("custid"));
               // ssize_t data_read = read(clientsocket,custmod.id,sizeof(custmod.id));

               // if (data_read <= 0)
                //{
                  //      close(clientsocket);
                    //    exit(1);
               // }

               // if(custmod.id[data_read-1]=='\n')
                 //       custmod.id[data_read-1]='\0';
                //else    
                  //      custmod.id[data_read]='\0';
		int new_balance=atoi(temp.bal)-amount;
		sprintf(custmod.bal, "%d", new_balance);
		printf("%s\n",custmod.bal);
                snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,custmod.bal,temp.active);

                lseek(dbfile, curr_pos - strlen(line) - 1, SEEK_SET);

                if (write(dbfile, buff2, strlen(buff2)) == -1) {
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

                flag = true;
                break;
            }
        }
    }

        close(dbfile);

        if (!flag) {
                write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;

}// end of withdraw

bool transaction(int clientsocket)
{
struct transaction trans;
//int empid=get_id();
//add.id=empid;
write(clientsocket,"enter senderid\n",strlen("enter senderid\n"));
int read1=read(clientsocket,trans.sender,sizeof(trans.sender));
trans.sender[read1 -1]='\0';
write(clientsocket,"enter receiver\n",strlen("enter receiver\n"));
 read1=read(clientsocket,trans.rec,sizeof(trans.rec));
//add.id[read -1]='\0';
if(read1<=0)
{send(clientsocket,"error in receiver\n",strlen("error in receiver\n"),0);
return false;}
trans.rec[read1-1]='\0';
write(clientsocket,"enter amount for transaction\n",strlen("enter amount for transaction\n"));
read1=read(clientsocket,trans.amount,sizeof(trans.amount));
int amount=atoi(trans.amount);printf("amount in transaction%d\n",amount);
if(read1<=0)
{send(clientsocket,"error occurred in amount\n",strlen("error occurred in amount\n"),0);
return false;}
trans.amount[read1-1]='\0';

//send(clientsocket,"enter initial balance of customer\n",strlen("enter initial balance of customer\n"),0);
//read1=recv(clientsocket,add.bal,sizeof(add.bal),0);
//if(read<=0)
//{send(clientsocket,"error in fetching bal\n",strlen("error in fetching bal\n"),0);
//return false;}
strcpy(trans.flag, "2");

//add.flag[read1-1]='\0';
//add.active=true;
FILE *file=fopen("transaction.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",trans.sender,trans.rec,trans.amount,trans.flag);
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

struct customer custmod;
        char custid[10];
        char buff2[300];
        char enter_id[] = "Enter sender id:";

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
        bool flag = false;

        struct flock lock;
        memset(&lock, 0, sizeof(lock));
        lock.l_type = F_WRLCK;  
        lock.l_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos = 0;

         char buffer;
        int line_ind = 0;

        while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        }
         else {
                line[line_ind] = '\0';
                line_ind = 0;

                curr_pos = lseek(dbfile, 0, SEEK_CUR);

                int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                lock.l_start = curr_pos - strlen(line) - 1;  
                lock.l_len = strlen(line) + 1; 

                if (fcntl(dbfile, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(dbfile);
                        return false;
                }

		int new_balance=atoi(temp.bal)-amount;
		sprintf(custmod.bal, "%d", new_balance);
		printf("%s\n",custmod.bal);
                snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,custmod.bal,temp.active);

                lseek(dbfile, curr_pos - strlen(line) - 1, SEEK_SET);

                if (write(dbfile, buff2, strlen(buff2)) == -1) {
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

                flag = true;
                break;
            }
        }
    }

        close(dbfile);

        if (!flag) {
                write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        struct customer custmod1;
        char custid1[10];
        char buff21[300];
        char enter_id1[] = "Enter customer id:";

        write(clientsocket, enter_id1, sizeof(enter_id1));
        ssize_t bytes_id1 = read(clientsocket, custid1, sizeof(custid1));
        if (bytes_id1 == -1) {
                perror("Error in receiving customer id");
                return false;
        }
        custid1[bytes_id1] = '\0';  
        printf("Received customer id: %s\n", custid1);

        int dbfile1 = open("customer.txt", O_RDWR);
        if (dbfile1 == -1) {
                perror("Error in opening the customer file");
                return false;
        }

        char line1[300];
        struct customer temp1;
        bool flag1 = false;

        struct flock lock1;
        memset(&lock1, 0, sizeof(lock1));
        lock1.l_type = F_WRLCK;  
        lock1.l_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos1 = 0;

         char buffer1;
        int line_ind1 = 0;

        while (read(dbfile1, &buffer1, 1) > 0) {
        if (buffer1 != '\n') {
            line1[line_ind1++] = buffer1;
        }
         else {
                line1[line_ind1] = '\0';
                line_ind1 = 0;

                curr_pos1 = lseek(dbfile1, 0, SEEK_CUR);

                int is_active_int1;
                sscanf(line1, "%[^,],%[^,],%[^,],%[^,],%d", temp1.id, temp1.password, temp1.username,temp1.bal, &is_active_int1);
                temp1.active = (is_active_int1 != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp1.id, temp1.password, temp1.username,temp1.bal,temp1.active);

                if (atoi(temp1.id)==atoi( custid1)) {
                        printf("customer is matched.\n");

                lock1.l_start = curr_pos1 - strlen(line1) - 1;  
                lock1.l_len = strlen(line1) + 1; 

                if (fcntl(dbfile1, F_SETLKW, &lock) == -1) {
                         perror("Error in obtaining lock");
                        close(dbfile1);
                        return false;
                }

                //write(clientsocket, "username:", strlen("username:"));
              //ssize_t read1=  read(clientsocket, custmod.username, sizeof(custmod.username));
		//if(read1<=0)
//{
		//close(clientsocket);exit(1);}
		//if(custmod.username[read1 -1]=='\n')
		//	custmod.username[read1 -1]='\0';
		//else
		//	custmod.username[read1]='\0';
                 //write(clientsocket, "custid", strlen("custid"));
               // ssize_t data_read = read(clientsocket,custmod.id,sizeof(custmod.id));

               // if (data_read <= 0)
                //{
                  //      close(clientsocket);
                    //    exit(1);
               // }

               // if(custmod.id[data_read-1]=='\n')
                 //       custmod.id[data_read-1]='\0';
                //else    
                  //      custmod.id[data_read]='\0';
		int new_balance1=atoi(temp1.bal)+amount;
		sprintf(custmod1.bal, "%d", new_balance1);
		printf("%s\n",custmod1.bal);
                snprintf(buff21, sizeof(buff21), "%s,%s,%s,%s,%d\n", temp1.id, temp1.password, temp1.username,custmod1.bal,temp1.active);

                lseek(dbfile, curr_pos1 - strlen(line1) - 1, SEEK_SET);

                if (write(dbfile1, buff21, strlen(buff21)) == -1) {
                        write(clientsocket, "Error in Updating Data", strlen("Error in Updating Data"));
                        close(dbfile1);
                        return false;
                }

                lock1.l_type = F_UNLCK;
                if (fcntl(dbfile1, F_SETLK, &lock1) == -1) {
                        perror("Error in releasing the lock");
                        close(dbfile1);
                        return false;
                }

                flag1 = true;
                break;
            }
        }
    }

        close(dbfile1);

        if (!flag1) {
                write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
                return false;
        }

        return true;


}// end of transaction

bool change_password(int clientsocket)
{printf("inside change password\n");
struct customer custmod;
    char empid[10];
	char password[10];
    char buff2[300];
    char enter_id[] = "enter id";

    write(clientsocket, enter_id, sizeof(enter_id));
    ssize_t bytes_id = read(clientsocket, empid, sizeof(empid));
    if (bytes_id == -1) {
        perror("Error in receiving Employee ID");
        return false;
    }
    printf("Received Employee ID: %s\n", empid);
write(clientsocket, "old password\n", strlen("old password\n"));
     bytes_id = read(clientsocket, password, sizeof(password));
    if (bytes_id == -1) {
        perror("Error in receiving password");
        return false;
    }
    printf("password: %s\n", password);


    write(clientsocket, "new password:", strlen("new password:"));
    read(clientsocket, custmod.password, sizeof(custmod.password));
	printf("pass=%s",custmod.password);
    //write(clientsocket, "ID:", strlen("ID:"));
    //read(clientsocket, custmod.id, sizeof(custmod.id));
	//write(clientsocket,"role",strlen("role"));
	//read(clientsocket,custmod.role,sizeof(custmod.role));

    int dbfile = open("customer.txt", O_RDWR);
    if (dbfile == -1) {
        perror("Error in opening the database file");
        return false;
    }

    char line[300];
    struct customer temp;
    bool flag = false;

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;  
    lock.l_whence = SEEK_SET;  

    off_t record_offset = 0;
    off_t curr_pos = 0;

    char buffer;
    int line_ind = 0;

    while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        } else {
            line[line_ind] = '\0';
            line_ind = 0;

            curr_pos = lseek(dbfile, 0, SEEK_CUR);
		int is_active_int;
                sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.bal, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Balance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.bal,temp.active);


            //sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
            //printf("Read Employee: ID=%s, password=%s, username=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,empid);
            if (atoi(temp.id)==atoi( empid)) {
                printf("Employee ID matched.\n");
                lock.l_start = curr_pos - strlen(line) - 1;
                lock.l_len = strlen(line) + 1;

                if (fcntl(dbfile, F_SETLK, &lock) == -1) {
                    perror("Error in obtaining lock");
                    close(dbfile);
                    return false;
                }
		printf("%s",custmod.password);
                //strcpy(custmod.password, temp.password);  
 if (atoi(temp.id)==atoi( empid)&& atoi(temp.password)==atoi(password)){
                //snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s\n", temp.id, custmod.password, temp.username, temp.role);
	snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, custmod.password, temp.username,temp.bal,temp.active);


                lseek(dbfile, curr_pos - strlen(line) - 1, SEEK_SET);
		printf("%s",custmod.password);
                if (write(dbfile, buff2, strlen(buff2)) == -1) {
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

                flag = true;
                break;
}
            }
        }
    }

    close(dbfile);

    if (!flag) {
        write(clientsocket, "Employee Not Found", strlen("Employee Not Found"));
        return false;
    }

    return true;
}

bool transaction_history(int clientsocket){
	 struct transaction custmod;
        char emplid[10];
        char buff2[300];
        char enter_id[] = "-----View Assigned Loan Application Processes-----\nEnter Your ID:";

        write(clientsocket, enter_id, sizeof(enter_id));
        ssize_t bytes_id = read(clientsocket, emplid, sizeof(emplid));
        if (bytes_id == -1) {
                perror("Error in receiving Customer ID");
                return false;
        }
        emplid[bytes_id] = '\0';  
        printf("Received Customer ID: %s\n", emplid);

        int dbfile = open("loan_db.txt", O_RDWR);
        if (dbfile == -1) {
                perror("Error in opening the database file");
                return false;
        }
	 char buffer;
        int line_ind = 0;
	char transaction_buffer[500];
char line[300];
        struct transaction temp;
        bool flag = false;
	off_t curr_pos = 0;
	

	while (read(dbfile, &buffer, 1) > 0) {
        if (buffer != '\n') {
            line[line_ind++] = buffer;
        }

         else {
                line[line_ind] = '\0';
                line_ind = 0;

                curr_pos = lseek(dbfile, 0, SEEK_CUR);

                sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.sender,temp.rec, temp.amount,temp.flag);
               // printf("Read Customer: ID=%s, Name=%s, Password=%s, Is Employed=%d\n", temp.id, temp.name, temp.pass, temp.is_empl);

                if (atoi(temp.sender)== emplid ||atoi(temp.rec)==emplid) {
                        printf("Employee ID matched.\n");

		char temp1[256];
                snprintf(temp1, sizeof(temp1), "CID: %s,amount:%s,transaction performed:%s\n",temp.sender,temp.amount,temp.flag);
		
		 strcat(transaction_buffer, temp1);
		continue;            
		

                }

         
            }}
	    if(transaction_buffer!=NULL){
	    write(clientsocket,transaction_buffer,strlen(transaction_buffer));
	   return true;

        	}
	    else
		write(clientsocket,"No Loan Applications Assigned\n",strlen("No Loan Applications Assigned\n"));
		return false;
	
//return true;
}

