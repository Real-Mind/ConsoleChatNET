#include "Header.h"
#include "Chat.h"

#define PORT 54000 // ���� �������
#define SERVER "127.0.0.1" // ����� �������

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

    // ����������� � �������
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "�� ������� ������������ � �������!" << endl;
        return 1;
    }

    Chat chat; // �������������� ���

    // ���� ��� �������� ���������
    string message;
    while (true) {
        cout << "������� ��������� ��� �������� (��� 'exit' ��� ������): ";
        getline(cin, message);
        if (message == "exit") break;

        send(sock, message.c_str(), message.size(), 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}