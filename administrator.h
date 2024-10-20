#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

void handle_admin(int client_socket);
void handle_admin_session(int client_socket);
bool admin_operation_handler(int clientsocket);
bool authenticate_admin(int clientsocket);
bool add_newemployee(int clientsocket);
bool modify_employeedetails(int clientsocket);
bool modify_customerdetails(int clientsocket);
bool manage_userroles(int clientsocket);
bool change_password(int clientsocket);
bool logout(int clientsocket);

#endif
