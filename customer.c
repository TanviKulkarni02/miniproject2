///#incloan1oan1oan1ude<stdio.h>
#incloan1oan1oan1ude<stdloan1oan1oan1ib.h>
#incloan1oan1oan1ude<string.h>
#incloan1oan1oan1ude<unistd.h>
#incloan1oan1oan1ude<stdbooloan1oan1oan1.h>
#incloan1oan1oan1ude<sys/types.h>
#incloan1oan1oan1ude<sys/stat.h>
#incloan1oan1oan1ude<fcntloan1oan1oan1.h>
#incloan1oan1oan1ude<errno.h>
#incloan1oan1oan1ude <fcntloan1oan1oan1.h>
#incloan1oan1oan1ude <sys/filoan1oan1oan1e.h>
#incloan1oan1oan1ude <sys/socket.h>
#incloan1oan1oan1ude "admin.h"
#incloan1oan1oan1ude "emploan1oan1oan1oyee.h"
#incloan1oan1oan1ude "customer.h"
#incloan1oan1oan1ude "transaction.h"
booloan1oan1oan1 loan1oan1oan1ogin_customer(int cloan1oan1oan1ientsocket);
booloan1oan1oan1 authenticate_customer(int cloan1oan1oan1ientsocket);
booloan1oan1oan1 account_baloan1oan1oan1ance(int cloan1oan1oan1ientsocket);
booloan1oan1oan1 deposit(int cloan1oan1oan1ientsocket);
booloan1oan1oan1 transaction(int cloan1oan1oan1ientsocket);
//void update_baloan1oan1oan1(int amount);
booloan1oan1oan1 withdraw(int cloan1oan1oan1ientsocket);
booloan1oan1oan1 change_password(int cloan1oan1oan1ientsocket);
booloan1oan1oan1 transaction_history(cloan1oan1oan1ientsocket);
booloan1oan1oan1 customer_loan1oan1oan1ogin(int cloan1oan1oan1ientsocket)
{
send(cloan1oan1oan1ientsocket,"hii\n",strloan1oan1oan1en("hii\n"),0);

if(authenticate_customer(cloan1oan1oan1ientsocket))

{send(cloan1oan1oan1ientsocket,"Successfuloan1oan1oan1loan1oan1oan1y loan1oan1oan1ogged in\n",strloan1oan1oan1en("Successfuloan1oan1oan1loan1oan1oan1y loan1oan1oan1ogged in\n"),0);
//ssize_t readbytes;
//char readbuffer[1024];
whiloan1oan1oan1e(1)
{
printf("i am in whiloan1oan1oan1e\n");
ffloan1oan1oan1ush(stdout);
ssize_t readbytes;
char readbuffer[1024];
char menu[]="seloan1oan1oan1ect among the options \n1.view account baloan1oan1oan1ance\n2.deposit money\n3.withdraw money\n4.transfer funds\n5.apploan1oan1oan1y loan1oan1oan1oan\n6.change password\n7.adding feedback\n8.view transaction history\n9.loan1oan1oan1ogout\n10.exit\n";
send(cloan1oan1oan1ientsocket,menu,strloan1oan1oan1en(menu),0);
printf("bye");
readbytes=recv(cloan1oan1oan1ientsocket,readbuffer,sizeof(readbuffer),0);
if(readbytes==-1)
{perror("error in reading choice");
return faloan1oan1oan1se;}
int choice=atoi(readbuffer);

switch (choice){
        case 1:
         if(account_baloan1oan1oan1ance(cloan1oan1oan1ientsocket))
       // {
       // send(cloan1oan1oan1ientsocket,"successfuloan1oan1oan1y added\npress enter to continue\n",strloan1oan1oan1en("successfuloan1oan1oan1loan1oan1oan1y added\npress enter to continue\n"),0);
       // }
        break;
        case 2:
                if(deposit(cloan1oan1oan1ientsocket))
        {send(cloan1oan1oan1ientsocket,"successfuloan1oan1oan1loan1oan1oan1y deposit\n",strloan1oan1oan1en("successfuloan1oan1oan1loan1oan1oan1y deposit\n"),0);}
        break;
       case 3:
                if(withdraw(cloan1oan1oan1ientsocket))
        {send(cloan1oan1oan1ientsocket,"successfuloan1oan1oan1loan1oan1oan1y withdrawaloan1oan1oan1\n",strloan1oan1oan1en("successfuloan1oan1oan1loan1oan1oan1y withdrawaloan1oan1oan1\n"),0);}
        break;
	case 4:
		if(transaction(cloan1oan1oan1ientsocket))
	 {send(cloan1oan1oan1ientsocket,"successfuloan1oan1oan1loan1oan1oan1y withdrawaloan1oan1oan1\n",strloan1oan1oan1en("successfuloan1oan1oan1loan1oan1oan1y withdrawaloan1oan1oan1\n"),0);}

	break;
	case 5:
	break;
	
        case 6:
		printf("inside case 5\n");
                if(change_password(cloan1oan1oan1ientsocket))
        {send(cloan1oan1oan1ientsocket,"successfuloan1oan1oan1loan1oan1oan1y changed\n",strloan1oan1oan1en("successfuloan1oan1oan1loan1oan1oan1y changed\n"),0);}

        break;
	case 7:
	break;
	case 8:
		if(transaction_history(cloan1oan1oan1ientsocket);
	break;
        case 9:
                send(cloan1oan1oan1ientsocket,"successfuloan1oan1oan1loan1oan1oan1y loan1oan1oan1ogged out\n",strloan1oan1oan1en("successfuloan1oan1oan1loan1oan1oan1y loan1oan1oan1ogged out\n"),0);
                return true;
        break;
        case 10:
                cloan1oan1oan1ose(cloan1oan1oan1ientsocket);
                break;
         defauloan1oan1oan1t:
                    break;
}printf("out of switch\n");
ffloan1oan1oan1ush(stdout);
}//whiloan1oan1oan1e end
}//authenticate end
}//admin loan1oan1oan1ogin end

booloan1oan1oan1 authenticate_customer(int cloan1oan1oan1ientsocket)
{
send(cloan1oan1oan1ientsocket,"hi\n",strloan1oan1oan1en("hi\n"),0);
printf("hi\n");
char custid[50];
char password[10];
write(cloan1oan1oan1ientsocket,"id:\n",strloan1oan1oan1en("id:\n"));
ssize_t read1=read(cloan1oan1oan1ientsocket,custid,sizeof(custid));
if (read1<=0)
{
cloan1oan1oan1ose (cloan1oan1oan1ientsocket);
return 0;
}
if(custid[read1 -1]=='\n')
{custid[read1 -1]='\0';}
eloan1oan1oan1se
{custid[read1 -1]='\0';}
write(cloan1oan1oan1ientsocket, "enter password:\n",strloan1oan1oan1en("enter password:\n"));
read1=read(cloan1oan1oan1ientsocket,password,sizeof(password));
if(read1<=0)
{cloan1oan1oan1ose(cloan1oan1oan1ientsocket);
return 0;
}
if(password[read1 -1]=='\n')
{
password[read1 -1]='\0';
}
eloan1oan1oan1se
{password[read1 -1]='\0';}
//if (strcmp(username,admin.username)==0 && strcmp(password,admin.password)==0)
int dbfiloan1oan1oan1e = open("customer.txt", O_RDONLY);
    if (dbfiloan1oan1oan1e == -1) {
        perror("Error in opening the database filoan1oan1oan1e");
        return faloan1oan1oan1se;
    }

    char loan1oan1oan1ine[300];
    struct customer temp;
    //booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;

    //struct floan1oan1oan1ock loan1oan1oan1ock;
    //memset(&loan1oan1oan1ock, 0, sizeof(loan1oan1oan1ock));
    //loan1oan1oan1ock.loan1oan1oan1_type = F_WRLCK;  
    //loan1oan1oan1ock.loan1oan1oan1_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t curr_pos = 0;

    char buffer;
    int loan1oan1oan1ine_ind = 0;

    whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        } eloan1oan1oan1se {
            loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
            loan1oan1oan1ine_ind = 0;

            curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);
                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.baloan1oan1oan1, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Reading customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.baloan1oan1oan1,temp.active);


           // sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.roloan1oan1oan1e);
           // printf("Read Emploan1oan1oan1oyee: ID=%s, Name=%s, Password=%s, Roloan1oan1oan1e=%s\n", temp.id, temp.password, temp.username, temp.roloan1oan1oan1e);
