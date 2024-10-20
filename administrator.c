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
bool login_administrator(int clientsocket);
bool authenticate_administrator(int clientsocket);
//bool change_password(int clientsocket);
void save_credentials(const char *username, const char *password);
bool verify_credentials(const char *username, const char *password);
bool add_employee(int clientsocket);
int get_id();
void update_id(int id);
int read_id();
bool modify_employeedetails(int clientsocket);
bool manage_userroles(int clientsocket);

struct administratorcredentials  //edited
{
char username[100];
char password[100];
};
bool admin_login(int clientsocket)
{printf("hello\n");
send(clientsocket,"hello\n",strlen("hello\n"),0);

if(authenticate_administrator(clientsocket))

{send(clientsocket,"login successful\n",strlen("login successful\n"),0);
//ssize_t rbytes;
//char rbuff[1024];
while(1)
{
printf("i am in while\n");
fflush(stdout);
ssize_t readbytes;
char readbuffer[100];
char menu[]="select the option number \n1.Add new bank employee\n2.modify customer/employee details\n3.manage user roles\n4.change password\n5.logout\n6.exit";
send(clientsocket,menu,strlen(menu),0);
printf("bye");
readbytes=recv(clientsocket,readbuffer,sizeof(readbuffer),0);
if(readbytes==-1)
{perror("error in reading choice");
return false;}
int choice=atoi(readbuffer);
switch (choice){
	case 1:
	 if(add_employee(clientsocket))
        {
        send(clientsocket,"successfuly added\npress enter to continue\n",strlen("successfully added\npress enter to continue\n"),0);
        }
	break;
	case 2:
		if(modify_employeedetails(clientsocket))    //edited
	{send(clientsocket,"successfully modify\n",strlen("successfully modify\n"),0);}
	break;
	case 3:
		if(manage_user(clientsocket))
	{send(clientsocket,"success\n",strlen("success\n"),0);}
	break;
	case 4:
		if(change_password(clientsocket))
	{send(clientsocket,"successfully changed\n",strlen("successfully changed\n"),0);}

	break;
	case 5:
		send(clientsocket,"successfully logged out\n",strlen("successfully logged out\n"),0);
		return true;
	break;
	case 6:
		close(clientsocket);
		break;
	 default:
                    break;
}//switch end
printf("out of switch\n");
fflush(stdout);
}//while end
}//authenticate end
}//admin login end
bool authenticate_administrator(int clientsocket)
{
send(clientsocket,"hi\n",strlen("hi\n"),0);
printf("hi\n");
char username[100];
char password[100];
send(clientsocket,"enter username:\n",strlen("enter username:\n"),0);
ssize_t read=recv(clientsocket,username,sizeof(username),0);
if (read<=0)
{
close (clientsocket);
return 0;
}
if(username[read -1]=='\n')
{username[read -1]='\0';}
else
{username[read -1]='\0';}
send(clientsocket, "enter password:\n",strlen("enter password:\n"),0);
read=recv(clientsocket,password,sizeof(password),0);
if(read<=0)
{close(clientsocket);
return 0;
}
if(password[read -1]=='\n')
{
password[read -1]='\0';
}
else
{password[read -1]='\0';}
//if (strcmp(username,admin.username)==0 && strcmp(password,admin.password)==0)
   if (verify_credentials(username, password))
{return true;}
else
{send(clientsocket,"invalid credentials\n",strlen("invalid credentials\n"),0);
close(clientsocket);
return false;
}
}
/*bool change_password(int clientsocket)
{
char passmod[10];
send(clientsocket,"enter new password\n",strlen("enter new password\n"),0);
ssize_t readbytes=recv(clientsocket,passmod,sizeof(passmod),0);
if(readbytes<=0)
{send(clientsocket,"error in receiving password\n",strlen("error in receiving password\n"),0);
return false;}
if (passmod[readbytes -1]=='\n')
{passmod[readbytes -1]='\0';}
else
{passmod[readbytes -1]='\0';}
save_credentials("Shatakshee",passmod);
return true;
}
*/

