#ifndef ADMIN
#define ADMIN

struct Employee{
char employeeID[100];
char name[100];
char password[100];
char role[100];
bool active;
//char custid[100];
};



bool administrator_login(int clientSocket);
bool authenticate_administrator(int clientSocket);
bool change_password(int clientSocket);
#endif