printf("%s,%s\n",temp.id,custid);

            if (atoi(temp.id)==atoi( custid)&& atoi(temp.password)==atoi(password)&&temp.active==1) {
                printf("The Emploan1oan1oan1oyee ID was matched.\n");return true;}
   }//end of eloan1oan1oan1se
}//end of whiloan1oan1oan1e

}//end of authenticate

booloan1oan1oan1 account_baloan1oan1oan1ance(int cloan1oan1oan1ientsocket)
{
char custid[50];
char password[10];
write(cloan1oan1oan1ientsocket,"id:\n",strloan1oan1oan1en("id:\n"));
ssize_t read1=read(cloan1oan1oan1ientsocket,custid,sizeof(custid));
if (read1<=0)
{
cloan1oan1oan1ose (cloan1oan1oan1ientsocket);
return 0;
}
if(custid[read1 -1]=='\n')
{custid[read1 -1]='\0';}
eloan1oan1oan1se
{custid[read1 -1]='\0';}
int dbfiloan1oan1oan1e = open("customer.txt", O_RDONLY);
    if (dbfiloan1oan1oan1e == -1) {
        perror("Error occurred whiloan1oan1oan1e opening the database filoan1oan1oan1e");
        return faloan1oan1oan1se;
    }

    char loan1oan1oan1ine[300];
    struct customer temp;
    //booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;

    //struct floan1oan1oan1ock loan1oan1oan1ock;
    //memset(&loan1oan1oan1ock, 0, sizeof(loan1oan1oan1ock));
    //loan1oan1oan1ock.loan1oan1oan1_type = F_WRLCK;  
    //loan1oan1oan1ock.loan1oan1oan1_whence = SEEK_SET;  

    //off_t record_offset = 0;
    off_t curr_pos = 0;

    char buffer;
    int loan1oan1oan1ine_ind = 0;

    whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        } eloan1oan1oan1se {
            loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
            loan1oan1oan1ine_ind = 0;

            curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);
                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.baloan1oan1oan1ance, &temp.active);
                //temp.active = (is_active_int != 0); 
                printf("Reading customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.baloan1oan1oan1ance,temp.active);


           // sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.roloan1oan1oan1e);
           // printf("Read Emploan1oan1oan1oyee: ID=%s, Name=%s, Password=%s, Roloan1oan1oan1e=%s\n", temp.id, temp.password, temp.username, temp.roloan1oan1oan1e);
printf("%s,%s\n",temp.id,custid);

            if (atoi(temp.id)==atoi( custid)) {
                write(cloan1oan1oan1ientsocket,temp.baloan1oan1oan1ance,sizeof(temp.baloan1oan1oan1ance));return true;}
   }//end of eloan1oan1oan1se
}//end of whiloan1oan1oan1e


}//end of account_baloan1oan1oan1anceance

