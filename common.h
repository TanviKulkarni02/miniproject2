#ifndef COMMON_H
#define COMMON_H
#define DB_FILE "employee_db.txt"
#include <stdbool.h>

struct Employee{
char employeeID[100];
char name[100];
char password[100];
char role[100];
bool active;
//char custid[100];
};

struct Customer {
 char custid[100];
    char name[100];
    char password[100];
    char balance[100];
    char transactionHistory[100][100]; // Simple transaction history
    int transactionCount;
bool active;
};





#endif
