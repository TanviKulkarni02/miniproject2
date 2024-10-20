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
// #include "customer.h"
// #include "login.h"

bool admin_operation_handler(int clientsocket);
// bool login (int clientsocket);
/*bool view_accountbalace(int clientsocket);
bool deposit_money(int clientsocket);
bool withdraw_money(int clientsocket);
bool transfer_funds(int clientsocket);
bool applyfor_loan(int clientsocket);
bool change_password(int clientsocket);
bool add_feedback(int clientsocket);
bool view_transactionhistory(int clientsocket);
bool logout(int clientsocket);
bool nano_exit(int clientsocket);
*/
// bool admin_options(int cd);
bool authenticate_admin(int clientsocket);
bool add_newemployee(int clientsocket);
bool modify_customerdetails(int clientsocket);
bool modify_employeedetails(int clientsocket);
// bool manage_userroles(int clientsocket);
// bool change_password(int clientsocket);
bool logout(int clientsocket);

struct usercredentials
{
    char username[100];
    char password[100];
};

struct usercredentials admincredentials = {"Tanvi", "666"};

bool admin_operation_handler(int clientsocket)
{
    if (authenticate_admin(clientsocket))
    {
        // send(clientsocket,"Logged in successfully\n",strlen("Logged in successfully!\n"),0);
        ssize_t readbytes;
        // ssize_t writebytes ;
        char readbuffer[1000];
        // char writebuffer[1000];

        while (1)
        {
            char menu[] = "Welcome!! Do you want to:- \n1.Add new bank employee\n - 2.Modify customer/employee details\n - 3.Manage user roles\n - 4.Change password\n - 5.Logout\n - 6.Exit\n - 7.View All Customers\n";
            send(clientsocket, menu, strlen(menu), 0);
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
                if (add_newemployee(clientsocket))
                {
                    send(clientsocket, "Added a new bank employee successfully\n", strlen("Added a new bank employee successfully\n"), 0);
                }
                break;

            case 2:
                if (modify_employeedetails(clientsocket))
                {
                    send(clientsocket, "Modified the details of bank employee successfully\n", strlen("Modified the details of bank employee successfully\n"), 0);
                }
                else
                {
                    send(clientsocket, "Please try again\n", strlen("Please try again\n"), 0);
                }
                break;
            case 7:
                int fd=open("./employee_db.data", O_RDONLY,0777);
                int tempBytes;
                struct Employee tempEmp;
                while(tempBytes=read(fd, &tempEmp, sizeof(struct Employee))>0)
                {
                    printf("Id is-: %s\n", tempEmp.employeeID);
                    printf("Name is-: %s\n", tempEmp.name);
                    printf("Password is-: %s\n", tempEmp.password);
                    printf("Role is-: %s\n", tempEmp.role);

                }
                close(fd);
                break;

                /*
                case 3:
                if(1)
                {
                send(clientsocket , "Modified the details of customer successfully\n", strlen("Modified the details of customer successfully\n"),0);
                }
                else{
                send(clientsocket, "Please try again", strlen("Please try again"),0);
                }
                break;


                case 4:
                if(1)
                {
                send(clientsocket , "Successfully  managed user roles\n", strlen("Successfully  managed user roles\n"),0);
                }
                else{
                send(clientsocket , "Please try again" , strlen("Please try again"),0);
                }
                break;

                case 5:
                if(1)
                {
                send(clientsocket, "Successfully changed the password\n", strlen("Successfully changed the password\n"),0);
                }
                else{
                send(clientsocket , "Please try again" , strlen("Please try again"),0);
                }
                break;

                case 6:
                if(1)
                {
                send(clientsocket, "Logged out\n",strlen("Logged out\n"),0);
                }
                else
                {
                send(clientsocket , "Please try again" , strlen("Please try again"),0);
                }
                break;
                */

                /*case 7:
                close(clientsocket);
                return true;
                */

/*default:
send(clientsocket , "Unfortunately had to logout\n" , strlen("Unfortunately had to logout\n"),0);
close(clientsocket);
return false;
*/}
        }
    }
    return false;
}

/* if(authenticate_admin(clientsocket))
{printf("hello");
}
}
*/

/////     TRY    ////