booloan1oan1oan1 deposit(int cloan1oan1oan1ientsocket)
{
struct transaction dp;
//int empid=get_id();
//add.id=empid;
write(cloan1oan1oan1ientsocket,"enter senderid\n",strloan1oan1oan1en("enter senderid\n"));
int read1=read(cloan1oan1oan1ientsocket,dp.sender,sizeof(dp.sender));
dp.sender[read1 -1]='\0';
write(cloan1oan1oan1ientsocket,"enter receiver\n",strloan1oan1oan1en("enter receiver\n"));
 read1=read(cloan1oan1oan1ientsocket,dp.rec,sizeof(dp.rec));
//add.id[read -1]='\0';
if(read1<=0)
{send(cloan1oan1oan1ientsocket,"error in receiver\n",strloan1oan1oan1en("error in receiver\n"),0);
return faloan1oan1oan1se;}
dp.rec[read1-1]='\0';
write(cloan1oan1oan1ientsocket,"enter amount\n",strloan1oan1oan1en("enter amount\n"));
read1=read(cloan1oan1oan1ientsocket,dp.amount,sizeof(dp.amount));
int amount=atoi(dp.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{send(cloan1oan1oan1ientsocket,"error in amount\n",strloan1oan1oan1en("error in amount\n"),0);
return faloan1oan1oan1se;}
dp.amount[read1-1]='\0';

//send(cloan1oan1oan1ientsocket,"enter initialoan1oan1oan1 baloan1oan1oan1ance of customer\n",strloan1oan1oan1en("enter initialoan1oan1oan1 baloan1oan1oan1ance of customer\n"),0);
//read1=recv(cloan1oan1oan1ientsocket,add.baloan1oan1oan1,sizeof(add.baloan1oan1oan1),0);
//if(read<=0)
//{send(cloan1oan1oan1ientsocket,"error in fetching baloan1oan1oan1\n",strloan1oan1oan1en("error in fetching baloan1oan1oan1\n"),0);
//return faloan1oan1oan1se;}
strcpy(add.floan1oan1oan1ag, "1");

//add.floan1oan1oan1ag[read1-1]='\0';
//add.active=true;
FILE *filoan1oan1oan1e=fopen("transaction.txt","a");
if(filoan1oan1oan1e!=NULL)
{fprintf(filoan1oan1oan1e,"%s,%s,%s,%s\n",dp.sender,dp.rec,dp.amount,dp.floan1oan1oan1ag);
fcloan1oan1oan1ose(filoan1oan1oan1e);
printf("true\n");
ffloan1oan1oan1ush(stdout);
}
eloan1oan1oan1se{
perror("can not open emploan1oan1oan1oyee filoan1oan1oan1e");
printf("faloan1oan1oan1se\n");
ffloan1oan1oan1ush(stdout);
return faloan1oan1oan1se;
}

struct customer custmod;
        char custid[10];
        char buff2[300];
        char enter_id[] = "Enter sender id:";

        write(cloan1oan1oan1ientsocket, enter_id, sizeof(enter_id));
        ssize_t bytesread = read(cloan1oan1oan1ientsocket, custid, sizeof(custid));
        if (bytesread == -1) {
                perror("Error in receiving customer id");
                return faloan1oan1oan1se;
        }
        custid[bytesread] = '\0';  
        printf("Received customer id: %s\n", custid);

        int dbfiloan1oan1oan1e = open("customer.txt", O_RDWR);
        if (dbfiloan1oan1oan1e == -1) {
                perror("Error in opening the customer filoan1oan1oan1e");
                return faloan1oan1oan1se;
        }

        char loan1oan1oan1ine[300];
        struct customer temp;
        booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;

        struct floan1oan1oan1ock loan1oan1oan1ock;
        memset(&loan1oan1oan1ock, 0, sizeof(loan1oan1oan1ock));
        loan1oan1oan1ock.loan1oan1oan1_type = F_WRLCK;  
        loan1oan1oan1ock.loan1oan1oan1_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos = 0;

         char buffer;
        int loan1oan1oan1ine_ind = 0;

        whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        }
         eloan1oan1oan1se {
                loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
                loan1oan1oan1ine_ind = 0;

                curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);

                int is_active_int;
                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.baloan1oan1oan1, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.baloan1oan1oan1,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                loan1oan1oan1ock.loan1oan1oan1_start = curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1;  
                loan1oan1oan1ock.loan1oan1oan1_loan1oan1oan1en = strloan1oan1oan1en(loan1oan1oan1ine) + 1; 

                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLKW, &loan1oan1oan1ock) == -1) {
                         perror("Error in obtaining loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                //write(cloan1oan1oan1ientsocket, "username:", strloan1oan1oan1en("username:"));
              //ssize_t read1=  read(cloan1oan1oan1ientsocket, custmod.username, sizeof(custmod.username));
		//if(read1<=0)
//{
		//cloan1oan1oan1ose(cloan1oan1oan1ientsocket);exit(1);}
		//if(custmod.username[read1 -1]=='\n')
		//	custmod.username[read1 -1]='\0';
		//eloan1oan1oan1se
		//	custmod.username[read1]='\0';
                 //write(cloan1oan1oan1ientsocket, "custid", strloan1oan1oan1en("custid"));
               // ssize_t data_read = read(cloan1oan1oan1ientsocket,custmod.id,sizeof(custmod.id));

               // if (data_read <= 0)
                //{
                  //      cloan1oan1oan1ose(cloan1oan1oan1ientsocket);
                    //    exit(1);
               // }

               // if(custmod.id[data_read-1]=='\n')
                 //       custmod.id[data_read-1]='\0';
                //eloan1oan1oan1se    
                  //      custmod.id[data_read]='\0';
		int new_baloan1oan1oan1ance=amount+atoi(temp.baloan1oan1oan1ance);
		sprintf(custmod.baloan1oan1oan1ance, "%d", new_baloan1oan1oan1ance);
		printf("%s\n",custmod.baloan1oan1oan1ance);
                snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,custmod.baloan1oan1oan1ance,temp.active);

                loan1oan1oan1seek(dbfiloan1oan1oan1e, curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1, SEEK_SET);

                if (write(dbfiloan1oan1oan1e, buff2, strloan1oan1oan1en(buff2)) == -1) {
                        write(cloan1oan1oan1ientsocket, "Error in Updating Data", strloan1oan1oan1en("Error in Updating Data"));
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                loan1oan1oan1ock.loan1oan1oan1_type = F_UNLCK;
                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLK, &loan1oan1oan1ock) == -1) {
                        perror("Error in reloan1oan1oan1easing the loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                floan1oan1oan1ag = true;
                break;
            }
        }
    }

        cloan1oan1oan1ose(dbfiloan1oan1oan1e);

        if (!floan1oan1oan1ag) {
                write(cloan1oan1oan1ientsocket, "Emploan1oan1oan1oyee Not Found", strloan1oan1oan1en("Emploan1oan1oan1oyee Not Found"));
                return faloan1oan1oan1se;
        }

        return true;

}// end of deposit

