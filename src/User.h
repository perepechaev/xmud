/*
 * User.h
 *
 *  Created on: 17.03.2010
 *      Author: topas
 */

#ifndef USER_H_
#define USER_H_

#include "Encoder.h"
#include "ServerSocket.h"

class User
{
public:
    User(ServerSocket *socket);
    void setEncoding(const char* client, const char* server);
    void setName(std::string name){this->name = (char* ) name.c_str();};
    char* getName(){return name;}
    void send(const char* message);
    void send(const char* message, int hexdebug);
    void send(const std::string message);
    void send(int i){ char str[10]; sprintf(str, "%d", i); send(str);};
    std::string* recive();
    std::string* recive(const char* prompt){ send(prompt); return recive();}
    bool operator==(User user){ return this->id == user.id; }
    virtual ~User();
    int id;
private:
    Encoder *encoder;
    ServerSocket *socket;
    static int last_id;
    char* name;
};

#endif /* USER_H_ */
