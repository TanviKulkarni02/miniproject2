#ifndef TRANSACTION
#define TRANSACTION
struct transaction
{
char flag[10];
char sender[10];
char receiver_id[10];
char amount[256];
};
#endif
