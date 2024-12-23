#pragma once
#include "Header.h"

class Message
{
public:
	Message() = default;
	Message(const string& text, const string& sender, const string& recipient)
		: text(text), sender(sender), recipient(recipient) {}
	~Message() {}
	
	string getMessage() const;
	string getRecipient() const;
	string getSender() const;

private:
	string text;
	string sender;
	string recipient;
};