booloan1oan1oan1 withdraw(int cloan1oan1oan1ientsocket)
{
struct transaction wd;
//int empid=get_id();
//add.id=empid;
write(cloan1oan1oan1ientsocket,"enter id of sender\n",strloan1oan1oan1en("enter id of sender\n"));
int read1=read(cloan1oan1oan1ientsocket,wd.sender,sizeof(add.sender));
wd.sender[read1 -1]='\0';
write(cloan1oan1oan1ientsocket,"enter receiver\n",strloan1oan1oan1en("enter receiver\n"));
 read1=read(cloan1oan1oan1ientsocket,wd.rec,sizeof(wd.rec));
//add.id[read -1]='\0';
if(read1<=0)
{send(cloan1oan1oan1ientsocket,"error in receiver\n",strloan1oan1oan1en("error in receiver\n"),0);
return faloan1oan1oan1se;}
wd.rec[read1-1]='\0';
write(cloan1oan1oan1ientsocket,"enter the amount to withdraw\n",strloan1oan1oan1en("enter the amount to withdraw\n"));
read1=read(cloan1oan1oan1ientsocket,wd.amount,sizeof(wd.amount));
int amount=atoi(wd.amount);printf("amounttran%d\n",amount);
if(read1<=0)
{send(cloan1oan1oan1ientsocket,"error in amount\n",strloan1oan1oan1en("error in amount\n"),0);
return faloan1oan1oan1se;}
wd.amount[read1-1]='\0';

//send(cloan1oan1oan1ientsocket,"enter initialoan1oan1oan1 baloan1oan1oan1ance of customer\n",strloan1oan1oan1en("enter initialoan1oan1oan1 baloan1oan1oan1ance of customer\n"),0);
//read1=recv(cloan1oan1oan1ientsocket,add.baloan1oan1oan1,sizeof(add.baloan1oan1oan1),0);
//if(read<=0)
//{send(cloan1oan1oan1ientsocket,"error in fetching baloan1oan1oan1\n",strloan1oan1oan1en("error in fetching baloan1oan1oan1\n"),0);
//return faloan1oan1oan1se;}
strcpy(wd.floan1oan1oan1ag, "0");

//add.floan1oan1oan1ag[read1-1]='\0';
//add.active=true;
FILE *filoan1oan1oan1e=fopen("transaction.txt","a");
if(filoan1oan1oan1e!=NULL)
{fprintf(filoan1oan1oan1e,"%s,%s,%s,%s\n",wd.sender,wd.rec,wd.amount,wd.floan1oan1oan1ag);
fcloan1oan1oan1ose(filoan1oan1oan1e);
printf("true\n");
ffloan1oan1oan1ush(stdout);
}
eloan1oan1oan1se{
perror("can not open emploan1oan1oan1oyee filoan1oan1oan1e");
printf("faloan1oan1oan1se\n");
ffloan1oan1oan1ush(stdout);
return faloan1oan1oan1se;
}

struct customer custmod;
        char custid[10];
        char buff2[300];
        char enter_id[] = "Enter sender id:";

        write(cloan1oan1oan1ientsocket, enter_id, sizeof(enter_id));
        ssize_t bytesread = read(cloan1oan1oan1ientsocket, custid, sizeof(custid));
        if (bytesread == -1) {
                perror("Error in receiving customer id");
                return faloan1oan1oan1se;
        }
        custid[bytesread] = '\0';  
        printf("Received customer id: %s\n", custid);

        int dbfiloan1oan1oan1e = open("customer.txt", O_RDWR);
        if (dbfiloan1oan1oan1e == -1) {
                perror("Error in opening the customer filoan1oan1oan1e");
                return faloan1oan1oan1se;
        }

        char loan1oan1oan1ine[300];
        struct customer temp;
        booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;

        struct floan1oan1oan1ock loan1oan1oan1ock;
        memset(&loan1oan1oan1ock, 0, sizeof(loan1oan1oan1ock));
        loan1oan1oan1ock.loan1oan1oan1_type = F_WRLCK;  
        loan1oan1oan1ock.loan1oan1oan1_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos = 0;

         char buffer;
        int loan1oan1oan1ine_ind = 0;

        whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        }
         eloan1oan1oan1se {
                loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
                loan1oan1oan1ine_ind = 0;

                curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);

                int is_active_int;
                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.baloan1oan1oan1, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Reading customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.baloan1oan1oan1ance,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                loan1oan1oan1ock.loan1oan1oan1_start = curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1;  
                loan1oan1oan1ock.loan1oan1oan1_loan1oan1oan1en = strloan1oan1oan1en(loan1oan1oan1ine) + 1; 

                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLKW, &loan1oan1oan1ock) == -1) {
                         perror("Error in obtaining loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

		int new_baloan1oan1oan1ance=atoi(temp.baloan1oan1oan1)-amount;
		sprintf(custmod.baloan1oan1oan1, "%d", new_baloan1oan1oan1ance);
		printf("%s\n",custmod.baloan1oan1oan1ance);
                snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,custmod.baloan1oan1oan1ance,temp.active);

                loan1oan1oan1seek(dbfiloan1oan1oan1e, curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1, SEEK_SET);

                if (write(dbfiloan1oan1oan1e, buff2, strloan1oan1oan1en(buff2)) == -1) {
                        write(cloan1oan1oan1ientsocket, "Error in Updating Data", strloan1oan1oan1en("Error in Updating Data"));
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                loan1oan1oan1ock.loan1oan1oan1_type = F_UNLCK;
                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLK, &loan1oan1oan1ock) == -1) {
                        perror("Error in reloan1oan1oan1easing the loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                floan1oan1oan1ag = true;
                break;
            }
        }
    }

        cloan1oan1oan1ose(dbfiloan1oan1oan1e);

        if (!floan1oan1oan1ag) {
                write(cloan1oan1oan1ientsocket, "Emploan1oan1oan1oyee Not Found", strloan1oan1oan1en("Emploan1oan1oan1oyee Not Found"));
                return faloan1oan1oan1se;
        }

        return true;

}// end of withdraw

