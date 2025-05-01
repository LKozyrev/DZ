#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <random>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")

std::mutex mtx;
std::vector<SOCKET> clients;
bool gameRunning = true;
int targetNumber = 0;

void generateNewNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    targetNumber = distr(gen);
    std::cout << "Новое загаданное число: " << targetNumber << std::endl;
}

void handleClient(SOCKET clientSocket) {
    char buffer[1024];
    int bytesReceived;

    const char* welcomeMsg = "Введите число:\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    while (gameRunning) {
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cout << "Клиент отключился или произошла ошибка\n";
            break;
        }

        buffer[bytesReceived] = '\0';
        std::cout << "Получено от клиента: " << buffer;

        int guess = atoi(buffer);
        std::string response;

        if (guess < targetNumber) {
            response = "Ваше число меньше загаданного. Попробуйте еще:\n";
        }
        else if (guess > targetNumber) {
            response = "Ваше число больше загаданного. Попробуйте еще:\n";
        }
        else {
            response = "Поздравляем! Вы угадали число! Начинаем новую игру.\n";

            mtx.lock();
            for (SOCKET sock : clients) {
                if (sock != clientSocket) {
                    send(sock, "Кто-то угадал число! Начинаем новую игру.\n", 44, 0);
                }
            }
            mtx.unlock();

            generateNewNumber();
        }

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    mtx.lock();
    auto it = std::find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    mtx.unlock();

    closesocket(clientSocket);
    std::cout << "Клиент отключен. Осталось клиентов: " << clients.size() << std::endl;
}

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Ошибка инициализации Winsock\n";
        return 1;
    }


    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка создания сокета\n";
        WSACleanup();
        return 1;
    }


    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345);


    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка привязки сокета\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }


    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Ошибка прослушивания\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Сервер запущен. Ожидание подключений на порту 12345...\n";

    generateNewNumber();

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка принятия подключения\n";
            continue;
        }

        mtx.lock();
        clients.push_back(clientSocket);
        mtx.unlock();

        std::thread(handleClient, clientSocket).detach();

        std::cout << "Новое подключение. Всего клиентов: " << clients.size() << std::endl;
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}