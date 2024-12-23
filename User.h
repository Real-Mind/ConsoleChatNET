#pragma once
#include "Header.h"
class User
{
public:
	User() = default;
	User(string& username, string& pass)
		: username(username), pass(pass) {}
	~User() {}

	string getUsername();
	string getPass();

private:
	string username;
	string pass;
};