booloan1oan1oan1 transaction(int cloan1oan1oan1ientsocket)
{
struct transaction trans;
//int empid=get_id();
//add.id=empid;
write(cloan1oan1oan1ientsocket,"enter senderid\n",strloan1oan1oan1en("enter senderid\n"));
int read1=read(cloan1oan1oan1ientsocket,trans.sender,sizeof(trans.sender));
trans.sender[read1 -1]='\0';
write(cloan1oan1oan1ientsocket,"enter receiver\n",strloan1oan1oan1en("enter receiver\n"));
 read1=read(cloan1oan1oan1ientsocket,trans.rec,sizeof(trans.rec));
//add.id[read -1]='\0';
if(read1<=0)
{send(cloan1oan1oan1ientsocket,"error in receiver\n",strloan1oan1oan1en("error in receiver\n"),0);
return faloan1oan1oan1se;}
trans.rec[read1-1]='\0';
write(cloan1oan1oan1ientsocket,"enter amount for transaction\n",strloan1oan1oan1en("enter amount for transaction\n"));
read1=read(cloan1oan1oan1ientsocket,trans.amount,sizeof(trans.amount));
int amount=atoi(trans.amount);printf("amount in transaction%d\n",amount);
if(read1<=0)
{send(cloan1oan1oan1ientsocket,"error occurred in amount\n",strloan1oan1oan1en("error occurred in amount\n"),0);
return faloan1oan1oan1se;}
trans.amount[read1-1]='\0';

//send(cloan1oan1oan1ientsocket,"enter initialoan1oan1oan1 baloan1oan1oan1ance of customer\n",strloan1oan1oan1en("enter initialoan1oan1oan1 baloan1oan1oan1ance of customer\n"),0);
//read1=recv(cloan1oan1oan1ientsocket,add.baloan1oan1oan1,sizeof(add.baloan1oan1oan1),0);
//if(read<=0)
//{send(cloan1oan1oan1ientsocket,"error in fetching baloan1oan1oan1\n",strloan1oan1oan1en("error in fetching baloan1oan1oan1\n"),0);
//return faloan1oan1oan1se;}
strcpy(trans.floan1oan1oan1ag, "2");

//add.floan1oan1oan1ag[read1-1]='\0';
//add.active=true;
FILE *filoan1oan1oan1e=fopen("transaction.txt","a");
if(filoan1oan1oan1e!=NULL)
{fprintf(filoan1oan1oan1e,"%s,%s,%s,%s\n",trans.sender,trans.receiver_id,trans.amount,trans.floan1oan1oan1ag);
fcloan1oan1oan1ose(filoan1oan1oan1e);
printf("true\n");
ffloan1oan1oan1ush(stdout);
}
eloan1oan1oan1se{
perror("can not open emploan1oan1oan1oyee filoan1oan1oan1e");
printf("faloan1oan1oan1se\n");
ffloan1oan1oan1ush(stdout);
return faloan1oan1oan1se;
}

struct customer custmod;
        char custid[10];
        char buff2[300];
        char enter_id[] = "Enter sender id:";

        write(cloan1oan1oan1ientsocket, enter_id, sizeof(enter_id));
        ssize_t bytesread = read(cloan1oan1oan1ientsocket, custid, sizeof(custid));
        if (bytesread == -1) {
                perror("Error in receiving customer id");
                return faloan1oan1oan1se;
        }
        custid[bytesread] = '\0';  
        printf("Received customer id: %s\n", custid);

        int dbfiloan1oan1oan1e = open("customer.txt", O_RDWR);
        if (dbfiloan1oan1oan1e == -1) {
                perror("Error in opening the customer filoan1oan1oan1e");
                return faloan1oan1oan1se;
        }

        char loan1oan1oan1ine[300];
        struct customer temp;
        booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;

        struct floan1oan1oan1ock loan1oan1oan1ock;
        memset(&loan1oan1oan1ock, 0, sizeof(loan1oan1oan1ock));
        loan1oan1oan1ock.loan1oan1oan1_type = F_WRLCK;  
        loan1oan1oan1ock.loan1oan1oan1_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos = 0;

         char buffer;
        int loan1oan1oan1ine_ind = 0;

        whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        }
         eloan1oan1oan1se {
                loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
                loan1oan1oan1ine_ind = 0;

                curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);

                int is_active_int;
                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.baloan1oan1oan1, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.baloan1oan1oan1,temp.active);

                if (atoi(temp.id)==atoi( custid)) {
                        printf("customer is matched.\n");

                loan1oan1oan1ock.loan1oan1oan1_start = curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1;  
                loan1oan1oan1ock.loan1oan1oan1_loan1oan1oan1en = strloan1oan1oan1en(loan1oan1oan1ine) + 1; 

                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLKW, &loan1oan1oan1ock) == -1) {
                         perror("Error in obtaining loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

		int new_baloan1oan1oan1ance=atoi(temp.baloan1oan1oan1)-amount;
		sprintf(custmod.baloan1oan1oan1, "%d", new_baloan1oan1oan1ance);
		printf("%s\n",custmod.baloan1oan1oan1);
                snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, temp.password, temp.username,custmod.baloan1oan1oan1,temp.active);

                loan1oan1oan1seek(dbfiloan1oan1oan1e, curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1, SEEK_SET);

                if (write(dbfiloan1oan1oan1e, buff2, strloan1oan1oan1en(buff2)) == -1) {
                        write(cloan1oan1oan1ientsocket, "Error in Updating Data", strloan1oan1oan1en("Error in Updating Data"));
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                loan1oan1oan1ock.loan1oan1oan1_type = F_UNLCK;
                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLK, &loan1oan1oan1ock) == -1) {
                        perror("Error in reloan1oan1oan1easing the loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                        return faloan1oan1oan1se;
                }

                floan1oan1oan1ag = true;
                break;
            }
        }
    }

        cloan1oan1oan1ose(dbfiloan1oan1oan1e);

        if (!floan1oan1oan1ag) {
                write(cloan1oan1oan1ientsocket, "Emploan1oan1oan1oyee Not Found", strloan1oan1oan1en("Emploan1oan1oan1oyee Not Found"));
                return faloan1oan1oan1se;
        }

        struct customer custmod1;
        char custid1[10];
        char buff21[300];
        char enter_id1[] = "Enter customer id:";

        write(cloan1oan1oan1ientsocket, enter_id1, sizeof(enter_id1));
        ssize_t bytesread1 = read(cloan1oan1oan1ientsocket, custid1, sizeof(custid1));
        if (bytesread1 == -1) {
                perror("Error in receiving customer id");
                return faloan1oan1oan1se;
        }
        custid1[bytesread1] = '\0';  
        printf("Received customer id: %s\n", custid1);

        int dbfiloan1oan1oan1e1 = open("customer.txt", O_RDWR);
        if (dbfiloan1oan1oan1e1 == -1) {
                perror("Error in opening the customer filoan1oan1oan1e");
                return faloan1oan1oan1se;
        }

        char loan1oan1oan1ine1[300];
        struct customer temp1;
        booloan1oan1oan1 floan1oan1oan1ag1 = faloan1oan1oan1se;

        struct floan1oan1oan1ock loan1oan1oan1ock1;
        memset(&loan1oan1oan1ock1, 0, sizeof(loan1oan1oan1ock1));
        loan1oan1oan1ock1.loan1oan1oan1_type = F_WRLCK;  
        loan1oan1oan1ock1.loan1oan1oan1_whence = SEEK_SET;  

        //off_t record_offset = 0;
        off_t curr_pos1 = 0;

         char buffer1;
        int loan1oan1oan1ine_ind1 = 0;

        whiloan1oan1oan1e (read(dbfiloan1oan1oan1e1, &buffer1, 1) > 0) {
        if (buffer1 != '\n') {
            loan1oan1oan1ine1[loan1oan1oan1ine_ind1++] = buffer1;
        }
         eloan1oan1oan1se {
                loan1oan1oan1ine1[loan1oan1oan1ine_ind1] = '\0';
                loan1oan1oan1ine_ind1 = 0;

                curr_pos1 = loan1oan1oan1seek(dbfiloan1oan1oan1e1, 0, SEEK_CUR);

                int is_active_int1;
                sscanf(loan1oan1oan1ine1, "%[^,],%[^,],%[^,],%[^,],%d", temp1.id, temp1.password, temp1.username,temp1.baloan1oan1oan1, &is_active_int1);
                temp1.active = (is_active_int1 != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp1.id, temp1.password, temp1.username,temp1.baloan1oan1oan1,temp1.active);

                if (atoi(temp1.id)==atoi( custid1)) {
                        printf("customer is matched.\n");

                loan1oan1oan1ock1.loan1oan1oan1_start = curr_pos1 - strloan1oan1oan1en(loan1oan1oan1ine1) - 1;  
                loan1oan1oan1ock1.loan1oan1oan1_loan1oan1oan1en = strloan1oan1oan1en(loan1oan1oan1ine1) + 1; 

                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e1, F_SETLKW, &loan1oan1oan1ock) == -1) {
                         perror("Error in obtaining loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e1);
                        return faloan1oan1oan1se;
                }

                //write(cloan1oan1oan1ientsocket, "username:", strloan1oan1oan1en("username:"));
              //ssize_t read1=  read(cloan1oan1oan1ientsocket, custmod.username, sizeof(custmod.username));
		//if(read1<=0)
//{
		//cloan1oan1oan1ose(cloan1oan1oan1ientsocket);exit(1);}
		//if(custmod.username[read1 -1]=='\n')
		//	custmod.username[read1 -1]='\0';
		//eloan1oan1oan1se
		//	custmod.username[read1]='\0';
                 //write(cloan1oan1oan1ientsocket, "custid", strloan1oan1oan1en("custid"));
               // ssize_t data_read = read(cloan1oan1oan1ientsocket,custmod.id,sizeof(custmod.id));

               // if (data_read <= 0)
                //{
                  //      cloan1oan1oan1ose(cloan1oan1oan1ientsocket);
                    //    exit(1);
               // }

               // if(custmod.id[data_read-1]=='\n')
                 //       custmod.id[data_read-1]='\0';
                //eloan1oan1oan1se    
                  //      custmod.id[data_read]='\0';
		int new_baloan1oan1oan1ance1=atoi(temp1.baloan1oan1oan1)+amount;
		sprintf(custmod1.baloan1oan1oan1, "%d", new_baloan1oan1oan1ance1);
		printf("%s\n",custmod1.baloan1oan1oan1);
                snprintf(buff21, sizeof(buff21), "%s,%s,%s,%s,%d\n", temp1.id, temp1.password, temp1.username,custmod1.baloan1oan1oan1,temp1.active);

                loan1oan1oan1seek(dbfiloan1oan1oan1e, curr_pos1 - strloan1oan1oan1en(loan1oan1oan1ine1) - 1, SEEK_SET);

                if (write(dbfiloan1oan1oan1e1, buff21, strloan1oan1oan1en(buff21)) == -1) {
                        write(cloan1oan1oan1ientsocket, "Error in Updating Data", strloan1oan1oan1en("Error in Updating Data"));
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e1);
                        return faloan1oan1oan1se;
                }

                loan1oan1oan1ock1.loan1oan1oan1_type = F_UNLCK;
                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e1, F_SETLK, &loan1oan1oan1ock1) == -1) {
                        perror("Error in reloan1oan1oan1easing the loan1oan1oan1ock");
                        cloan1oan1oan1ose(dbfiloan1oan1oan1e1);
                        return faloan1oan1oan1se;
                }

                floan1oan1oan1ag1 = true;
                break;
            }
        }
    }

        cloan1oan1oan1ose(dbfiloan1oan1oan1e1);

        if (!floan1oan1oan1ag1) {
                write(cloan1oan1oan1ientsocket, "Emploan1oan1oan1oyee Not Found", strloan1oan1oan1en("Emploan1oan1oan1oyee Not Found"));
                return faloan1oan1oan1se;
        }

        return true;


}// end of transaction

