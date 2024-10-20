#ifndef CUSTOMER
#define CUSTOMER
struct customer
{
char id[10];
char password[20];
char username[50];
char bal[1024];
bool active;
};
bool login_customer(int clientSocket);
#endif
