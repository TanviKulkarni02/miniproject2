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



bool login_administrator(int clientsocket);
bool authenticate_administrator(int clientsocket);
//bool change_password(int clientsocket);
#endif