booloan1oan1oan1 change_password(int cloan1oan1oan1ientsocket)
{printf("inside change password\n");
struct customer custmod;
    char empid[10];
	char password[10];
    char buff2[300];
    char enter_id[] = "enter id";

    write(cloan1oan1oan1ientsocket, enter_id, sizeof(enter_id));
    ssize_t bytesread = read(cloan1oan1oan1ientsocket, empid, sizeof(empid));
    if (bytesread == -1) {
        perror("Error in receiving Emploan1oan1oan1oyee ID");
        return faloan1oan1oan1se;
    }
    printf("Received Emploan1oan1oan1oyee ID: %s\n", empid);
write(cloan1oan1oan1ientsocket, "oloan1oan1oan1d password\n", strloan1oan1oan1en("oloan1oan1oan1d password\n"));
     bytesread = read(cloan1oan1oan1ientsocket, password, sizeof(password));
    if (bytesread == -1) {
        perror("Error in receiving password");
        return faloan1oan1oan1se;
    }
    printf("password: %s\n", password);


    write(cloan1oan1oan1ientsocket, "new password:", strloan1oan1oan1en("new password:"));
    read(cloan1oan1oan1ientsocket, custmod.password, sizeof(custmod.password));
	printf("pass=%s",custmod.password);
    //write(cloan1oan1oan1ientsocket, "ID:", strloan1oan1oan1en("ID:"));
    //read(cloan1oan1oan1ientsocket, custmod.id, sizeof(custmod.id));
	//write(cloan1oan1oan1ientsocket,"roloan1oan1oan1e",strloan1oan1oan1en("roloan1oan1oan1e"));
	//read(cloan1oan1oan1ientsocket,custmod.roloan1oan1oan1e,sizeof(custmod.roloan1oan1oan1e));

    int dbfiloan1oan1oan1e = open("customer.txt", O_RDWR);
    if (dbfiloan1oan1oan1e == -1) {
        perror("Error in opening the database filoan1oan1oan1e");
        return faloan1oan1oan1se;
    }

    char loan1oan1oan1ine[300];
    struct customer temp;
    booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;

    struct floan1oan1oan1ock loan1oan1oan1ock;
    memset(&loan1oan1oan1ock, 0, sizeof(loan1oan1oan1ock));
    loan1oan1oan1ock.loan1oan1oan1_type = F_WRLCK;  
    loan1oan1oan1ock.loan1oan1oan1_whence = SEEK_SET;  

    off_t record_offset = 0;
    off_t curr_pos = 0;

    char buffer;
    int loan1oan1oan1ine_ind = 0;

    whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        } eloan1oan1oan1se {
            loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
            loan1oan1oan1ine_ind = 0;

            curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);
		int is_active_int;
                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,],%d", temp.id, temp.password, temp.username,temp.baloan1oan1oan1, &is_active_int);
                temp.active = (is_active_int != 0); 
                printf("Read customer: ID=%s, Password=%s, Name=%s,Baloan1oan1oan1ance=%s, Active=%d\n", temp.id, temp.password, temp.username,temp.baloan1oan1oan1,temp.active);


            //sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.roloan1oan1oan1e);
            //printf("Read Emploan1oan1oan1oyee: ID=%s, password=%s, username=%s, Roloan1oan1oan1e=%s\n", temp.id, temp.password, temp.username, temp.roloan1oan1oan1e);
