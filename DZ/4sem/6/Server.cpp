#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <random>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")  // Автоматическая линковка Winsock библиотеки

// Глобальные переменные для управления игрой и клиентами
std::mutex mtx;                     // Мьютекс для синхронизации доступа к общим данным
std::vector<SOCKET> clients;        // Вектор для хранения подключенных клиентов
bool gameRunning = true;            // Флаг состояния игры
int targetNumber = 0;               // Загаданное число для угадывания

/**
 * Генерирует новое случайное число от 1 до 100 и сохраняет его в targetNumber
 */
void generateNewNumber() {
    std::random_device rd;          // Источник энтропии
    std::mt19937 gen(rd());        // Генератор случайных чисел
    std::uniform_int_distribution<> distr(1, 100);  // Равномерное распределение
    targetNumber = distr(gen);      // Генерация числа
    std::cout << "Новое загаданное число: " << targetNumber << std::endl;
}

/**
 * Обрабатывает взаимодействие с клиентом
 * @param clientSocket - сокет подключенного клиента
 */
void handleClient(SOCKET clientSocket) {
    char buffer[1024];              // Буфер для приема данных
    int bytesReceived;              // Количество полученных байт

    // Отправка приветственного сообщения клиенту
    const char* welcomeMsg = "Введите число:\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    // Основной цикл обработки клиента
    while (gameRunning) {
        // Получение данных от клиента
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cout << "Клиент отключился или произошла ошибка\n";
            break;
        }

        buffer[bytesReceived] = '\0';  // Добавление нуль-терминатора
        std::cout << "Получено от клиента: " << buffer;

        int guess = atoi(buffer);    // Преобразование ввода в число
        std::string response;       // Ответ клиенту

        // Проверка введенного числа
        if (guess < targetNumber) {
            response = "Ваше число меньше загаданного. Попробуйте еще:\n";
        }
        else if (guess > targetNumber) {
            response = "Ваше число больше загаданного. Попробуйте еще:\n";
        }
        else {
            response = "Поздравляем! Вы угадали число! Начинаем новую игру.\n";

            // Уведомление всех клиентов о победе (с синхронизацией)
            mtx.lock();
            for (SOCKET sock : clients) {
                if (sock != clientSocket) {
                    send(sock, "Кто-то угадал число! Начинаем новую игру.\n", 44, 0);
                }
            }
            mtx.unlock();

            generateNewNumber();    // Генерация нового числа для игры
        }

        // Отправка ответа клиенту
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    // Удаление клиента из списка (с синхронизацией)
    mtx.lock();
    auto it = std::find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    mtx.unlock();

    closesocket(clientSocket);      // Закрытие сокета клиента
    std::cout << "Клиент отключен. Осталось клиентов: " << clients.size() << std::endl;
}

int main() {
    // Инициализация Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Ошибка инициализации Winsock\n";
        return 1;
    }

    // Создание серверного сокета
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка создания сокета\n";
        WSACleanup();
        return 1;
    }

    // Настройка адреса сервера
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;           // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;   // Принимать подключения на все IP
    serverAddr.sin_port = htons(12345);        // Порт 12345

    // Привязка сокета к адресу
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка привязки сокета\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Начало прослушивания подключений
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Ошибка прослушивания\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Сервер запущен. Ожидание подключений на порту 12345...\n";

    generateNewNumber();  // Первоначальная генерация числа

    // Основной цикл сервера
    while (true) {
        // Принятие нового подключения
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка принятия подключения\n";
            continue;
        }

        // Добавление клиента в список (с синхронизацией)
        mtx.lock();
        clients.push_back(clientSocket);
        mtx.unlock();

        // Запуск отдельного потока для обработки клиента
        std::thread(handleClient, clientSocket).detach();

        std::cout << "Новое подключение. Всего клиентов: " << clients.size() << std::endl;
    }

    // Закрытие серверного сокета и очистка Winsock (на практике сюда не дойдет)
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}