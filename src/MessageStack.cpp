/*
 * MessageStack.cpp
 *
 *  Created on: 16.03.2010
 *      Author: topas
 */

#include "MessageStack.h"

MessageStack::MessageStack(){

}

void MessageStack::append(Message *message){
    pthread_mutex_lock(&mutex);
    messages.insert(messages.end(), message);
    pthread_mutex_unlock(&mutex);
}

std::string MessageStack::viewLast(int i){
    std::string result;

    int count, size;

    size    = (int) messages.size();
    count   = i > size ? size : i;
    for (i = count; i > 0; i--){
        result.append( messages[size-i]->get());
    }
    return result;

    return result;
}

std::vector <Message *> MessageStack::messages;
pthread_mutex_t MessageStack::mutex = PTHREAD_MUTEX_INITIALIZER;