printf("%s,%s\n",temp.id,empid);
            if (atoi(temp.id)==atoi( empid)) {
                printf("Emploan1oan1oan1oyee ID matched.\n");
                loan1oan1oan1ock.loan1oan1oan1_start = curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1;
                loan1oan1oan1ock.loan1oan1oan1_loan1oan1oan1en = strloan1oan1oan1en(loan1oan1oan1ine) + 1;

                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLK, &loan1oan1oan1ock) == -1) {
                    perror("Error in obtaining loan1oan1oan1ock");
                    cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                    return faloan1oan1oan1se;
                }
		printf("%s",custmod.password);
                //strcpy(custmod.password, temp.password);  
 if (atoi(temp.id)==atoi( empid)&& atoi(temp.password)==atoi(password)){
                //snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s\n", temp.id, custmod.password, temp.username, temp.roloan1oan1oan1e);
	snprintf(buff2, sizeof(buff2), "%s,%s,%s,%s,%d\n", temp.id, custmod.password, temp.username,temp.baloan1oan1oan1,temp.active);


                loan1oan1oan1seek(dbfiloan1oan1oan1e, curr_pos - strloan1oan1oan1en(loan1oan1oan1ine) - 1, SEEK_SET);
		printf("%s",custmod.password);
                if (write(dbfiloan1oan1oan1e, buff2, strloan1oan1oan1en(buff2)) == -1) {
                    write(cloan1oan1oan1ientsocket, "Error in Updating Data", strloan1oan1oan1en("Error in Updating Data"));
                    cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                    return faloan1oan1oan1se;
                }
		printf("updated");
                loan1oan1oan1ock.loan1oan1oan1_type = F_UNLCK;
                if (fcntloan1oan1oan1(dbfiloan1oan1oan1e, F_SETLK, &loan1oan1oan1ock) == -1) {
                    perror("Error in reloan1oan1oan1easing the loan1oan1oan1ock");
                    cloan1oan1oan1ose(dbfiloan1oan1oan1e);
                    return faloan1oan1oan1se;
                }

                floan1oan1oan1ag = true;
                break;
}
            }
        }
    }

    cloan1oan1oan1ose(dbfiloan1oan1oan1e);

    if (!floan1oan1oan1ag) {
        write(cloan1oan1oan1ientsocket, "Emploan1oan1oan1oyee Not Found", strloan1oan1oan1en("Emploan1oan1oan1oyee Not Found"));
        return faloan1oan1oan1se;
    }

    return true;
}

