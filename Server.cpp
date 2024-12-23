#include "Header.h"
#include "Chat.h"

#define PORT 54000 // Порт, на который будет слушать сервер

void handleClient(SOCKET clientSocket, Chat& chat) {
    char buffer[1024];
    int bytesReceived;

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesReceived] = '\0'; // Завершаем строку

        // Обрабатываем сообщение
        string receivedMessage(buffer);
        cout << "Сообщение от клиента: " << receivedMessage << endl;
        chat.sendMessage(); // Здесь можно доработать обработку

        // Например, можем отправить обратно
        send(clientSocket, "Сообщение получено", 18, 0);
    }
    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientSize = sizeof(clientAddr);

    // Инициализация Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    Chat chat; // Инициализируем чат

    cout << "Сервер запущен. Ожидание клиентов..." << endl;

    while (true) {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        thread(handleClient, clientSocket, ref(chat)).detach(); // Обработка клиентов в отдельном потоке
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}