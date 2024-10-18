#ifndef COMMON_H
#define COMMON_H
#define DB_FILE "employee_db.txt"
#include <stdbool.h>

struct Employee{
char name[100];
char password[100];
char role[100];
char employeeID[100];
bool active;
};

#endif
