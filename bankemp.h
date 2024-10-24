#ifndef EMPLOYEE
#define EMPLOYEE

bool employee_login(int socket);
bool authenticate_emp(int socket);

bool manager_login(int socket);

struct Employee
{
char id[50];
char username[50];
char password[10];
char role[50];
};
#endif

