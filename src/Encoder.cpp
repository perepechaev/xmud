/*
 * Encoder.cpp
 *
 *  Created on: 17.03.2010
 *      Author: topas
 */

#include "Encoder.h"
#include <string>
#include <iconv.h>

Encoder::Encoder(const char* client_encode, const char* server_encode) {
    printf("Конструктор: Encoder \n");
    this->client_encode = (char *) client_encode;
    this->server_encode = (char *) server_encode;
//    iconv_t cd;
//    size_t str_len = strlen(message);
//    size_t out_len = strlen(message) * 2 + 10;
//    int buf_size = out_len;
//    char *out = (char *) malloc(sizeof(char) * out_len);
//    cd = iconv_open("CP1251", "UTF-8");
//    iconv(cd, (const char**) &message, &str_len, &out, &out_len);
//    *socket << (out - buf_size + out_len);
//    printf("strlen: %d\n", strlen(out - buf_size + out_len));
//    iconv_close(cd);
//    free(out);

}

std::string* Encoder::convert(std::string* str, const char* from, const char* to){

    iconv_t cd;
    size_t str_len = str->length() * 2 + 1;
    size_t out_len = str->length() * 2 + 1;

    int buf_size = out_len;
    char *out = (char *) malloc(sizeof(char) * out_len + 1);
    const char *in = str->c_str();

    cd = iconv_open(to, from);
    iconv(cd, (const char**) &in, &str_len, &out, &out_len);
    iconv_close(cd);

    str->assign( out - buf_size + out_len);
    free(out - buf_size + out_len);
    return str;
}

Encoder::~Encoder() {
    // TODO Auto-generated destructor stub
}
