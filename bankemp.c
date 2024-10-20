#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <string.h>
// #include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <errno.h>
#include <fcntl.h>
#include "administrator.h"
#include "common.h"

bool employee_login(int clientSocket);
bool authenticate_bankemp(int clientSocket);
bool add_newcustomer(int cd);
bool modify_customerdetails(int clientSocket);

{
send(clientSocket,"hello\n",strlen("hello\n"),0);

/*struct usercredentials
{
    char username[100];
    char password[100];
};*/

//struct usercredentials admincredentials = {"Tanvi", "666"};

//bool admin_operation_handler(int clientsocket)
//{*/
    if (authenticate_bankemp(clientsocket))
    {
send(clientSocket,"login successful\n",strlen("login successful\n"),0);

// ssize_t readbytes;
        // ssize_t writebytes ;
  //      char readbuffer[1000];

 while (1)
        {
printf("i am in while\n");
fflush(stdout);
ssize_t readbytes;
char readbuffer[1000];

            char menu[] = "Welcome!! Do you want to:- \n1.Add new customer\n - 2.Modify customer details\n - 3.Process Loan Applications\n - 4.Approve/Reject Loans\n - 5.View Assigned Loan Applications";
            send(clientsocket, menu, strlen(menu), 0);
printf("bye");            
readbytes = recv(clientsocket, readbuffer, sizeof(readbuffer), 0);
            if (readbytes == -1)
            {
                perror("Error while reading client's choice");
                return false;
            }
            int choice = atoi(readbuffer);

switch (choice)
            {


            case 1:
                if (add_newcustomer(clientsocket))
                {
                    send(clientsocket, "Added a new customer successfully\n", strlen("Added anew customer successfully\n"), 0);
                }
                break;

            case 2:
                if (modify_customerdetails(clientsocket))
                {
                    send(clientsocket, "Modified the details of customer successfully\n", strlen("Modified the details of customer successfull>
                }
                else
                {
                    send(clientsocket, "Please try again\n", strlen("Please try again\n"), 0);
                }
                break;

case 7:
                int fd=open("./customer_db.txt", O_RDONLY,0777);
                int tempBytes;
                struct Employee tempEmp;
                while(tempBytes=read(fd, &tempEmp, sizeof(struct Customer))>0)
                {
                    printf("Id is-: %s\n", tempEmp.customerID);
                    printf("Name is-: %s\n", tempEmp.name);
                    printf("Password is-: %s\n", tempEmp.password);
                    printf("Role is-: %s\n", tempEmp.role);

                }
                close(fd);
                break;
}printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end




bool authenticate_bankemp(int clientsocket)
{
send(clientSocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");

    char bankempID[100];
    char password[100];

    const char *userprompt = "Enter bankempID: \n";
    send(clientsocket, userprompt, strlen(userprompt), 0);

    ssize_t bytesread = recv(clientsocket, bankempID, sizeof(bankempID), 0);
    if (bytesread <= 0)
    {
        close(clientsocket);
        return false;
    }
if(bankempID[read1 -1]=='\n')
{
bankempID[read1 -1]='\0';
}
else
{bankempID[read1 -1]='\0';}

/*    if (username[bytesread - 1] == '\n')
    {
        username[bytesread - 1] = '\0';
    }

    else
    {
        username[bytesread] = '\0';
    }
*/
const char *passprompt = "Enter password: \n";
    send(clientsocket, passprompt, strlen(passprompt), 0);
    bytesread = recv(clientsocket, password, sizeof(password), 0);

    if (bytesread <= 0)
    {
        close(clientsocket);
        return false;
    }

    if (password[bytesread - 1] == '\n')
    {
        password[bytesread - 1] = '\0';
    }
    else
    {
        password[bytesread] = '\0';
    }

int db_fd = open("bankemp_db.txt", O_RDONLY);
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

/*    if (strcmp(username, bankempcredentials.username) == 0 &&
        strcmp(password, bankempcredentials.password) == 0)
    {

        const char *successtxt = "Authentication successful\n";
        send(clientsocket, successtxt, strlen(successtxt), 0);
        return true;
}
 else
    {
        const char *failuretxt = "Authentication failed\n";
        send(clientsocket, failuretxt, strlen(failuretxt), 0);
        close(clientsocket);
        return false;
    }
}
*/

bool add_newcustomer(int clientsocket)
{
    struct Customer cust;
    char namePrompt[] = "Enter customer name: ";

    send(clientsocket, namePrompt, strlen(namePrompt), 0);
    int readdata = recv(clientsocket, cust.name, sizeof(cust.name) - 1, 0);
    if (readdata <= 0)
    {
        send(clientsocket, "Couldn't receive customer name from client", strlen("Couldn't receive customer name from client"), 0);
        return false;
    }
    cust.name[readdata] = '\0';

    // Check for newline
    if (cust.name[readdata - 1] == '\n')
    {
 cust.name[readdata - 1] = '\0';
    }

    // Similar prompts for password, role, and employee ID...
    char passPrompt[] = "Enter password: ";
    send(clientsocket, passPrompt, strlen(passPrompt), 0);
    readdata = recv(clientsocket, cust.password, sizeof(cust.password) - 1, 0);
    if (readdata <= 0)
    {
        send(clientsocket, "Couldn't receive customer password from client", strlen("Couldn't receive customer password from client"), 0);
        return false;
    }
    cust.password[readdata] = '\0';
    if (cust.password[readdata - 1] == '\n')
    {
        cust.password[readdata - 1] = '\0';
    }

    char custIDprompt[] = "Enter customer ID: \n";
    send(clientsocket, custIDprompt, strlen(custIDprompt), 0);
    readdata = recv(clientsocket, cust.custid, sizeof(cust.custid) - 1, 0);
    if (readdata <= 0)
    {
        perror("Error receiving customer ID\n");
        return false;
    }
    else if (readdata == 0)
    {
        printf("Connection closed by the client.\n");
        return false;
    }
    cust.custid[readdata] = '\0';
    if (cust.custid[readdata - 1] == '\n')
    {
        cust.custid[readdata - 1] = '\0';
 }

char custIDprompt[] = "Enter initial balance of customer\n: \n";
    send(clientsocket, custIDprompt, strlen(custIDprompt), 0);
    readdata = recv(clientsocket, cust.balance, sizeof(cust.balance) - 1, 0);
    if (readdata <= 0)
    {
        perror("Error receiving balance\n");
        return false;
    }
    else if (readdata == 0)
    {
        printf("Connection closed by the client.\n");
        return false;
    }
    cust.balance[readdata] = '\0';
    if (cust.balance[readdata - 1] == '\n')
    {
        cust.balance[readdata - 1] = '\0';
 }


    cust.active = true;

    // Use fopen to write to the file
    int fd = open("./customer_db.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
    if(fd==-1)
        return false;
    if (fd != -1)
    {
        write(fd, &emp, sizeof(struct Customer));
        close(fd);
        // int *ptr = empID;
        /*fprintf(dbfile, "%s,%s,%s,%s\n", emp.employeeID, emp.name, emp.password, emp.role);
        fclose(dbfile);
        printf("Employee added successfully.\n");
        fflush(stdout);*/
        return true;
    }
    
    perror("Cannot open customer file");
    printf("Failed to add customer.\n");
    fflush(stdout);
    return false;
}


bool modify_customerdetails(int clientsocket)
{
    // char empid_buffer[100];
    char custid[100] = "";
 char format[300];
 
    send(clientsocket, "Enter the customer ID to update: ", strlen("Enter the customer ID to update: "), 0);
    ssize_t bytesread = 0;
    bytesread = recv(clientsocket, &custid, sizeof(custid) - 1, 0);
    printf("bytesread : %zd\n", bytesread);

    if (bytesread < 0)
    {
        perror("recv error");
        return false; // Handle error appropriately
    }
    else if (bytesread == 0)
    {
        printf("Connection closed by the client.\n");
        return false; // Handle closure appropriately
    }

     custid[bytesread] = '\0'; // Null-terminate the string          //edited
  printf("Received customer id: %s\n", custid);

    // int empid = atoi(empid_buffer); // Convert to int
    //empid[strcspn(empid, "\n")] = 0;

    const char *dbFileName = "customer_db.data";
    int dbfile = open(dbFileName, O_RDWR);
    if (dbfile == -1)
    {
        perror("Error opening the database file");
        return false;
    }

    // Lock the file for writing
    if (flock(dbfile, LOCK_EX) == -1)
    {
        perror("Error locking the file for writing");
        close(dbfile);
        return false;
    }

    // Iterate through the file to find the student record
    struct Customer custrecord;
    bool found = false;
    printf("%s is emp id received\n", custid);
    while (read(dbfile, &custrecord, sizeof(struct Customer)) > 0)
    {
        printf("Debug: Reading Employee Record: \n");
        printf("Customer ID: %s\n", custrecord.custid);
        printf("Name: %s\n", custrecord.name);
        int strCompareResult=strcmp(custrecord.custid, custid);
        printf("%d is the comparison result\n", strCompareResult);
        if (strCompareResult==0)          //changed
        {
            found = true;
            printf("entered if");

            // Prompt for and receive updated information from the client
            send(clientsocket, "Enter updated customer name: ", strlen("Enter updated customer name: "), 0);
            bytesread = recv(clientsocket, emprecord.name, sizeof(emprecord.name) - 1, 0);
            if (bytesread <= 0)
            {
                send(clientsocket, "Error receiving updated customer name from client", strlen("Error receiving updated customer name from client"), 0);
                return false;
            }
            emprecord.name[bytesread] = '\0';

            send(clientsocket, "Enter updated customer password: ", strlen("Enter updated customer password: "), 0);
            bytesread = recv(clientsocket, emprecord.password, sizeof(emprecord.password) - 1, 0);
            if (bytesread <= 0)
            {
                send(clientsocket, "Error receiving updated customer password from client", strlen("Error receiving updated customer password from client"), 0);
                return false;
            }
            emprecord.password[bytesread] = '\0';


            // Move the file pointer back to the beginning of the record and update it
            lseek(dbfile, (-1)*sizeof(struct Employee), SEEK_CUR);
            write(dbfile, &emprecord, sizeof(struct Employee));
            break;
        }
    }

    if (found)
    {
        // Student record updated successfully
        const char *updateMessage = "employee record updated successfully\n";
        send(clientsocket, updateMessage, strlen(updateMessage), 0);
    }
    else
    {
        // Student not found
        const char *notFoundMessage = "employee not found\n";
        send(clientsocket, notFoundMessage, strlen(notFoundMessage), 0);
    }

    // Unlock the file
    if (flock(dbfile, LOCK_UN) == -1)
    {
        perror("Error unlocking the file");
    }

    // Close the file
    close(dbfile);

    return found; // Return whether the student was found and updated.
}