bool authenticate_admin(int clientsocket)
{
    char username[100];
    char password[100];

    const char *userprompt = "Enter username: \n";
    send(clientsocket, userprompt, strlen(userprompt), 0);

    ssize_t bytesread = recv(clientsocket, username, sizeof(username), 0);
    if (bytesread <= 0)
    {
        close(clientsocket);
        return false;
    }

    if (username[bytesread - 1] == '\n')
    {
        username[bytesread - 1] = '\0';
    }

    else
    {
        username[bytesread] = '\0';
    }

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

    if (strcmp(username, admincredentials.username) == 0 &&
        strcmp(password, admincredentials.password) == 0)
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

bool add_newemployee(int clientsocket)
{
    struct Employee emp;
    char namePrompt[] = "Enter employee name: ";

    send(clientsocket, namePrompt, strlen(namePrompt), 0);
    int readdata = recv(clientsocket, emp.name, sizeof(emp.name) - 1, 0);
    if (readdata <= 0)
    {
        send(clientsocket, "Couldn't receive employee name from client", strlen("Couldn't receive employee name from client"), 0);
        return false;
    }
    emp.name[readdata] = '\0';

    // Check for newline
    if (emp.name[readdata - 1] == '\n')
    {
        emp.name[readdata - 1] = '\0';
    }

    // Similar prompts for password, role, and employee ID...
    char passPrompt[] = "Enter password: ";
    send(clientsocket, passPrompt, strlen(passPrompt), 0);
    readdata = recv(clientsocket, emp.password, sizeof(emp.password) - 1, 0);
    if (readdata <= 0)
    {
        send(clientsocket, "Couldn't receive employee password from client", strlen("Couldn't receive employee password from client"), 0);
        return false;
    }
    emp.password[readdata] = '\0';
    if (emp.password[readdata - 1] == '\n')
    {
        emp.password[readdata - 1] = '\0';
    }

    char rolePrompt[] = "Enter role: ";
    send(clientsocket, rolePrompt, strlen(rolePrompt), 0);
    readdata = recv(clientsocket, emp.role, sizeof(emp.role) - 1, 0);
    if (readdata <= 0)
    {
        send(clientsocket, "Couldn't receive employee role from client", strlen("Couldn't receive employee role from client"), 0);
        return false;
    }
    emp.role[readdata] = '\0';
    if (emp.role[readdata - 1] == '\n')
    {
        emp.role[readdata - 1] = '\0';
    }

    char empIDprompt[] = "Enter employee ID: \n";
    send(clientsocket, empIDprompt, strlen(empIDprompt), 0);
    readdata = recv(clientsocket, emp.employeeID, sizeof(emp.employeeID) - 1, 0);
    if (readdata <= 0)
    {
        perror("Error receiving employee ID\n");
        return false;
    }
    else if (readdata == 0)
    {
        printf("Connection closed by the client.\n");
        return false;
    }
    emp.employeeID[readdata] = '\0';
    if (emp.employeeID[readdata - 1] == '\n')
    {
        emp.employeeID[readdata - 1] = '\0';
    }

    emp.active = true;

    // Use fopen to write to the file
    int fd = open("./employee_db.data", O_RDWR | O_CREAT | O_APPEND, 0777);
    if(fd==-1)
        return false;
    if (fd != -1)
    {
        write(fd, &emp, sizeof(struct Employee));
        close(fd);
        // int *ptr = empID;
        /*fprintf(dbfile, "%s,%s,%s,%s\n", emp.employeeID, emp.name, emp.password, emp.role);
        fclose(dbfile);
        printf("Employee added successfully.\n");
        fflush(stdout);*/
        return true;
    }
    
    perror("Cannot open employee file");
    printf("Failed to add employee.\n");
    fflush(stdout);
    return false;
}

bool modify_employeedetails(int clientsocket)
{
    // char empid_buffer[100];
    char empid[100] = "";
    send(clientsocket, "Enter the employee ID to update: ", strlen("Enter the employee ID to update: "), 0);
    ssize_t bytesread = 0;
    bytesread = recv(clientsocket, &empid, sizeof(empid) - 1, 0);
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

     empid[bytesread] = '\0'; // Null-terminate the string          //edited
    // int empid = atoi(empid_buffer); // Convert to int
    //empid[strcspn(empid, "\n")] = 0;

    const char *dbFileName = "employee_db.data";
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
    struct Employee emprecord;
    bool found = false;
    printf("%s is emp id received\n", empid);
    while (read(dbfile, &emprecord, sizeof(struct Employee)) > 0)
    {
        printf("Debug: Reading Employee Record: \n");
        printf("Employee ID: %s\n", emprecord.employeeID);
        printf("Name: %s\n", emprecord.name);
        int strCompareResult=strcmp(emprecord.employeeID, empid);
        printf("%d is the comparison result\n", strCompareResult);
        if (strCompareResult==0)          //changed
        {
            found = true;
            printf("entered if");

            // Prompt for and receive updated information from the client
            send(clientsocket, "Enter updated employee name: ", strlen("Enter updated employee name: "), 0);
            bytesread = recv(clientsocket, emprecord.name, sizeof(emprecord.name) - 1, 0);
            if (bytesread <= 0)
            {
                send(clientsocket, "Error receiving updated employee name from client", strlen("Error receiving updated employee name from client"), 0);
                return false;
            }
            emprecord.name[bytesread] = '\0';

            send(clientsocket, "Enter updated student password: ", strlen("Enter updated student password: "), 0);
            bytesread = recv(clientsocket, emprecord.password, sizeof(emprecord.password) - 1, 0);
            if (bytesread <= 0)
            {
                send(clientsocket, "Error receiving updated employee password from client", strlen("Error receiving updated employee password from client"), 0);
                return false;
            }
            emprecord.password[bytesread] = '\0';

            send(clientsocket, "Enter updated employee role: \n", strlen("Enter updated employee role: \n"), 0);
            bytesread = recv(clientsocket, emprecord.role, sizeof(emprecord.role) - 1, 0);
            if (bytesread <= 0)
            {
                send(clientsocket, "Error in receiving updates employee role", strlen("Error in receiving updates employee role"), 0);
                return false;
            }
            emprecord.role[bytesread] = '\0';

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

