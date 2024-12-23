#include "Chat.h"

Chat::Chat() {
	loadUsers();
	loadMessages();
}

Chat::~Chat() {
	saveMessages();
	saveUsers();
}

void Chat::loadMessages() {
	string recipient, sender, text;
	ifstream file;
	file.open("Messages.txt");
	if (file.is_open()) {
		while (file >> recipient >> sender >> text) {
			messages.push_back(Message(text, sender, recipient));
		}
		file.close();
	}
	else {
		cerr << "Файл не открылся!" << endl;
	}
}

void Chat::saveMessages() {
	string recipient, sender, text;
	ofstream file;
	file.open("Messages.txt");
	if (file.is_open()) {
		for (const Message& message : messages) {
			file << recipient << " " << sender << " " << text << endl;
		}
		file.close();
	}
	else {
		cerr << "Файл сообщений не открылся!" << endl;
	}
}

void Chat::loadUsers() {
	string username, pass;
	ifstream file;
	file.open("Users.txt");
	if (file.is_open()) {
		while (file >> username >> pass) {
			users.push_back(User(username, pass));
		}
		file.close();
	}
	else {
		cerr << "Файл пользователей не открылся" << endl;
	}
}

void Chat::saveUsers() {
	string username, pass;
	ofstream file;
	file.open("Users.txt");
	if (file.is_open()) {
		for (User& user : users) {
			file << user.getUsername() << " " << user.getPass() << endl;
		}
		file.close();
	}
	else {
		cerr << "Не удалось сохранить файл пользователей" << endl;
	}
}

void Chat::showMessagesFromUser() {
	system("cls");
	string username;
	cout << "Введите имя пользователя: ";
	cin >> username;
	for (Message& message : messages) {
		if ((username == message.getSender() && user.getUsername() == message.getRecipient()) ||
			(username == message.getRecipient() && user.getUsername() == message.getSender())) {
			cout << message.getMessage() << endl;
		}
	}
}

void Chat::showAllUsers() {
	system("cls");
	for (User& username : users) {
		cout << username.getUsername() << endl;
	}
}

void Chat::login() {
	system("cls");
	cout << "Вход в аккаунт." << endl;
	string username, pass;
	cout << "Логин: ";
	cin >> username;
	cout << "Пароль: ";
	cin >> pass;
	for (User& user : users) {
		if (user.getUsername() == username && user.getPass() == pass) {
			this->user = user;
			cout << "Вы успешно вошли!" << endl;
			return;
		}
	}
	cout << "Неверные логин или пароль!" << endl;
}

void Chat::registration() {
	system("cls");
	cout << "Регистрация нового пользователя." << endl;
	string username, pass;
	cout << "Логин: ";
	cin >> username;
	cout << "Пароль: ";
	cin >> pass;
	for (User& user : users) {
		if (user.getUsername() == username) {
			cout << "Пользователь с таким логином уже существует!" << endl;
			return;
		}
	}
	cout << "Вы успешно зарегистрировались!" << endl;
}

void Chat::sendMessage() {
	system("cls");
	cout << "Введите имя пользователя для отправки сообщения." << endl;
	string recipient, text;
	cout << "Получатель: ";
	cin >> recipient;
	cin.ignore();
	for (User& user : users) {
		if (user.getUsername() == recipient) {
			cout << "Введите сообщение для отправки: " << endl;
			getline(cin, text);
			messages.push_back(Message(text, this->user.getUsername(), recipient));
			cout << "Сообщение отправлено!" << endl;
			return;
		}
	}
	cout << "Пользователь с таким именем не найден!" << endl;
}

void Chat::receiveMessage(int socket) {
	char buffer[1024];
	int bytesReceived;

	bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);

	if (bytesReceived < 0) {
		std::cerr << "Ошибка при получении сообщения!" << std::endl;
		return;
	}
	buffer[bytesReceived] = '\0';
	std::string message(buffer);
	std::cout << "Новое сообщение: " << message << std::endl;
}