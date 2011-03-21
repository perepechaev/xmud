/*
 * User.cpp
 *
 *  Created on: 17.03.2010
 *      Author: topas
 */

#include "User.h"
#include "Encoder.h"


User::User(ServerSocket *socket){
    this->socket = socket;
    this->id = ++last_id;
//    last_id++;
}

void User::setEncoding(const char* client, const char* server){
    encoder = new Encoder(client, server);
}

//void User::setName(std::string name) {
//    printf("OLD: %s\n", name.c_str());
//    if (encoder != NULL){
////        encoder->toServer(&name);
//    }
//
//    printf("NEW: %s\n", name.c_str());
//    this->name = (char* ) name.c_str();
//}

void User::send(const char* message){
    std::string out(message);

    if (encoder != NULL){
        encoder->toClient(&out);
    }

    *socket << out;
}

void User::send(const std::string message){
    std::string out(message);

    if (encoder != NULL){
        encoder->toClient(&out);
    }

    *socket << out;
}

void User::send(const char* message, int hexdebug){
    this->send(message);

    std::string out(message);

    if (encoder != NULL){
        encoder->toClient(&out);
    }

    int len = out.length();
    int i;
    char hexcode[10];
    *socket << "\n";
    for (i = 0; i < len; ++i){
        sprintf(hexcode, "%X ", (char) out[i]);
        *socket << hexcode;
    }
    *socket << "\n";
}

std::string* User::recive(){
    std::string* request = new std::string();

    *socket >> *request;

    if (encoder != NULL){
        encoder->toServer(request);
    }

    return request;
}



User::~User() {
    // TODO Auto-generated destructor stub
}

int User::last_id = 0;
