/*
 * Encoder.h
 *
 *  Created on: 17.03.2010
 *      Author: topas
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>

class Encoder {
public:
    Encoder(const char* client_encode, const char* server_encode);
    std::string* toClient(std::string* str){ return convert(str, server_encode, client_encode); };
    std::string* toServer(std::string* str){ return convert(str, client_encode, server_encode); };
    virtual ~Encoder();
private:
    std::string* convert(std::string* str, const char* from, const char* to);
    char *client_encode;
    char *server_encode;
};

#endif /* ENCODER_H_ */