void save_credentials(const char *username, const char *password) {
FILE *file = fopen("adminlogin.txt", "w");
if (file == NULL) {
perror("Error opening file");
exit(EXIT_FAILURE);
}

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
}
bool verify_credentials(const char *username, const char *password) {
    FILE *file = fopen("adminlogin.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    char savedusername[100];
    char savedpassword[100];

    while (fscanf(file, "%s %s", savedusername, savedpassword) != EOF) {
        if (strcmp(savedusername, username) == 0 && strcmp(savedpassword, password) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}


bool add_employee(int clientsocket)
{
struct employee emp1;
//int empid=get_id();
//add.id=empid;
send(clientsocket,"enter empid\n",strlen("enter empid\n"),0);
int readbytes=recv(clientsocket,emp1.id,sizeof(emp1.id),0);
emp1.id[read -1]='\0';
send(clientsocket,"enter username\n",strlen("enter username\n"),0);
 readbytes=recv(clientsocket,emp1.username,sizeof(emp1.username),0);
//add.id[read -1]='\0';
if(readbytes<=0)
{send(clientsocket,"error in fetching username\n",strlen("error in fetching username\n"),0);
return false;}
emp1.username[readbytes-1]='\0';
send(clientsocket,"enter password\n",strlen("enter password\n"),0);
readbytes=recv(clientsocket,emp1.password,sizeof(emp1.password),0);
if(readbytes<=0)
{send(clientsocket,"error in fetching password\n",strlen("error in fetching password\n"),0);
return false;}
emp1.password[readbytes-1]='\0';
send(clientsocket,"enter role of employee\n",strlen("enter role of employee\n"),0);
readbytes=recv(clientsocket,emp1.role,sizeof(emp1.role),0);
if(readbytes<=0)
{send(clientsocket,"error in fetching role\n",strlen("error in fetching role\n"),0);
return false;}
emp1.role[readbytes-1]='\0';
FILE *file=fopen("employee.txt","a");
if(file!=NULL)
{fprintf(file,"%s,%s,%s,%s\n",emp1.id,emp1.password,emp1.username,emp1.role);
fclose(file);
printf("true\n");
fflush(stdout);
return true;}
perror("can not open employee file");
printf("false\n");
fflush(stdout);
return false;
}//end of add employee


bool modify_employeedetails(int clientsocket) {
    struct employee empmod;
    char empid[10];
    char format[300];
    char enter_id[] = "-----Update Employee Data-----\nEnter ID of the employee whose data needs to be changed:";

    write(clientsocket, enter_id, sizeof(enter_id));
    ssize_t bytes_id = read(clientsocket, empid, sizeof(empid));
    if (bytes_id == -1) {
        perror("Error in receiving Employee ID");
        return false;
    }
    printf("Received Employee ID: %s\n", empid);

    write(clientsocket, "Name:", strlen("Name:"));
    read(clientsocket, empmod.username, sizeof(empmod.username));

    write(clientsocket, "ID:", strlen("ID:"));
    read(clientsocket, empmod.id, sizeof(empmod.id));
	write(clientsocket,"role",strlen("role"));
	read(clientsocket,empmod.role,sizeof(empmod.role));

    int dbfile = open("employee.txt", O_RDWR);
    if (dbfile == -1) {
        perror("Error in opening the database file");
        return false;
    }

    char line[300];
    struct employee temp;
    bool is_there = false;

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;  
    lock.l_whence = SEEK_SET;  

    off_t record_offset = 0;
    off_t current_position = 0;

    char buff;
    int line_index = 0;

    while (read(dbfile, &buff, 1) > 0) {
        if (buff != '\n') {
            line[line_index++] = buff;
        } else {
            line[line_index] = '\0';
            line_index = 0;

            current_position = lseek(dbfile, 0, SEEK_CUR);

            sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
            printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
printf("%s,%s\n",temp.id,empid);
            if (atoi(temp.id)==atoi( empid)) {
                printf("Employee ID matched.\n");
                lock.l_start = current_position - strlen(line) - 1;
                lock.l_len = strlen(line) + 1;

                if (fcntl(dbfile, F_SETLK, &lock) == -1) {
                    perror("Error in obtaining lock");
                    close(dbfile);
                    return false;
                }

                strcpy(empmod.password, temp.password);  
                snprintf(format, sizeof(format), "%s,%s,%s,%s\n", empmod.id, empmod.password, empmod.username, empmod.role);

                lseek(dbfile, current_position - strlen(line) - 1, SEEK_SET);

                if (write(dbfile, format, strlen(format)) == -1) {
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
}


bool manage_userroles(int clientsocket)
{
struct employee empmod;
    char empid[10];
    char format[300];
    char enter_id[] = "-----Update Employee Data-----\nEnter ID of the employee whose data needs to be changed:";

    // Ask for the employee ID to update
    write(clientsocket, enter_id, sizeof(enter_id));
    ssize_t bytes_id = read(clientsocket, empid, sizeof(empid));
    if (bytes_id == -1) {
        perror("Error in receiving Employee ID");
        return false;
    }
    empid[bytes_id] = '\0';  // Null-terminate the employee ID
    printf("Received Employee ID: %s\n", empid);

    // Ask for new employee data (name and is_empl)
    //write(cd, "Name:", strlen("Name:"));
    //read(cd, data_new.username, sizeof(data_new.username));

    //write(cd, "ID:", strlen("ID:"));
    //read(cd, data_new.id, sizeof(data_new.id));
	write(clientsocket,"role",strlen("role"));
	read(clientsocket,empmod.role,sizeof(empmod.role));

    // Open the employee database file in read-write mode
    int dbfile = open("employee.txt", O_RDWR);
    if (dbfile == -1) {
        perror("Error in opening the database file");
        return false;
    }

    // File read buffer for lines
    char line[300];
    struct employee temp;
    bool is_there = false;

    // Lock structure for file locking
    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;  // Write lock
    lock.l_whence = SEEK_SET;  // Lock from the start of the file

    // Keep track of the file offset
    off_t record_offset = 0;
    off_t current_position = 0;

    // Buffer to store characters read from the file
    char buffer;
    int line_index = 0;

    // Read file character-by-character to handle newlines and read line-by-line
    while (read(dbfile, &buffer, 1) > 0) {
        // Accumulate characters until we hit a newline or end of the buffer
        if (buffer != '\n') {
            line[line_index++] = buffer;
        } else {
            // Terminate the current line with a null character
            line[line_index] = '\0';
            line_index = 0;

            // Store the current position (start of the record)
            current_position = lseek(dbfile, 0, SEEK_CUR);

            // Parse the line to extract employee details
            sscanf(line, "%[^,],%[^,],%[^,],%[^,]", temp.id, temp.password, temp.username, &temp.role);
            printf("Read Employee: ID=%s, Name=%s, Password=%s, Role=%s\n", temp.id, temp.password, temp.username, temp.role);
	printf("%s,%s\n",temp.id,empid);
            // Check if the employee ID matches
            if (atoi(temp.id)==atoi( empid)) {
                printf("Employee ID matched.\n");

                // Set up the file lock
                lock.l_start = current_position - strlen(line) - 1;  // Lock the start of the current record (move back for the newline)
                lock.l_len = strlen(line) + 1;  // Include the length of the current record and the newline

                // Try to obtain the lock
                if (fcntl(dbfile, F_SETLK, &lock) == -1) {
                    perror("Error in obtaining lock");
                    close(dbfile);
                    return false;
                }

                // Prepare updated employee data
                strcpy(empmod.password, temp.password);  // Preserve the old password
                snprintf(format, sizeof(format), "%s,%s,%s,%s\n", temp.id, temp.password, temp.username, empmod.role);

                // Move file pointer to the start of the current employee record
                lseek(dbfile, current_position - strlen(line) - 1, SEEK_SET);

                // Write the updated employee record
                if (write(dbfile, format, strlen(format)) == -1) {
                    write(cd, "Error in Updating Data", strlen("Error in Updating Data"));
                    close(dbfile);
                    return false;
                }

                // Unlock the file
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

    // Close the file
    close(dbfile);

    // Handle case where employee is not found
    if (!is_there) {
        write(cd, "Employee Not Found", strlen("Employee Not Found"));
        return false;
    }

    return true;
}
