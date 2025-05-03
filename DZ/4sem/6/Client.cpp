#include <iostream>
#include <winsock2.h>  // ���������� ��� ������ � �������� � Windows

#pragma comment(lib, "ws2_32.lib")  // �������������� �������� ���������� Winsock

int main() {
    // 1. ������������� Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;  // ������ �������������
    }

    // 2. �������� ������
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();  // ������������ �������� Winsock
        return 1;      // ������ �������� ������
    }

    // 3. ��������� ������ ������� (��������� ����, ���� 12345)
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;                  // IPv4
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP ������� (localhost)
    serverAddr.sin_port = htons(12345);               // ���� ������� (� ������� ������� ����)

    // 4. ����������� � �������
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(clientSocket);  // �������� ������ ��� ������
        WSACleanup();              // ������������ �������� Winsock
        return 1;                  // ������ �����������
    }

    std::cout << "���������� � �������. ������� ����� (��� 'exit' ��� ������).\n";

    char buffer[1024];  // ����� ��� ������ ������
    int bytesReceived;  // ���������� ���������� ����

    // 5. �������������� ��������� �� ������� (��������, �����������)
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';  // ��������� ����-����������
        std::cout << buffer;           // ������� ��������� �������
    }

    // 6. �������� ���� �������� � ��������� ������
    while (true) {
        std::string guess;
        std::getline(std::cin, guess);  // ������ ����� ������������

        if (guess == "exit") {  // ����� �� �������
            break;
        }

        // �������� ������ �������
        send(clientSocket, guess.c_str(), guess.size(), 0);

        // ��������� ������ �� �������
        bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';  // ��������� ����-����������
            std::cout << buffer;          // ������� ����� �������
        }
        else {
            std::cout << "���������� � �������� ���������\n";
            break;
        }
    }

    // 7. ���������� ������
    closesocket(clientSocket);  // �������� ������
    WSACleanup();              // ������������ �������� Winsock
    return 0;
}