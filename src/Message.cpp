/*
 * Message.cpp
 *
 *  Created on: 16.03.2010
 *  Author: topas
 */

#include "Message.h"

Message::Message(const char* name, const char* message){
    this->name      = (char *) malloc(sizeof(char) * strlen(name) + 1);
    strcpy(this->name, name);

    this->message    = (char *) malloc(sizeof(char) * strlen(message) + 1);
    strcpy(this->message, message);
    id = ++last;
}

Message::Message(const std::string name, const std::string message){
    this->name      = (char *) malloc(sizeof(char) * name.length() + 1);
    strcpy(this->name, name.c_str());

    this->message    = (char *) malloc(sizeof(char) * message.length() + 1);
    strcpy(this->message, message.c_str());
    id = ++last;
}

int Message::last = 0;

std::string Message::get(){
    char* result;
    std::string data;

    result = (char*) malloc(sizeof(char) * 256 + 1);
    sprintf(result, "\r[%d] %s: %s\n", id, name, message);
    data.append( result );

    free(result);

    return data;
}
