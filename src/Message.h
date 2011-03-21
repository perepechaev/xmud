/*
 * Message.h
 *
 *  Created on: 16.03.2010
 *  Author: topas
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>

class Message {
public:
    Message(const char* name, const char* message);
    Message(std::string,std::string);
    std::string get();
private:
    char *name;
    char *message;
    int id;
    static int last;
};

#endif /* MESSAGE_H_ */
