#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <random>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")  // �������������� �������� Winsock ����������

// ���������� ���������� ��� ���������� ����� � ���������
std::mutex mtx;                     // ������� ��� ������������� ������� � ����� ������
std::vector<SOCKET> clients;        // ������ ��� �������� ������������ ��������
bool gameRunning = true;            // ���� ��������� ����
int targetNumber = 0;               // ���������� ����� ��� ����������

/**
 * ���������� ����� ��������� ����� �� 1 �� 100 � ��������� ��� � targetNumber
 */
void generateNewNumber() {
    std::random_device rd;          // �������� ��������
    std::mt19937 gen(rd());        // ��������� ��������� �����
    std::uniform_int_distribution<> distr(1, 100);  // ����������� �������������
    targetNumber = distr(gen);      // ��������� �����
    std::cout << "����� ���������� �����: " << targetNumber << std::endl;
}

/**
 * ������������ �������������� � ��������
 * @param clientSocket - ����� ������������� �������
 */
void handleClient(SOCKET clientSocket) {
    char buffer[1024];              // ����� ��� ������ ������
    int bytesReceived;              // ���������� ���������� ����

    // �������� ��������������� ��������� �������
    const char* welcomeMsg = "������� �����:\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    // �������� ���� ��������� �������
    while (gameRunning) {
        // ��������� ������ �� �������
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cout << "������ ���������� ��� ��������� ������\n";
            break;
        }

        buffer[bytesReceived] = '\0';  // ���������� ����-�����������
        std::cout << "�������� �� �������: " << buffer;

        int guess = atoi(buffer);    // �������������� ����� � �����
        std::string response;       // ����� �������

        // �������� ���������� �����
        if (guess < targetNumber) {
            response = "���� ����� ������ �����������. ���������� ���:\n";
        }
        else if (guess > targetNumber) {
            response = "���� ����� ������ �����������. ���������� ���:\n";
        }
        else {
            response = "�����������! �� ������� �����! �������� ����� ����.\n";

            // ����������� ���� �������� � ������ (� ��������������)
            mtx.lock();
            for (SOCKET sock : clients) {
                if (sock != clientSocket) {
                    send(sock, "���-�� ������ �����! �������� ����� ����.\n", 44, 0);
                }
            }
            mtx.unlock();

            generateNewNumber();    // ��������� ������ ����� ��� ����
        }

        // �������� ������ �������
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    // �������� ������� �� ������ (� ��������������)
    mtx.lock();
    auto it = std::find(clients.begin(), clients.end(), clientSocket);
    if (it != clients.end()) {
        clients.erase(it);
    }
    mtx.unlock();

    closesocket(clientSocket);      // �������� ������ �������
    std::cout << "������ ��������. �������� ��������: " << clients.size() << std::endl;
}

int main() {
    // ������������� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "������ ������������� Winsock\n";
        return 1;
    }

    // �������� ���������� ������
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "������ �������� ������\n";
        WSACleanup();
        return 1;
    }

    // ��������� ������ �������
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;           // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;   // ��������� ����������� �� ��� IP
    serverAddr.sin_port = htons(12345);        // ���� 12345

    // �������� ������ � ������
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "������ �������� ������\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // ������ ������������� �����������
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "������ �������������\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "������ �������. �������� ����������� �� ����� 12345...\n";

    generateNewNumber();  // �������������� ��������� �����

    // �������� ���� �������
    while (true) {
        // �������� ������ �����������
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "������ �������� �����������\n";
            continue;
        }

        // ���������� ������� � ������ (� ��������������)
        mtx.lock();
        clients.push_back(clientSocket);
        mtx.unlock();

        // ������ ���������� ������ ��� ��������� �������
        std::thread(handleClient, clientSocket).detach();

        std::cout << "����� �����������. ����� ��������: " << clients.size() << std::endl;
    }

    // �������� ���������� ������ � ������� Winsock (�� �������� ���� �� ������)
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}