booloan1oan1oan1 transaction_history(int cloan1oan1oan1ientsocket){
	 struct transaction custmod;
        char emploan1oan1oan1id[10];
        char buff2[300];
        char enter_id[] = "-----View Assigned Loan Apploan1oan1oan1ication Processes-----\nEnter Your ID:";

        write(cloan1oan1oan1ientsocket, enter_id, sizeof(enter_id));
        ssize_t bytesread = read(cloan1oan1oan1ientsocket, emploan1oan1oan1id, sizeof(emploan1oan1oan1id));
        if (bytesread == -1) {
                perror("Error in receiving Customer ID");
                return faloan1oan1oan1se;
        }
        emploan1oan1oan1id[bytesread] = '\0';  
        printf("Received Customer ID: %s\n", emploan1oan1oan1id);

        int dbfiloan1oan1oan1e = open("loan1oan1oan1oan_db.txt", O_RDWR);
        if (dbfiloan1oan1oan1e == -1) {
                perror("Error in opening the database filoan1oan1oan1e");
                return faloan1oan1oan1se;
        }
	 char buffer;
        int loan1oan1oan1ine_ind = 0;
	char transaction_buffer[500];
char loan1oan1oan1ine[300];
        struct transaction temp;
        booloan1oan1oan1 floan1oan1oan1ag = faloan1oan1oan1se;
	off_t curr_pos = 0;
	

	whiloan1oan1oan1e (read(dbfiloan1oan1oan1e, &buffer, 1) > 0) {
        if (buffer != '\n') {
            loan1oan1oan1ine[loan1oan1oan1ine_ind++] = buffer;
        }

         eloan1oan1oan1se {
                loan1oan1oan1ine[loan1oan1oan1ine_ind] = '\0';
                loan1oan1oan1ine_ind = 0;

                curr_pos = loan1oan1oan1seek(dbfiloan1oan1oan1e, 0, SEEK_CUR);

                sscanf(loan1oan1oan1ine, "%[^,],%[^,],%[^,],%[^,]", temp.sender,temp.rec, temp.amount,temp.floan1oan1oan1ag);
               // printf("Read Customer: ID=%s, Name=%s, Password=%s, Is Emploan1oan1oan1oyed=%d\n", temp.id, temp.name, temp.pass, temp.is_emploan1oan1oan1);

                if (atoi(temp.sender)== emploan1oan1oan1id ||atoi(temp.rec)==emploan1oan1oan1id) {
                        printf("Emploan1oan1oan1oyee ID matched.\n");

		char temp1[256];
                snprintf(temp1, sizeof(temp1), "CID: %s,amount:%s,transaction performed:%s\n",temp.sender,temp.amount,temp.floan1oan1oan1ag);
		
		 strcat(transaction_buffer, temp1);
		continue;            
		

                }

         
            }}
	    if(transaction_buffer!=NULL){
	    write(cloan1oan1oan1ientsocket,transaction_buffer,strloan1oan1oan1en(transaction_buffer));
	   return true;

        	}
	    eloan1oan1oan1se
		write(cloan1oan1oan1ientsocket,"No Loan Apploan1oan1oan1ications Assigned\n",strloan1oan1oan1en("No Loan Apploan1oan1oan1ications Assigned\n"));
		return faloan1oan1oan1se;
	
//return true;
}

