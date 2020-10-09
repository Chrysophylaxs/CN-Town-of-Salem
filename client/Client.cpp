#include "Client.h"
#include <ws2tcpip.h>
#include <iostream>

Client::Client() {
    tv.tv_sec = 0;
    tv.tv_usec = 5000;
}

Client::~Client() = default;

int Client::setup() {
    int wsaError = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaError != 0) {
        std::cout << " > Failed Initialising WSA. Code: " << wsaError << std::endl;
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "Failed Creating Socket. Code: " << WSAGetLastError() << std::endl;
        return 2;
    }

    addrinfo* result = nullptr;
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int addrInfoError = getaddrinfo(ServerIP.c_str(), ServerPort.c_str(), &hints, &result);
    if (addrInfoError != 0) {
        std::cout << "Failed Getting Address Info. Code: " << WSAGetLastError() << std::endl;
        return 3;
    }
    addrinfo addrInfo = *result;

    int connectError = connect(sock, addrInfo.ai_addr, (int)addrInfo.ai_addrlen);
    if (connectError != 0) {
        std::cout << "Failed Connecting to Server. Code: " << WSAGetLastError() << std::endl;
        return 4;
    }
    connected = true;

    freeaddrinfo(result);
    return 0;
}

int Client::login(std::string name) {
    int error = sendMsg("LOGIN " + name + "\n");
    if (error <= 0) {
        return -1;
    }
    std::string response = receive();
    if (response.empty()) {
        return -2;
    }
    if (response == "INUSE\n") {
        return 1;
    }
    if (response == "HELLO " + name + "\n") {
        return 0;
    }
    return 2;
}

int Client::poll() {
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);

    if (select(0, &readfds, nullptr, nullptr, &tv) == SOCKET_ERROR) {
        std::cout << "Failed Selecting. Code: " << WSAGetLastError() << std::endl;
        return -1;
    }

    if (FD_ISSET(sock, &readfds)) {
        return 1;
    }
    else {
        return 0;
    }
}

int Client::sendMsg(std::string msg) {
    const char *buf = msg.c_str();
    int bytesSent = send(sock, buf, (int)msg.size(), 0);
    if (bytesSent == SOCKET_ERROR) {
        return -1;
    }
    return bytesSent;

}

std::string Client::receive() {
    int size = 2048;
    auto *buffer = new char[size];
    int bytesReceived = recv(sock, buffer, size, 0);
    if (bytesReceived == SOCKET_ERROR) {
        return "";
    }
    buffer[bytesReceived] = '\0';
    std::string response = buffer;
    delete[] buffer;
    return response;
}

void Client::shutdown() {
    closesocket(sock);
    WSACleanup();
}