#ifndef BANKEMP_CONTROLLER_H
#define BANKEMP_CONTROLLER_H

bool employee_login(int clientsocket);
bool authenticate_bankemp(int clientsocket);
bool add_newcustomer(int clientsocket);
bool modify_customerdetails(int clientsocket);

#endif
