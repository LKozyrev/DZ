#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Ошибка инициализации Winsock\n";
        return 1;
    }


    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка создания сокета\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(12345);


    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка подключения к серверу\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Подключено к серверу. Вводите числа (или 'exit' для выхода).\n";

    char buffer[1024];
    int bytesReceived;

    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }

    while (true) {
        std::string guess;
        std::getline(std::cin, guess);

        if (guess == "exit") {
            break;
        }

        send(clientSocket, guess.c_str(), guess.size(), 0);

        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << buffer;
        }
        else {
            std::cout << "Соединение с сервером потеряно\n";
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}