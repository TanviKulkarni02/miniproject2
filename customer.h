#ifndef CUSTOMER
#define CUSTOMER

struct customer
{
char id[10];
char password[100];
char username[100];
char bal[100];
bool active;
};

bool login_customer(int clientSocket);
#endif
