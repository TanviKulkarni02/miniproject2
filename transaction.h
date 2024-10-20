#ifndef TRANSACTION
#define TRANSACTION
struct transaction
{
char sender[10];
char rec[10];
char flag[2];
char amount[1024];
};
#endif
