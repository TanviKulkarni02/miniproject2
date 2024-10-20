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
};

struct Customer {
 int id;
    char name[100];
    char password[100];
    double balance;
    char transactionHistory[100][100]; // Simple transaction history
    int transactionCount;
};





#endif
