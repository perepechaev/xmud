/*
 * UserStack.h
 *
 *  Created on: 16.03.2010
 *      Author: topas
 */

#ifndef USERSTACK_H_
#define USERSTACK_H_

#include "ServerSocket.h"
#include "Socket.h"
#include "SocketException.h"
#include "User.h"
#include <vector>

class UserStack{
public:
    void join(User* user);
    void disconnect(User *user);
    void sendMessage(const char* message);
    int size(){return users.size();}
    std::vector <User *> list(){return users;};
private:
    static std::vector <User *> users;
};

#endif /* USERSTACK_H_ */
