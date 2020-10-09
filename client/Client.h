#ifndef TOS_CLIENT_H
#define TOS_CLIENT_H

#include <winsock2.h>
#include <string>

class Client {
private:
    SOCKET sock;
    WSADATA wsaData;
    fd_set readfds;
    timeval tv;
    bool connected;
public:
    //std::string ServerIP = "84.107.111.15";
    std::string ServerIP = "192.168.0.120";
    //std::string ServerIP = "10.0.1.28";
    std::string ServerPort = "8888";

    Client();
    ~Client();

    int setup();
    int login(std::string name);
    void shutdown();

    int poll();
    int sendMsg(std::string msg);
    std::string receive();
};

#endif // TOS_CLIENT_H