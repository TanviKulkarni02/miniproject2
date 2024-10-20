#ifndef ADMIN
#define ADMIN


bool admin_login(int clientSocket);
bool authenticate_admin(int clientSocket);
bool change_pass(int clientSocket);

#endif
