#pragma once
#include "Header.h"
#include "User.h"
#include "Message.h"

class Chat
{
public:
    Chat();
    ~Chat();

    void login();
    void registration();
    void sendMessage();
    void showAllUsers();
    void showMessagesFromUser();
    void receiveMessage(int socket);

private:
    void loadUsers();
    void saveUsers();
    void loadMessages();
    void saveMessages();

    vector<User> users;
    vector<Message> messages;
    User user;
};