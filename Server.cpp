#include "Header.h"
#include "Chat.h"

#define PORT 54000 // ����, �� ������� ����� ������� ������

void handleClient(SOCKET clientSocket, Chat& chat) {
    char buffer[1024];
    int bytesReceived;

    while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytesReceived] = '\0'; // ��������� ������

        // ������������ ���������
        string receivedMessage(buffer);
        cout << "��������� �� �������: " << receivedMessage << endl;
        chat.sendMessage(); // ����� ����� ���������� ���������

        // ��������, ����� ��������� �������
        send(clientSocket, "��������� ��������", 18, 0);
    }
    closesocket(clientSocket);
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientSize = sizeof(clientAddr);

    // ������������� Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    Chat chat; // �������������� ���

    cout << "������ �������. �������� ��������..." << endl;

    while (true) {
        clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        thread(handleClient, clientSocket, ref(chat)).detach(); // ��������� �������� � ��������� ������
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}