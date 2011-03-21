#include "ServerSocket.h"
#include "SocketException.h"
#include "Message.h"
#include "MessageStack.h"
#include "UserStack.h"
#include "Encoder.h"
#include <string>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <vector>

ServerSocket server(9001);


void* rundle(void* socket);
void* game(void* socket);

/*****************************************************/

int main(int argc, int argv[]) {
    std::cout << "running....\n";

    Message message("topas", "Hello World"), m2("topas", "where are you?"),
        m3("guest", "Hi");

    MessageStack messages;
    messages.append(&message);
    messages.append(&m2);
    messages.append(&m3);

    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    try {
        pthread_create(&tid, &attr, &game, NULL);
        while (true) {

            try{
                ServerSocket *new_sock = new ServerSocket;
                server.accept(*new_sock);

                pthread_create(&tid, &attr, &rundle, new_sock);
            }
            catch (SocketException& e) {
                std::cout << "Exception was caught:" << e.description()
                        << "\nExiting.\n";
            }
        }
    } catch (SocketException& e) {
        std::cout << "Exception was caught:" << e.description()
                << "\nExiting.\n";
    }

    return 0;
}

void echor(ServerSocket* socket, std::string message){
    *socket << message;
}

void echos(ServerSocket* socket, const char* message){
    *socket << message;
}

//char* toCP1251(const char* from, char** to){
//    iconv_t cd;
//    printf("FROM: %s\n", from);
//    size_t str_len = strlen(from), out_len;
////    cd = iconv_open("UTF-8", "CP1251");
//    cd = iconv_open("KOI8-R", "CP1251");
//
//    char *out;
//    *out = NULL;

//    printf("TO: %p\n", out);
//    iconv(cd, &from, &str_len, &out, &out_len);
//    printf("TO: %s\n", out);
//    printf("LEN: %d\n", out_len);
//    printf("LEN2: %d\n", str_len);conv
//    printf("FROM: %s\n", from);
//    iconv_close(cd);
//    return *to;
//}

void echos(ServerSocket* socket, std::string message){
    *socket << message;
}

std::string trimr(std::string source){
    return source.erase( source.find_last_not_of("\r\n") + 1 );
}

User* init_connection(ServerSocket *socket){
    User *user = new User( (ServerSocket *) socket );
    std::string *request, username;
    int is_utf8 = 0;

    user->send("Welcome to Monolipe\n\n==========\n");
    user->send("Enter your codepage (cp1251 on default): ");

    while (username.length() == 0){
        request = user->recive();

        if ( (*request)[0] == (char) 255){
            if ((*request)[1] == (char) 251){
                // WILL (option code)   251 Указывает на желание исполнять или подтверждает, что сейчас исполняется указанная опция.
                printf("It's telnet\n");
                continue;
            }
        }

        *request = trimr(*request);

        if (request->compare("utf8") == 0){
            is_utf8 = 1;
        }
        else {
            if (!is_utf8){
                user->setEncoding("cp1251", "utf-8");
            }
            username = *request;
        }

        user->send("Ваше имя: ");
    }
    user->setName(username);

    return user;
}

void* rundle(void* socket){
    ServerSocket *client = (ServerSocket *) socket;
    std::string data;

    MessageStack messages;

    UserStack users;
    User *user;

    try {
        user = init_connection(client);
    }
    catch (SocketException& e) {
        printf("Error initial connection in function rundle()\n");
        return NULL;
    }

    try {
        users.join(user);
        user->send("Добро пожаловать, о ");
        user->send("\n---- // enter \"quit\" for exit\n\n");
        user->send(messages.viewLast());


        while (true) {
            data = *user->recive("> ");
            data = trimr(data);
            if ( data.compare("quit") == 0) {
                user->send("Bye! До скорых встреч");
                sleep(2);
                break;
            }
            if ( data.compare("help") == 0){
                user->send("\r==== Список пользователей ====\n");
            }
            if ( data.compare("who") == 0){
                user->send("\r==== Список пользователей ====\n");
                std::vector <User*> list = users.list();
                for (int i = list.size() - 1; i >= 0; --i){
                    user->send(list[i]->id);
                    user->send(": ");
                    user->send(list[i]->getName());
                    user->send("\n");
                }
                continue;
            }


            if ( data.length() == 0){
                continue;
            }

            Message *message = new Message(user->getName(), data);
            messages.append( message );
            users.sendMessage(message->get().c_str());
        }
    } catch (SocketException& e) {
        std::cout << "Exception was caught:" << e.description()
                << "\nExiting.\n";
    }

    users.disconnect(user);

    delete client;

    return NULL;
}

void* game(void* socket){
    UserStack users;

    while (true){
//        printf("Количество online: %d\n", users.size());
//        users.sendMessage("\rПривет всем!!! Яблоко, яблоко: \n");
        sleep(7);
    }
}
