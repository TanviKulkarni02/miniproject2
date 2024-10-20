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
#include "common.h"
#include "administrator.c"

#define DB_FILE "customer_db.txt"
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








{
    struct Faculty authenticatedprof;

    bool authenticated = authenticate_prof(clientSocket, &authenticatedprof);

    if (authenticated)
    {
        ssize_t readBytes;
        char readbuff[1000];

        // Send a welcome message after successful login
        send(clientSocket, "Login Successfully\n", strlen("Login Successfully\n"), 0);

        while (1)
        {
            // Send the professor menu to the client
            char profMenu[] = "Professor Menu:\n1. Add new Course\n2. Remove offered course\n3. View enrollments in the course\n4. View offered course detials\n  5.Update course details\n 6. Exit\n 7.Change Password\n";
            send(clientSocket, profMenu, strlen(profMenu), 0);

            // Receive the client's menu choice
            readBytes = recv(clientSocket, readbuff, sizeof(readbuff), 0);
            if (readBytes == -1)
            {
                perror("Error while reading client's choice for PROF_MENU");
                return false;
            }

            int choice = atoi(readbuff);

            // Handle the menu choice
            switch (choice)
            {
                case 1:
                    if (add_course(clientSocket,&authenticatedprof))
                    {
                        send(clientSocket,"Done successfully\n", strlen("Done successfully\n"), 0);
                    }
                   /* else
                     {
                     send(clientSocket,"There is some error please try again!\n", strlen("There is some error please try again\n!"), 0);
                     }*/
                    break;
               case 2:
                    if(remove_course(clientSocket,&authenticatedprof))
                     {
                     send(clientSocket,"Done successfully\n",strlen("Done successfully\n"),0);
                     }
                     else
                     {
                     send(clientSocket,"There is some error please try again!\n", strlen("There is some error please try again!\n"), 0);
                     }
                     break;
              case 3: view_enrollments(clientSocket);
                      break;
              case 4: view_offered(clientSocket);
                      break;
              case 5: if(update_course(clientSocket))
                      {
                      send(clientSocket,"Done successfully\n", strlen("Done successfully\n"), 0);
                      }
                      else
                      {
                      send(clientSocket,"There is some error please try again!\n", strlen("There is some error please try again!\n"), 0);
                      }
                     break;
              case 6:close(clientSocket);
                     break;
              case 7:
                if (change_password(clientSocket, &authenticatedprof)) {
                    send(clientSocket, "Password changed successfully\n", strlen("Password changed successfully\n"), 0);
                } else {
                    send(clientSocket, "Failed to change password\n", strlen("Failed to change password\n"), 0);
                }
                break;

              }
        }
    }
    return false;
}
