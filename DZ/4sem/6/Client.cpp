#include <iostream>
#include <winsock2.h>  // Библиотека для работы с сокетами в Windows

#pragma comment(lib, "ws2_32.lib")  // Автоматическая линковка библиотеки Winsock

int main() {
    // 1. Инициализация Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;  // Ошибка инициализации
    }

    // 2. Создание сокета
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();  // Освобождение ресурсов Winsock
        return 1;      // Ошибка создания сокета
    }

    // 3. Настройка адреса сервера (локальный хост, порт 12345)
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;                  // IPv4
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP сервера (localhost)
    serverAddr.sin_port = htons(12345);               // Порт сервера (в сетевом порядке байт)

    // 4. Подключение к серверу
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);  // Закрытие сокета при ошибке
        WSACleanup();              // Освобождение ресурсов Winsock
        return 1;                  // Ошибка подключения
    }

    std::cout << "Подключено к серверу. Вводите числа (или 'exit' для выхода).\n";

    char buffer[1024];  // Буфер для приема данных
    int bytesReceived;  // Количество полученных байт

    // 5. Первоначальное сообщение от сервера (например, приветствие)
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // Добавляем нуль-терминатор
        std::cout << buffer;           // Выводим сообщение сервера
    }

    // 6. Основной цикл отправки и получения данных
    while (true) {
        std::string guess;
        std::getline(std::cin, guess);  // Чтение ввода пользователя

        if (guess == "exit") {  // Выход по команде
            break;
        }

        // Отправка данных серверу
        send(clientSocket, guess.c_str(), guess.size(), 0);

        // Получение ответа от сервера
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';  // Добавляем нуль-терминатор
            std::cout << buffer;          // Выводим ответ сервера
        }
        else {
            std::cout << "Соединение с сервером разорвано\n";
            break;
        }
    }

    // 7. Завершение работы
    closesocket(clientSocket);  // Закрытие сокета
    WSACleanup();              // Освобождение ресурсов Winsock
    return 0;
}