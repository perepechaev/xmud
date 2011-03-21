/*
 * MessageStack.h
 *
 *  Created on: 16.03.2010
 *      Author: topas
 */

#ifndef MESSAGESTACK_H_
#define MESSAGESTACK_H_

#include <string>
#include <vector>
#include "Message.h"

class MessageStack{
public:
    MessageStack();
    void append(Message *message);
    std::string viewLast(int i = 10);

private:
    static std::vector <Message*> messages;
    static pthread_mutex_t mutex;
};

#endif /* MESSAGESTACK_H_ */
