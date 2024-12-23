#include "Header.h"
#include "Chat.h"

#define PORT 54000 // Порт сервера
#define SERVER "127.0.0.1" // Адрес сервера

int main() {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in serverAddr;

    // Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER, &serverAddr.sin_addr);

    // Подключение к серверу
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Не удалось подключиться к серверу!" << endl;
        return 1;
    }

    Chat chat; // Инициализируем чат

    // Цикл для отправки сообщений
    string message;
    while (true) {
        cout << "Введите сообщение для отправки (или 'exit' для выхода): ";
        getline(cin, message);
        if (message == "exit") break;

        send(sock, message.c_str(), message.size(), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}