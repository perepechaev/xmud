/*
 * UserStack.cpp
 *
 *  Created on: 16.03.2010
 *      Author: topas
 */

#include "UserStack.h"
#include "User.h"

void echos(ServerSocket* socket, const char* message);

void UserStack::join(User* user){
    printf("Вошел пользователь %s\n", user->getName());
    users.insert(users.end(), user);
}

void UserStack::disconnect(User *user){
    int i, len = users.size();
    for (i = 0; i < len; ++i){
        if (users[i] == user){
            users.erase(users.begin() + i);
            break;
        }
    }
}

void UserStack::sendMessage(const char* message){
    printf("%s", message);
    int i, len;
    len = users.size();
    for (i = 0; i < len; i++){
        try{
            users[i]->send(message);
        }
        catch (SocketException e) {
            printf("Error in function sendMessage()\n");
        }
    }
}

std::vector <User *> UserStack::users;

